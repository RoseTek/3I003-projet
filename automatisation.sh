#!/bin/bash

make re

for fic in $(ls -Sr instances/*)
do
    clear
    echo $fic
    ./Tomo $fic
done
