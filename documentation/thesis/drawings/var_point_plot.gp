#
# Demo of reading color information from the data file itself
#

#
rgb(r,g,b) = int(r)*65536 + int(g)*256 + int(b)

#
set border -1 front linetype -1 linewidth 1.000
set ticslevel 0
set xtics border
set ytics border
set ztics border
#
#
set xlabel "Red" tc rgb "red"
set xrange [0:255]
set ylabel "Green" tc rgb "green"
set yrange [0:255]
set zlabel "Blue" tc rgb "blue"
set zrange [0:255]

#
#
# Unfortunately, not all platforms allow us to read hexadecimal constants
# from a data file. Warn the user if that is the case.
#
if (0 == int('0x01')) \
   set label 99 at screen .05, screen .15 "If you see only black dots,\nthis means your platform does not \nsupport reading hexadecimal constants\nfrom a data file. Get a newer libc."

set hidden3d
#splot 'data.dat' using 1:2:3:(5):4 with points pt 7 ps variable lc rgb variable \
 #     title "variable pointsize and rgb color read as hexidecimal"

splot 'data.dat' using 1:2:3:4 with points lt 1 pt 6 ps variable \
      title "variable pointsize and rgb color read as hexidecimal"
