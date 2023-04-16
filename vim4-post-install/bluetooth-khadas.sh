#!/bin/bash

bt_tty="ttyS1"

/usr/sbin/rfkill block 0
/usr/sbin/rfkill block bluetooth
/bin/sleep 2
/usr/sbin/rfkill unblock 0
/usr/sbin/rfkill unblock bluetooth

# FIXME Delay
/bin/sleep 1

# Attach HCI adapter
/usr/local/bin/hciattach -n -s 115200 /dev/$bt_tty bcm43xx 2000000