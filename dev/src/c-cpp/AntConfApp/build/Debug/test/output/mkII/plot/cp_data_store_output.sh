#!/bin/bash

echo "Hello, "$USER"."

echo -n "Please enter the base-filename you want to copy [ENTER]:"
read filenamebase

#echo -n "Please name the first file index [ENTER]:"
#read first

#echo -n "Last index [ENTER]:"
#read last

echo "moving data to archive"
tar -czf $filenamebase/data.tar.gz data 

#for((i=$first;i<$last;i++))
#do
#	echo "Processing: '../"$filenamebase$i".dat'" 
#	cat ../$filenamebase$i.dat | sed 's/(/ /g' | sed 's/,/ /g' | sed 's/)/ /g' | sed '1d' >> data/$i.dat
#done

#cat ../CMA-ES_wt_mkII_A_1.dat | sed 's/(/ /g' | sed 's/,/ /g' | sed 's/)/ /g' | sed '1d' >> data1.dat
#cat ../CMA-ES_wt_mkII_A_2.dat | sed 's/(/ /g' | sed 's/,/ /g' | sed 's/)/ /g' | sed '1d' >> data2.dat
#cat ../CMA-ES_wt_mkII_A_3.dat | sed 's/(/ /g' | sed 's/,/ /g' | sed 's/)/ /g' | sed '1d' >> data3.dat
#cat ../CMA-ES_wt_mkII_A_4.dat | sed 's/(/ /g' | sed 's/,/ /g' | sed 's/)/ /g' | sed '1d' >> data4.dat
