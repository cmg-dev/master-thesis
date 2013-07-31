#!/bin/bash

echo -n "Please enter the base-filename you want to copy [ENTER]:"
read filenamebase

echo -n "Please enter the output filename [ENTER]:"
read outfilename

echo -n "Please enter total trial amount [ENTER]:"
read trials

for(( i=0; i <= $trials;i++ )) {
    searchfor=$filenamebase"."$i"_"
    out=data/$outfilename"_"$i."dat"
    outtemp=data/$outfilename"_"$i."tmp"

    rm $out;

    #copy all last lines to one single file
    find $searchfor* -type f -exec tail -n1 {} >> $out \;
    
    #process the data stream, remove all (),-tokens
    cat $out | sed 's/(/ /g' | sed 's/,/ /g' | sed 's/)/ /g' >> $outtemp 

    #mv temp file to its real name
    mv $outtemp $out 

    #add line numbers
    sed '/./=' $out | sed '/./N; s/\n/ /' >> $outtemp 

    mv $outtemp $out 

    echo "done see results in: "$out

}
