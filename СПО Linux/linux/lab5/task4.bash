#!/bin/bash

cd archive_files

zip -r -q $1 $2/
sleep $3
unzip -q $1 -d ./..
#rm $1

