#!/usr/bin/env bash

SOURCE=${BASH_SOURCE[0]}
while [ -L "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )
  SOURCE=$(readlink "$SOURCE")
  [[ $SOURCE != /* ]] && SOURCE=$DIR/$SOURCE # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )

if [ $# -lt 1 ]; then
    echo "Usage: $0 <env> [target]"
    exit 1
fi

env=$1
target=$2

cp "${DIR}/../src/DoorbellGatewayHardware.h" "${DIR}/../lib/OGM-Common/include/hardware.h"
cp "${DIR}/../src/DoorbellGateway.h" "${DIR}/../lib/OGM-Common/include/knxprod.h"

(
    cd "${DIR}/../" || exit 2

    if [ -n "$target" ]; then
        pio run -e "$env" --target "$target"
    else
        pio run -e "$env"
    fi
)

gzip -kf "${DIR}/../.pio/build/${env}/firmware.bin"
