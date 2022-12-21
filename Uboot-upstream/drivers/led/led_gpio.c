// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2015 Google, Inc
 * Written by Simon Glass <sjg@chromium.org>
 */

#include <common.h>
#include <dm.h>
#include <errno.h>
#include <led.h>
#include <log.h>
#include <malloc.h>
#include <asm/gpio.h>
#include <dm/lists.h>
#include <time.h>

struct led_gpio_priv {
	struct gpio_desc gpio;
#ifdef CONFIG_LED_BLINK
  int period_ms;
  int passed_ms;
#endif
};

static int gpio_led_set_state(struct udevice *dev, enum led_state_t state)
{
	struct led_gpio_priv *priv = dev_get_priv(dev);
	int ret;

	if (!dm_gpio_is_valid(&priv->gpio))
		return -EREMOTEIO;
	switch (state) {
	case LEDST_OFF:
	case LEDST_ON:
#ifdef CONFIG_LED_BLINK
    priv->period_ms = 0;
#endif
		break;
	case LEDST_TOGGLE:
		ret = dm_gpio_get_value(&priv->gpio);
		if (ret < 0)
			return ret;
		state = !ret;
#ifdef CONFIG_LED_BLINK
    priv->period_ms = 0;
#endif
		break;
#ifdef CONFIG_LED_BLINK
	case LEDST_BLINK:
		return 0;
#endif
default:
		return -ENOSYS;
	}

	return dm_gpio_set_value(&priv->gpio, state);
}

static enum led_state_t gpio_led_get_state(struct udevice *dev)
{
	struct led_gpio_priv *priv = dev_get_priv(dev);
	int ret;

	if (!dm_gpio_is_valid(&priv->gpio))
		return -EREMOTEIO;
	ret = dm_gpio_get_value(&priv->gpio);
	if (ret < 0)
		return ret;

	return ret ? LEDST_ON : LEDST_OFF;
}

#ifdef CONFIG_LED_BLINK
void gpio_led_tick(ulong tick_ms)
{
	int ret;
  struct udevice *dev;
  struct led_gpio_priv *priv;
  static ulong s_latest_tick_ms;

  ret = uclass_first_device(UCLASS_LED, &dev);
  if (ret)
    return;

  for (ret = uclass_next_device(&dev);
       dev;
       ret = uclass_next_device(&dev)) {
    priv = dev_get_priv(dev);
    if (priv->period_ms > 0) {
      if (time_after(tick_ms, s_latest_tick_ms))
        priv->passed_ms += (tick_ms - s_latest_tick_ms);

      if (priv->passed_ms < priv->period_ms) {
        gpio_led_set_state(dev, LEDST_OFF);
      } else if (priv->passed_ms < (priv->period_ms * 4 / 3)) {
        gpio_led_set_state(dev, LEDST_ON);
      } else {
        gpio_led_set_state(dev, LEDST_OFF);
        priv->passed_ms -= (priv->period_ms * 4 / 3);
      }
    }
  }

  s_latest_tick_ms = tick_ms;
}

static int gpio_led_set_period(struct udevice *dev, int period_ms)
{
  struct led_gpio_priv *priv = dev_get_priv(dev);

  if (period_ms <= 0)
    return -EREMOTEIO;

  priv->period_ms = period_ms;
  priv->passed_ms = 0;

  return 0;
}
#endif

static int led_gpio_probe(struct udevice *dev)
{
	struct led_uc_plat *uc_plat = dev_get_uclass_plat(dev);
	struct led_gpio_priv *priv = dev_get_priv(dev);
	int ret;

	/* Ignore the top-level LED node */
	if (!uc_plat->label)
		return 0;

	ret = gpio_request_by_name(dev, "gpios", 0, &priv->gpio, GPIOD_IS_OUT);
	if (ret)
		return ret;

	return 0;
}

static int led_gpio_remove(struct udevice *dev)
{
	/*
	 * The GPIO driver may have already been removed. We will need to
	 * address this more generally.
	 */
#ifndef CONFIG_SANDBOX
	struct led_gpio_priv *priv = dev_get_priv(dev);

	if (dm_gpio_is_valid(&priv->gpio))
		dm_gpio_free(dev, &priv->gpio);
#endif

	return 0;
}

static int led_gpio_bind(struct udevice *parent)
{
	struct udevice *dev;
	ofnode node;
	int ret;

	dev_for_each_subnode(node, parent) {
		struct led_uc_plat *uc_plat;
		const char *label;

		label = ofnode_read_string(node, "label");
		if (!label)
			label = ofnode_get_name(node);
		ret = device_bind_driver_to_node(parent, "gpio_led",
						 ofnode_get_name(node),
						 node, &dev);
		if (ret)
			return ret;
		uc_plat = dev_get_uclass_plat(dev);
		uc_plat->label = label;
	}

	return 0;
}

static const struct led_ops gpio_led_ops = {
	.set_state	= gpio_led_set_state,
	.get_state	= gpio_led_get_state,
#ifdef CONFIG_LED_BLINK
	.set_period = gpio_led_set_period,
#endif
};

static const struct udevice_id led_gpio_ids[] = {
	{ .compatible = "gpio-leds" },
	{ }
};

U_BOOT_DRIVER(led_gpio) = {
	.name	= "gpio_led",
	.id	= UCLASS_LED,
	.of_match = led_gpio_ids,
	.ops	= &gpio_led_ops,
	.priv_auto	= sizeof(struct led_gpio_priv),
	.bind	= led_gpio_bind,
	.probe	= led_gpio_probe,
	.remove	= led_gpio_remove,
};
