#
# Copyright (C) 2011-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=ar-tool
PKG_VERSION:=1

include $(INCLUDE_DIR)/host-build.mk

define Host/Prepare
	mkdir -p $(HOST_BUILD_DIR)
	$(CP) ./src/* $(HOST_BUILD_DIR)/
endef

define Host/Compile
	$(MAKE) -C $(HOST_BUILD_DIR)
endef

define Host/Configure
endef

define Host/Install
	$(CP) $(HOST_BUILD_DIR)/ar-tool $(STAGING_DIR_HOST)/bin/
endef

define Host/Clean
	rm -f $(HOST_BUILD_DIR)/ar-tool
	rm -f $(STAGING_DIR_HOST)/bin/ar-tool
endef

$(eval $(call HostBuild))
