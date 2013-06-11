set terminal png medium size 800,600 \
				xffffff x000000 xA0A0A0 \
				x202020 x202020 \
				x303030 xA0A0A0 \
				x404040 xA0A0A0 \
				x505050 xA0A0A0 \
				x606060 x404040 \
				x707070 xA0A0A0 \
				x808080 xA0A0A0 \
				x909090 xA0A0A0 enhanced
				
set output 'surface1.16.png'
set dummy u,v

set xtics 1.0
set ytics 2.0
set ztics 1.0
set parametric
set view 50, 60, 1, 1
set samples 800, 800
set isosamples 2, 33
set hidden3d offset 1 trianglepattern 3 undefined 1 altdiagonal bentover
#set ztics border in scale 1,0.5 nomirror norotate  offset character 0, 0, 0, -1.00000,0.25,1.00000
# set title "\"fence plot\" using separate parametric surfaces"
set xlabel "Referenzantenne"
set xlabel  offset character 0, 0, 0 font "" textcolor lt -1 norotate
set xrange [ 1.00000 : 8.00000 ] noreverse nowriteback
set ylabel "Permutation"
set ylabel  offset character 0, 0, 0 font "" textcolor lt -1 rotate by 90
set yrange [ 1.00000 : 35.00000 ] noreverse nowriteback
set zlabel "||Kondition||"
set zlabel  offset character 0, 0, -10 font "" textcolor lt -1 norotate
set zrange [ 0 : 1.10000 ] noreverse nowriteback

sinc(u,v) = sin(sqrt(u**2+v**2)) / sqrt(u**2+v**2)
# set style function impulses
# splot [u=0:1][v=0:4.99] x0, v, (u<0.5) ? -1 : sinc(x0,v) notitle, x1, v, (u<0.5) ? -1 : sinc(x1,v) notitle, 	x2, v, (u<0.5) ? -1 : sinc(x2,v) notitle, 	x3, v, (u<0.5) ? -1 : sinc(x3,v) notitle, 	x4, v, (u<0.5) ? -1 : sinc(x4,v) notitle, 	x5, v, (u<0.5) ? -1 : sinc(x5,v) notitle, 	x6, v, (u<0.5) ? -1 : sinc(x6,v) notitle, 	x7, v, (u<0.5) ? -1 : sinc(x7,v) notitle
# set style func linespoints
set grid
 splot  [u=0:9] [v=0:36]"data.dat" using 2:1:3 notitle w linespoints, \
		"data.dat" using 4:1:5 notitle w linespoints, \
		"data.dat" using 6:1:7 notitle w linespoints, \
		"data.dat" using 8:1:9 notitle w linespoints, \
		"data.dat" using 10:1:11 notitle w linespoints, \
		"data.dat" using 12:1:13 notitle w linespoints,  \
		"data.dat" using 14:1:15 notitle w linespoints, \
		"data.dat" using 16:1:17 notitle w linespoints
# set dgrid3d 10,10,3
# pm3d