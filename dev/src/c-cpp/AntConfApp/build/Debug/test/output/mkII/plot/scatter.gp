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
set key right bottom vertical Left noreverse enhanced box samplen .2 
set key opaque
set grid

lastDataCol = 3+a+2
inputfile = "data/single_".i.".dat"
input_all = "data/single_".i.".dat"
input_one = "data/".i.".dat"

outMultiplot = "img/linien/kondensiert/scatter".i.".png"

print "Processing: Start" 

set output outMultiplot

set multiplot layout a,a

#collect information about the file
unset logscale
set autoscale

#-------------------------------------------------------------------------
#- Gather relevant information via stats ---------------------------------
#-------------------------------------------------------------------------
#stats inputfile u 2 name "Counts" nooutput

# notice: The fitness may be normalized to be shown correctly. Values below e-14 can no be processed correctly
#stats inputfile u 3 name "Fitness" nooutput 

#print "".a
#stats inputfile u 5 name "Xs" nooutput
#stats inputfile u 6 name "Ys" nooutput
#stats inputfile u 7 name "Zs" nooutput
#stats inputfile u 8 name "N0s" nooutput
#stats inputfile u 9 name "N1s" nooutput
#stats inputfile u 10 name "N2s" nooutput
#stats inputfile u 11 name "N3s" nooutput
#if(a>=8) stats inputfile u 12 name "N4s" nooutput 
#if(a>=9) stats inputfile u 13 name "N5s" nooutput   
#if(a==10) stats inputfile u 14 name "N6s" nooutput
#if(a==11) stats inputfile u 15 name "N7s" nooutput

#stats inputfile u lastDataCol name "Sigmas" nooutput


#-------------------------------------------------------------------------
#-------------------------------------------------------------------------
#1
#EvalOut = "EvaluationStats.dat"

#print "rm ".EvalOut.remove( EvalOut )
#print "wr head".header( EvalOut )
#print "wr ".to( EvalOut, Counts_min, Counts_lo_quartile, Counts_mean, Counts_up_quartile, Counts_max, 0)

#2
#FitnessOut = "FitnessStats.dat"

#print "rm ".FitnessOut.remove( FitnessOut)
#print "wr head".header( FitnessOut )
#print "wr".to( FitnessOut, Fitness_min, Fitness_lo_quartile, Fitness_mean, Fitness_up_quartile, Fitness_max, 0)

#3
#ObjectiveOut = "ObjectivStats.dat"

#print "rm ".ObjectiveOut.remove( ObjectiveOut )
#print "wr head".header( ObjectiveOut )
#print "wr ".to( ObjectiveOut, Xs_min, Xs_lo_quartile, Xs_mean, Xs_up_quartile, Xs_max, 1)
#print "  *".to( ObjectiveOut, Ys_min, Ys_lo_quartile, Ys_mean, Ys_up_quartile, Ys_max, 2)
#print "  *".to( ObjectiveOut, Zs_min, Zs_lo_quartile, Zs_mean, Zs_up_quartile, Zs_max, 3)
#print "  *".to( ObjectiveOut, N0s_min, N0s_lo_quartile, N0s_mean, N0s_up_quartile, N0s_max, 4)
#print "  *".to( ObjectiveOut, N1s_min, N1s_lo_quartile, N1s_mean, N1s_up_quartile, N1s_max, 5)
#print "  *".to( ObjectiveOut, N2s_min, N2s_lo_quartile, N2s_mean, N2s_up_quartile, N2s_max, 6)
#print "  *".to( ObjectiveOut, N3s_min, N3s_lo_quartile, N3s_mean, N3s_up_quartile, N3s_max, 7)

#if(a>=8) print "  *".to( ObjectiveOut, N4s_min, N4s_lo_quartile, N4s_mean, N4s_up_quartile, N4s_max, 8)
#if(a>=9) print "  *".to( ObjectiveOut, N5s_min, N5s_lo_quartile, N5s_mean, N5s_up_quartile, N5s_max, 9)

#stats ObjectiveOut u 5 name "Objective" nooutput

#4
#SigmaOut = "SigmaStats.dat"

#print "rm ".SigmaOut.remove( SigmaOut )
#print "wr head".header( SigmaOut )
#print "wr".to( SigmaOut, Sigmas_min, Sigmas_lo_quartile, Sigmas_mean, Sigmas_up_quartile, Sigmas_max, 0)

#unset label

#-------------------------------------------------------------------------
##setup the 1. plot

#LABEL1 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f ",Xs_mean, Xs_max, Xs_min, Xs_median )
#set label 1 at 1.2,Xs_mean LABEL1 front left font "Arial,7" 

#LABEL2 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f ",Ys_mean, Ys_max, Ys_min, Ys_median )
#set label 2 at 2.2,Ys_mean LABEL2 front left font "Arial,7" 

#LABEL3 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f" ,Zs_mean, Zs_max, Zs_min, Zs_median )
#set label 3 at 3.2,Zs_mean LABEL3 front left font "Arial,7" 

#LABEL4 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f ",N0s_mean, N0s_max, N0s_min, N0s_median )
#set label 4 at 4.2,N0s_mean LABEL4 front left font "Arial,7" 

#LABEL5 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f ",N1s_mean, N1s_max, N1s_min, N1s_median )
#set label 5 at 5.2,N1s_mean LABEL5 front left font "Arial,7" 

#LABEL6 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f ",N2s_mean, N2s_max, N2s_min, N2s_median  )
#set label 6 at 6.2,N2s_mean LABEL6 front left font "Arial,7" 

#LABEL7 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f ",N3s_mean, N3s_max, N3s_min, N3s_median )
#set label 7 at 7.2,N3s_mean LABEL7 front left font "Arial,7" 


#if(a>=8)LABEL8 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f ",N4s_mean, N4s_max, N4s_min, N4s_median )
#if(a>=8)set label 8 at 8.2,N4s_mean LABEL8 front left font "Arial,7"

#if(a>=9)LABEL9 = sprintf("mean = %.3f \nmax = %.3f \nmin = %.3f \nmedian = %.3f ",N5s_mean, N5s_max, N5s_min, N5s_median )
#if(a>=9)set label 9 at 9.2,N5s_mean LABEL9 front left font "Arial,7" 

#set boxwidth .2 absolute 
#set xlabel "Objective"
#set ylabel "Final Value"
#set size 1, .6
#set origin .0,.4
#set autoscale
#set xrange [.8:Objective_records+1]
#set xtics 

#set ytics format "%.2e"

#if(a==6) plot ObjectiveOut using 1:3:2:6:5 with candlesticks ls 1 title 'Quartiles' whiskerbars, \
        #'' using 1:4:4:4:4 with candlesticks ls 2 notitle, \
        #inputfile u (1.4):5 ls 3 notitle, \
        #'' u (2.4):6 ls 3 notitle, \
        #'' u (3.4):7 ls 3 notitle, \
        #'' u (4.4):8 ls 3 notitle, \
        #'' u (5.4):9 ls 3 notitle, \
        #'' u (6.4):10 ls 3 notitle

#if(a==7) plot ObjectiveOut using 1:3:2:6:5 with candlesticks ls 1 title 'Quartiles' whiskerbars, \
        #'' using 1:4:4:4:4 with candlesticks ls 2 notitle, \
        #inputfile u (1.4):5 ls 3 notitle, \
        #'' u (2.4):6 ls 3 notitle, \
        #'' u (3.4):7 ls 3 notitle, \
        #'' u (4.4):8 ls 3 notitle, \
        #'' u (5.4):9 ls 3 notitle, \
        #'' u (6.4):10 ls 3 notitle, \
        #'' u (7.4):11 ls 3 notitle

plot inputfile using 5:5 ls 1 notitle 
plot inputfile using 5:6 ls 1 notitle 
plot inputfile using 5:7 ls 1 notitle 
plot inputfile using 5:8 ls 1 notitle 
plot inputfile using 5:9 ls 1 notitle 
plot inputfile using 5:10 ls 1 notitle 
plot inputfile using 5:11 ls 1 notitle 
if(a>=8)plot inputfile using 5:12 ls 1 notitle 
if(a>=9)plot inputfile using 5:13 ls 1 notitle 
if(a>=10)plot inputfile using 5:14 ls 1 notitle 
if(a>=11)plot inputfile using 5:15 ls 1 notitle 

plot inputfile using 6:5 ls 1 notitle 
plot inputfile using 6:6 ls 1 notitle 
plot inputfile using 6:7 ls 1 notitle 
plot inputfile using 6:8 ls 1 notitle 
plot inputfile using 6:9 ls 1 notitle 
plot inputfile using 6:10 ls 1 notitle 
plot inputfile using 6:11 ls 1 notitle 
plot inputfile using 6:12 ls 1 notitle 
if(a>=8)plot inputfile using 6:13 ls 1 notitle 
if(a>=9)plot inputfile using 6:14 ls 1 notitle 
if(a>=10)plot inputfile using 6:15 ls 1 notitle 
if(a>=11)plot inputfile using 6:16 ls 1 notitle 

plot inputfile using 7:5 ls 1 notitle 
plot inputfile using 7:6 ls 1 notitle 
plot inputfile using 7:7 ls 1 notitle 
plot inputfile using 7:8 ls 1 notitle 
plot inputfile using 7:9 ls 1 notitle 
plot inputfile using 7:10 ls 1 notitle 
plot inputfile using 7:11 ls 1 notitle 
plot inputfile using 7:12 ls 1 notitle 
if(a>=8)plot inputfile using 7:13 ls 1 notitle 
if(a>=9)plot inputfile using 7:14 ls 1 notitle 
if(a>=10)plot inputfile using 7:15 ls 1 notitle 
if(a>=11)plot inputfile using 7:16 ls 1 notitle 

plot inputfile using 8:5 ls 1 notitle 
plot inputfile using 8:6 ls 1 notitle 
plot inputfile using 8:7 ls 1 notitle 
plot inputfile using 8:8 ls 1 notitle 
plot inputfile using 8:9 ls 1 notitle 
plot inputfile using 8:10 ls 1 notitle 
plot inputfile using 8:11 ls 1 notitle 
plot inputfile using 8:12 ls 1 notitle 
if(a>=8)plot inputfile using 8:13 ls 1 notitle 
if(a>=9)plot inputfile using 8:14 ls 1 notitle 
if(a>=10)plot inputfile using 8:15 ls 1 notitle 
if(a>=11)plot inputfile using 8:16 ls 1 notitle 

plot inputfile using 9:5 ls 1 notitle 
plot inputfile using 9:6 ls 1 notitle 
plot inputfile using 9:7 ls 1 notitle 
plot inputfile using 9:8 ls 1 notitle 
plot inputfile using 9:9 ls 1 notitle 
plot inputfile using 9:10 ls 1 notitle 
plot inputfile using 9:11 ls 1 notitle 
plot inputfile using 9:12 ls 1 notitle 
if(a>=8)plot inputfile using 9:13 ls 1 notitle 
if(a>=9)plot inputfile using 9:14 ls 1 notitle 
if(a>=10)plot inputfile using 9:15 ls 1 notitle 
if(a>=11)plot inputfile using 9:16 ls 1 notitle 

plot inputfile using 10:5 ls 1 notitle 
plot inputfile using 10:6 ls 1 notitle 
plot inputfile using 10:7 ls 1 notitle 
plot inputfile using 10:8 ls 1 notitle 
plot inputfile using 10:9 ls 1 notitle 
plot inputfile using 10:10 ls 1 notitle 
plot inputfile using 10:11 ls 1 notitle 
plot inputfile using 10:12 ls 1 notitle 
if(a>=8)plot inputfile using 10:13 ls 1 notitle 
if(a>=9)plot inputfile using 10:14 ls 1 notitle 
if(a>=10)plot inputfile using 10:15 ls 1 notitle 
if(a>=11)plot inputfile using 10:16 ls 1 notitle 

plot inputfile using 11:5 ls 1 notitle 
plot inputfile using 11:11 ls 1 notitle 
plot inputfile using 11:7 ls 1 notitle 
plot inputfile using 11:8 ls 1 notitle 
plot inputfile using 11:9 ls 1 notitle 
plot inputfile using 11:10 ls 1 notitle 
plot inputfile using 11:11 ls 1 notitle 
plot inputfile using 11:12 ls 1 notitle 
if(a>=8)plot inputfile using 11:13 ls 1 notitle 
if(a>=9)plot inputfile using 11:14 ls 1 notitle 
if(a>=10)plot inputfile using 11:15 ls 1 notitle 
if(a>=11)plot inputfile using 11:16 ls 1 notitle 

plot inputfile using 12:5 ls 1 notitle 
plot inputfile using 12:6 ls 1 notitle 
plot inputfile using 12:7 ls 1 notitle 
plot inputfile using 12:8 ls 1 notitle 
plot inputfile using 12:9 ls 1 notitle 
plot inputfile using 12:10 ls 1 notitle 
plot inputfile using 12:11 ls 1 notitle 
plot inputfile using 12:12 ls 1 notitle 
if(a>=8)plot inputfile using 12:13 ls 1 notitle 
if(a>=9)plot inputfile using 12:14 ls 1 notitle 
if(a>=10)plot inputfile using 12:15 ls 1 notitle 
if(a>=11)plot inputfile using 12:16 ls 1 notitle 

plot inputfile using 13:5 ls 1 notitle 
plot inputfile using 13:11 ls 1 notitle 
plot inputfile using 13:7 ls 1 notitle 
plot inputfile using 13:8 ls 1 notitle 
plot inputfile using 13:9 ls 1 notitle 
plot inputfile using 13:10 ls 1 notitle 
plot inputfile using 13:11 ls 1 notitle 
plot inputfile using 13:12 ls 1 notitle 
if(a>=8)plot inputfile using 13:13 ls 1 notitle 
if(a>=9)plot inputfile using 13:14 ls 1 notitle 
if(a>=10)plot inputfile using 13:15 ls 1 notitle 
if(a>=11)plot inputfile using 13:16 ls 1 notitle 

i=i+1

unset multiplot

if (i < m) reread
i=0
#print "rm ".ObjectiveOut.remove( ObjectiveOut )
#print "rm ".SigmaOut.remove( SigmaOut )
#print "rm ".FitnessOut.remove( FitnessOut)
#print "rm ".EvalOut.remove( EvalOut )
