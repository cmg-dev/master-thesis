#!/bin/bash

echo "Hello, " $USER "."

echo -n "Please enter the base-filename you want to copy [ENTER]:"
read filenamebase

echo -n "Please name the first file index [ENTER]:"
read first

echo -n "Last index [ENTER]:"
read last

echo "removing ALL old data"
rm data/*.dat

for((i=$first;i<$last;i++))
do
	echo "Processing: '../"$filenamebase$i".dat'" 
	cat ../$filenamebase$i.dat | sed 's/(/ /g' | sed 's/,/ /g' | sed 's/)/ /g' | sed '1d' >> data/$i.dat
done
