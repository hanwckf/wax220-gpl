#!/bin/bash
source ./autobuild/lede-build-sanity.sh

#get the brach_name
temp=${0%/*}
branch_name=${temp##*/}

rm -rf ${BUILD_DIR}/package/network/services/hostapd
cp -fpR ${BUILD_DIR}/./../mac80211_package/package/network/services/hostapd ${BUILD_DIR}/package/network/services

rm -rf ${BUILD_DIR}/package/libs/libnl-tiny
cp -fpR ${BUILD_DIR}/./../mac80211_package/package/libs/libnl-tiny ${BUILD_DIR}/package/libs

rm -rf ${BUILD_DIR}/package/network/utils/iw
cp -fpR ${BUILD_DIR}/./../mac80211_package/package/network/utils/iw ${BUILD_DIR}/package/network/utils

rm -rf ${BUILD_DIR}/package/network/utils/iwinfo
cp -fpR ${BUILD_DIR}/./../mac80211_package/package/network/utils/iwinfo ${BUILD_DIR}/package/network/utils

rm -rf ${BUILD_DIR}/package/kernel/mac80211
cp -fpR ${BUILD_DIR}/./../mac80211_package/package/kernel/mac80211 ${BUILD_DIR}/package/kernel

#use hostapd master package revision, remove hostapd 2102 patches
find ../mtk-openwrt-feeds/openwrt_patches-21.02 -name "*-2102-hostapd-*.patch" -delete

#use mt76 lastest commit, remove mt76 master patches
find ../mtk-openwrt-feeds/openwrt_patches-21.02 -name "*-master-mt76-*.patch" -delete

#step1 clean
#clean

#do prepare stuff
prepare

#hack mt7986 config5.4
echo "CONFIG_NETFILTER=y" >> ./target/linux/mediatek/mt7986/config-5.4
echo "CONFIG_NETFILTER_ADVANCED=y" >> ./target/linux/mediatek/mt7986/config-5.4
echo "CONFIG_RELAY=y" >> ./target/linux/mediatek/mt7986/config-5.4

#hack mt7986 hostapd config
echo "CONFIG_MBO=y" >> ./package/network/services/hostapd/files/hostapd-full.config
echo "CONFIG_WPS_UPNP=y"  >> ./package/network/services/hostapd/files/hostapd-full.config

#hack mt76 firmware/eeprom
#===================firmware bin name format=========================
#define MT7902_FIRMWARE_WA		"mediatek/mt7902_wa.bin"
#define MT7902_FIRMWARE_WM		"mediatek/mt7902_wm.bin"
#define MT7902_ROM_PATCH		"mediatek/mt7902_rom_patch.bin"
#define MT7902_FIRMWARE_ROM		"mediatek/mt7902_wf_rom.bin"
#define MT7902_FIRMWARE_ROM_SRAM	"mediatek/mt7902_wf_rom_sram.bin"

FW_SOURCE_DIR=${BUILD_DIR}/package/kernel/mt76
cp -rf ${FW_SOURCE_DIR}/firmware/mt7902/rebb/WIFI_RAM_CODE_bellwether.bin ${FW_SOURCE_DIR}/src/firmware/mt7902_wm.bin
cp -rf ${FW_SOURCE_DIR}/firmware/mt7902/rebb/bellwether_WACPU_RAM_CODE_release.bin ${FW_SOURCE_DIR}/src/firmware/mt7902_wa.bin
cp -rf ${FW_SOURCE_DIR}/firmware/mt7902/rebb/BELLWETHER_patch_e2_hdr.bin ${FW_SOURCE_DIR}/src/firmware/mt7902_rom_patch.bin
cp -rf ${FW_SOURCE_DIR}/firmware/mt7902/rebb/wf_rom.bin ${FW_SOURCE_DIR}/src/firmware/mt7902_wf_rom.bin
cp -rf ${FW_SOURCE_DIR}/firmware/mt7902/rebb/wf_rom_sram.bin ${FW_SOURCE_DIR}/src/firmware/mt7902_wf_rom_sram.bin

#===================eeprom bin name format=========================
#define MT7902_EEPROM_DEFAULT		"mediatek/mt7902_eeprom.bin"
cp -rf ${FW_SOURCE_DIR}/firmware/mt7902/rebb/BELLWETHER_EEPROM.bin ${FW_SOURCE_DIR}/src/firmware/mt7902_eeprom.bin

prepare_final ${branch_name}
cp -fpR ${BUILD_DIR}/autobuild/mt7986-mac80211/target/linux/mediatek/patches-5.4 ${BUILD_DIR}/target/linux/mediatek
patch -f -p1 -i ../mtk-openwrt-feeds/autobuild_mac80211_release/0001-master-mac80211-generate-hostapd-setting-from-ap-cap.patch
patch -f -p1 -i ../mtk-openwrt-feeds/autobuild_mac80211_release/0002-master-hostapd-makefile-for-utils.patch
#step2 build
if [ -z ${1} ]; then
	build ${branch_name} -j1 || [ "$LOCAL" != "1" ]
fi
