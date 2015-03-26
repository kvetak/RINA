#!/bin/bash
# Batch run scenarios and output fingerprints.

rina_root="$( readlink -f "$( dirname $0 )/.." )"
rina_scenarios="${rina_root}/examples"

if [ -f "${rina_root}/out/gcc-debug/src/RINA" ]; then
    rina_bin=${rina_root}/out/gcc-debug/src/RINA
elif [ -f "${rina_root}/out/gcc-debug/src/rina.exe" ]; then
    rina_bin=${rina_root}/out/gcc-debug/src/rina.exe
else
    echo "Cannot find the RINA executable!"
fi


cd $rina_scenarios

if [ -n "$2" ]; then
    if [ -n "$( find . -name "$2" -type d)" ]; then
        glob=$2
    else
        echo "No matching scenarios!"
        exit 1
    fi
else
    glob='*'
fi

case "$1" in
    check)
        for i in $glob/; do

            echo "Checking $i..."
            cd "$i"
            if [ ! -f omnetpp.ini ]; then echo "  omnetpp.ini not present!" && cd .. && continue; fi

            grep '^\[Config ' omnetpp.ini | sed 's/\[Config \(.*\)].*/\1/' | while read j; do
                echo "  $j:"
                $rina_bin -u Cmdenv -c "$j" -n ../../examples/:../../src omnetpp.ini | \
                grep '\(> Fingerprint\|> Error\|> Simulation\|Segmentation\|unprocessed PDUs\)' | \
                sed 's/^/    /g'
            done
            cd ..
        done
        ;;

    regen)
        # better do this with Python and ConfigParser
        ;;
    *)
        echo "Usage: fingerprints.sh check [scenario name glob]"
        ;;
esac
