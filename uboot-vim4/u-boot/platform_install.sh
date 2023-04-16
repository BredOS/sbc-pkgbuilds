DIR=/usr/lib/u-boot
write_uboot_platform () 
{ 
    dd if="$1/u-boot.bin.sd.bin.signed" of="$2" conv=fsync,notrunc bs=442 count=1 > /dev/null 2>&1;
    dd if="$1/u-boot.bin.sd.bin.signed" of="$2" conv=fsync,notrunc bs=512 skip=1 seek=1 > /dev/null 2>&1
}
write_uboot_platform_ext () 
{ 
    dd if="$1/u-boot.bin.signed" of=/dev/bootloader conv=fsync bs=512 seek=1 > /dev/null 2>&1;
    dd if="$1/u-boot.bin.signed" of=/dev/mmcblk0boot0 conv=fsync bs=512 seek=1 > /dev/null 2>&1;
    dd if="$1/u-boot.bin.signed" of=/dev/mmcblk0boot1 conv=fsync bs=512 seek=1 > /dev/null 2>&1
}
setup_write_uboot_platform () 
{ 
    local tmp=$(cat /proc/cmdline);
    local bootsource="${tmp##*boot_source=}";
    local partition_type="${tmp##*partition_type=}";
    bootsource="${bootsource%% *}";
    partition_type="${partition_type%% *}";
    if [ "$bootsource" == "sd" ]; then
        DEVICE="/dev/mmcblk1";
    else
        if [ "$bootsource" == "emmc" ]; then
            if [ "$partition_type" == "generic" ]; then
                DEVICE="/dev/mmcblk0";
            else
                DEVICE="VENDOR";
            fi;
        fi;
    fi
}
