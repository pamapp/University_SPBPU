#!/bin/bash

#echo "Укажите последовательность символов:"
#read str
#
#echo "Укажите имя файла результатов:"
#read filename

echo -e "\nПоиск $1:" >> $2

grep -r -n $1 cat3 >> $2



