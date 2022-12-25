#!/bin/b

while true
do
    if [[ $(ps -o stat= -p $$) =~ "+" ]]
    then
        echo "Foreground...";
        read a;
        if [ $a == "something" ]
        then
            echo "You print: $a";
            break;
        else
            sleep 3;
        fi;
    else
        echo "Backgroung...";
            sleep 10;
    fi;
done

echo "Done";
