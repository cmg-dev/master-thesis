# This scripts use is to generate a plot from the final values of the solutions for one antenna
#
#prerequesites set i, n and the number of antennas to proper values
#

at(file, row, col) = system( sprintf("awk -v row=%d -v col=%d 'NR == row {print $col}' %s", row, col, file) )
to(file, min, first, mean, third, max, row) = system( sprintf("echo %d %e %e %e %e %e >> %s", row, min, first, mean, third, max ,file) )
header(file) = system( sprintf("echo \"#Idx min first mean third max\" >> %s", file) )
toScientific(file, min, first, mean, third, max, row) = system( sprintf("echo %d %e %e %e %e %e >> %s", row, min, first, mean, third, max ,file) )
remove(file) = system( sprintf( "rm %s", file ) )
to2(file, value) = system( sprintf("echo 1 2 3 %s %s", value, file) )
echoStats( min, first, mean, third, max) = system( sprintf("echo %e %e %e %e %e ", min, first, mean, third, max) )

set style line 1 linetype 1 linecolor rgbcolor "#2f4f4f"  linewidth 1.5 pointtype 7 pointsize .5 pointinterval 1 
set style line 2 linetype 1 linecolor rgbcolor "#696969"  linewidth 1.5 pointtype 7 pointsize .5 pointinterval 1 
set style line 3 linetype 1 linecolor rgbcolor "#708090"  linewidth 1.5 pointtype 7 pointsize .5 pointinterval 1 
set style line 4 linetype 1 linecolor rgbcolor "#bebebe"  linewidth 1.5 pointtype 7 pointsize .5 pointinterval 1 
#set style line 1 linetype 1 linecolor rgb "#708090"  linewidth 1.5 pointtype 7 pointsize 1 pointinterval 1 
#set style line 2 linetype -1 linecolor rgb "#2f4f4f"  linewidth 1.2

#set style line 3 linetype 1 linecolor rgb "#ee2f4f4f"  linewidth 1.000 pointtype 7 pointsize 1 pointinterval 1
#set style line 3 linetype 1 linecolor rgb "red"  linewidth 1.000 pointtype 7 pointsize 1 pointinterval 5
#set style line 4 linetype 1 linecolor rgb "gray"  linewidth 1 pointtype 2 pointsize default pointinterval 0

set style arrow 1 heads size screen 0.008,90 ls 2

#if( i == 0 ) set terminal pngcairo enhanced font "arial,10" size 1000, 1000 
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

#print "Processing: Start" 

set output outMultiplot

set multiplot layout 1,3

#collect information about the file
unset logscale
set autoscale
unset label

#-------------------------------------------------------------------------
#setup the 1. plot

#LABEL1 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f ",Xs_mean, Xs_max, Xs_min, Xs_median )
#set label 1 at 1.2,Xs_mean LABEL1 front left font "Arial,7" 

#LABEL2 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f ",Ys_mean, Ys_max, Ys_min, Ys_median )
#set label 2 at 2.2,Ys_mean LABEL2 front left font "Arial,7" 

#LABEL3 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f" ,Zs_mean, Zs_max, Zs_min, Zs_median )
#set label 3 at 3.2,Zs_mean LABEL3 front left font "Arial,7" 

#if(a>3)LABEL4 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f ",N0s_mean, N0s_max, N0s_min, N0s_median )
#if(a>3)set label 4 at 4.2,N0s_mean LABEL4 front left font "Arial,7" 

#if(a>3)LABEL5 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f ",N1s_mean, N1s_max, N1s_min, N1s_median )
#if(a>3)set label 5 at 5.2,N1s_mean LABEL5 front left font "Arial,7" 

#if(a>3)LABEL6 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f ",N2s_mean, N2s_max, N2s_min, N2s_median  )
#if(a>3)set label 6 at 6.2,N2s_mean LABEL6 front left font "Arial,7" 

#if(a>3)LABEL7 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f ",N3s_mean, N3s_max, N3s_min, N3s_median )
#if(a>3)set label 7 at 7.2,N3s_mean LABEL7 front left font "Arial,7" 


#if(a>=8)LABEL8 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f ",N4s_mean, N4s_max, N4s_min, N4s_median )
#if(a>=8)set label 8 at 8.2,N4s_mean LABEL8 front left font "Arial,7"

#if(a>=9)LABEL9 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f ",N5s_mean, N5s_max, N5s_min, N5s_median )
#if(a>=9)set label 9 at 9.2,N5s_mean LABEL9 front left font "Arial,7" 

set style data boxplot
#set boxwidth .2 absolute 
set xlabel "Objective"
set ylabel "Final Value"
set size 1, .6
set origin .0,.4
set autoscale
set xrange [.5:a+1]
set xtics 

set ytics format "%.2e"

if(a==3) plot inputfile u (1):5 ls 1 notitle, \
        '' u (2):6 ls 2 notitle, \
        '' u (3):7 ls 3 notitle


if(a==6) plot inputfile u (1):5 ls 1 notitle, \
        '' u (2):6 ls 2 notitle, \
        '' u (3):7 ls 3 notitle, \
        '' u (4):8 ls 4 notitle, \
        '' u (5):9 ls 4 notitle, \
        '' u (6):10 ls 4 notitle

if(a==7) set xtics ("x" 1, "y" 2, "z" 3, "n0" 4,"n1" 5,"n2" 6,"n3" 7) scale 0.0

if(a==7) plot inputfile u ($2 < limit ? (1): 1/0):5 ls 1 notitle, \
        '' u ($2 < limit ? (2): 1/0):6 ls 2 notitle, \
        '' u ($2 < limit ? (3): 1/0):7 ls 3 notitle, \
        '' u ($2 < limit ? (4): 1/0):8 ls 4 notitle, \
        '' u ($2 < limit ? (5): 1/0):9 ls 4 notitle, \
        '' u ($2 < limit ? (6): 1/0):10 ls 4 notitle, \
        '' u ($2 < limit ? (7): 1/0):11 ls 4 notitle


if(a==8) set xtics ("x" 1, "y" 2, "z" 3, "n0" 4,"n1" 5,"n2" 6,"n3" 7,"n4" 8) scale 0.0

if(a==8) plot inputfile u ($2 < limit ? (1): 1/0):5 ls 1 notitle, \
        '' u ($2 < limit ? (2): 1/0):6 ls 2 notitle, \
        '' u ($2 < limit ? (3): 1/0):7 ls 3 notitle, \
        '' u ($2 < limit ? (4): 1/0):8 ls 4 notitle, \
        '' u ($2 < limit ? (5): 1/0):9 ls 4 notitle, \
        '' u ($2 < limit ? (6): 1/0):10 ls 4 notitle, \
        '' u ($2 < limit ? (7): 1/0):11 ls 4 notitle, \
        '' u ($2 < limit ? (8): 1/0):12 ls 4 notitle

if(a==9) set xtics ("x" 1, "y" 2, "z" 3, "n0" 4,"n1" 5,"n2" 6,"n3" 7,"n4" 8, "N5" 9) scale 0.0

if(a==9) plot inputfile u ($2 < limit ? (1): 1/0):5 ls 1 notitle, \
        '' u ($2 < limit ? (2): 1/0):6 ls 2 notitle, \
        '' u ($2 < limit ? (3): 1/0):7 ls 3 notitle, \
        '' u ($2 < limit ? (4): 1/0):8 ls 4 notitle, \
        '' u ($2 < limit ? (5): 1/0):9 ls 4 notitle, \
        '' u ($2 < limit ? (6): 1/0):10 ls 4 notitle, \
        '' u ($2 < limit ? (7): 1/0):11 ls 4 notitle, \
        '' u ($2 < limit ? (8): 1/0):12 ls 4 notitle, \
        '' u ($2 < limit ? (9): 1/0):12 ls 4 notitle

unset label

#-------------------------------------------------------------------------
#setup the 2. plot

set boxwidth 0.05 relative

set autoscale
set xlabel ""
set logscale y
set ylabel "Evaluations"
set size .25, .4
set origin .0,.0
unset xtics
#set xrange [-.2:.4]
set ytics format "%.1e"

plot inputfile u ($2 < limit ? (1): 1/0):2 ls 4 notitle 

#-------------------------------------------------------------------------
#setup the 3. plot
#unset yrange
set logscale y
set ytics 

set xlabel ""
set ylabel "Function Value"
set size .25, .4
set origin .25,.0
unset xtics
set ytics format "%.1e" 

plot inputfile u ($2 < limit ? (1): 1/0):3 ls 4 notitle 

#-------------------------------------------------------------------------
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

#-------------------------------------------------------------------------
#setup the 5. plot
set xlabel ""
set ylabel "Distance"
set ytics format "%.1e" 

set size .25, .4
set origin .75,.0

set autoscale
unset xtics
set ytics 

plot inputfile u ($2 < limit ? (1): 1/0):vectorCol ls 4 notitle  

#-------------------------------------------------------------------------
i=i+1

unset multiplot
unset xtics

if (i < m) reread
i=0
