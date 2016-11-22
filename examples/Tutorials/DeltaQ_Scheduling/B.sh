#!/bin/bash

opp_run -r 0 -u Cmdenv -c BEFree1Mbps3QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini
opp_run -r 0 -u Cmdenv -c BEFree1Mbps9QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini
opp_run -r 0 -u Cmdenv -c BEFree10Mbps3QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini

opp_run -r 0 -u Cmdenv -c BECong1Mbps3QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini
opp_run -r 0 -u Cmdenv -c BECong1Mbps9QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini
opp_run -r 0 -u Cmdenv -c BECong10Mbps3QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini


