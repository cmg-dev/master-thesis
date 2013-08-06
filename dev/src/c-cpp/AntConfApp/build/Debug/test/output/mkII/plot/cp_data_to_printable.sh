#!/bin/bash

echo "Hello, " $USER "."

#echo -n "Please enter the base-filename you want to copy [ENTER]:"
#read filenamebase
filenamebase=$1

#echo -n "Please name the first file index [ENTER]:"
#read first
first=$2

#echo -n "Last index [ENTER]:"
#read last
last=$3

#echo -n "trial amount [ENTER]:"
#read trials
trials=$4

#echo $1" "$2" "$3" "$4

if [ $5 == "yes" ]
then
    echo "generating single files"
fi

echo "removing ALL old data"
rm data/*.dat*

for (( j=0 ; j < $trials ; j++ ))
do

    fn_out_single="data/"$j.dat
    for (( i=$first ; i < $last ; i++ ))
    do
        fn=../$filenamebase.$j"_"$i.dat

        if [ $5 == "yes" ]
        then
            fn_out="data/"$j"_"$i.dat
            cat $fn | sed 's/(/ /g' | sed 's/,/ /g' | sed 's/)/ /g' | sed '1d' >> $fn_out
        fi

        cat $fn | sed 's/(/ /g' | sed 's/,/ /g' | sed 's/)/ /g' | sed '1d' >> $fn_out_single
        
        echo "" >> $fn_out_single
    done
           echo "Trial "$j" done" 
done
