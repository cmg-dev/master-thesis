#!/bin/bash

rm *.dat
cat ../CMA-ES_wt_mkII_A_0.dat | sed 's/(/ /g' | sed 's/,/ /g' | sed 's/)/ /g' | sed '1d' >> data0.dat
cat ../CMA-ES_wt_mkII_A_1.dat | sed 's/(/ /g' | sed 's/,/ /g' | sed 's/)/ /g' | sed '1d' >> data1.dat
cat ../CMA-ES_wt_mkII_A_2.dat | sed 's/(/ /g' | sed 's/,/ /g' | sed 's/)/ /g' | sed '1d' >> data2.dat
cat ../CMA-ES_wt_mkII_A_3.dat | sed 's/(/ /g' | sed 's/,/ /g' | sed 's/)/ /g' | sed '1d' >> data3.dat
cat ../CMA-ES_wt_mkII_A_4.dat | sed 's/(/ /g' | sed 's/,/ /g' | sed 's/)/ /g' | sed '1d' >> data4.dat
