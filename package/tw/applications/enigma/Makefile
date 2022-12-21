include $(TOPDIR)/rules.mk

PKG_NAME:=enigma
PKG_VERSION:=20201204

include $(INCLUDE_DIR)/package.mk

define Package/enigma
  SECTION:=TW Properties
  CATEGORY:=TW Properties
  SUBMENU:=Applications
  TITLE:= cipher machine
  DEPENDS:=+fwk +dai
endef

define Package/enigma/description
	This is only executable by root. Encrypts or decrypts or confuse of content to output to standard output
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
	[ ./files/enigma ] && $(CP) ./files/enigma $(PKG_BUILD_DIR)
endef

define Package/enigma/install
	tar -zxvf files/data.tar.gz -C $(1)/
endef

$(eval $(call BuildPackage,enigma))
