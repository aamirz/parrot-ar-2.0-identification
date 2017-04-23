#!/bin/bash
ID_FILE=$1
#once connect to drone, run this script
curl -T ./forkedServer_drone ftp://root:root@192.168.1.1:5551/
curl -T ./$ID_FILE ftp://root:root@192.168.1.1:5551/