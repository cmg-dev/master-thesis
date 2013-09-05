# set terminal pngcairo  transparent enhanced font "arial,10" fontscale 1.0 size 500, 350 
# set output 'rgb_variable.5.png'
unset border
set angles degrees
set label 99 "" at 0, 0, 0 left norotate back nopoint offset character 0, 0, 0
set xzeroaxis linetype -1 linecolor rgb "red"  linewidth 2.000
set yzeroaxis linetype -1 linecolor rgb "green"  linewidth 2.000
set zzeroaxis linetype -1 linecolor rgb "blue"  linewidth 2.000
set xyplane at 0
set xtics axis in scale 1,0.5 nomirror norotate  offset character 0, 0, 0 autojustify
set ytics axis in scale 1,0.5 nomirror norotate  offset character 0, 0, 0 autojustify
set ztics axis in scale 1,0.5 nomirror norotate  offset character 0, 0, 0 autojustify
set title "Both RGB color information\n and point size controlled by input" 
set xlabel "Red" 
set xlabel  offset character 0, 0, 0 font "" textcolor rgb "red"  norotate
set xrange [ 0.00000 : 255.000 ] noreverse nowriteback
set ylabel "Green" 
set ylabel  offset character 0, 0, 0 font "" textcolor rgb "green"  rotate by -270
set yrange [ 0.00000 : 255.000 ] noreverse nowriteback
set zlabel "Blue" 
set zlabel  offset character 0, 0, 0 font "" textcolor rgb "blue"  norotate
set zrange [ 0.00000 : 255.000 ] noreverse nowriteback
set lmargin  5
set bmargin  2
set rmargin  5
rgb(r,g,b) = int(r)*65536 + int(g)*256 + int(b)
xrgb(r,g,b) = (g-b)/255. * cos(30.)
yrgb(r,g,b) = r/255. - (g+b)/255. * sin(30.)
GPFUN_rgb = "rgb(r,g,b) = int(r)*65536 + int(g)*256 + int(b)"
GPFUN_xrgb = "xrgb(r,g,b) = (g-b)/255. * cos(30.)"
GPFUN_yrgb = "yrgb(r,g,b) = r/255. - (g+b)/255. * sin(30.)"

splot 'data.dat' using 1:2:3:4:(rgb($1,$2,$3)) with points pt 7 ps variable lc rgb variable\
	title "variable pointsize and rgb color computed from coords"
	
#splot 'rgb_variable.dat' using 1:2:3::(rgb($1,$2,$3)) with points pt 7 ps variable lc rgb variable\
#	title "variable pointsize and rgb color computed from coords"