#!/bin/bash

insmod /lib/modules/$(uname -r)/extra/protected_memory_allocator.ko
insmod /lib/modules/$(uname -r)/extra/memory_group_manager.ko
insmod /lib/modules/$(uname -r)/extra/mali_kbase.ko
insmod /lib/modules/$(uname -r)/extra/aipu.ko
insmod /lib/modules/$(uname -r)/extra/amvx.ko
insmod /lib/modules/$(uname -r)/kernel/drivers/hid/uhid.ko
insmod /lib/modules/$(uname -r)/kernel/drivers/bluetooth/btusb.ko
insmod /lib/modules/$(uname -r)/kernel/drivers/bluetooth/btrtl.ko
insmod /lib/modules/$(uname -r)/kernel/drivers/input/touchscreen/goodix_ts.ko
insmod /lib/modules/$(uname -r)/kernel/drivers/rtc/rtc-hym8563.ko

insmod /lib/modules/$(uname -r)/kernel/net/netfilter/x_tables.ko
insmod /lib/modules/$(uname -r)/kernel/net/ipv4/netfilter/ip_tables.ko
insmod /lib/modules/$(uname -r)/kernel/net/ipv4/netfilter/iptable_nat.ko
insmod /lib/modules/$(uname -r)/kernel/net/ipv4/netfilter/nf_defrag_ipv4.ko
insmod /lib/modules/$(uname -r)/kernel/net/ipv6/netfilter/nf_defrag_ipv6.ko
insmod /lib/modules/$(uname -r)/kernel/lib/libcrc32c.ko
insmod /lib/modules/$(uname -r)/kernel/net/netfilter/nf_conntrack.ko
insmod /lib/modules/$(uname -r)/kernel/net/netfilter/nf_nat.ko
insmod /lib/modules/$(uname -r)/kernel/net/netfilter/xt_MASQUERADE.ko
 
ln -s /dev/dma_heap/reserved /dev/dma_heap/linux,cma

if [[ ! -e  /etc/machine-id ]]; then
    dbus-uuidgen > /etc/machine-id
    ln -sf /etc/machine-id /var/lib/dbus/machine-id
fi



video_devices=($(ls /dev/video* 2>/dev/null | sort -V))

if [ ${#video_devices[@]} -eq 1 ]; then
    ln -s "${video_devices[0]}" /dev/video-cixdec0
elif [ ${#video_devices[@]} -eq 0 ]; then
    echo "Not found /dev/video*"
else
    max_device="${video_devices[-2]}"
    ln -s "$max_device" /dev/video-cixdec0
fi
