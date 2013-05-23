#Gnuplot Script file for data visualization

reset 

set terminal wxt size 1000,1000 enhanced font 'Verdana,10' persist

# color definitions
set style line  1 lc rgb '#0060ad' pt 5 ps 0.2 lt 1 lw 2    # blue

unset key

# Enable the use of macros
set macros

# Placement of the a,b,c,d labels in the graphs
POS = "at graph 0.92,0.9 font ',8'"

# TMARGIN = "set tmargin at screen 0.90; set bmargin at screen 0.55"
# BMARGIN = "set tmargin at screen 0.55; set bmargin at screen 0.20"

TMARGIN = "set tmargin at screen 0.96; set bmargin at screen 0.74"
M1MARGIN = "set tmargin at screen 0.72; set bmargin at screen 0.50"
M2MARGIN = "set tmargin at screen 0.48; set bmargin at screen 0.26"
BMARGIN = "set tmargin at screen 0.24; set bmargin at screen 0.02"

LMARGIN = "set lmargin at screen 0.10; set rmargin at screen 0.32"
RMARGIN = "set lmargin at screen 0.42; set rmargin at screen 0.64"

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
set contour base

set xrange [-1:10]
set yrange [-1:10]
set zrange [-300:300]
#set view 20,20,1.0,1.0
set dgrid3d 20,20,3
show contour

set pm3d map
# set view map
set contour

set palette defined ( 1 0 0 0 , 2 1 1 1 , 3 0 0 0 )

set multiplot layout 4,2 rowsfirst \
      title "Surface Plot of Antenna Data"


# unset colorbox
@TMARGIN; @LMARGIN
@NOXTICS; @YTICS
# set lable 1 'A1_1' at @POS
splot "gp_ready_a1_1.txt" 

@TMARGIN; @RMARGIN
@NOXTICS; @NOYTICS
# set lable 1 'A1_1' at @POS
splot "gp_ready_a1_2.txt" 

#@M1MARGIN; @LMARGIN
#@NOXTICS; @YTICS
## set lable 1 'A2_1' at @POS
#splot "gp_ready_a2_1.txt" 

#@M1MARGIN; @RMARGIN
#@NOXTICS; @NOYTICS
## set lable 1 'A2_2' at @POS
#splot "gp_ready_a2_2.txt" 

#@M2MARGIN; @LMARGIN
#@NOXTICS; @YTICS
#splot "gp_ready_a3_1.txt"

#@M2MARGIN; @RMARGIN
#@NOXTICS; @NOYTICS
#splot "gp_ready_a3_2.txt" 

@BMARGIN; @LMARGIN
@XTICS; @YTICS
splot "gp_ready_a4_1.txt" 

set colorbox

@BMARGIN; @RMARGIN
@XTICS; @NOYTICS
splot "gp_ready_a4_2.txt"

unset multiplot
