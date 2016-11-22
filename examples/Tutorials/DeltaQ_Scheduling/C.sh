#!/bin/bash

opp_run -r 0 -u Cmdenv -c WFQFree1Mbps3QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini
opp_run -r 0 -u Cmdenv -c WFQFree1Mbps9QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini
opp_run -r 0 -u Cmdenv -c WFQFree10Mbps3QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini

opp_run -r 0 -u Cmdenv -c WFQCong1Mbps3QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini
opp_run -r 0 -u Cmdenv -c WFQCong1Mbps9QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini
opp_run -r 0 -u Cmdenv -c WFQCong10Mbps3QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini


