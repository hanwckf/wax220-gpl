adie=$1
isIcap=$2

dir=/lib/firmware/
proDir=/etc/wireless/mediatek/
ram=WIFI_RAM_CODE_MT7986
patch=mt7986_patch_e1_hdr
backup=_bk
ICAP=""
curMode=""

curMode=$(cat ${proDir}curFW | grep TESTMODE)
if [ "$curMode" != "" ] && [ "$isIcap" = "1" ]
then
        echo "Already in test mode."
        exit 1
elif [ "$curMode" = "" ] && [ "$isIcap" = "0" ]
then
        echo "Already in normal mode."
        exit 1
fi


if [ "$isIcap" = "1" ]
then
        ICAP=_TESTMODE
elif [ "$isIcap" = "0" ]
then
        ICAP=""
else
        echo "The second augument shoud be 0 or 1"
        exit 1;
fi

if [ "$adie" = "7975" ]
then
        adie=_MT7975
elif [ "$adie" = "7976" ]
then
        adie=""
else
        echo "No such adie."
        exit 1;
fi

cat ${proDir}curFW
echo " > ${ram}${ICAP}${adie}"

echo ${ram}${ICAP}${adie} >  ${proDir}curFW;

if [ "$isIcap" = "1" ]
then
        cp ${dir}${ram}${adie}.bin ${dir}${ram}${adie}_bk.bin
        cp ${dir}${ram}${ICAP}${adie}.bin ${dir}${ram}${adie}.bin
        adie=$(echo $adie | tr 'A-Z' 'a-z')
        ICAP=$(echo $ICAP | tr 'A-Z' 'a-z')
        cp ${dir}${patch}${adie}.bin ${dir}${patch}${adie}_bk.bin
        cp ${dir}${patch}${ICAP}${adie}.bin ${dir}${patch}${adie}.bin
        grep -rl IsICAPFW  /etc/wireless/mediatek/*dat | xargs sed -i 's/IsICAPFW=0/IsICAPFW=1/g'
elif [ "$isIcap" = "0" ]
then
        cp ${dir}${ram}${adie}${backup}.bin ${dir}${ram}${adie}.bin
        adie=$(echo $adie | tr 'A-Z' 'a-z')
        cp ${dir}${patch}${adie}${backup}.bin ${dir}${patch}${adie}.bin
        grep -rl IsICAPFW  /etc/wireless/mediatek/*dat | xargs sed -i 's/IsICAPFW=1/IsICAPFW=0/g'
fi
echo  ${patch}${ICAP}${adie} >> ${proDir}curFW
reboot
