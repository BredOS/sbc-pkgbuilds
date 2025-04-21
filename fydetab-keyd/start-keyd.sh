#!/bin/bash

retry_count=0
max_retries=25

while [[ $retry_count -lt $max_retries ]]; do
    status=$(systemctl is-system-running)

    if [[ "$status" == "running" ]]; then
        systemctl start --no-block keyd
        exit 0
    elif [[ "$status" == "initializing" ]]; then
        logger -t "fydetab-keyd" "System is initializing. Retrying.."
        sleep 1
        ((retry_count++))
    elif [[ "$status" == "starting" ]]; then
        logger -t "fydetab-keyd" "System is starting. Retrying.."
        sleep 1
        ((retry_count++))
    else
        logger -t "fydetab-keyd" "Invalid system state, aborting! ($status)"
        exit 1
    fi
done

logger -t "fydetab-keyd" "Timeout waiting for system bootup for keyd loading!"
exit 1
