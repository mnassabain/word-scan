#!/bin/sh


first=$(date +%s%N)

./main > /dev/null

last=$(date +%s%N)

delay=$((last - first))

echo $delay
