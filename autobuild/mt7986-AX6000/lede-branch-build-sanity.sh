#!/bin/bash
source ./autobuild/lede-build-sanity.sh

#get the brach_name
temp=${0%/*}
branch_name=${temp##*/}
#step1 clean
#clean

#step2.1 choose which .config
if [ $1 = "6E" ]; then
	echo "CONFIG_MTK_6G_SUPPORT=y" >> autobuild/${branch_name}/.config
	echo "CONFIG_MTK_WIFI_ADIE_TYPE=\"mt7976\"" >> autobuild/${branch_name}/.config
	echo "CONFIG_first_card_profile_path=\"/etc/wireless/mediatek/mt7986-ax8400.dbdc.b0.dat;/etc/wireless/mediatek/mt7986-ax8400.dbdc.b1.dat\"" >> autobuild/${branch_name}/.config
fi

#step2.1 choose which .config
if [ $1 = "kasan" ]; then
	echo "CONFIG_KERNEL_KASAN=y" >> autobuild/${branch_name}/.config
	echo "CONFIG_KERNEL_KASAN_OUTLINE=y" >> autobuild/${branch_name}/.config
	echo "# CONFIG_PACKAGE_kmod-ufsd_driver is not set" >> autobuild/${branch_name}/.config
fi


#do prepare stuff
prepare

#step2.2 choose which config-5.4
if [ $1 = "kasan" ]; then
	echo "CONFIG_DEBUG_KMEMLEAK=y" >> ./target/linux/mediatek/mt7986/config-5.4
	echo "CONFIG_DEBUG_KMEMLEAK_AUTO_SCAN=y" >> ./target/linux/mediatek/mt7986/config-5.4
	echo "# CONFIG_DEBUG_KMEMLEAK_DEFAULT_OFF is not set" >> ./target/linux/mediatek/mt7986/config-5.4
	echo "CONFIG_DEBUG_KMEMLEAK_MEM_POOL_SIZE=16000" >> ./target/linux/mediatek/mt7986/config-5.4
	echo "CONFIG_DEBUG_KMEMLEAK_TEST=m" >> ./target/linux/mediatek/mt7986/config-5.4
	echo "CONFIG_KALLSYMS=y" >> ./target/linux/mediatek/mt7986/config-5.4
	echo "CONFIG_KASAN=y" >> ./target/linux/mediatek/mt7986/config-5.4
	echo "CONFIG_KASAN_GENERIC=y" >> ./target/linux/mediatek/mt7986/config-5.4
	echo "# CONFIG_KASAN_INLINE is not set" >> ./target/linux/mediatek/mt7986/config-5.4
	echo "CONFIG_KASAN_OUTLINE=y" >> ./target/linux/mediatek/mt7986/config-5.4
	echo "CONFIG_KASAN_SHADOW_OFFSET=0xdfffffd000000000" >> ./target/linux/mediatek/mt7986/config-5.4
	echo "# CONFIG_TEST_KASAN is not set" >> ./target/linux/mediatek/mt7986/config-5.4
	echo "CONFIG_SLUB_DEBUG=y" >> ./target/linux/mediatek/mt7986/config-5.4
fi

#install mtk feed target
#./scripts/feeds install mtk

#prepare mtk jedi wifi stuff
prepare_mtwifi ${branch_name}

prepare_final ${branch_name}
#step3 build
if [ -z ${1} ] || [ $1 = "6E" ] || [ $1 = "kasan" ]; then
	build ${branch_name} -j1 || [ "$LOCAL" != "1" ]
fi
