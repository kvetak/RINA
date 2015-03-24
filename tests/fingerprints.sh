#!/bin/bash
# Batch run scenarios and output fingerprints.

cd ../examples/

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
                ../../src/rina.exe -u Cmdenv -c "$j" -n ../../examples/:../../src omnetpp.ini | \
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
