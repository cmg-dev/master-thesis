set style line 1 linetype 1 linecolor rgbcolor "#2f4f4f"  linewidth 1.5 pointtype 7 pointsize .5 pointinterval 1 
set style line 2 linetype 1 linecolor rgbcolor "#696969"  linewidth 1.5 pointtype 7 pointsize .5 pointinterval 1 
set style line 3 linetype 1 linecolor rgbcolor "#708090"  linewidth 1.5 pointtype 7 pointsize .5 pointinterval 1 
set style line 4 linetype 1 linecolor rgbcolor "#bebebe"  linewidth 1.5 pointtype 7 pointsize .5 pointinterval 1 

if( i == 0 ) set terminal pngcairo truecolor transparent background "#ffffff" enhanced font "arial,10" size w, h 

set style fill transparent solid 0.3 noborder
#set style boxplot outliers pointtype 19
#set style data boxplot
#set key right bottom vertical Left noreverse enhanced box samplen .2 
#set key opaque
set grid

#in this column we find the Data for sigma
lastDataCol = 3+a+2
#int this column we expect the vector
vectorCol = 3+a+3
inputfile = "data/single_".i.".dat"
outMultiplot = "img/boxen/kondensiert/".i.".png"

set output outMultiplot
set multiplot layout 1,3
unset logscale
set autoscale
unset label

#----------------------------------------------
#setup the 1. plot
set style data boxplot
set xlabel "Optimzation objective"
set ylabel "Final Value - Coordinates ( x, y, z )"
 
set size 1, .6
set origin .0,.4
set autoscale
set xrange [.5:a+.5]
set xtics 

set ytics format "%.1f"
set yrange [-4:4]
if(a>3) set y2tics format "%.1f"
if(a>3) set y2label "Final Value - Wavenumbers ( n )"

print "a=",a
if(a==7) set xtics ("x" 1, "y" 2, "z" 3 ) scale 0.0
if(a==3) plot inputfile u (1):5 ls 1 axes x1y1 notitle, \
        '' u (2):6 ls 2 axes x1y1 notitle, \
        '' u (3):7 ls 3 axes x1y1 notitle
if(a==3) unset y2tics
if(a==3) unset y2label

if(a==6) plot inputfile u (1):5 ls 1 notitle, \
        '' u (2):6 ls 2 notitle, \
        '' u (3):7 ls 3 notitle, \
        '' u (4):8 ls 4 notitle, \
        '' u (5):9 ls 4 notitle, \
        '' u (6):10 ls 4 notitle

if(a==7) set xtics ("x" 1, "y" 2, "z" 3, "n0" 4,"n1" 5,"n2" 6,"n3" 7) scale 0.0

if(a==7) plot inputfile u ($2 < limit ? (1): 1/0):5 ls 1 axes x1y1 notitle, \
        '' u ($2 < limit ? (2): 1/0):6 ls 2 axes x1y1 notitle, \
        '' u ($2 < limit ? (3): 1/0):7 ls 3 axes x1y1 notitle, \
        '' u ($2 < limit ? (4): 1/0):8 ls 4 axes x1y2 notitle, \
        '' u ($2 < limit ? (5): 1/0):9 ls 4 axes x1y2 notitle, \
        '' u ($2 < limit ? (6): 1/0):10 ls 4 axes x1y2 notitle, \
        '' u ($2 < limit ? (7): 1/0):11 ls 4 axes x1y2 notitle


if(a==8) set xtics ("x" 1, "y" 2, "z" 3, "n0" 4,"n1" 5,"n2" 6,"n3" 7,"n4" 8) scale 0.0

if(a==8) plot inputfile u ($2 < limit ? (1): 1/0):5 ls 1 axes x1y1 notitle, \
        '' u ($2 < limit ? (2): 1/0):6 ls 2 axes x1y1 notitle, \
        '' u ($2 < limit ? (3): 1/0):7 ls 3 axes x1y1 notitle, \
        '' u ($2 < limit ? (4): 1/0):8 ls 4 axes x1y2 notitle, \
        '' u ($2 < limit ? (5): 1/0):9 ls 4 axes x1y2 notitle, \
        '' u ($2 < limit ? (6): 1/0):10 ls 4 axes x1y2 notitle, \
        '' u ($2 < limit ? (7): 1/0):11 ls 4 axes x1y2 notitle, \
        '' u ($2 < limit ? (8): 1/0):12 ls 4 axes x1y2 notitle

if(a==9) set xtics ("x" 1, "y" 2, "z" 3, "n0" 4,"n1" 5,"n2" 6,"n3" 7,"n4" 8, "N5" 9) scale 0.0

if(a==9) plot inputfile u ($2 < limit ? (1): 1/0):5 ls 1 axes x1y1 notitle, \
        '' u ($2 < limit ? (2): 1/0):6 ls 2 axes x1y1 notitle, \
        '' u ($2 < limit ? (3): 1/0):7 ls 3 axes x1y1 notitle, \
        '' u ($2 < limit ? (4): 1/0):8 ls 4 axes x1y2 notitle, \
        '' u ($2 < limit ? (5): 1/0):9 ls 4 axes x1y2 notitle, \
        '' u ($2 < limit ? (6): 1/0):10 ls 4 axes x1y2 notitle, \
        '' u ($2 < limit ? (7): 1/0):11 ls 4 axes x1y2 notitle, \
        '' u ($2 < limit ? (8): 1/0):12 ls 4 axes x1y2 notitle, \
        '' u ($2 < limit ? (9): 1/0):12 ls 4 axes x1y2 notitle

if(a==10) set xtics ("x" 1, "y" 2, "z" 3, "n0" 4,"n1" 5,"n2" 6,"n3" 7,"n4" 8, "N5" 9, "N6" 10) scale 0.0

if(a==10) plot inputfile u ($2 < limit ? (1): 1/0):5 ls 1 axes x1y1 notitle, \
        '' u ($2 < limit ? (2): 1/0):6 ls 2 axes x1y1 notitle, \
        '' u ($2 < limit ? (3): 1/0):7 ls 3 axes x1y1 notitle, \
        '' u ($2 < limit ? (4): 1/0):8 ls 4 axes x1y2 notitle, \
        '' u ($2 < limit ? (5): 1/0):9 ls 4 axes x1y2 notitle, \
        '' u ($2 < limit ? (6): 1/0):10 ls 4 axes x1y2 notitle, \
        '' u ($2 < limit ? (7): 1/0):11 ls 4 axes x1y2 notitle, \
        '' u ($2 < limit ? (8): 1/0):12 ls 4 axes x1y2 notitle, \
        '' u ($2 < limit ? (9): 1/0):12 ls 4 axes x1y2 notitle, \
        '' u ($2 < limit ? (10): 1/0):12 ls 4 axes x1y2 notitle

if(a==11) set xtics ("x" 1, "y" 2, "z" 3, "n0" 4,"n1" 5,"n2" 6,"n3" 7,"n4" 8, "N5" 9, "N6" 10, "N7" 11) scale 0.0

if(a==11) plot inputfile u ($2 < limit ? (1): 1/0):5 ls 1 axes x1y1 notitle, \
        '' u ($2 < limit ? (2): 1/0):6 ls 2 axes x1y1 notitle, \
        '' u ($2 < limit ? (3): 1/0):7 ls 3 axes x1y1 notitle, \
        '' u ($2 < limit ? (4): 1/0):8 ls 4 axes x1y2 notitle, \
        '' u ($2 < limit ? (5): 1/0):9 ls 4 axes x1y2 notitle, \
        '' u ($2 < limit ? (6): 1/0):10 ls 4 axes x1y2 notitle, \
        '' u ($2 < limit ? (7): 1/0):11 ls 4 axes x1y2 notitle, \
        '' u ($2 < limit ? (8): 1/0):12 ls 4 axes x1y2 notitle, \
        '' u ($2 < limit ? (9): 1/0):12 ls 4 axes x1y2 notitle, \
        '' u ($2 < limit ? (10): 1/0):12 ls 4 axes x1y2 notitle, \
        '' u ($2 < limit ? (11): 1/0):12 ls 4 axes x1y2 notitle
unset label
unset y2label
unset y2range
unset y2tics

#----------------------------------------------
#setup the 2. plot

set boxwidth 0.05 relative

set autoscale
set xlabel ""
#set logscale y
set ylabel "Evaluations"
set size .25, .4
set origin .0,.0
unset xtics
#set xrange [-.2:.4]
set ytics format "%.1e"

plot inputfile u ($2 < limit ? (1): 1/0):2 ls 4 notitle 

#----------------------------------------------
#setup the 3. plot
#set logscale y
set ytics 

set xlabel ""
set ylabel "Function Value"
set size .25, .4
set origin .25,.0
unset xtics
set ytics format "%.1e" 

plot inputfile u ($2 < limit ? (1): 1/0):3 ls 4 notitle 

#----------------------------------------------
#setup the 4. plot
set xlabel ""
set ylabel "Sigma"
set ytics format "%.1e" 

set size .25, .4
set origin .50,.0

unset logscale
set autoscale
unset xtics
set ytics 

plot inputfile u ($2 < limit ? (1): 1/0):lastDataCol ls 4 notitle 

#----------------------------------------------
#setup the 5. plot
set xlabel ""
set ylabel "Distance"
set ytics format "%.2e" 

set size .25, .4
set origin .75,.0

set autoscale
unset xtics
set ytics 

plot inputfile u ($2 < limit ? (1): 1/0):vectorCol ls 4 notitle  

#----------------------------------------------
i=i+1

unset multiplot
unset xtics

if (i < m) reread
i=0
