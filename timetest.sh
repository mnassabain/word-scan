#!/bin/sh


first=$(date +%s)

./main > /dev/null

last=$(date +%s)

delay=$((last - first))

echo $delay
