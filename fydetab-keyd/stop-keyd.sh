#!/bin/bash

# Check the system status
status=$(systemctl is-system-running)

# If the system is not 'running', exit with an error
if [[ "$status" != "running" ]]; then
    echo "System is not running normally, refusing to touch keyd! ($status)" | systemd-cat
    exit 1
fi

sleep 1
systemctl stop keyd
systemctl reset-failed keyd
