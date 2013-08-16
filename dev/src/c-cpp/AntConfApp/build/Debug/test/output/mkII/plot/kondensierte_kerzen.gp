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

set style line 1 linetype 1 linecolor rgb "#708090"  linewidth 1.5
set style line 2 linetype -1 linecolor rgb "#2f4f4f"  linewidth 1.2

set style line 3 linetype 1 linecolor rgb "#ee2f4f4f"  linewidth 1.000 pointtype 7 pointsize 1 pointinterval 1
#set style line 3 linetype 1 linecolor rgb "red"  linewidth 1.000 pointtype 7 pointsize 1 pointinterval 5
#set style line 4 linetype 1 linecolor rgb "gray"  linewidth 1 pointtype 2 pointsize default pointinterval 0

set style arrow 1 heads size screen 0.008,90 ls 2

#if( i == 0 ) set terminal pngcairo enhanced font "arial,10" size 1000, 1000 
if( i == 0 ) set terminal pngcairo truecolor transparent background "#ffffff" enhanced font "arial,10" size w, h 

set style fill transparent solid 0.3 noborder
#set style boxplot outliers pointtype 19
#set style data boxplot
set key right bottom vertical Left noreverse enhanced box samplen .2 
set key opaque
set grid

#in this column we find the Data for sigma
lastDataCol = 3+a+2
#int this column we expect the vector
vectorCol = 3+a+3
inputfile = "data/single_".i.".dat"
outMultiplot = "img/kerzen/kondensiert/".i.".png"

#print "Processing: Start" 
#print " Limit is: ".limit 

set output outMultiplot

set multiplot layout 1,3

#collect information about the file
unset logscale
set autoscale

#-------------------------------------------------------------------------
#- Gather relevant information via stats ---------------------------------
#-------------------------------------------------------------------------
stats inputfile u 2 name "Counts" nooutput

# notice: The fitness may be normalized to be shown correctly. Values below e-14 can no be processed correctly
stats inputfile u 3 name "Fitness" nooutput 

stats inputfile u 5 name "Xs" nooutput
stats inputfile u 6 name "Ys" nooutput
stats inputfile u 7 name "Zs" nooutput

if(a>3)stats inputfile u 8 name "N0s" nooutput
if(a>3)stats inputfile u 9 name "N1s" nooutput
if(a>3)stats inputfile u 10 name "N2s" nooutput
if(a>3)stats inputfile u 11 name "N3s" nooutput
if(a>=8) stats inputfile u 12 name "N4s" nooutput 
if(a>=9) stats inputfile u 13 name "N5s" nooutput   
if(a==10) stats inputfile u 14 name "N6s" nooutput
if(a==11) stats inputfile u 15 name "N7s" nooutput

stats inputfile u lastDataCol name "Sigmas" nooutput
stats inputfile u vectorCol name "Vectors" nooutput

#-------------------------------------------------------------------------
#-------------------------------------------------------------------------
#1
EvalOut = "EvaluationStats.dat"

print "rm ".EvalOut.remove( EvalOut )
print "wr head".header( EvalOut )
print "wr ".to( EvalOut, Counts_min, Counts_lo_quartile, Counts_mean, Counts_up_quartile, Counts_max, 0)

#2
FitnessOut = "FitnessStats.dat"

print "rm ".FitnessOut.remove( FitnessOut)
print "wr head".header( FitnessOut )
print "wr".to( FitnessOut, Fitness_min, Fitness_lo_quartile, Fitness_mean, Fitness_up_quartile, Fitness_max, 0)

#3
ObjectiveOut = "ObjectivStats.dat"

print "rm ".ObjectiveOut.remove( ObjectiveOut )
print "wr head".header( ObjectiveOut )
print "wr ".to( ObjectiveOut, Xs_min, Xs_lo_quartile, Xs_mean, Xs_up_quartile, Xs_max, 1)
print "  *".to( ObjectiveOut, Ys_min, Ys_lo_quartile, Ys_mean, Ys_up_quartile, Ys_max, 2)
print "  *".to( ObjectiveOut, Zs_min, Zs_lo_quartile, Zs_mean, Zs_up_quartile, Zs_max, 3)
if(a>3)print "  *".to( ObjectiveOut, N0s_min, N0s_lo_quartile, N0s_mean, N0s_up_quartile, N0s_max, 4)
if(a>3)print "  *".to( ObjectiveOut, N1s_min, N1s_lo_quartile, N1s_mean, N1s_up_quartile, N1s_max, 5)
if(a>3)print "  *".to( ObjectiveOut, N2s_min, N2s_lo_quartile, N2s_mean, N2s_up_quartile, N2s_max, 6)
if(a>3)print "  *".to( ObjectiveOut, N3s_min, N3s_lo_quartile, N3s_mean, N3s_up_quartile, N3s_max, 7)

if(a>=8) print "  *".to( ObjectiveOut, N4s_min, N4s_lo_quartile, N4s_mean, N4s_up_quartile, N4s_max, 8)
if(a>=9) print "  *".to( ObjectiveOut, N5s_min, N5s_lo_quartile, N5s_mean, N5s_up_quartile, N5s_max, 9)

stats ObjectiveOut u 5 name "Objective" nooutput

#4
SigmaOut = "SigmaStats.dat"

print "rm ".SigmaOut.remove( SigmaOut )
print "wr head".header( SigmaOut )
print "wr".to( SigmaOut, Sigmas_min, Sigmas_lo_quartile, Sigmas_mean, Sigmas_up_quartile, Sigmas_max, 0)

#5
VectorOut = "VectorStats.dat"

print "rm ".VectorOut.remove( VectorOut )
print "wr head".header( VectorOut )
print "wr".to( VectorOut, Vectors_min, Vectors_lo_quartile, Vectors_mean, Vectors_up_quartile, Vectors_max, 0)

unset label

#-------------------------------------------------------------------------
#setup the 1. plot

LABEL1 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f ",Xs_mean, Xs_max, Xs_min, Xs_median )
set label 1 at 1.2,Xs_mean LABEL1 front left font "Arial,7" 

LABEL2 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f ",Ys_mean, Ys_max, Ys_min, Ys_median )
set label 2 at 2.2,Ys_mean LABEL2 front left font "Arial,7" 

LABEL3 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f" ,Zs_mean, Zs_max, Zs_min, Zs_median )
set label 3 at 3.2,Zs_mean LABEL3 front left font "Arial,7" 

if(a>3)LABEL4 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f ",N0s_mean, N0s_max, N0s_min, N0s_median )
if(a>3)set label 4 at 4.2,N0s_mean LABEL4 front left font "Arial,7" 

if(a>3)LABEL5 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f ",N1s_mean, N1s_max, N1s_min, N1s_median )
if(a>3)set label 5 at 5.2,N1s_mean LABEL5 front left font "Arial,7" 

if(a>3)LABEL6 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f ",N2s_mean, N2s_max, N2s_min, N2s_median  )
if(a>3)set label 6 at 6.2,N2s_mean LABEL6 front left font "Arial,7" 

if(a>3)LABEL7 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f ",N3s_mean, N3s_max, N3s_min, N3s_median )
if(a>3)set label 7 at 7.2,N3s_mean LABEL7 front left font "Arial,7" 


if(a>=8)LABEL8 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f ",N4s_mean, N4s_max, N4s_min, N4s_median )
if(a>=8)set label 8 at 8.2,N4s_mean LABEL8 front left font "Arial,7"

if(a>=9)LABEL9 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f ",N5s_mean, N5s_max, N5s_min, N5s_median )
if(a>=9)set label 9 at 9.2,N5s_mean LABEL9 front left font "Arial,7" 

set boxwidth .2 absolute 
set xlabel "Objective"
set ylabel "Final Value"
set size 1, .6
set origin .0,.4
set autoscale
set xrange [.8:Objective_records+1]
set xtics 

set ytics format "%.2e"

if(a==3) plot ObjectiveOut using 1:3:2:6:5 with candlesticks ls 1 title 'Quartiles' whiskerbars, \
        '' using 1:4:4:4:4 with candlesticks ls 2 notitle, \
        inputfile u (1.4):5 ls 3 notitle, \
        '' u (2.4):6 ls 3 notitle, \
        '' u (3.4):7 ls 3 notitle


if(a==6) plot ObjectiveOut using 1:3:2:6:5 with candlesticks ls 1 title 'Quartiles' whiskerbars, \
        '' using 1:4:4:4:4 with candlesticks ls 2 notitle, \
        inputfile u (1.4):5 ls 3 notitle, \
        '' u (2.4):6 ls 3 notitle, \
        '' u (3.4):7 ls 3 notitle, \
        '' u (4.4):8 ls 3 notitle, \
        '' u (5.4):9 ls 3 notitle, \
        '' u (6.4):10 ls 3 notitle

if(a==7) plot ObjectiveOut using 1:3:2:6:5 with candlesticks ls 1 title 'Quartiles' whiskerbars, \
        '' using 1:4:4:4:4 with candlesticks ls 2 notitle, \
        inputfile u (1.4):5 ls 3 notitle, \
        '' u (2.4):6 ls 3 notitle, \
        '' u (3.4):7 ls 3 notitle, \
        '' u (4.4):8 ls 3 notitle, \
        '' u (5.4):9 ls 3 notitle, \
        '' u (6.4):10 ls 3 notitle, \
        '' u (7.4):11 ls 3 notitle

if(a==8) plot ObjectiveOut using 1:3:2:6:5 with candlesticks ls 1 title 'Quartiles' whiskerbars, \
        '' using 1:4:4:4:4 with candlesticks ls 2 notitle, \
        inputfile u (1.4):5 ls 3 notitle, \
        '' u (2.4):6 ls 3 notitle, \
        '' u (3.4):7 ls 3 notitle, \
        '' u (4.4):8 ls 3 notitle, \
        '' u (5.4):9 ls 3 notitle, \
        '' u (6.4):10 ls 3 notitle, \
        '' u (7.4):11 ls 3 notitle, \
        '' u (8.4):12 ls 3 notitle

if(a==9) plot ObjectiveOut using 1:3:2:6:5 with candlesticks ls 1 title 'Quartiles' whiskerbars, \
        '' using 1:4:4:4:4 with candlesticks ls 2 notitle, \
        inputfile u (1.4):5 ls 3 notitle, \
        '' u (2.4):6 ls 3 notitle, \
        '' u (3.4):7 ls 3 notitle, \
        '' u (4.4):8 ls 3 notitle, \
        '' u (5.4):9 ls 3 notitle, \
        '' u (6.4):10 ls 3 notitle, \
        '' u (7.4):11 ls 3 notitle, \
        '' u (8.4):12 ls 3 notitle, \
        '' u (9.4):13 ls 3 notitle

unset label

#-------------------------------------------------------------------------
#setup the 2. plot

set boxwidth 0.05 relative

set xlabel ""
set ylabel "Evaluations"
set size .25, .4
set origin .0,.0
unset xtics
set xrange [-.2:.4]
set ytics format "%.0f"

plot EvalOut using 1:3:2:6:5 with candlesticks ls 1 title 'Quartiles' whiskerbars, \
    ''        using 1:4:4:4:4 with candlesticks ls 2 notitle, \
        inputfile u (0.2):2 ls 3 notitle
    

#-------------------------------------------------------------------------
#setup the 3. plot
#unset yrange
set autoscale
set logscale y
set ytics 

set xlabel ""
set ylabel "Function Value"
set size .25, .4
set origin .25,.0
set xrange [-.2:.4]
unset xtics
set ytics format "%.1e" 
plot FitnessOut using 1:3:2:6:5 with candlesticks ls 1 title 'Quartiles' whiskerbars, \
    ''        using 1:4:4:4:4 with candlesticks ls 2 notitle,\
        inputfile u (0.2):3 ls 3 notitle

#-------------------------------------------------------------------------
#setup the 4. plot
set xlabel ""
set ylabel "Sigma"
set ytics format "%.1e" 

set size .25, .4
set origin .50,.0

#set yrange [Sigmas_max:Sigmas_min]
#unset yrange
unset logscale
set autoscale
set xrange [-.2:.4]
unset xtics
set ytics 

plot SigmaOut using 1:3:2:6:5 with candlesticks ls 1 title 'Quartiles' whiskerbars, \
    ''        using 1:4:4:4:4 with candlesticks ls 2 notitle,\
        inputfile u (0.2):lastDataCol ls 3 notitle

#-------------------------------------------------------------------------
#setup the 5. plot
set xlabel ""
set ylabel "Distance"
set ytics format "%.1e" 

set size .25, .4
set origin .75,.0

#set yrange [Vectors_max:Vectors_min]
#unset yrange
#set logscale y
set autoscale
set xrange [-.2:.4]
unset xtics
set ytics 

plot VectorOut using 1:3:2:6:5 with candlesticks ls 1 title 'Quartiles' whiskerbars, \
    ''        using 1:4:4:4:4 with candlesticks ls 2 notitle,\
        inputfile u (0.2):vectorCol ls 3 notitle

#-------------------------------------------------------------------------
i=i+1

unset multiplot

if (i < m) reread
i=0
#print "rm ".ObjectiveOut.remove( ObjectiveOut )
#print "rm ".SigmaOut.remove( SigmaOut )
#print "rm ".FitnessOut.remove( FitnessOut)
#print "rm ".EvalOut.remove( EvalOut )
