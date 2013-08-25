 set terminal pngcairo enhanced size 1024,1024
 set output 'multi2.png'

#set terminal wxt size 2048,512 enhanced font 'Verdana,10' persist
# color definitions
set style line  1 lc rgb '#0060ad' pt 5 ps 0.2 lt 1 lw 2    # blue

unset key

# Enable the use of macros
set macros

# Placement of the a,b,c,d labels in the graphs
POS = "at graph 0.92,0.9 font ',8'"


# x- and ytics for each row resp. column
NOXTICS = "set xtics ('' 0,'' 1,'' 2,'' 3,'' 4,'' 5,'' 6,'' 7,'' 8, '' 9 ); \
          unset xlabel"
XTICS = "set xtics ('0' 0,'1' 1,'2' 2,'3' 3,'4' 4,'5' 5,'6' 6,'7' 7,'8' 8, '9' 9 ); \
          set xlabel 'x'"
NOYTICS = "set ytics ('' 0,'' 1,'' 2,'' 3,'' 4,'' 5,'' 6,'' 7,'' 8, '' 9 ); \
	  unset ylabel"
YTICS = "set ytics ('0' 0,'1' 1,'2' 2,'3' 3,'4' 4,'5' 5,'6' 6,'7' 7,'8' 8, '9' 9 ); \
	set ylabel 'y'"

set style data lines
#set contour base

set xrange [-1:10]
set yrange [-1:10]
set xrange [-.1:9]
set yrange [-.1:9]
set zrange [-300:300]
set view 20,20,1.0,1.0

set dgrid3d 20,20,3
#show contour

#set hidden3d

#set pm3d map
#set view map
#set contour

set ticslevel 0.0

set pm3d at b
#set hidden3d
set grid
set palette cubehelix

set view 60,40
set palette defined ( 1 0 0 0 , 2 1 1 1 , 3 0 0 0 )
set isosamples 100,100; set samples 100,100;

set multiplot layout 1,4 rowsfirst 
unset colorbox

unset key
# unset colorbox
#@TMARGIN; @LMARGIN
@NOXTICS; @YTICS
# set lable 1 'A1_1' at @POS
splot "gp_ready_a1_1.txt" 

#@M1MARGIN; @LMARGIN
#@NOXTICS; @YTICS
# set lable 1 'A2_1' at @POS
splot "gp_ready_a2_1.txt"

#@M2MARGIN; @LMARGIN
#@NOXTICS; @YTICS
splot "gp_ready_a3_1.txt"

#@BMARGIN; @LMARGIN
#@XTICS; @YTICS
splot "gp_ready_a4_1.txt" 

unset multiplot
