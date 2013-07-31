#prerequesites set i, n and the number of antennas to proper values
at(file, row, col) = system( sprintf("awk -v row=%d -v col=%d 'NR == row {print $col}' %s", row, col, file) )

set style line 1 linetype 1 linecolor rgb "blue"  linewidth 1.000 pointtype 7 pointsize .2 pointinterval 10
set style line 2 linetype 1 linecolor rgb "green"  linewidth 1.000 pointtype 7 pointsize .2 pointinterval 10
set style line 3 linetype 1 linecolor rgb "red"  linewidth 1.000 pointtype 7 pointsize .2 pointinterval 10
set style line 4 linetype 1 linecolor rgb "gray"  linewidth 1 pointtype 2 pointsize default pointinterval 0

if( i == 0 ) set terminal pngcairo enhanced font "arial,10" size 1000, 800 
#if( i == 0 ) set term png small

set key right bottom vertical Left noreverse enhanced box samplen .2 
set key opaque
set grid

lastDataCol = 3+a+1
inputfile = "data/".i.".dat"
#outFitness = "img/fitness.".j."_".i.".png"
#outObject = "img/objectVar.".j."_".i.".png"
#outSigma = "img/sigma.".j."_".i.".png"
outMultiplot = "img/AllInOne.".i.".png"

#print "Processing: '".inputfile."' >> ".outFitness." + ".outObject." + ".outSigma 

file=inputfile ; row=2 ; col=2

set output outMultiplot

set multiplot layout 1,3

#set output outObject

#collect information about the file
unset logscale
set autoscale

#-------------------------------------------------------------------------
stats inputfile u 1 name "Stat" nooutput

#print "test ".at(file,Stat_records,1)

#setup the first plot
#set yrange [-10:10]
set xlabel "Funtion Evaluations"
set ylabel "Objective Values"
set size 1., .6
set origin .0,.4

if( a==9 ) plot inputfile u 1:4 w lines title "x", \
		"" u 1:5 w lines title "($5-STATS_records)=y", \
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

if( a==7 ) plot inputfile u 1:4 w lines title "x = ".at(file,Stat_records,4) ls 1 , \
		"" u 1:5 w lines title "y = ".at(file,Stat_records,5) ls 2, \
		"" u 1:6 w lines title "z = ".at(file,Stat_records,6) ls 3, \
		"" u 1:7 w lines title "n0 = ".at(file,Stat_records,7) ls 4, \
		"" u 1:8 w lines title "n1 = ".at(file,Stat_records,8) ls 4, \
		"" u 1:9 w lines title "n2 = ".at(file,Stat_records,9) ls 4, \
		"" u 1:10 w lines title "n3 = ".at(file,Stat_records,10) ls 4

#set output outFitness
set autoscale

set logscale y
set xlabel ""
set ylabel "Fitness"

set size .5, .4
set yrange [1e-25:20000]
set origin .0,.0
plot inputfile u 1:2 w lines title "fitness"

#set output outSigma

set size .5, .4
set origin .5,.0
set yrange [1e-10:2]
set ylabel "Sigma"

plot inputfile u 1:lastDataCol w lines title "{/Symbol s}"

i=i+1

unset multiplot

if (i < n) reread
i=0

