#!/bin/bash -e

if [ $# -lt 1 ]; then
    echo "Usage: $0 <env> [target]"
    exit 1
fi

env=$1
target=$2

cp src/DoorbellGatewayHardware.h lib/OGM-Common/include/hardware.h
cp src/DoorbellGatewayKnxprod.h lib/OGM-Common/include/knxprod.h

if [ -n "$target" ]; then
    pio run -e "$env" --target "$target"
else
    pio run -e "$env"
fi
