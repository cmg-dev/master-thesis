#!/bin/bash

echo "Hello, " $USER "."

#echo -n "Please enter the base-filename you want to copy [ENTER]:"
#read filenamebase
#filenamebase=$1

#echo -n "Please name the first file index [ENTER]:"
#read first
first=$1

#echo -n "Last index [ENTER]:"
#read last
last=$2

#echo -n "trial amount [ENTER]:"
#read trials
trials=$3

configs=$4

echo $1" "$2" "$3" "$4

fn_out_single="VectorStats_"$first"_"$last.dat

rm $fn_out_single

for (( i=0 ; i < $trials ; i++ ))
do
    #
    # The output goes to...
    #
    fn_out_antenna="VectorStats_"$first"_"$last"_A"$i.dat
    rm $fn_out_antenna
done
for (( i=0 ; i < $configs ; i++ ))
do
    #
    # The output goes to...
    #
    fn_out_antenna="VectorStats_"$first"_"$last"_C"$i.dat
    rm $fn_out_antenna
done

k=0
l=0
m=0
n=0
for (( j=$first ; j < $last ; j++ ))
do
    fn_out_configuration="VectorStats_"$first"_"$last"_C"$l.dat
    for (( i=0 ; i < $trials ; i++ ))
    do
        #
        # The output goes to...
        #
        fn_out_antenna="VectorStats_"$first"_"$last"_A"$i.dat
       
        #
        # This will use median values as inputs
        #
        fn=$j/data/VectorStatsMedian$i.dat

        #
        # if you want to use mean values uncomment this
        #
        #fn=$j/data/VectorStats$i.dat

        echo -n $j $m $l $k $i $n "">> $fn_out_single
        echo -n $j $m $l $k $i $n "">> $fn_out_antenna
        echo -n $j $m $l $k $i $n "">> $fn_out_configuration
        k=$((k+1))

        #fn_out=$j/data/VectorStats"_"$i.dat
        cat $fn | sed '1d' >> $fn_out_single
        cat $fn | sed '1d' >> $fn_out_antenna
        cat $fn | sed '1d' >> $fn_out_configuration

    done
    l=$((l+1))
    m=$((m+1))
    if (( l >= $configs ))
    then
        l=0
        n=$((n+1))

    fi
    #echo Data $j done
done

