#! /bin/bash

FILENAME=$1
FILENAME2=$2

for i in `seq 1 8`;
do
    gnuplot -e "datafile='${FILENAME}_${i}.dat';datafile2='${FILENAME2}';outputname='${FILENAME}_${i}.png'" plotoutput.plg
done
