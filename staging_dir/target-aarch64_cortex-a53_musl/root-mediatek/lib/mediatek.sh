#!/bin/sh
#
# Copyright (C) 2016 OpenWrt.org
#

. /lib/functions.sh

ubi_mknod() {
    local dir="$1"
    local dev="/dev/$(basename $dir)"

    [ -e "$dev" ] && return 0

    local devid="$(cat $dir/dev)"
    local major="${devid%%:*}"
    local minor="${devid##*:}"
    mknod "$dev" c $major $minor
}

nand_find_volume() {
    local ubidevdir ubivoldir
    ubidevdir="/sys/devices/virtual/ubi/$1"
    [ ! -d "$ubidevdir" ] && return 1
    for ubivoldir in $ubidevdir/${1}_*; do
	[ ! -d "$ubivoldir" ] && continue
	if [ "$( cat $ubivoldir/name )" = "$2" ]; then
	    basename $ubivoldir
	    ubi_mknod "$ubivoldir"
	    return 0
	fi
    done
}

nand_find_ubi() {
    local ubidevdir ubidev mtdnum
    mtdnum="$( find_mtd_index $1 )"
    [ ! "$mtdnum" ] && return 1
    for ubidevdir in /sys/devices/virtual/ubi/ubi*; do
	[ ! -d "$ubidevdir" ] && continue
	cmtdnum="$( cat $ubidevdir/mtd_num )"
	[ ! "$mtdnum" ] && continue
	if [ "$mtdnum" = "$cmtdnum" ]; then
	    ubidev=$( basename $ubidevdir )
	    ubi_mknod "$ubidevdir"
	    echo $ubidev
	    return 0
	fi
    done
}

mediatek_board_detect() {
	local machine
	local name

	machine=$(cat /proc/device-tree/model)
    
	case "$machine" in
	"MediaTek MT7623 evaluation board")
		name="mt7623"
		;;
	"MediaTek MT7623a eMMC evaluation board")
		name="mt7623"
		;;
	"MediaTek MT7623a NAND evaluation board")
		name="mt7623"
		;;
	"MediaTek MT7623n eMMC+Ephy board")
		name="mt7623-gphy"
		;;
	"MediaTek MT7622 AC2600rfb1 board")
		name="mt7622"
		;;
	"MediaTek MT7622 AC4300rfb1 board")
		name="mt7622"
		;;
	"Mediatek MT7622 AC4300-gmac1 board")
		name="mt7622-gmac1_only"
		;;
	"MediaTek MT7622 AX3600 board")
		name="mt7622-ax"
		;;
	"MediaTek MT7622 AX3600-gmac1 board")
		name="mt7622-ax-gmac1_only"
		;;
	"MediaTek MT7629 RFB1 board")
		name="mt7629"
		;;
	"MediaTek MT7986b RFB")
		name="mt7986-snand-wax220"
		;;
	esac

	[ -z "$name" ] && name="unknown"

	[ -e "/tmp/sysinfo/" ] || mkdir -p "/tmp/sysinfo/"

	echo "$name" > /tmp/sysinfo/board_name
	echo "$machine" > /tmp/sysinfo/model
}

mediatek_board_name() {
	local name

	[ -f /tmp/sysinfo/board_name ] && name=$(cat /tmp/sysinfo/board_name)
	[ -z "$name" ] && name="unknown"

	echo "$name"
}

mediatek_sync_uboot_env() {
	local fenv_region=$(fw_printenv fenv_region 2> /dev/null | awk -F = '{print $2;}')
	local region=$(envctl factory get region 2> /dev/null)

	if [ -n "$fenv_region" ] && [ "$fenv_region" != "$region" ]; then
		echo "Sync uboot env fenv_region o factory env"
		envctl factory set region $fenv_region
	fi

	local fenv_restore=$(fw_printenv fenv_restore 2> /dev/null | awk -F = '{print $2;}')
	local upper_dir="/var/mnt/cfg"
	if [ "$fenv_restore" == "yes" ]; then
		echo "uboot env fenv_restore is yes"
		mkdir -p $upper_dir
		touch $upper_dir/.restore
		fw_setenv fenv_restore no
	fi
}

mediatek_mount_cfg() {
	local upper_dir="/var/root_etc"
	local work_dir="/var/root_etc.work"

	mkdir -p $upper_dir
	mkdir -p $work_dir
	mount -n -t overlay overlay \
		-o rw,noatime,lowerdir=/etc,upperdir=$upper_dir,workdir=$work_dir /etc

	local ubidev=$( nand_find_ubi "ubi" )
	if [ ! "$ubidev" ]; then
	    local mtdnum=$( find_mtd_index "ubi" )
	    ubiattach -m "$mtdnum"
	    ubidev=$( nand_find_ubi "ubi" )
	fi
	local ubivol=$( nand_find_volume $ubidev "CFG" )
	if [ ! "$ubivol" ]; then
	    ubimkvol /dev/$ubidev -N "CFG" -s 4MiB
	    ubivol=$( nand_find_volume $ubidev "CFG" )
	    if [ ! "$ubivol" ]; then
		echo "ubimkvol CFG failed"
		return 1
	    fi
	fi

	local mount_dir="/var/mnt"
	mkdir -p $mount_dir
	mount -t ubifs /dev/$ubivol $mount_dir
	if [ $? != 0 ]; then
	    echo "mount CFG volume failed"
	    return 1
	fi

	mediatek_sync_uboot_env
	local model=$(envctl factory get model 2> /dev/null)
	local factory_mode=$(envctl factory get factory_mode 2> /dev/null)

	local cfg_dir=""
	if [ "$factory_mode" != "off" ]; then
		cfg_dir="/cfg/factory:"
	else
		if [ -n "$model" ] && [ -d "/cfg/$model" ]; then
			cfg_dir="/cfg/$model:"
		fi
	fi

	local lower_dir="$cfg_dir/cfg/common:/etc/config"
	upper_dir="$mount_dir/cfg"
	work_dir="$mount_dir/cfg.work"
	if [ "$factory_mode" != "off" ] || [ -e $upper_dir/.restore ]; then
		echo "Restore to default config"
		if [ -e $upper_dir/.restore ]; then
			cp $upper_dir/.restore /tmp/.restore
		fi

		rm -fr $upper_dir
#       in /lib/preinit/05_set_iface_mac_mediatek  check /tmp/.restore
		touch /tmp/.restore
	fi

	mkdir -p $upper_dir
	mkdir -p $work_dir
	mount -n -t overlay overlay \
		-o rw,noatime,lowerdir=$lower_dir,upperdir=$upper_dir,workdir=$work_dir /etc/config

	local upper_dir="$mount_dir/rc.d"
	local work_dir="$mount_dir/rc.d.work"

	mkdir -p $upper_dir
	mkdir -p $work_dir
	mount -n -t overlay overlay \
		-o rw,noatime,lowerdir=/etc/rc.d,upperdir=$upper_dir,workdir=$work_dir /etc/rc.d
}

mediatek_mount_rae() {
	local mtd_id=`cat /proc/mtd | grep "RAE" | awk -F : '{print $1;}' | sed s/mtd//`

	if [ $? != 0 ] || [ ! $mtd_id ]; then
		echo "Get RAE partition failed"
		return 1
	fi

	local mount_dir="/rae"
	mount -t jffs2 /dev/mtdblock$mtd_id $mount_dir
	if [ $? != 0 ]; then
		echo "flash_erase RAE partition"
		mtd erase /dev/mtd$mtd_id
		mount -t jffs2 /dev/mtdblock$mtd_id $mount_dir
		if [ $? != 0 ]; then
			echo "mount RAE partition failed"
			return 1
		fi
	fi
}

mediatek_load_systempasswd() {
	if [ ! -f /etc/config/config/shadow ]; then
		if [ ! -d /etc/config/config ]; then
			mkdir -p /etc/config/config
		fi
		cp /etc/shadow_default /etc/config/config/shadow
	fi
}
