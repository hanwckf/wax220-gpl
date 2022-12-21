#
# Copyright (C) 2008-2014 The LuCI Team <luci@lists.subsignal.org>
#
# This is free software, licensed under the Apache License, Version 2.0 .
#

include $(TOPDIR)/rules.mk

LUCI_TITLE:=NIXIO POSIX library
LUCI_DEPENDS:=+PACKAGE_luci-lib-nixio_openssl:libopenssl +PACKAGE_luci-lib-nixio_cyassl:libcyassl +liblua

LUCI_MK_PATH_OLD:=$(shell test -e ../luci.mk && echo "old")
LUCI_MK_PATH_FEEDS:=$(shell test -e $(TOPDIR)/feeds/luci/luci.mk && echo "feeds")
ifeq ($(LUCI_MK_PATH_OLD),old)
include ../luci.mk
else ifeq ($(LUCI_MK_PATH_FEEDS),feeds)
include $(TOPDIR)/feeds/luci/luci.mk
else
include $(TOPDIR)/package/luci/luci.mk
endif

# call BuildPackage - OpenWrt buildroot signature
