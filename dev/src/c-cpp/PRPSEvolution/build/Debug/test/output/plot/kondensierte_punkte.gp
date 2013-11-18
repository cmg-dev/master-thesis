#prerequesites set i, n and the number of antennas to proper values
at(file, row, col) = system( sprintf("awk -v row=%d -v col=%d 'NR == row {print $col}' %s", row, col, file) )

set style line 3 linetype 1 linecolor rgb "#2f4f4f"  linewidth 1.000 pointtype 11 pointsize 1 
set style line 2 linetype 1 linecolor rgb "#696969"  linewidth 1.000 pointtype 13 pointsize 1
set style line 1 linetype 1 linecolor rgb "#708090"  linewidth 1.000 pointtype 9 pointsize 1
set style line 4 linetype 1 linecolor rgb "#bebebe"  linewidth 1 pointtype 4 pointsize .8 

set style line 5 linetype 2 linecolor rgb "#bebebe"  linewidth 1.000 pointtype 4 pointsize 1

set style line 6 linetype 1 linecolor rgb "#bebebe"  linewidth 1.000 pointtype 4 pointsize 1
set style line 7 linetype 1 linecolor rgb "#bebebe"  linewidth 1.000 pointtype 6 pointsize 1
set style line 8 linetype 1 linecolor rgb "#bebebe"  linewidth 1.000 pointtype 8 pointsize 1
set style line 9 linetype 1 linecolor rgb "#bebebe"  linewidth 1.000 pointtype 10 pointsize 1
set style line 10 linetype 1 linecolor rgb "#8B8B8B"  linewidth 1.000 pointtype 12 pointsize 1
set style line 11 linetype 1 linecolor rgb "#8B8B8B"  linewidth 1.000 pointtype 14 pointsize 1

if( i == 0 ) set terminal pngcairo enhanced font "arial,10" size h, w 
#if( i == 0 ) set term png small

set key right top vertical Left noreverse enhanced box samplen .2 
set key opaque
set grid

lastDataCol = 3+a+2
inputfile = "data/single_".i.".dat"
outFitness = "img/fitness.".j."_".i.".png"
outObject = "img/objectVar.".j."_".i.".png"
outSigma = "img/sigma.".j."_".i.".png"
outMultiplot = "img/punkte/kondensiert/".j."_".i.".png"

print "Processing: '".inputfile."' >> ".outMultiplot

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
set xlabel "Trial"
set ylabel "Final Objective Values"
set size 1., .6
set origin .0,.4

unset label

if( a==8 ) plot inputfile u 1:8 w points title "n0" ls 4, \
               "" u 1:9 title "n1" ls 6, \
               "" u 1:10 title "n2" ls 7, \
               "" u 1:11 title "n3" ls 8, \
               "" u 1:12 title "n4" ls 9, \
               "" u 1:5 title "x" ls 1, \
               "" u 1:6 title "y" ls 2, \
               "" u 1:7 title "z" ls 3

if( a==9 ) plot inputfile u 1:8 w points title "n0" ls 4, \
               "" u 1:9 title "n1" ls 6, \
               "" u 1:10 title "n2" ls 7, \
               "" u 1:11 title "n3" ls 8, \
               "" u 1:12 title "n4" ls 9, \
               "" u 1:13 title "n5" ls 10, \
               "" u 1:5 title "x" ls 1, \
               "" u 1:6 title "y" ls 2, \
               "" u 1:7 title "z" ls 3

if( a==10 ) plot inputfile u 1:4 w points title "x", \
		"" u 1:5 title "y", \
		"" u 1:6 title "z", \
		"" u 1:7 title "n0", \
		"" u 1:8 title "n1", \
		"" u 1:9 title "n2", \
		"" u 1:10 title "n3", \
		"" u 1:11 title "n4", \
		"" u 1:12 title "n5", \
		"" u 1:13 title "n6"

if( a==7 ) plot inputfile u 1:4 w points title "x" ls 1 , \
		"" u 1:5 title "y" ls 2, \
		"" u 1:6 title "z" ls 3, \
		"" u 1:7 title "n0" ls 4, \
		"" u 1:8 title "n1" ls 4, \
		"" u 1:9 title "n2" ls 4, \
		"" u 1:10 title "n3" ls 4

#set output outFitness
set autoscale

set logscale y
set xlabel ""
set ylabel "Fitness"

set size .5, .4
#set yrange [1e-25:20000]
set origin .5,.0
set ytics format "%.2e"
set origin .0,.0
plot inputfile u 1:3 w linespoints title "fitness" ls 5

#set output outSigma

set size .5, .4
set origin .5,.0
set autoscale
#set yrange [1e-10:2]
set ytics format "%.2e"
set ylabel "Sigma"

plot inputfile u 1:lastDataCol w linespoints title "{/Symbol s}" ls 5

i=i+1

unset multiplot

if (i < m) reread
i=0
