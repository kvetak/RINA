#!/bin/bash
# Batch run scenarios and output fingerprints.
# TODO: remove bashisms

exclude_scenarios=(BigRandNet DC)

rina_root="$( readlink -f "$( dirname $0 )/.." )"
rina_scenarios="${rina_root}/examples"

# enable colors if we're connected to stdout
if [ -t 1 ]; then
    colorize=true
    txtred='\033[0;31m'
    txtgreen='\033[0;32m'
    txtyellow='\033[0;33m'
    txtcyan='\033[0;36m'
    txtrst='\033[0m'
else
    colorize=false
fi

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

should_exclude()
{
    for scen in "${exclude_scenarios[@]}"; do
        if [ "${i%/}" = "$scen" ]; then echo "Skipping $i..."; return 0; fi
    done
    return 1
}

case "$1" in
    check)
        for i in $glob/; do
            # exclude some scenarios if needed
            if should_exclude "$i"; then continue; fi

            echo "Checking $i..."
            cd "$i"

            if [ ! -f omnetpp.ini ]; then echo "  omnetpp.ini not present!" && cd .. && continue; fi

            get_configs omnetpp.ini | while read j; do
                echo "  $j:"

                output="$( run_simulation "$j" 2>&1 )"
                ret=$?

                if $colorize; then
                    if [ $ret -eq 0 ]; then
                        printf "${txtgreen}"
                    else
                        printf "${txtred}    Error code returned!\n"; fi
                fi
                echo "$output" | grep '\(> Simulation\|> No more events\|> Error\|Segmentation\)' | sed 's/^/    /g'

                if $colorize; then printf "${txtgreen}"; fi
                echo "$output" | grep 'Fingerprint successfully verified' | sed 's/^/    /g'
                if $colorize; then printf "${txtcyan}"; fi
                echo "$output" | grep 'Fingerprint mismatch' | sed 's/^/    /g'
                if $colorize; then printf "${txtyellow}"; fi
                echo "$output" | grep 'unprocessed PDUs' | sed 's/^/    /g'
                if $colorize; then printf "${txtrst}"; fi

            done
            cd ..
        done
        ;;

    update)
        for i in $glob/; do
            # exclude some scenarios if needed
            if should_exclude "$i"; then continue; fi

            echo "Updating fingerprints for $i..."
            cd "$i"

            if [ ! -f omnetpp.ini ]; then echo "  omnetpp.ini not present!" && cd .. && continue; fi

            get_configs omnetpp.ini | while read j; do
                printf "  Processing $j... "

                if [ -z "$( sed -n "/^\[Config $j/,/^\[Config/p" omnetpp.ini | grep '^fingerprint[ =]')" ]; then
                    echo -e "${txtred}NO FINGERPRINT SPECIFIED${txtrst}"
                    continue
                fi

                fingerprint=$(
                    run_simulation "$j" | \
                    grep '<!> Fingerprint mismatch!' | \
                    sed 's/.*calculated: \(.\{9\}\).*/\1/'
                )

                if [ -n "$fingerprint" ]; then
                    sed -i "/^\[Config $j/,/^\[Config/s/^fingerprint[ =].*/fingerprint = \"$fingerprint\"/" omnetpp.ini
                    if $colorize; then printf "${txtgreen}"; fi
                    echo "UPDATED ($fingerprint)"
                else
                    if $colorize; then printf "${txtcyan}"; fi
                    echo "UNCHANGED"
                fi
                if $colorize; then printf "${txtrst}"; fi
            done
            cd ..
        done
        ;;
    *)
        echo "Usage: fingerprints.sh check|update [scenario name glob]"
        ;;
esac
