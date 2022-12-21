#
# hua.shao@mediatek.com
#
# MTK Property Software.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=sigma_dut
PKG_REVISION:=236e7ac2
PKG_SOURCE:=$(PKG_NAME)-$(PKG_REVISION).tar.bz2
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)
PKG_KCONFIG:=RALINK_MT7620 RALINK_MT7621 RALINK_MT7628
PKG_CONFIG_DEPENDS:=$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),CONFIG_$(c)))


include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

define Package/sigma_dut
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  TITLE:=SIGMA_DUT(WFA SIGMA DUT)
  SUBMENU:=Applications
  DEPENDS:= +libpthread +librt
endef

define Package/sigma_dut/description
  SIGMA_DUT
endef



TARGET_CFLAGS += \
	$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),-DCONFIG_$(c)=$(CONFIG_$c)))

#MAKE_FLAGS += \
	CFLAGS="$(TARGET_CFLAGS)"

define Package/sigma_dut/install
	$(INSTALL_DIR) $(1)/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/dut/wfa_dut $(1)/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ca/wfa_ca $(1)/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/scripts/arp_neigh_loop $(1)/sbin/arp_neigh_loop
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/scripts/getipconfig.sh $(1)/sbin/getipconfig.sh
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/scripts/getpid.sh $(1)/sbin/getpid.sh
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/scripts/getpstats.sh $(1)/sbin/getpstats.sh
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/scripts/gpstats.sh $(1)/sbin/gpstats.sh
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/scripts/stoping.sh $(1)/sbin/stoping.sh
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/scripts/updatepid.sh $(1)/sbin/updatepid.sh
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/scripts/wfaping6.sh $(1)/sbin/wfaping6.sh
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/scripts/wfaping.sh $(1)/sbin/wfaping.sh
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/scripts/wfa_test_cli.sh $(1)/sbin/wfa_test_cli.sh
	$(INSTALL_BIN) ./files/sigma $(1)/sbin/sigma
	$(INSTALL_DIR) $(1)/etc/init.d
#	$(INSTALL_BIN) ./files/wfa_dut $(1)/etc/init.d/wfa_dut
#	$(INSTALL_BIN) ./files/sigma $(1)/etc/init.d/sigma
	$(INSTALL_DIR) $(1)/etc/config/
	$(INSTALL_DIR) $(1)/etc/config/wirelessCfg
	$(INSTALL_DIR) $(1)/etc/config/wirelessCfg/sigma_test
	$(INSTALL_BIN) ./files/wifi_cert_b0.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert_b0.dat
	$(INSTALL_BIN) ./files/wifi_cert_b1.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert_b1.dat
	$(INSTALL_BIN) ./files/wifi_cert.1.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert.1.dat
	$(INSTALL_BIN) ./files/wifi_cert.2.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert.2.dat
	if [ "$$(CONFIG_first_card_name)" = "MT7603" -a "$$(CONFIG_second_card_name)" = "MT7663" ] ; then \
		$(INSTALL_BIN) ./files/wifi_cert_7603.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert.1.dat; \
		$(INSTALL_BIN) ./files/wifi_cert_7663.2.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert.2.dat; \
		$(INSTALL_BIN) ./files/wifi_cert_7603.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert_b0.dat; \
		$(INSTALL_BIN) ./files/wifi_cert_7663.2.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert_b1.dat; \
	fi
	if [ "$$(CONFIG_first_card_name)" = "MT7663" -a "$$(CONFIG_second_card_name)" = "MT7663" ] ; then \
		$(INSTALL_BIN) ./files/wifi_cert_7663.1.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert.1.dat; \
		$(INSTALL_BIN) ./files/wifi_cert_7663.2.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert.2.dat; \
		$(INSTALL_BIN) ./files/wifi_cert_7663.1.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert_b0.dat; \
		$(INSTALL_BIN) ./files/wifi_cert_7663.2.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert_b1.dat; \
	fi
	if [ "$$(CONFIG_first_card_name)" = "MT7615" -a "$$(CONFIG_second_card_name)" = "MT7615" ] ; then \
		$(INSTALL_BIN) ./files/wifi_cert_7615e.1.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert.1.dat; \
		$(INSTALL_BIN) ./files/wifi_cert_7615e.2.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert.2.dat; \
		$(INSTALL_BIN) ./files/wifi_cert_7615e.1.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert_b0.dat; \
		$(INSTALL_BIN) ./files/wifi_cert_7615e.2.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert_b1.dat; \
	fi
	if [ "$$(CONFIG_first_card_name)" = "MT7986" -a "$$(CONFIG_MTK_WIFI_SKU_TYPE)" = "AX4200" ] ; then \
		$(INSTALL_BIN) ./files/wifi_cert_mt7986_ax4200_b0.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert_b0.dat; \
		$(INSTALL_BIN) ./files/wifi_cert_mt7986_ax4200_b1.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert_b1.dat; \
	fi
	if [ "$$(CONFIG_first_card_name)" = "MT7986" -a "$$(CONFIG_MTK_WIFI_SKU_TYPE)" = "AX6000" ] ; then \
		$(INSTALL_BIN) ./files/wifi_cert_mt7986_ax6000_b0.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert_b0.dat; \
		$(INSTALL_BIN) ./files/wifi_cert_mt7986_ax6000_b1.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert_b1.dat; \
	fi
	if [ "$$(CONFIG_first_card_name)" = "MT7986" -a "$$(CONFIG_MTK_WIFI_SKU_TYPE)" = "AX8400" ] ; then \
		$(INSTALL_BIN) ./files/wifi_cert_mt7986_ax8400_b0.1.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert_b0.dat; \
		$(INSTALL_BIN) ./files/wifi_cert_mt7986_ax8400_b1.1.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert_b1.dat; \
		$(INSTALL_BIN) ./files/wifi_cert_mt7986_ax8400_5g.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert_b2.dat; \
	fi
	if [ "$$(CONFIG_first_card_name)" = "MT7916" ] ; then \
		$(INSTALL_BIN) ./files/wifi_cert_mt7916_b0.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert_b0.dat; \
		$(INSTALL_BIN) ./files/wifi_cert_mt7916_b1.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert_b1.dat; \
	fi
	if [ "$$(CONFIG_first_card_name)" = "MT7981" ] ; then \
		$(INSTALL_BIN) ./files/wifi_cert_mt7981_b0.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert_b0.dat; \
		$(INSTALL_BIN) ./files/wifi_cert_mt7981_b1.dat $(1)/etc/config/wirelessCfg/sigma_test/wifi_cert_b1.dat; \
	fi
	$(INSTALL_DIR) $(1)/etc/WfaEndpoint
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/wfa_cli.txt $(1)/etc/WfaEndpoint/wfa_cli.txt

endef

$(eval $(call BuildPackage,sigma_dut))

