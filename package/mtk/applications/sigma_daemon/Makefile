#
# yanfang.liu@mediatek.com
#
# MTK Property Software.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=sigma_daemon
PKG_REVISION:=07b9f71e
PKG_SOURCE:=$(PKG_NAME)-$(PKG_REVISION).tar.bz2
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)
PKG_KCONFIG:=RALINK_MT7620 RALINK_MT7621 RALINK_MT7628
PKG_CONFIG_DEPENDS:=$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),CONFIG_$(c)))


include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

define Package/sigma_daemon
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  TITLE:=SIGMA_DAEMON(WFA SIGMA DAEMON)
  SUBMENU:=Applications
  DEPENDS:= +libpthread +librt
endef

define Package/sigma_daemon/description
  SIGMA_DAEMON
endef

define Package/sigma_daemon/config
	if PACKAGE_sigma_daemon
		config SIGMA_DAEMON_AUTOSTART
			bool "Enable Sigma Daemon Autostart"
			default n
	endif
endef



TARGET_CFLAGS += \
	$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),-DCONFIG_$(c)=$(CONFIG_$c)))

#MAKE_FLAGS += \
	CFLAGS="$(TARGET_CFLAGS)"

define Package/sigma_daemon/install
	$(INSTALL_DIR) $(1)/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/dut/mtk_dut $(1)/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/dut/mtk_dut_start.sh $(1)/sbin
	$(INSTALL_BIN) ./files/mtk_dut_jedi_hostapd_start.sh $(1)/sbin
#	$(INSTALL_BIN) $(PKG_BUILD_DIR)/scripts/arp_neigh_loop $(1)/sbin/arp_neigh_loop
#	$(INSTALL_BIN) $(PKG_BUILD_DIR)/scripts/getipconfig.sh $(1)/sbin/getipconfig.sh
#	$(INSTALL_BIN) $(PKG_BUILD_DIR)/scripts/getpid.sh $(1)/sbin/getpid.sh
#	$(INSTALL_BIN) $(PKG_BUILD_DIR)/scripts/getpstats.sh $(1)/sbin/getpstats.sh
#	$(INSTALL_BIN) $(PKG_BUILD_DIR)/scripts/gpstats.sh $(1)/sbin/gpstats.sh
#	$(INSTALL_BIN) $(PKG_BUILD_DIR)/scripts/stoping.sh $(1)/sbin/stoping.sh
#	$(INSTALL_BIN) $(PKG_BUILD_DIR)/scripts/updatepid.sh $(1)/sbin/updatepid.sh
#	$(INSTALL_BIN) $(PKG_BUILD_DIR)/scripts/wfaping6.sh $(1)/sbin/wfaping6.sh
#	$(INSTALL_BIN) $(PKG_BUILD_DIR)/scripts/wfaping.sh $(1)/sbin/wfaping.sh
#	$(INSTALL_BIN) $(PKG_BUILD_DIR)/scripts/wfa_test_cli.sh $(1)/sbin/wfa_test_cli.sh
	if [ "$$(CONFIG_SIGMA_DAEMON_AUTOSTART)" != "" ]; then \
		$(INSTALL_DIR) $(1)/etc/init.d; \
		$(INSTALL_BIN) ./files/mtk_dut $(1)/etc/init.d/mtk_dut; \
	fi
#	$(INSTALL_BIN) ./files/sigma $(1)/etc/init.d/sigma
#	$(INSTALL_DIR) $(1)/etc/wireless/sigma_test
#	$(INSTALL_BIN) ./files/wifi_cert_b0.dat $(1)/etc/wireless/sigma_test/wifi_cert_b0.dat
#	$(INSTALL_BIN) ./files/wifi_cert_b1.dat $(1)/etc/wireless/sigma_test/wifi_cert_b1.dat
#	$(INSTALL_DIR) $(1)/etc/WfaEndpoint
#	$(INSTALL_BIN) $(PKG_BUILD_DIR)/wfa_cli.txt $(1)/etc/WfaEndpoint/wfa_cli.txt

endef

$(eval $(call BuildPackage,sigma_daemon))

