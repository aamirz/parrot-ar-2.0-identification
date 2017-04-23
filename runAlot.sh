#!/bin/bash
END=$1
HOST=$2
PORT=$3
echo $END
for i in $(seq 1 $END)
do echo "runalot\n" | ./client $HOST $PORT
#sleep '0.2'
done

