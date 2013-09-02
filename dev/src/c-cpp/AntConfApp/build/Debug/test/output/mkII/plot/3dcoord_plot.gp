#
#This script generated the three-dimensional coord plot
#

set terminal pngcairo truecolor transparent background "#ffffff" enhanced font "arial,10" size 1000,1000

set style line 1 linetype 1 linecolor rgb "#2f4f4f"  linewidth 1.000 pointtype 7 pointsize 1 pointinterval 1

set output "img/Coord.png"
set multiplot layout 2,2

unset key

set grid
set ticslevel 0

#plot "data/coord_plot.dat" u 1:2 every ::1:::

set title "x-y View"
plot "data/coord_plot.dat" u 1:2 ls 1

set title "x-z - View"
set xrange [-2:2]
set yrange [-0:2]
plot "data/coord_plot.dat" u 1:3 ls 1

set title "y-z View"
set xrange [-2:2]
set yrange [0:2]
plot "data/coord_plot.dat" u 2:3 ls 1

set title "3d View"
#3d plot
set xrange [-3:3]
set yrange [-3:3]
set zrange [0:2]
set view 70, 65
splot "data/coord_plot.dat" u 1:2:3 ls 1

unset multiplot
