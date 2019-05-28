#!/bin/bash

sudo ovs-ofctl -O OpenFlow13 dump-table-features edge > logs/dumptablefeatures_edge.log 2>&1
