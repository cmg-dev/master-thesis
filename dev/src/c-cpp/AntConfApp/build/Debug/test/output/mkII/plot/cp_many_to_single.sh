#!/bin/bash

echo -n "Please enter the base-filename you want to copy [ENTER]:"
read filenamebase

echo -n "Please enter the output filename [ENTER]:"
read outfilename

rm data/$outfilename;

#copy all last lines to one single file
find $filenamebase* -exec tail -n1 {} >> data/$outfilename \;

echo "Processing: '../"$filenamebase$i".dat'"

#process the data stream, remove all (),-tokens
cat data/$outfilename | sed 's/(/ /g' | sed 's/,/ /g' | sed 's/)/ /g' >> data/outfilename_processed.tmp

#mv temp file to its real name
mv data/outfilename_processed.tmp data/$outfilename

#add line numbers
sed '/./=' data/$outfilename | sed '/./N; s/\n/ /' >> data/outfilename_processed.tmp

mv data/outfilename_processed.tmp data/$outfilename

echo "done see results in: data/"$outfilename
