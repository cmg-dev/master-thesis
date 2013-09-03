#
# This plot generates the x-y view of the fitness plane
#
set terminal pngcairo truecolor transparent background "#ffffff" enhanced font "arial,10" size 1200,1000 

reset

set loadpath '~/dev/gnuplot-colorbrewer/diverging' \
 '~/dev/gnuplot-colorbrewer/qualitavive' \
 '~/dev/gnuplot-colorbrewer/sequential'

set dgrid3d 20,20,1

########################################################################
stats "data/plane_".i."_0.dat" u 8 name "A0" nooutput 
stats "data/plane_".i."_1.dat" u 8 name "A1" nooutput 
stats "data/plane_".i."_2.dat" u 8 name "A2" nooutput 
stats "data/plane_".i."_3.dat" u 8 name "A3" nooutput 
stats "data/plane_".i."_4.dat" u 8 name "A4" nooutput 
stats "data/plane_".i."_5.dat" u 8 name "A5" nooutput 
stats "data/plane_".i."_6.dat" u 8 name "A6" nooutput 
stats "data/plane_".i."_7.dat" u 8 name "A7" nooutput 
stats "data/plane_".i."_8.dat" u 8 name "A8" nooutput 
stats "data/plane_".i."_9.dat" u 8 name "A9" nooutput 
stats "data/plane_".i."_10.dat" u 8 name "A10" nooutput 
stats "data/plane_".i."_11.dat" u 8 name "A11" nooutput 
stats "data/plane_".i."_12.dat" u 8 name "A12" nooutput 
stats "data/plane_".i."_13.dat" u 8 name "A13" nooutput 
stats "data/plane_".i."_14.dat" u 8 name "A14" nooutput 
stats "data/plane_".i."_15.dat" u 8 name "A15" nooutput 
########################################################################

print "stats created"

set contour base
set cntrparam level incremental .0, 75, 5000
#set isosample 1, 1
unset surface 
########################################################################

set table 'data/processed/1.dat'
#splot "data/plane_".i."_0.dat" u 1:2:( $8/A0_max )
splot "data/plane_".i."_0.dat" u 1:2:8
unset table

set table 'data/processed/2.dat'
splot "data/plane_".i."_1.dat" u 1:2:8
unset table

set table 'data/processed/3.dat'
splot "data/plane_".i."_2.dat" u 1:2:8
unset table

set table 'data/processed/4.dat'
splot "data/plane_".i."_3.dat" u 1:2:8
unset table

set table 'data/processed/5.dat'
splot "data/plane_".i."_4.dat" u 1:2:8
unset table

set table 'data/processed/6.dat'
splot "data/plane_".i."_5.dat" u 1:2:8
unset table

set table 'data/processed/7.dat'
splot "data/plane_".i."_6.dat" u 1:2:8
unset table

set table 'data/processed/8.dat'
splot "data/plane_".i."_7.dat" u 1:2:8
unset table

set table 'data/processed/9.dat'
splot "data/plane_".i."_8.dat" u 1:2:8
unset table

set table 'data/processed/10.dat'
splot "data/plane_".i."_9.dat" u 1:2:8
unset table

set table 'data/processed/11.dat'
splot "data/plane_".i."_10.dat" u 1:2:8 
unset table

set table 'data/processed/12.dat'
splot "data/plane_".i."_11.dat" u 1:2:8
unset table

set table 'data/processed/13.dat'
splot "data/plane_".i."_12.dat" u 1:2:8
unset table

set table 'data/processed/14.dat'
splot "data/plane_".i."_13.dat" u 1:2:8
unset table

set table 'data/processed/15.dat'
splot "data/plane_".i."_14.dat" u 1:2:8
unset table

set table 'data/processed/16.dat'
splot "data/plane_".i."_15.dat" u 1:2:8
unset table
########################################################################

reset 

set output "img/xy_a".i.".png"
set multiplot layout 4,4 rowsfirst title "Antenne ".i." x-y - view"

set style data lines

unset key
set tic scale 0
set view map
set dgrid3d 40, 40, 1

set contour base

#set palette negative 


#load 'BrBG.plt'
load 'Greys.plt'
unset xtics
unset ytics

plot "data/plane_".i."_0.dat" u 1:2:( $8/A0_max) with image, "data/processed/1.dat" w l lt -1 lw 1.5 lc rgb "#2f4f4f"
plot "data/plane_".i."_1.dat" u 1:2:( $8/A1_max) with image, "data/processed/2.dat" w l lt -1 lw 1.5 lc rgb "#2f4f4f"
plot "data/plane_".i."_2.dat" u 1:2:( $8/A2_max) with image, "data/processed/3.dat" w l lt -1 lw 1.5 lc rgb "#2f4f4f"
plot "data/plane_".i."_3.dat" u 1:2:( $8/A3_max) with image, "data/processed/4.dat" w l lt -1 lw 1.5 lc rgb "#2f4f4f"
plot "data/plane_".i."_4.dat" u 1:2:( $8/A4_max) with image, "data/processed/5.dat" w l lt -1 lw 1.5 lc rgb "#2f4f4f"
plot "data/plane_".i."_5.dat" u 1:2:( $8/A5_max) with image, "data/processed/6.dat" w l lt -1 lw 1.5 lc rgb "#2f4f4f"
plot "data/plane_".i."_6.dat" u 1:2:( $8/A6_max) with image, "data/processed/7.dat" w l lt -1 lw 1.5 lc rgb "#2f4f4f"
plot "data/plane_".i."_7.dat" u 1:2:( $8/A7_max) with image, "data/processed/8.dat" w l lt -1 lw 1.5 lc rgb "#2f4f4f"
plot "data/plane_".i."_8.dat" u 1:2:( $8/A8_max) with image, "data/processed/9.dat" w l lt -1 lw 1.5 lc rgb "#2f4f4f"
plot "data/plane_".i."_9.dat" u 1:2:( $8/A9_max) with image, "data/processed/10.dat" w l lt -1 lw 1.5 lc rgb "#2f4f4f"
plot "data/plane_".i."_10.dat" u 1:2:( $8/A1_max) with image, "data/processed/11.dat" w l lt -1 lw 1.5 lc rgb "#2f4f4f"
plot "data/plane_".i."_11.dat" u 1:2:( $8/A11_max) with image, "data/processed/12.dat" w l lt -1 lw 1.5 lc rgb "#2f4f4f"
plot "data/plane_".i."_12.dat" u 1:2:( $8/A12_max) with image, "data/processed/13.dat" w l lt -1 lw 1.5 lc rgb "#2f4f4f"
plot "data/plane_".i."_13.dat" u 1:2:( $8/A13_max) with image, "data/processed/14.dat" w l lt -1 lw 1.5 lc rgb "#2f4f4f"
plot "data/plane_".i."_14.dat" u 1:2:( $8/A14_max) with image, "data/processed/15.dat" w l lt -1 lw 1.5 lc rgb "#2f4f4f"
plot "data/plane_".i."_15.dat" u 1:2:( $8/A15_max) with image, "data/processed/16.dat" w l lt -1 lw 1.5 lc rgb "#2f4f4f"

w=.25
h=w

#set size   w,h
#set origin .25,.75

#splot "data/plane_".i."_1.dat" u 1:2:8
#set size   w,h
#set origin .50,.75
#splot "data/plane_".i."_2.dat" u 1:2:8
#set size   w,h
#set origin .75,.75
#splot "data/plane_".i."_3.dat" u 1:2:8
#set size   w,h
#set origin .00,.50
#splot "data/plane_".i."_4.dat" u 1:2:8
#set size   w,h
#set origin .25,.50
#splot "data/plane_".i."_5.dat" u 1:2:8
#set size   w,h
#set origin .50,.50
#splot "data/plane_".i."_6.dat" u 1:2:8
#set size   w,h
#set origin .75,.50
#splot "data/plane_".i."_7.dat" u 1:2:8 
#set size   w,h
#set origin .00,.25
#splot "data/plane_".i."_8.dat" u 1:2:8 
#set size   w,h
#set origin .25,.25
#splot "data/plane_".i."_9.dat" u 1:2:8 
#set size   w,h
#set origin .50,.25
#splot "data/plane_".i."_10.dat" u 1:2:8 
#set size   w,h
#set origin .75,.25
#splot "data/plane_".i."_11.dat" u 1:2:8 
#set size   w,h
#set origin .00,.00
#splot "data/plane_".i."_12.dat" u 1:2:8 
#set size   w,h
#set origin .25,.00
#splot "data/plane_".i."_13.dat" u 1:2:8 
#set size   w,h
set origin .50,.00
#splot "data/plane_".i."_14.dat" u 1:2:8 
#set size   w,h
#set origin .75,.00
#splot "data/plane_".i."_15.dat" u 1:2:8 

unset multiplot

i=i+1
if( i < t ) reread
i=0

quit
