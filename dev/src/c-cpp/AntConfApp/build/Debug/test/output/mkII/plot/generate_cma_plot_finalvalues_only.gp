# This scripts use is to generate a plot from the final values of the solutions for one antenna
#
#prerequesites set i, n and the number of antennas to proper values
#

at(file, row, col) = system( sprintf("awk -v row=%d -v col=%d 'NR == row {print $col}' %s", row, col, file) )
to(file, min, first, mean, third, max, row) = system( sprintf("echo %d %e %e %e %e %e >> %s", row, min, first, mean, third, max ,file) )
toScientific(file, min, first, mean, third, max, row) = system( sprintf("echo %d %e %e %e %e %e >> %s", row, min, first, mean, third, max ,file) )
remove(file) = system( sprintf( "rm %s", file ) )
to2(file, value) = system( sprintf("echo 1 2 3 %s %s", value, file) )
echoStats( min, first, mean, third, max) = system( sprintf("echo %e %e %e %e %e ", min, first, mean, third, max) )

#set style line 1 linetype 1 linecolor rgb "blue"  linewidth 1.000 pointtype 7 pointsize .2 pointinterval 10
#set style line 2 linetype 1 linecolor rgb "green"  linewidth 1.000 pointtype 7 pointsize .2 pointinterval 10
#set style line 3 linetype 1 linecolor rgb "red"  linewidth 1.000 pointtype 7 pointsize .2 pointinterval 10
#set style line 4 linetype 1 linecolor rgb "gray"  linewidth 1 pointtype 2 pointsize default pointinterval 0

set style arrow 1 heads size screen 0.008,90 ls 2

if( i == 0 ) set terminal pngcairo enhanced font "arial,10" size 1000, 800 
#if( i == 0 ) set term png small

set key right bottom vertical Left noreverse enhanced box samplen .2 
set key opaque
set grid

lastDataCol = 3+a+2
inputfile = "data/single_".i.".dat"
outMultiplot = "img/SingleSolution_".i.".png"

print "Processing: Start" 

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
stats inputfile u 8 name "N0s" nooutput
stats inputfile u 9 name "N1s" nooutput
stats inputfile u 10 name "N2s" nooutput
stats inputfile u 11 name "N3s" nooutput
if(a==8) stats inputfile u 13 name "N4s" nooutput
if(a==9) stats inputfile u 14 name "N5s" nooutput
if(a==10) stats inputfile u 15 name "N6s" nooutput
if(a==11) stats inputfile u 16 name "N7s" nooutput

stats inputfile u lastDataCol name "Sigmas" nooutput


#-------------------------------------------------------------------------
#-------------------------------------------------------------------------
#1
EvalOut = "EvaluationStats.dat"

print "rm ".EvalOut.remove( EvalOut )
print "wr ".to( EvalOut, Counts_min, Counts_lo_quartile, Counts_mean, Counts_up_quartile, Counts_max, 0)

#2
FitnessOut = "FitnessStats.dat"

print "rm ".FitnessOut.remove( FitnessOut)
print "wr".to( FitnessOut, Fitness_min, Fitness_lo_quartile, Fitness_mean, Fitness_up_quartile, Fitness_max, 0)

#3
ObjectiveOut = "ObjectivStats.dat"

print "rm ".ObjectiveOut.remove( ObjectiveOut )
print "wr".to( ObjectiveOut, Xs_min, Xs_lo_quartile, Xs_mean, Xs_up_quartile, Xs_max, 1)
print "  *".to( ObjectiveOut, Ys_min, Ys_lo_quartile, Ys_mean, Ys_up_quartile, Ys_max, 2)
print "  *".to( ObjectiveOut, Zs_min, Zs_lo_quartile, Zs_mean, Zs_up_quartile, Zs_max, 3)
print "  *".to( ObjectiveOut, N0s_min, N0s_lo_quartile, N0s_mean, N0s_up_quartile, N0s_max, 4)
print "  *".to( ObjectiveOut, N1s_min, N1s_lo_quartile, N1s_mean, N1s_up_quartile, N1s_max, 5)
print "  *".to( ObjectiveOut, N2s_min, N2s_lo_quartile, N2s_mean, N2s_up_quartile, N2s_max, 6)
print "  *".to( ObjectiveOut, N3s_min, N3s_lo_quartile, N3s_mean, N3s_up_quartile, N3s_max, 7)

stats ObjectiveOut u 5 name "Objective" nooutput

#4
SigmaOut = "SigmaStats.dat"

print "rm ".SigmaOut.remove( SigmaOut )
print "wr".to( SigmaOut, Sigmas_min, Sigmas_lo_quartile, Sigmas_mean, Sigmas_up_quartile, Sigmas_max, 0)

#-------------------------------------------------------------------------
#setup the 1. plot

LABEL1 = sprintf("mean =\t%.3f \nmin =\t%.3f \nmax =\t%.3f \nmedian =\t%.3f ",Xs_mean, Xs_max, Xs_min, Xs_median )
set label 1 at 1.1,Xs_mean LABEL1 front left font "Arial,8" 

LABEL2 = sprintf("mean =\t%.3f \nmin =\t%.3f \nmax =\t%.3f \nmedian =\t%.3f ",Ys_mean, Ys_max, Ys_min, Ys_median )
set label 2 at 2.1,Ys_mean LABEL2 front left font "Arial,8" 

LABEL3 = sprintf("mean =\t%.3f \nmin =\t%.3f \nmax =\t%.3f \nmedian =\t%.3f" ,Zs_mean, Zs_max, Zs_min, Zs_median )
set label 3 at 3.1,Zs_mean LABEL3 front left font "Arial,8" 

LABEL4 = sprintf("mean =\t%.3f \nmin =\t%.3f \nmax =\t%.3f \nmedian =\t%.3f ",N0s_mean, N0s_max, N0s_min, N0s_median )
set label 4 at 4.1,N0s_mean LABEL4 front left font "Arial,8" 

LABEL5 = sprintf("mean =\t%.3f \nmin =\t%.3f \nmax =\t%.3f \nmedian =\t%.3f ",N1s_mean, N1s_max, N1s_min, N1s_median )
set label 5 at 5.1,N1s_mean LABEL5 front left font "Arial,8" 

LABEL6 = sprintf("mean =\t%.3f \nmin =\t%.3f \nmax =\t%.3f \nmedian =\t%.3f ",N2s_mean, N2s_max, N2s_min, N2s_median  )
set label 6 at 6.1,N2s_mean LABEL6 front left font "Arial,8" 

LABEL7 = sprintf("mean =\t%.3f \nmin =\t%.3f \nmax =\t%.3f \nmedian =\t%.3f ",N3s_mean, N3s_max, N3s_min, N3s_median )
set label 7 at 7.1,N3s_mean LABEL7 front left font "Arial,8" 

set boxwidth 0.1 absolute 
set xlabel "Objective"
set ylabel "Final Value"
set size 1, .6
set origin .0,.4
set autoscale
set xrange [.2:Objective_records+1]
#set yrange [-10:30]


set ytics format "%.0f"

plot ObjectiveOut using 1:3:2:6:5 with candlesticks lt 1 lw 1 title 'Quartiles' whiskerbars, \
    ''        using 1:4:4:4:4 with candlesticks lt -1 lw 1 notitle

unset label 1
unset label 2
unset label 3
unset label 4
unset label 5
unset label 6
unset label 7


#-------------------------------------------------------------------------
#setup the 2. plot

set xlabel ""
set ylabel "Evaluations"
set size .33, .4
set origin .0,.0
unset xtics
set xrange [-.5:.5]
set ytics format "%.0f"

plot EvalOut using 1:3:2:6:5 with candlesticks lt 1 lw 1 title 'Quartiles' whiskerbars, \
    ''        using 1:4:4:4:4 with candlesticks lt -1 lw 1 notitle

#-------------------------------------------------------------------------
#setup the 3. plot
set xlabel ""
set ylabel "Function Value"
set size .33, .4
set origin .33,.0
set xrange [-.5:.5]
unset xtics
set ytics format "%.1e" 
plot FitnessOut using 1:3:2:6:5 with candlesticks lt 1 lw 1 title 'Quartiles' whiskerbars, \
    ''        using 1:4:4:4:4 with candlesticks lt -1 lw 1 notitle

#-------------------------------------------------------------------------
#setup the 4. plot
set xlabel ""
set ylabel "Sigma"
set size .33, .4
set origin .66,.0
set xrange [-.5:.5]
unset xtics

plot SigmaOut using 1:3:2:6:5 with candlesticks lt 1 lw 1 title 'Quartiles' whiskerbars, \
    ''        using 1:4:4:4:4 with candlesticks lt -1 lw 1 notitle

i=i+1

unset multiplot

if (i < m) reread
i=0
