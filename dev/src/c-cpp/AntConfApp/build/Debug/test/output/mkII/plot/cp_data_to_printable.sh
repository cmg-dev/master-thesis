#!/bin/bash

echo "Hello, " $USER "."

echo -n "Please enter the base-filename you want to copy [ENTER]:"
read filenamebase

echo -n "Please name the first file index [ENTER]:"
read first

echo -n "Last index [ENTER]:"
read last

echo -n "trial amount [ENTER]:"
read trials

echo "removing ALL old data"

for (( j=0 ; j < $trials ; j++ ))
do

    fn_out_single="data/"$j.dat
    for (( i=$first ; i < $last ; i++ ))
    do
        fn=../$filenamebase.$j"_"$i.dat
        fn_out="data/"$j"_"$i.dat
        rm $fn_out
	    cat $fn | sed 's/(/ /g' | sed 's/,/ /g' | sed 's/)/ /g' | sed '1d' >> $fn_out
         
	    cat $fn | sed 's/(/ /g' | sed 's/,/ /g' | sed 's/)/ /g' | sed '1d' >> $fn_out_single
        echo "" >> $fn_out_single
    done
	    echo "Trial "$j" done" 
done
