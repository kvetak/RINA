#!/bin/bash

opp_run -r 0 -u Cmdenv -c Free1Mbps3QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini
opp_run -r 0 -u Cmdenv -c Free1Mbps9QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini
opp_run -r 0 -u Cmdenv -c Free10Mbps3QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini

opp_run -r 0 -u Cmdenv -c Cong1Mbps3QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini
opp_run -r 0 -u Cmdenv -c Cong1Mbps9QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini
opp_run -r 0 -u Cmdenv -c Cong10Mbps3QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini

