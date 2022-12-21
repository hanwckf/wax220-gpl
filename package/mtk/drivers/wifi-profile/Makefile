#
# Copyright (C) 2016 MediaTek
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/version.mk

PKG_NAME:=wifi-profile
PKG_RELEASE:=1
PKG_BUILD_DEPENDS:=
PKG_FILE_DEPENDS:=
PKG_LICENSE:=GPL-2.0

include $(INCLUDE_DIR)/package.mk

define Package/wifi-profile
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  SUBMENU:=Drivers
  DEPENDS:=
  TITLE:=Build WiFi l1profile.data on demand & install wifi l2 profile.
  VERSION:=$(PKG_RELEASE)-$(REVISION)
  MENU:=1
endef

define Package/wifi-profile/description
  This package helps to build l1profile on demand & install wifi l2 profile.
endef

define Package/wifi-profile/config
	if PACKAGE_wifi-profile
	source "$(SOURCE)/l1profile.config.in"
	endif
endef


CFG_PREFIX:=CONFIG_MTK_WLAN
define Build/Compile
	rm -rf $(PKG_BUILD_DIR)
	mkdir -p $(PKG_BUILD_DIR)
	python ./make-l1profile.py $(TOPDIR)/.config /dev/null
	if [ "$$(CONFIG_PACKAGE_kmod-unified_wlan)" = "y" ] ; then \
		grep "$(CFG_PREFIX)" $(TOPDIR)/.config > $(PKG_BUILD_DIR)/wlan_kconfig; \
		sed -i '/# $(CFG_PREFIX)/d' $(PKG_BUILD_DIR)/wlan_kconfig; \
		sed -i -e 's/=.*//g' $(PKG_BUILD_DIR)/wlan_kconfig; \
		sed -i -e 's/$(CFG_PREFIX)_//g' $(PKG_BUILD_DIR)/wlan_kconfig; \
	fi
endef

define Package/wifi-profile/install
	rm -rf $(1)/../etc/wireless
	$(INSTALL_DIR) $(1)/etc/config/
	$(INSTALL_DIR) $(1)/etc/config/wirelessCfg
	#$(INSTALL_DIR) $(1)/etc/wireless/
	cd $(1)/etc; ln -s  ./config/wirelessCfg  wireless
	python ./make-l1profile.py $(TOPDIR)/.config $(1)/etc/wireless/l1profile.dat > /dev/null

	$(INSTALL_DIR) $(1)/etc/init.d/
	$(INSTALL_DIR) $(1)/lib/wifi/
	$(INSTALL_DIR) $(1)/etc/wireless/mediatek/
	$(INSTALL_DIR) $(1)/sbin/
	$(INSTALL_BIN) ./files/common/wifi_jedi $(1)/sbin/wifi
	echo $(PKG_VERSION) > $(1)/etc/wireless/mediatek/version
	$(INSTALL_BIN) ./files/common/mtwifi.lua $(1)/lib/wifi/
	$(INSTALL_BIN) ./files/common/wifi_services.lua $(1)/lib/wifi/
	$(INSTALL_BIN) ./files/common/firmware.sh $(1)/etc/init.d/
	#if [ "$$(CONFIG_WIFI_QUICK_SETTING)" = "y" ] ; then \
	#	$(INSTALL_BIN) ./files/common/quick_setting.lua $(1)/lib/wifi/; \
	#fi




	# Example combination mt7622 + mt7615e/a + mt7615e/a.
	if [ "$$(CONFIG_first_card_name)" = "MT7622" ] ; then \
		$(INSTALL_BIN) ./files/mt7622.1.dat $(1)/etc/wireless/mediatek/; \
		if [ "$$(CONFIG_MTK_MAP_SUPPORT)" = "y"  ] ; then \
			$(INSTALL_BIN) ./files/mt7622_map.1.dat $(1)/etc/wireless/mediatek/mt7622.1.dat; \
		fi; \
		if [ "$$(CONFIG_second_card_name)" = "MT7615" ] ; then \
			$(INSTALL_BIN) ./files/mt7615e.1.dat $(1)/etc/wireless/mediatek/; \
			if [ "$$(CONFIG_MTK_MAP_SUPPORT)" = "y"  ] ; then \
				$(INSTALL_BIN) ./files/mt7615e_map.1.dat $(1)/etc/wireless/mediatek/mt7615e.1.dat; \
			fi; \
			$(INSTALL_BIN) ./files/mt7615a.b0.5g.dat $(1)/etc/wireless/mediatek/mt7615a.1.b0.5g.dat; \
			$(INSTALL_BIN) ./files/mt7615a.b1.5g.dat $(1)/etc/wireless/mediatek/mt7615a.1.b1.5g.dat; \
		fi; \
		if [ "$$(CONFIG_third_card_name)" = "MT7615" ] ; then \
			$(INSTALL_BIN) ./files/mt7615e.2.dat $(1)/etc/wireless/mediatek/; \
			if [ "$$(CONFIG_MTK_MAP_SUPPORT)" = "y"  ] ; then \
				$(INSTALL_BIN) ./files/mt7615e_map.2.dat $(1)/etc/wireless/mediatek/mt7615e.2.dat; \
			fi; \
			$(INSTALL_BIN) ./files/mt7615a.b0.5g.dat $(1)/etc/wireless/mediatek/mt7615a.2.b0.5g.dat; \
			$(INSTALL_BIN) ./files/mt7615a.b1.5g.dat $(1)/etc/wireless/mediatek/mt7615a.2.b1.5g.dat; \
		fi; \
		$(INSTALL_BIN) ./files/mt7615e*.bin $(1)/etc/wireless/mediatek/; \
	fi

	# Example combination mt7623 + mt7615e/a + mt7615e/a.
	if [ "$$(CONFIG_first_card_name)" = "MT7615" ] ; then \
		$(INSTALL_BIN) ./files/mt7615e.1.dat $(1)/etc/wireless/mediatek/; \
		$(INSTALL_BIN) ./files/mt7615a.b0.5g.dat $(1)/etc/wireless/mediatek/mt7615a.1.b0.5g.dat; \
		$(INSTALL_BIN) ./files/mt7615a.b1.5g.dat $(1)/etc/wireless/mediatek/mt7615a.1.b1.5g.dat; \
		if [ "$$(CONFIG_second_card_name)" = "MT7615" ] ; then \
			$(INSTALL_BIN) ./files/mt7615e.2.dat $(1)/etc/wireless/mediatek/; \
			$(INSTALL_BIN) ./files/mt7615a.b0.5g.dat $(1)/etc/wireless/mediatek/mt7615a.2.b0.5g.dat; \
			$(INSTALL_BIN) ./files/mt7615a.b1.5g.dat $(1)/etc/wireless/mediatek/mt7615a.2.b1.5g.dat; \
		fi; \
		$(INSTALL_BIN) ./files/mt7615e*.bin $(1)/etc/wireless/mediatek/; \
	fi

	# Example combination mt7622 + axe.
	if [ "$$(CONFIG_first_card_name)" = "AXE" ] ; then \
		$(INSTALL_BIN) ./files/axe.1.dat $(1)/etc/wireless/mediatek/; \
	fi

	# Example combination mt7622 + harrier.
	if [ "$$(CONFIG_first_card_name)" = "MT7915" -o "$$(CONFIG_second_card_name)" = "MT7915" \
		-o "$$(CONFIG_third_card_name)" = "MT7915" ] ; then \
		$(INSTALL_BIN) ./files/mt7915/mt7915.*.dat $(1)/etc/wireless/mediatek/; \
		$(INSTALL_BIN) ./files/mt7915/wifi_cert.*.dat $(1)/etc/wireless/mediatek/; \
	fi

	# Example combination mt7622 + Panther.
	if [ "$$(CONFIG_first_card_name)" = "MT7986" -o "$$(CONFIG_second_card_name)" = "MT7986" ] ; then \
		$(INSTALL_BIN) ./files/mt7986/* $(1)/etc/wireless/mediatek/; \
	fi

	# Example combination mt7622 + Merlin.
	if [ "$$(CONFIG_first_card_name)" = "MT7916" -o "$$(CONFIG_second_card_name)" = "MT7916" ] ; then \
		$(INSTALL_BIN) ./files/mt7916/* $(1)/etc/wireless/mediatek/; \
	fi

	# Example combination mt7622 + Cheetah.
	if [ "$$(CONFIG_first_card_name)" = "MT7981" -o "$$(CONFIG_second_card_name)" = "MT7981" ] ; then \
		$(INSTALL_BIN) ./files/mt7981/* $(1)/etc/wireless/mediatek/; \
	fi

	# Example combination mt7622 + bellwether.
	if [ "$$(CONFIG_first_card_name)" = "Bellwether" -o "$$(CONFIG_second_card_name)" = "Bellwether" ] ; then \
		$(INSTALL_BIN) ./files/bellwether/* $(1)/etc/wireless/mediatek/; \
	fi

	# Example combination mt7622 + Eagle.
	if [ "$$(CONFIG_first_card_name)" = "MT7990" -o "$$(CONFIG_second_card_name)" = "MT7990" ] ; then \
		$(INSTALL_BIN) ./files/mt7990/* $(1)/etc/wireless/mediatek/; \
	fi

	# Example mt7902
	if [ "$$(CONFIG_first_card_name)" = "MT7902" -o "$$(CONFIG_second_card_name)" = "MT7902" ] ; then \
		 $(INSTALL_BIN) ./files/bellwether/* $(1)/etc/wireless/mediatek/; \
	fi

	# Example mt7615D
	if [ "$$(CONFIG_first_card_name)" = "MT7615D" -o "$$(CONFIG_second_card_name)" = "MT7615D" ] ; then \
		$(INSTALL_BIN) ./files/mt7615D/*.* $(1)/etc/wireless/mediatek/; \
	fi

	if [ "$$(CONFIG_PACKAGE_hostapd-common)" != "y" -a "$$(CONFIG_PACKAGE_kmod-unified_wlan)" != "y" ] ; then \
		$(INSTALL_DIR) $(1)/etc/rc.button; \
		$(INSTALL_BIN) ./files/common/wps-hotplug.sh $(1)/etc/rc.button/wps; \
	fi
endef

$(eval $(call BuildPackage,wifi-profile))
