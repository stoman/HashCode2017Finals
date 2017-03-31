#! /bin/bash

FILENAME1=$1
FILENAME2=$2

gnuplot -e "datafile='${FILENAME1}';datafile2='${FILENAME2}'; outputname='${FILENAME1}.png'" plot.plg
