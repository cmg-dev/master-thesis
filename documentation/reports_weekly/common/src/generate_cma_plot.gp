#prerequesites set i, n and the number of antennas to proper values
if( i == 0 ) set terminal pngcairo enhanced font "arial,10" size 650, 500 

#set key outside center bottom horizontal Right noreverse enhanced nobox 
set key off
set style data filledcurves
set grid

lastDataCol = 3+a+1
inputfile = "data.".i.".dat"
outFitness = "img/fitness.".i.".png"
outObject = "img/objectVar.".i.".png"
outSigma = "img/sigma.".i.".png"

print "Processing: '".inputfile."' >> ".outFitness." + ".outObject." + ".outSigma 

set output outObject

unset logscale y
 
set yrange [-10:10]
set xlabel "Funtion Evaluations"

if( a==9 ) plot inputfile u 1:4 w lines title "x", \
		"" u 1:5 w lines title "y", \
		"" u 1:6 w lines title "z", \
		"" u 1:7 w lines title "n0", \
		"" u 1:8 w lines title "n1", \
		"" u 1:9 w lines title "n2", \
		"" u 1:10 w lines title "n3", \
		"" u 1:11 w lines title "n4", \
		"" u 1:12 w lines title "n5"

if( a==10 ) plot inputfile u 1:4 w lines title "x", \
		"" u 1:5 w lines title "y", \
		"" u 1:6 w lines title "z", \
		"" u 1:7 w lines title "n0", \
		"" u 1:8 w lines title "n1", \
		"" u 1:9 w lines title "n2", \
		"" u 1:10 w lines title "n3", \
		"" u 1:11 w lines title "n4", \
		"" u 1:12 w lines title "n5", \
		"" u 1:13 w lines title "n6"

if( a==7 ) plot inputfile u 1:4 w lines title "x", \
		"" u 1:5  title "y", \
		"" u 1:6  title "z", \
		"" u 1:7 title "n0", \
		"" u 1:8 title "n1", \
		"" u 1:9 title "n2", \
		"" u 1:10 title "n3"

set output outFitness

set autoscale
set logscale y

plot inputfile u 1:2 w lines title "fitness"

set output outSigma

plot inputfile u 1:lastDataCol w lines title "{/Symbol s}"

i=i+1

if (i < n) reread
