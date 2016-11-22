#!/bin/bash

opp_run -r 0 -u Cmdenv -c Free1Mbps3QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini
opp_run -r 0 -u Cmdenv -c Free1Mbps9QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini
opp_run -r 0 -u Cmdenv -c Free10Mbps3QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini

opp_run -r 0 -u Cmdenv -c Cong1Mbps3QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini
opp_run -r 0 -u Cmdenv -c Cong1Mbps9QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini
opp_run -r 0 -u Cmdenv -c Cong10Mbps3QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini


opp_run -r 0 -u Cmdenv -c BEFree1Mbps3QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini
opp_run -r 0 -u Cmdenv -c BEFree1Mbps9QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini
opp_run -r 0 -u Cmdenv -c BEFree10Mbps3QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini

opp_run -r 0 -u Cmdenv -c BECong1Mbps3QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini
opp_run -r 0 -u Cmdenv -c BECong1Mbps9QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini
opp_run -r 0 -u Cmdenv -c BECong10Mbps3QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini


opp_run -r 0 -u Cmdenv -c WFQFree1Mbps3QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini
opp_run -r 0 -u Cmdenv -c WFQFree1Mbps9QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini
opp_run -r 0 -u Cmdenv -c WFQFree10Mbps3QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini

opp_run -r 0 -u Cmdenv -c WFQCong1Mbps3QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini
opp_run -r 0 -u Cmdenv -c WFQCong1Mbps9QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini
opp_run -r 0 -u Cmdenv -c WFQCong10Mbps3QoS -n ../../.. -l ../../../policies/rinasim --debug-on-errors=false omnet.ini


