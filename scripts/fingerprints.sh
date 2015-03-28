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


get_configs()
{
    grep '^\[Config ' $1 | sed 's/\[Config \(.*\)].*/\1/'
}

run_simulation()
{
    $rina_bin -u Cmdenv -c "$1" -n ../../examples/:../../src omnetpp.ini
}

case "$1" in
    check)
        for i in $glob/; do
            echo "Checking $i..."
            cd "$i"

            if [ ! -f omnetpp.ini ]; then echo "  omnetpp.ini not present!" && cd .. && continue; fi

            get_configs omnetpp.ini | while read j; do
                echo "  $j:"

                run_simulation "$j" | \
                    grep '\(> Fingerprint\|> Error\|> Simulation\|Segmentation\|unprocessed PDUs\)' | \
                    sed 's/^/    /g'
            done
            cd ..
        done
        ;;

    update)
        for i in $glob/; do

            echo "Updating fingerprints for $i..."
            cd "$i"

            if [ ! -f omnetpp.ini ]; then echo "  omnetpp.ini not present!" && cd .. && continue; fi

            get_configs omnetpp.ini | while read j; do
                printf "  Processing $j... "

                if [ -z "$( sed -n "/^\[Config $j/,/^\[Config/p" omnetpp.ini | grep '^fingerprint[ =]')" ]; then
                    echo -e "\033[0;31mNO FINGERPRINT SPECIFIED\033[0m"
                    continue
                fi

                fingerprint=$(
                    run_simulation "$j" | \
                    grep '<!> Fingerprint mismatch!' | \
                    sed 's/.*calculated: \(.\{9\}\).*/\1/'
                )

                if [ -n "$fingerprint" ]; then
                    sed -i "/^\[Config $j/,/^\[Config/s/^fingerprint[ =].*/fingerprint = \"$fingerprint\"/" omnetpp.ini
                    echo -e "\033[0;32mUPDATED ($fingerprint)\033[0m"
                else
                    echo -e "\033[0;36mUNCHANGED\033[0m"
                fi
            done
            cd ..
        done
        ;;
    *)
        echo "Usage: fingerprints.sh check|update [scenario name glob]"
        ;;
esac
