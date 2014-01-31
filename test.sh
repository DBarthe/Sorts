#!/bin/bash

modules=(./test/test_heapsort ./test/test_quicksort ./test/test_mergesort)
make re-infos
make tests
clear
n=1000
while [ $n -lt 10000000 ]
do
    echo "============= test with $n elements ============="
    for module in ${modules[*]}
    do
	echo -n "$module: "
	/usr/bin/time -f '%es' $module $n $1
	echo
    done
    n=$(($n*10))
done
echo "======================================================="