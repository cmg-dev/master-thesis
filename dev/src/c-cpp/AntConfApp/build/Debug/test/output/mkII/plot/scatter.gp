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

unset style
set style line 1 linetype 1 linecolor rgb "#708090"  linewidth 1 pointtype 7 pointsize .5
set style line 2 linetype -1 linecolor rgb "#2f4f4f"  linewidth 1.2

set style line 3 linetype 1 linecolor rgb "#ee708090"  linewidth 1.000 pointtype 7 pointsize .5 pointinterval 1
#set style line 3 linetype 1 linecolor rgb "red"  linewidth 1.000 pointtype 7 pointsize 1 pointinterval 5
#set style line 4 linetype 1 linecolor rgb "gray"  linewidth 1 pointtype 2 pointsize default pointinterval 0

set style arrow 1 heads size screen 0.008,90 ls 2

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

#print "Processing: Start" 

set output outMultiplot

set multiplot layout a,a

#collect information about the file
unset logscale
set autoscale
unset label
unset xlabel
unset ylabel

#-------------------------------------------------------------------------
#setup the 1. plot
unset ytics
unset xtics

LABELX = sprintf("x" )
LABELY = sprintf("y" )
LABELZ = sprintf("z" )
LABELN0 = sprintf("n0" )
LABELN1 = sprintf("n1" )
LABELN2 = sprintf("n2" )
LABELN3 = sprintf("n3" )
LABELN4 = sprintf("n4" )
LABELN5 = sprintf("n5" )
LABELN6 = sprintf("n6" )

unset key

labelxpos = .1
labelypos = .5

############################################################################################
set label at graph labelxpos,labelypos center LABELX front left font "Arial,24" textcolor rgb "#4f2f2f" 
plot inputfile u ($2 < 8000 ? $5: 1/0):5 ls 3 notitle 
unset label

plot inputfile u ($2 < 8000 ? $5: 1/0):6 ls 1 notitle 
plot inputfile u ($2 < 8000 ? $5: 1/0):7 ls 1 notitle 
if(a>=4)plot inputfile u ($2 < 8000 ? $5: 1/0):8 ls 1 notitle 
if(a>=5)plot inputfile u ($2 < 8000 ? $5: 1/0):9 ls 1 notitle 
if(a>=6)plot inputfile u ($2 < 8000 ? $5: 1/0):10 ls 1 notitle 
if(a>=7)plot inputfile u ($2 < 8000 ? $5: 1/0):11 ls 1 notitle 
if(a>=8)plot inputfile u ($2 < 8000 ? $5: 1/0):12 ls 1 notitle 
if(a>=9)plot inputfile u ($2 < 8000 ? $5: 1/0):13 ls 1 notitle 
if(a>=10)plot inputfile u ($2 < 8000 ? $5: 1/0):14 ls 1 notitle 
if(a>=11)plot inputfile u ($2 < 8000 ? $5: 1/0):15 ls 1 notitle 

############################################################################################
plot inputfile u ($2 < 8000 ? $6: 1/0):5 ls 1 notitle 

set label at graph labelxpos,labelypos center LABELY front left font "Arial,24" textcolor rgb "#4f2f2f" 
plot inputfile u ($2 < 8000 ? $6: 1/0):6 ls 3 notitle 
unset label

plot inputfile u ($2 < 8000 ? $6: 1/0):7 ls 1 notitle 
if(a>=4)plot inputfile u ($2 < 8000 ? $6: 1/0):8 ls 1 notitle 
if(a>=5)plot inputfile u ($2 < 8000 ? $6: 1/0):9 ls 1 notitle 
if(a>=6)plot inputfile u ($2 < 8000 ? $6: 1/0):10 ls 1 notitle 
if(a>=7)plot inputfile u ($2 < 8000 ? $6: 1/0):11 ls 1 notitle 
if(a>=8)plot inputfile u ($2 < 8000 ? $6: 1/0):12 ls 1 notitle 
if(a>=9)plot inputfile u ($2 < 8000 ? $6: 1/0):13 ls 1 notitle 
if(a>=10)plot inputfile u ($2 < 8000 ? $6: 1/0):14 ls 1 notitle 
if(a>=11)plot inputfile u ($2 < 8000 ? $6: 1/0):15 ls 1 notitle 

############################################################################################
plot inputfile u ($2 < 8000 ? $7: 1/0):5 ls 1 notitle 
plot inputfile u ($2 < 8000 ? $7: 1/0):6 ls 1 notitle 

set label at graph labelxpos,labelypos center LABELZ front left font "Arial,24" textcolor rgb "#4f2f2f" 
plot inputfile u ($2 < 8000 ? $7: 1/0):7 ls 3 notitle 
unset label

if(a>=4)plot inputfile u ($2 < 8000 ? $7: 1/0):8 ls 1 notitle 
if(a>=5)plot inputfile u ($2 < 8000 ? $7: 1/0):9 ls 1 notitle 
if(a>=6)plot inputfile u ($2 < 8000 ? $7: 1/0):10 ls 1 notitle 
if(a>=7)plot inputfile u ($2 < 8000 ? $7: 1/0):11 ls 1 notitle 
if(a>=8)plot inputfile u ($2 < 8000 ? $7: 1/0):12 ls 1 notitle 
if(a>=9)plot inputfile u ($2 < 8000 ? $7: 1/0):13 ls 1 notitle 
if(a>=10)plot inputfile u ($2 < 8000 ? $7: 1/0):14 ls 1 notitle 
if(a>=11)plot inputfile u ($2 < 8000 ? $7: 1/0):15 ls 1 notitle 

############################################################################################
if(a>3)plot inputfile u ($2 < 8000 ? $8: 1/0):5 ls 1 notitle 
if(a>3)plot inputfile u ($2 < 8000 ? $8: 1/0):6 ls 1 notitle 
if(a>3)plot inputfile u ($2 < 8000 ? $8: 1/0):7 ls 1 notitle 

set label at graph labelxpos,labelypos center LABELN0 front left font "Arial,24" textcolor rgb "#4f2f2f"
if(a>=4)plot inputfile u ($2 < 8000 ? $8: 1/0):8 ls 3 notitle 
unset label

if(a>=5)plot inputfile u ($2 < 8000 ? $8: 1/0):9 ls 1 notitle 
if(a>=6)plot inputfile u ($2 < 8000 ? $8: 1/0):10 ls 1 notitle 
if(a>=7)plot inputfile u ($2 < 8000 ? $8: 1/0):11 ls 1 notitle 
if(a>=8)plot inputfile u ($2 < 8000 ? $8: 1/0):12 ls 1 notitle 
if(a>=9)plot inputfile u ($2 < 8000 ? $8: 1/0):13 ls 1 notitle 
if(a>=10)plot inputfile u ($2 < 8000 ? $8: 1/0):14 ls 1 notitle 
if(a>=11)plot inputfile u ($2 < 8000 ? $8: 1/0):15 ls 1 notitle 

############################################################################################
if(a>3)plot inputfile u ($2 < 8000 ? $9: 1/0):5 ls 1 notitle 
if(a>3)plot inputfile u ($2 < 8000 ? $9: 1/0):6 ls 1 notitle 
if(a>3)plot inputfile u ($2 < 8000 ? $9: 1/0):7 ls 1 notitle 
if(a>=4)plot inputfile u ($2 < 8000 ? $9: 1/0):8 ls 1 notitle 

set label at graph labelxpos,labelypos center LABELN1 front left font "Arial,24" textcolor rgb "#4f2f2f"
if(a>=5)plot inputfile u ($2 < 8000 ? $9: 1/0):9 ls 3 notitle 
unset label

if(a>=6)plot inputfile u ($2 < 8000 ? $9: 1/0):10 ls 1 notitle 
if(a>=7)plot inputfile u ($2 < 8000 ? $9: 1/0):11 ls 1 notitle 
if(a>=8)plot inputfile u ($2 < 8000 ? $9: 1/0):12 ls 1 notitle 
if(a>=9)plot inputfile u ($2 < 8000 ? $9: 1/0):13 ls 1 notitle 
if(a>=10)plot inputfile u ($2 < 8000 ? $9: 1/0):14 ls 1 notitle 
if(a>=11)plot inputfile u ($2 < 8000 ? $9: 1/0):15 ls 1 notitle 

############################################################################################
if(a>3)plot inputfile u ($2 < 8000 ? $10: 1/0):5 ls 1 notitle 
if(a>3)plot inputfile u ($2 < 8000 ? $10: 1/0):6 ls 1 notitle 
if(a>3)plot inputfile u ($2 < 8000 ? $10: 1/0):7 ls 1 notitle 
if(a>=4)plot inputfile u ($2 < 8000 ? $10: 1/0):8 ls 1 notitle 
if(a>=5)plot inputfile u ($2 < 8000 ? $10: 1/0):9 ls 1 notitle 

set label at graph labelxpos,labelypos center LABELN2 front left font "Arial,24" textcolor rgb "#4f2f2f"
if(a>=6)plot inputfile u ($2 < 8000 ? $10: 1/0):10 ls 3 notitle 
unset label

if(a>=7)plot inputfile u ($2 < 8000 ? $10: 1/0):11 ls 1 notitle 
if(a>=8)plot inputfile u ($2 < 8000 ? $10: 1/0):12 ls 1 notitle 
if(a>=9)plot inputfile u ($2 < 8000 ? $10: 1/0):13 ls 1 notitle 
if(a>=10)plot inputfile u ($2 < 8000 ? $10: 1/0):14 ls 1 notitle 
if(a>=11)plot inputfile u ($2 < 8000 ? $10: 1/0):15 ls 1 notitle 

############################################################################################
if(a>3)plot inputfile u ($2 < 8000 ? $11: 1/0):5 ls 1 notitle 
if(a>3)plot inputfile u ($2 < 8000 ? $11: 1/0):6 ls 1 notitle 
if(a>3)plot inputfile u ($2 < 8000 ? $11: 1/0):7 ls 1 notitle 
if(a>=4)plot inputfile u ($2 < 8000 ? $11: 1/0):8 ls 1 notitle 
if(a>=5)plot inputfile u ($2 < 8000 ? $11: 1/0):9 ls 1 notitle 
if(a>=6)plot inputfile u ($2 < 8000 ? $11: 1/0):10 ls 1 notitle 
set label at graph labelxpos,labelypos center LABELN3 front left font "Arial,24" textcolor rgb "#4f2f2f"
if(a>=7)plot inputfile u ($2 < 8000 ? $11: 1/0):11 ls 3 notitle 
unset label

if(a>=8)plot inputfile u ($2 < 8000 ? $11: 1/0):12 ls 1 notitle 
if(a>=9)plot inputfile u ($2 < 8000 ? $11: 1/0):13 ls 1 notitle 
if(a>=10)plot inputfile u ($2 < 8000 ? $11: 1/0):14 ls 1 notitle 
if(a>=11)plot inputfile u ($2 < 8000 ? $11: 1/0):15 ls 1 notitle 

############################################################################################
if(a>=8)    plot inputfile u ($2 < 8000 ? $12: 1/0):5 ls 1 notitle 
if(a>=8)    plot inputfile u ($2 < 8000 ? $12: 1/0):6 ls 1 notitle 
if(a>=8)    plot inputfile u ($2 < 8000 ? $12: 1/0):7 ls 1 notitle 
if(a>=8)    plot inputfile u ($2 < 8000 ? $12: 1/0):8 ls 1 notitle 
if(a>=8)    plot inputfile u ($2 < 8000 ? $12: 1/0):9 ls 1 notitle 
if(a>=8)    plot inputfile u ($2 < 8000 ? $12: 1/0):10 ls 1 notitle 
if(a>=8)    plot inputfile u ($2 < 8000 ? $12: 1/0):11 ls 1 notitle

if(a>=8)    set label at graph labelxpos,labelypos center LABELN4 front left font "Arial,24" textcolor rgb "#4f2f2f"
if(a>=8)    plot inputfile u ($2 < 8000 ? $12: 1/0):12 ls 3 notitle 
if(a>=8)    unset label

if(a>=9)    plot inputfile u ($2 < 8000 ? $12: 1/0):13 ls 1 notitle 
if(a>=10)   plot inputfile u ($2 < 8000 ? $12: 1/0):14 ls 1 notitle 
if(a>=11)   plot inputfile u ($2 < 8000 ? $12: 1/0):15 ls 1 notitle 

############################################################################################
if(a>=9)    plot inputfile u ($2 < 8000 ? $13: 1/0):5 ls 1 notitle 
if(a>=9)    plot inputfile u ($2 < 8000 ? $13: 1/0):6 ls 1 notitle 
if(a>=9)    plot inputfile u ($2 < 8000 ? $13: 1/0):7 ls 1 notitle 
if(a>=9)    plot inputfile u ($2 < 8000 ? $13: 1/0):8 ls 1 notitle 
if(a>=9)    plot inputfile u ($2 < 8000 ? $13: 1/0):9 ls 1 notitle 
if(a>=9)    plot inputfile u ($2 < 8000 ? $13: 1/0):10 ls 1 notitle 
if(a>=9)    plot inputfile u ($2 < 8000 ? $13: 1/0):11 ls 1 notitle 
if(a>=9)    plot inputfile u ($2 < 8000 ? $13: 1/0):12 ls 1 notitle 

if(a>=9)    set label at graph labelxpos,labelypos center LABELN5 front left font "Arial,24" textcolor rgb "#4f2f2f"
if(a>=9)    plot inputfile u ($2 < 8000 ? $13: 1/0):13 ls 3 notitle 
if(a>=9)    unset label

if(a>=10)   plot inputfile u ($2 < 8000 ? $13: 1/0):14 ls 1 notitle 
if(a>=11)   plot inputfile u ($2 < 8000 ? $13: 1/0):15 ls 1 notitle 

i=i+1

unset multiplot

if (i < m) reread
i=0
#print "rm ".ObjectiveOut.remove( ObjectiveOut )
#print "rm ".SigmaOut.remove( SigmaOut )
#print "rm ".FitnessOut.remove( FitnessOut)
#print "rm ".EvalOut.remove( EvalOut )
