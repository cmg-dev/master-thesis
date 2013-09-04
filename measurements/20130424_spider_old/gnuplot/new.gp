set loadpath '/d/dev/gnuplot-colorbrewer/diverging' \
    '/d/dev/gnuplot-colorbrewer/qualitative' \
    '/d/dev/gnuplot-colorbrewer/sequential'
set loadpath 'd:/dev/gnuplot-colorbrewer/diverging' \
    'd:/dev/gnuplot-colorbrewer/qualitative' \
    'd:/dev/gnuplot-colorbrewer/sequential'
set loadpath 'd:/06_dev/gnuplot-colorbrewer/diverging' \
    'd:/06_dev/gnuplot-colorbrewer/qualitative' \
    'd:/06_dev/gnuplot-colorbrewer/sequential'
	
set terminal pngcairo enhanced transparent size 800,800
set output '1.png'

#set terminal wxt size 2048,512 enhanced font 'Verdana,10' persist
# color definitions
set style line  1 lc rgb '#0060ad' pt 5 ps 0.2 lt 1 lw 2    # blue

unset key

reset
set dgrid3d 25,25,3
stats "gp_ready_a1_1.txt"  u 3 name "A1" 
stats "gp_ready_a2_1.txt"  u 3 name "A2"
stats "gp_ready_a3_1.txt"  u 3 name "A3"
stats "gp_ready_a4_1.txt"  u 3 name "A4"

set contour base
set cntrparam level incremental -.1, .01, .1
set isosample 250, 250
unset surface

set table 'cont1.dat'
splot "gp_ready_a1_1.txt" u 1:2:( $3 > 0 ? $3/A1_max : -$3/A1_min)
unset table


set table 'cont2.dat'
splot "gp_ready_a2_1.txt" u 1:2:( $3 > 0 ? $3/A2_max : -$3/A2_min)
unset table


set table 'cont3.dat'
splot "gp_ready_a3_1.txt" u 1:2:( $3 > 0 ? $3/A3_max : -$3/A3_min)
unset table


set table 'cont4.dat'
splot "gp_ready_a4_1.txt" u 1:2:( $3 > 0 ? $3/A4_max : -$3/A4_min)
unset table
reset

set style data lines

set autoscale
set xrange [-0.5:9.5]
set yrange [-.5:9.5]
set xtics left
set ytics left
set view 20,20,1.0,1.0

set dgrid3d 30,30,3
set ticslevel 0.0

set pm3d at b
unset grid
load 'BrBG.plt'

#set palette cubehelix

set view 150,45
#set palette defined ( 1 0 0 0 , 2 1 1 1 , 3 0 0 0 )
set isosamples 100,100; set samples 100,100;

unset key
set zrange [-3:3]
set output 'Plate0_A1.png'
splot "gp_ready_a1_1.txt" u 1:2:( $3 > 0 ? $3/A1_max : -$3/A1_min) lc rgb "#2f4f4f"

set output 'Plate0_A2.png'
splot "gp_ready_a2_1.txt" u 1:2:( $3 > 0 ? $3/A2_max : -$3/A2_min) lc rgb "#2f4f4f"

set output 'Plate0_A3.png'
splot "gp_ready_a3_1.txt" u 1:2:( $3 > 0 ? $3/A3_max : -$3/A3_min) lc rgb "#2f4f4f"

set output 'Plate0_A4.png'
splot "gp_ready_a4_1.txt" u 1:2:( $3 > 0 ? $3/A4_max : -$3/A4_min) lc rgb "#2f4f4f"

unset surface

unset grid
set view map
unset key


reset
set contour base
set cntrparam level incremental -3, 0.5, 3
set cntrparam bspline
unset surface

set xrange [-1:10]
set yrange [-1:10]
set xtics 0,1,9
set ytics 0,1,9
set grid
load 'BrBG.plt'
#load 'PiYg.plt'
#load 'PRGn.plt'
#load 'PuOr.plt'
#load 'RdGy.plt'
#load 'RdBu.plt'

set isosample 250, 250
unset key

#draw contours ###########################################
set terminal pngcairo transparent size 900,800
set output 'c1.png'

plot "gp_ready_a1_1.txt" u 1:2:( $3 > 0 ? $3/A1_max : -$3/A1_min) with image, "cont1.dat" w l lt -1 lw 2.5 lc rgb "#2f4f4f"

set output 'c2.png'
plot "gp_ready_a2_1.txt" u 1:2:( $3 > 0 ? $3/A2_max : -$3/A2_min) with image, "cont2.dat" w l lt -1 lw 2.5 lc rgb "#2f4f4f"

set output 'c3.png'
plot "gp_ready_a3_1.txt" u 1:2:( $3 > 0 ? $3/A3_max : -$3/A3_min) with image, "cont3.dat" w l lt -1 lw 2.5 lc rgb "#2f4f4f"

set output 'c4.png'
plot "gp_ready_a4_1.txt" u 1:2:( $3 > 0 ? $3/A4_max : -$3/A4_min) with image, "cont4.dat" w l lt -1 lw 2.5 lc rgb "#2f4f4f"

#draw countours wo colormap ###########################################
set terminal pngcairo transparent enhanced size 800,800
unset colorbox
unset xtics
unset ytics
unset ztics

set output 'c1_.png'
plot "gp_ready_a1_1.txt" u 1:2:( $3 > 0 ? $3/A1_max : -$3/A1_min) with image, "cont1.dat" w l lt -1 lw 2.5 lc rgb "#2f4f4f"

set output 'c2_.png'
plot "gp_ready_a2_1.txt" u 1:2:( $3 > 0 ? $3/A2_max : -$3/A2_min) with image, "cont2.dat" w l lt -1 lw 2.5 lc rgb "#2f4f4f"

set output 'c3_.png'
plot "gp_ready_a3_1.txt" u 1:2:( $3 > 0 ? $3/A3_max : -$3/A3_min) with image, "cont3.dat" w l lt -1 lw 2.5 lc rgb "#2f4f4f"

set output 'c4_.png'
plot "gp_ready_a4_1.txt" u 1:2:( $3 > 0 ? $3/A4_max : -$3/A4_min) with image, "cont4.dat" w l lt -1 lw 2.5 lc rgb "#2f4f4f"

#draw maps ###########################################
set terminal pngcairo transparent enhanced size 800,800
set dgrid3d 20,20,3
set view map
set contour base 
set contour base
set cntrparam level incremental -1, .5, 1
set isosample 250, 250
set style data lines

set colorbox 
#unset surface
set output 'm1.png'
splot "gp_ready_a1_1.txt" u 1:2:( $3 > 0 ? $3/A1_max : -$3/A1_min)

set output 'm2.png'
splot "gp_ready_a2_1.txt" u 1:2:( $3 > 0 ? $3/A2_max : -$3/A2_min)

set output 'm3.png'
splot "gp_ready_a3_1.txt" u 1:2:( $3 > 0 ? $3/A3_max : -$3/A3_min)

set output 'm4.png'
splot "gp_ready_a4_1.txt" u 1:2:( $3 > 0 ? $3/A4_max : -$3/A4_min)

#unset multiplot
