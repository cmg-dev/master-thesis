#reset

unset key
#unset colorbox
#set ytics offset 0,-1
#set ticslevel 0
#min = 0
#col = 8

#set xlabel "Permutation"
#set xlabel  offset character 0, 0, 0 font "" textcolor lt -1 norotate
set xrange [ -1 : 8 ] noreverse nowriteback
#set ylabel "Referenzantenne"
#set ylabel  offset character 0, 0, 0 font "" textcolor lt -1 rotate by 90
set yrange [ -1 : 10 ] noreverse nowriteback
#set zlabel "||Kondition||"
#set zlabel  offset character 0, 0, 0 font "" textcolor lt -0 rotate by 90
#set zrange [ -3.2 : 1.10000 ] noreverse nowriteback

#set palette defined ( 1 1 1 1 , 2 1 1 1, 3 1 1 1, 4 1 1 1 , 5 1 1 1, 6 1 1 1, 7 1 1 1, 8 1 1 1, 9 1 1 1, 10 0 0 0 )


set terminal pngcairo enhanced size 600,600
set output 'matplot.png'

#set palette gray
#plot 'results.dat' matrix with image


set view map
set style data pm3d
set style function pm3d

set palette model RGB
set palette model RGB defined (0 "white", 1e-19 "dark-red", 8 "orange", 10 "yellow", 11 "dark-green" )

splot 'results.dat' matrix with image

