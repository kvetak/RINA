#!/bin/sh
# Run RINASim scenarios from the command line.

if ! type opp_run >/dev/null 2>/dev/null; then
    echo "opp_run isn't present in \$PATH!"
    exit 1
fi

# initialize variables
rina_ui="Cmdenv"
rina_example=""
rina_conf=""
opp_xargs=""
rina_root="$( readlink -f "$( dirname $0 )" )"
rina_lib="${rina_root}/policies/librinasim"

if [ -f "${rina_lib}.so" ]; then
    rina_lib="${rina_lib}.so"
elif [ -f "${rina_lib}.dll" ]; then
    rina_lib="${rina_lib}.dll"
else
    echo "Cannot find the RINASim dynamic library! Forgot to compile?"
    exit 1
fi

# process command line arguments
process_args()
{
    if [ -z "$*" ]; then
        echo "Usage: ./simulate example_folder [-G] [-c configuration] [-x additional opp_run options]"
        exit 0
    elif [ -d "$1" ] && [ -f "$1"/omnetpp.ini ]; then
        rina_example="$1"
    else
        echo "Invalid example folder provided!"
        exit 1
    fi

    shift

    while getopts "Gc:x:" opt; do
      case $opt in
        "G") rina_ui="Tkenv";;
        "c") rina_conf="$OPTARG" ;;
        "x") opp_xargs="$OPTARG" ;;
        *) ;;
      esac
    done
}

# run given simulation
# args: example folder; interface; configuration ID; extra opp_run args
run_simulation()
{
    cd "$1"
    opp_run -u "$2" -c "$3" -n "$rina_root" -l "$rina_lib" $opp_xargs omnetpp.ini
}

process_args $@

run_simulation "$rina_example" "$rina_ui" "$rina_conf" "$opp_xargs"

