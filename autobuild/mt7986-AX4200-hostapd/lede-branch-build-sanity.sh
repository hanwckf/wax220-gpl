#!/bin/bash
source ./autobuild/lede-build-sanity.sh

#get the brach_name
temp=${0%/*}
branch_name=${temp##*/}
#step1 clean
#clean

#do prepare stuff
prepare

echo "CONFIG_CFG80211=y" >> ./target/linux/mediatek/mt7986/config-5.4
echo "CONFIG_NL80211_TESTMODE=y" >> ./target/linux/mediatek/mt7986/config-5.4
echo "# CONFIG_CFG80211_CERTIFICATION_ONUS is not set" >> ./target/linux/mediatek/mt7986/config-5.4
echo "CONFIG_CFG80211_CRDA_SUPPORT=y" >> ./target/linux/mediatek/mt7986/config-5.4
echo "# CONFIG_CFG80211_DEBUGFS is not set" >> ./target/linux/mediatek/mt7986/config-5.4
echo "CONFIG_CFG80211_DEFAULT_PS=y" >> ./target/linux/mediatek/mt7986/config-5.4
echo "# CONFIG_CFG80211_DEVELOPER_WARNINGS is not set" >> ./target/linux/mediatek/mt7986/config-5.4
echo "CONFIG_CFG80211_REQUIRE_SIGNED_REGDB=y" >> ./target/linux/mediatek/mt7986/config-5.4
echo "CONFIG_CFG80211_USE_KERNEL_REGDB_KEYS=y" >> ./target/linux/mediatek/mt7986/config-5.4
echo "# CONFIG_CFG80211_WEXT is not set" >> ./target/linux/mediatek/mt7986/config-5.4
echo "# CONFIG_VIRT_WIFI is not set" >> ./target/linux/mediatek/mt7986/config-5.4
echo "# CONFIG_RTL8723BS is not set" >> ./target/linux/mediatek/mt7986/config-5.4
echo "# CONFIG_WILC1000_SDIO is not set" >> ./target/linux/mediatek/mt7986/config-5.4
echo "# CONFIG_WILC1000_SPI is not set" >> ./target/linux/mediatek/mt7986/config-5.4
echo "# CONFIG_PKCS8_PRIVATE_KEY_PARSER is not set" >> ./target/linux/mediatek/mt7986/config-5.4
echo "# CONFIG_PKCS7_TEST_KEY is not set" >> ./target/linux/mediatek/mt7986/config-5.4
echo "# CONFIG_SYSTEM_EXTRA_CERTIFICATE is not set" >> ./target/linux/mediatek/mt7986/config-5.4
echo "# CONFIG_SECONDARY_TRUSTED_KEYRING is not set" >> ./target/linux/mediatek/mt7986/config-5.4

#install mtk feed target
#./scripts/feeds install mtk

#prepare mtk jedi wifi stuff
prepare_mtwifi ${branch_name}

prepare_final ${branch_name}
#step2 build
if [ -z ${1} ]; then
	build ${branch_name} -j1 || [ "$LOCAL" != "1" ]
fi
