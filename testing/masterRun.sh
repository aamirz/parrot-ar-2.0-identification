#!/bin/bash
START=1
END=$1
NUMBER=5
for ((i=$START; i<=$END; i++))
do 
    ./runAlot.sh $NUMBER 192.168.1.1 8881 > out_$i.txt
    NUMBER=$((($NUMBER)+5))
done