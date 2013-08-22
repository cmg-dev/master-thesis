#prerequesites set i, n and the number of antennas to proper values
at(file, row, col) = system( sprintf("awk -v row=%d -v col=%d 'NR == row {print $col}' %s", row, col, file) )

set style line 1 linetype 1 linecolor rgbcolor "#882f4f4f"  linewidth .5 
set style line 2 linetype 1 linecolor rgbcolor "#88696969"  linewidth .5 
set style line 3 linetype 1 linecolor rgbcolor "#88708090"  linewidth .5
set style line 4 linetype 1 linecolor rgbcolor "#ccbebebe"  linewidth .5

set style line 5 linetype 1 linecolor rgbcolor "#99696969"  linewidth .3

if( i == 0 ) set terminal pngcairo truecolor transparent background "#ffffff" enhanced font "arial,10" size w, h 
#if( i == 0 ) set term png small

set key right bottom vertical Left noreverse enhanced box samplen .2 
set key opaque
set grid

lastDataCol = 3+a+2
inputfile = "data/".i.".dat"
#outFitness = "img/fitness.".j."_".i.".png"
#outObject = "img/objectVar.".j."_".i.".png"
#outSigma = "img/sigma.".j."_".i.".png"
outMultiplot = "img/linien/kondensiert/".i.".png"

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

locallimit=0.5*limit
#setup the first plot
set xrange [0:locallimit]
set autoscale
set clip one
set xlabel "Funtion Evaluations"
set ylabel "Objective Values"
set xtics
set ytics
set size 1., .6
set origin .0,.4


#print "local locallimit ",locallimit

if( a==3 ) plot inputfile u ($1 < locallimit ? $1 : 1/0):4 w lines title "x" ls 1, \
		"" u ($1 < locallimit ? $1 : 1/0):5 w lines title "y" ls 2, \
		"" u ($1 < locallimit ? $1 : 1/0):6 w lines title "z" ls 3

if( a==7 ) plot inputfile u ($1 < locallimit ? $1 : 1/0):4 w lines title "x" ls 1 , \
		"" u ($1 < locallimit ? $1 : 1/0):5 w lines title "y" ls 2, \
		"" u ($1 < locallimit ? $1 : 1/0):6 w lines title "z" ls 3, \
		"" u ($1 < locallimit ? $1 : 1/0):7 w lines title "n0" ls 4, \
		"" u ($1 < locallimit ? $1 : 1/0):8 w lines title "n1" ls 4, \
		"" u ($1 < locallimit ? $1 : 1/0):9 w lines title "n2" ls 4, \
		"" u ($1 < locallimit ? $1 : 1/0):10 w lines title "n3" ls 4

if( a==8 ) plot inputfile u ($1 < locallimit  ? $1 : 1/0):7 w lines title "n0" ls 4, \
		"" u ($1 < locallimit  ? $1 : 1/0):8 w lines title "n1" ls 4, \
		"" u ($1 < locallimit  ? $1 : 1/0):9 w lines title "n2" ls 4, \
		"" u ($1 < locallimit  ? $1 : 1/0):10 w lines title "n3" ls 4, \
		"" u ($1 < locallimit  ? $1 : 1/0):11 w lines title "n4" ls 4, \
        "" u ($1 < locallimit  ? $1 : 1/0):4 w lines title "x" ls 1, \
		"" u ($1 < locallimit  ? $1 : 1/0):5 w lines title "y" ls 2, \
		"" u ($1 < locallimit  ? $1 : 1/0):6 w lines title "z" ls 3

if( a==9 ) plot inputfile u ($1 < locallimit  ? $1 : 1/0):7 w lines title "n0" ls 4, \
		"" u ($1 < locallimit  ? $1 : 1/0):8 w lines title "n1" ls 4, \
		"" u ($1 < locallimit  ? $1 : 1/0):9 w lines title "n2" ls 4, \
		"" u ($1 < locallimit  ? $1 : 1/0):10 w lines title "n3" ls 4, \
		"" u ($1 < locallimit  ? $1 : 1/0):11 w lines title "n4" ls 4, \
		"" u ($1 < locallimit  ? $1 : 1/0):12 w lines title "n5" ls 4, \
        "" u($1 < locallimit  ? $1 : 1/0):4 w lines title "x" ls 1, \
		"" u ($1 < locallimit  ? $1 : 1/0):5 w lines title "y" ls 2, \
		"" u ($1 < locallimit  ? $1 : 1/0):6 w lines title "z" ls 3
		 
if( a==10 ) plot inputfile u ($1 < locallimit  ? $1 : 1/0):7 w lines title "n0" ls 4, \
		"" u ($1 < locallimit  ? $1 : 1/0):8 w lines title "n1" ls 4, \
		"" u ($1 < locallimit  ? $1 : 1/0):9 w lines title "n2" ls 4, \
		"" u ($1 < locallimit  ? $1 : 1/0):10 w lines title "n3" ls 4, \
		"" u ($1 < locallimit  ? $1 : 1/0):11 w lines title "n4" ls 4, \
		"" u ($1 < locallimit  ? $1 : 1/0):12 w lines title "n5" ls 4, \
		"" u ($1 < locallimit  ? $1 : 1/0):13 w lines title "n6" ls 4, \
        "" u ($1 < locallimit  ? $1 : 1/0):4 w lines title "x" ls 1, \
		"" u ($1 < locallimit  ? $1 : 1/0):5 w lines title "y" ls 2, \
		"" u ($1 < locallimit  ? $1 : 1/0):6 w lines title "z" ls 3

if( a==11 ) plot inputfile u ($1 < locallimit  ? $1 : 1/0):7 w lines title "n0" ls 4, \
		"" u ($1 < locallimit  ? $1 : 1/0):8 w lines title "n1" ls 4, \
		"" u ($1 < locallimit  ? $1 : 1/0):9 w lines title "n2" ls 4, \
		"" u ($1 < locallimit  ? $1 : 1/0):10 w lines title "n3" ls 4, \
		"" u ($1 < locallimit  ? $1 : 1/0):11 w lines title "n4" ls 4, \
		"" u ($1 < locallimit  ? $1 : 1/0):12 w lines title "n5" ls 4, \
		"" u ($1 < locallimit  ? $1 : 1/0):13 w lines title "n6" ls 4, \
		"" u ($1 < locallimit  ? $1 : 1/0):14 w lines title "n7" ls 4, \
        "" u($1 < locallimit  ? $1 : 1/0):4 w lines title "x" ls 1, \
		"" u ($1 < locallimit  ? $1 : 1/0):5 w lines title "y" ls 2, \
		"" u ($1 < locallimit  ? $1 : 1/0):6 w lines title "z" ls 3

set autoscale

set logscale y
set xlabel ""
set ylabel "Fitness"
set size .5, .4
set yrange [1e-25:20000]
set origin .0,.0
plot inputfile u ($1 < locallimit  ? $1 : 1/0):2 w lines ls 5 title "fitness"

set size .5, .4
set origin .5,.0
set autoscale
#set yrange [1e-10:2]
#set xrange [0:3500]
#set clip one
set ylabel "Sigma"

plot inputfile u ($1 < locallimit  ? $1 : 1/0):lastDataCol w lines ls 5 title "{/Symbol s}"

i=i+1

unset multiplot

if (i < m) reread
i=0

