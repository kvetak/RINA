#!/bin/bash
# Batch operations on scenario fingerprints.
# TODO: remove bashisms

# scenarios to exclude (e.g. if they're too resource-expensive)
exclude_scenarios=(BigRandNet DC)

# initialize the mandatory stuff
rina_root="$( readlink -f "$( dirname $0 )/.." )"
rina_scenarios="${rina_root}/examples"
glob='*'

# locate the executable
if [ -f "${rina_root}/out/gcc-debug/src/RINA" ]; then
    rina_bin=${rina_root}/out/gcc-debug/src/RINA
elif [ -f "${rina_root}/out/gcc-debug/src/rina.exe" ]; then
    rina_bin=${rina_root}/out/gcc-debug/src/rina.exe
else
    echo "Cannot find the RINA executable!"
    exit 1
fi

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

# process command line arguments
process_args()
{
    case "$1" in
        check)
            mode="check"
            ;;

        update)
            mode="update"
            ;;
        *)
            echo "Usage: fingerprints.sh check|update [scenario name glob]"
            exit 0
            ;;
    esac

    if [ -n "$2" ]; then
        if [ -n "$( find . -name "$2" -type d)" ]; then
            glob=$2
        else
            echo "No matching scenarios!"
            exit 1
        fi
    fi
}

# analyze output of a simulation run
# args: output, return value
analyze_output()
{
    echo
    if $colorize; then
        if [ $2 -eq 0 ]; then
            printf "${txtgreen}"
        else
            printf "${txtred}    Error code returned!\n"; fi
    fi
    echo "$1" | grep '\(> Simulation\|> No more events\|> Error\|Segmentation\)' | sed 's/^/    /g'

    if $colorize; then printf "${txtgreen}"; fi
    echo "$1" | grep 'Fingerprint successfully verified' | sed 's/^/    /g'
    if $colorize; then printf "${txtcyan}"; fi
    echo "$1" | grep 'Fingerprint mismatch' | sed 's/^/    /g'
    if $colorize; then printf "${txtyellow}"; fi
    echo "$1" | grep 'unprocessed PDUs' | sed 's/^[^.]*.//g;s/^/    /g'
    if $colorize; then printf "${txtrst}"; fi
}

# update given scenario configuration fingerprint
# args: simulation output, config file, configuration ID
update_fingerprint()
{
    if [ -z "$( sed -n "/^\[Config $3/,/^\[Config/p" omnetpp.ini | grep '^fingerprint[ =]')" ]; then
        echo -e "${txtred}NO FINGERPRINT SPECIFIED${txtrst}"
        return
    fi

    fingerprint=$(
        echo "$1" | \
        grep '<!> Fingerprint mismatch!' | \
        sed 's/.*calculated: \(.\{9\}\).*/\1/'
    )

    if [ -n "$fingerprint" ]; then
        sed -i "/^\[Config $3/,/^\[Config/s/^fingerprint[ =].*/fingerprint = \"$fingerprint\"/" $2
        if $colorize; then printf "${txtgreen}"; fi
        echo "UPDATED ($fingerprint)"
    else
        if $colorize; then printf "${txtcyan}"; fi
        echo "UNCHANGED"
    fi
    if $colorize; then printf "${txtrst}"; fi
}

# begin!

process_args $@

cd $rina_scenarios

# run the main loop
for i in $glob/; do
    # exclude the scenario if this is wanted
    for scen in "${exclude_scenarios[@]}"; do
        if [ "${i%/}" = "$scen" ]; then echo "Skipping $i..."; continue 2; fi
    done

    echo "Processing $i..."
    cd "$i"

    if [ ! -f omnetpp.ini ]; then echo "  omnetpp.ini not present!" && cd .. && continue; fi

    grep '^\[Config ' omnetpp.ini | sed 's/\[Config \(.*\)].*/\1/' | while read j; do
        printf "  $j: "
        output="$( $rina_bin -u Cmdenv -c "$j" -n ../../examples/:../../src omnetpp.ini 2>&1 )"
        ret=$?

        if [ $mode = "check" ]; then
            analyze_output "$output" $ret
        elif [ $mode = "update" ]; then
            update_fingerprint "$output" omnetpp.ini "$j"
        fi
    done
    cd ..
done

