#!/bin/sh
NUM=$1
chmod +x forkedServer_drone
mv drone_id_$NUM.txt drone_id.txt
mv forkedServer_drone /id-servers
mv drone_id.txt /id-servers