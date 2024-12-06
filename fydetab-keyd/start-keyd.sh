#!/bin/bash

retry_count=0
max_retries=20

while [[ $retry_count -lt $max_retries ]]; do
    status=$(systemctl is-system-running)

    if [[ "$status" == "running" ]]; then
        systemctl start --no-block keyd
        exit 0
    elif [[ "$status" == "initializing" ]]; then
        echo "System is initializing. Retrying.." | systemd-cat
        sleep 1
        ((retry_count++))
    elif [[ "$status" == "starting" ]]; then
        echo "System is starting. Retrying.." | systemd-cat
        sleep 1
        ((retry_count++))
    else
        echo "Invalid system state, aborting! ($status)" | systemd-cat
        exit 1
    fi
done

echo "Timeout waiting for system bootup for keyd loading!" | systemd-cat
exit 1
