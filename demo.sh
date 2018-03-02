#!/bin/bash

make re
make clean

for fic in $(ls -Sr instances/*)
do
    clear
    echo $fic
    ./tomo $fic
done
