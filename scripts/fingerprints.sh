#!/bin/bash
# Batch operations on scenario fingerprints.
# TODO: remove bashisms

# scenarios to exclude (e.g. if they're too resource-expensive)
exclude_scenarios=(BigRandNet DC Circular)

# initialize the mandatory stuff
rina_root="$( readlink -f "$( dirname $0 )/.." )"
rina_scenarios="${rina_root}/examples"
rina_lib="${rina_root}/policies/librinasim"
glob='*'

if ! type opp_run >/dev/null 2>/dev/null; then
    echo "opp_run isn't present in \$PATH!"
    exit 1
fi


if [ -f "${rina_lib}.so" ]; then
    rina_lib="${rina_lib}.so"
elif [ -f "${rina_lib}.dll" ]; then
    rina_lib="${rina_lib}.dll"
else
    echo "Cannot find the RINASim dynamic library! Forgot to compile?"
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
    glob_scenario="*"
    glob_group="*"
    glob_config="*"

    case "$1" in
        check)
            mode="check"
            ;;

        update)
            mode="update"
            ;;
        *)
            echo "Usage: fingerprints.sh check|update [-g group] [-s scenario] [-c configuration]"
            exit 0
            ;;
    esac

    shift

    while getopts ":g:s:c:" opt; do
      case $opt in
        "g") glob_group="$OPTARG" ;;
        "s") glob_scenario="$OPTARG" ;;
        "c") glob_config="$OPTARG" ;;
        *) ;;
      esac
    done
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
    fingerprint=$(
        echo "$1" | \
        grep '<!> Fingerprint mismatch!' | \
        sed 's/.*calculated: \(.\{9\}\).*/\1/'
    )

    if [ -n "$fingerprint" ]; then
        sed -i "/^\[\(Config \)\?$3/,/^\[Config/s/^fingerprint[ =].*/fingerprint = \"$fingerprint\"/" $2
        if $colorize; then printf "${txtgreen}"; fi
        echo "UPDATED ($fingerprint)"
    else
        if $colorize; then printf "${txtcyan}"; fi
        echo "UNCHANGED"
    fi
    if $colorize; then printf "${txtrst}"; fi
}

# run given simulation in the console mode
# args: simulation folder (with the omnetpp.ini file), configuration ID
run_simulation()
{
    cd "$1"
    opp_run -u Cmdenv -c "$2" -n "$rina_root" -l "$rina_lib" omnetpp.ini 2>&1
}

# begin!

process_args $@

cd $rina_scenarios

# retrieve scenarios by the given directory glob
scenarios="$( find . -type f -path "./${glob_group}/${glob_scenario}/omnetpp.ini"  \
        $( for scen in "${exclude_scenarios[@]}"; do echo -not -path ./*/"$scen"/omnetpp.ini; done ) \
        | sort )"

if [ -z "$scenarios" ]; then echo "No matching scenarios!"; exit 1; fi

# run the main loop
echo "$scenarios" | while read simfile; do
    simdir="$( dirname $simfile)"
    echo "Processing $simdir..."

    configs="General"$'\n'"$( grep '^\[Config ' "$simfile" | sed 's/\[Config \(.*\)].*/\1/' )"

    echo "$configs" | while read simconf; do
        if [[ "$simconf" != $glob_config ]]; then continue; fi

        printf "  $simconf: "

        if [ $mode = "check" ]; then
            output=$( run_simulation "$simdir" "$simconf" )
            analyze_output "$output" $?
        elif [ $mode = "update" ]; then

            if [ -z "$( sed -n "/^\[\(Config \)\?$simconf/,/^\[Config/p" "$simfile" | grep '^fingerprint[ =]')" ]; then
                echo -e "${txtred}NO FINGERPRINT SPECIFIED${txtrst}"
            else
                output=$( run_simulation "$simdir" "$simconf" )
                update_fingerprint "$output" "$simfile" "$simconf"
            fi
        fi
    done
done

