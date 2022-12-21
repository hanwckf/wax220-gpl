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

#prepare mtk jedi wifi stuff
prepare_mtwifi ${branch_name}

#cp autobuild(mt7986-AX6000) customized file into SDK
cp -fpR ${BUILD_DIR}/autobuild/mt7986-AX6000/target/ ${BUILD_DIR}
cp -fpR ${BUILD_DIR}/autobuild/mt7986-AX6000/package/ ${BUILD_DIR}

prepare_final ${branch_name}
#step2 build
build ${branch_name} -j1 || [ "$LOCAL" != "1" ]
