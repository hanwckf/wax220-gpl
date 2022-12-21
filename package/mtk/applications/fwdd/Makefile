#
# jie.shen@mediatek.com
#
# MTK Property Software.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=fwdd
PKG_REVISION:=fefee635
PKG_SOURCE:=$(PKG_NAME)-$(PKG_REVISION).tar.bz2
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

#TARGET_CFLAGS += -DCONFIG_SUPPORT_OPENWRT
#MAKE_FLAGS += CONFIG_SUPPORT_OPENWRT=y

define Package/fwdd
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  TITLE:=Forward daemon
  DEPENDS:=+dai
  SUBMENU:=Applications
endef

define Package/fwdd/description
  forward daemon
endef


define Package/fwdd/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/etc/init.d/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/fwdd $(1)/usr/bin
	$(INSTALL_BIN) ./files/fwdd.init $(1)/etc/init.d/fwdd
endef


$(eval $(call BuildPackage,fwdd))
