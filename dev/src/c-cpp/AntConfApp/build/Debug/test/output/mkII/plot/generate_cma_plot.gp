if( i == 0 ) 
	set terminal pngcairo enhanced font "arial,10" size 500, 350 

set key outside center bottom horizontal Right noreverse enhanced nobox 

set grid

inputfile = "data".i.".dat"
outFitness = "img/fitness".i.".png"
outObject = "img/objectVar".i.".png"
outSigma = "img/sigma".i.".png"

#print filename." ".plotfile

set output outObject

unset logscale y
 
set yrange [-10:10]

plot inputfile u 1:4 w lines title "0", \
		"" u 1:5 w lines title "1", \
		"" u 1:6 w lines title "2", \
		"" u 1:7 w lines title "3", \
		"" u 1:8 w lines title "4", \
		"" u 1:9 w lines title "5", \
		"" u 1:10 w lines title "6", \
		"" u 1:11 w lines title "7", \
		"" u 1:12 w lines title "8"

set output outFitness

set autoscale
set logscale y

plot inputfile u 1:2 w lines title "fitness"

set output outSigma

plot inputfile u 1:13 w lines title "$\sigma$"

i=i+1

if (i < n) reread
