#!/bin/bash

echo "Hello, "$USER"."

#echo -n "Please enter the filename of the data you want to copy [ENTER]:"
#read filenamebase

#echo -n "Please enter the name of the experiment [ENTER]:"
#read experiment
experiment=$1

#f1=$filenamebase"_data".tar.gz
#f2=$experiment"_img".tar.gz

f1="data.tar.gz"
f2="img.tar.gz"

echo "moving data to archive"
tar -czf $f1 data/$Experiment*

echo "moving images to archive"
tar -czf $f2 img

tar -czf store/$experiment.tar.gz $f1 $f2
tar -czf store/$experiment.tar.gz data/$Experiment* img *Stats.dat

#tar -cjf store/$experiment.tar.gz2 $f1 $f2

rm $f1
rm $f2

