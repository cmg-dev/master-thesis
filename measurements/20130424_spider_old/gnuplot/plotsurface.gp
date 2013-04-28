#Gnuplot Script file for data visualization
#
set style data lines
set contour base

set xrange [-1:10]
set yrange [-1:10]
set zrange [-100:300]
set view 20,20,1.0,1.0
set dgrid3d 10,10,3
show contour

set pm3d
set view map
set contour
set key outside
set palette gray negative
