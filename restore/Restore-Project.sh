#!/bin/bash -e

SOURCE=${BASH_SOURCE[0]}
while [ -L "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )
  SOURCE=$(readlink "$SOURCE")
  [[ $SOURCE != /* ]] && SOURCE=$DIR/$SOURCE # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )

find "${DIR}/../lib/" -type l | while read -r PROJECT_SYMLINK; do
    PROJECT=$(basename "${PROJECT_SYMLINK}")

    if [ -d "${DIR}/../../${PROJECT}" ]; then
        echo "${PROJECT} has already been cloned, pulling..."

        (
            cd "${DIR}/../../${PROJECT}"
            git pull
        )
    else
        if [ "${PROJECT}" == "knx" ]; then
            git clone https://github.com/thelsing/knx.git "${DIR}/../../${PROJECT}"
        else
            git clone "https://github.com/OpenKNX/${PROJECT}.git" "${DIR}/../../${PROJECT}"
        fi
    fi
done
