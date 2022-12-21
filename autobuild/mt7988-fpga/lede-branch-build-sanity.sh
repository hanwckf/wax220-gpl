#!/bin/bash
source ./autobuild/lede-build-sanity.sh

#get the brach_name
temp=${0%/*}
branch_name=${temp##*/}
#step1 clean
#clean
#do prepare stuff
prepare

#install mtk feed target
#./scripts/feeds install mtk
#copy U3 FPGA test patch from mt7986
cp -fpR ${BUILD_DIR}/autobuild/mt7986-FPGA/target/linux/mediatek/files-5.4/drivers/phy/ ${BUILD_DIR}/target/linux/mediatek/files-5.4/drivers/
cp -fpR ${BUILD_DIR}/autobuild/mt7986-FPGA/target/linux/mediatek/patches-5.4/800*.patch ${BUILD_DIR}/target/linux/mediatek/patches-5.4/
#cp eth driver from mtk_feed file-5.4 
#cp -fpR ${BUILD_DIR}/target/linux/mediatek/files-5.4/drivers/net/ethernet/ ${BUILD_DIR}/target/linux/mediatek/files-5.10/drivers/net/

#prepare mtk jedi wifi stuff
prepare_mtwifi ${branch_name}

prepare_final ${branch_name}
#step2 build
build ${branch_name} -j1 || [ "$LOCAL" != "1" ]
