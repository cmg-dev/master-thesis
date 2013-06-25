reset

unset key
unset colorbox
set ytics offset 0,-1
set ticslevel 0
min = 0
col = 8

set xlabel "Permutation"
set xlabel  offset character 0, 0, 0 font "" textcolor lt -1 norotate
set xrange [ 1.00000 : 10.00000 ] noreverse nowriteback
set ylabel "Referenzantenne"
set ylabel  offset character 0, 0, 0 font "" textcolor lt -1 rotate by 90
set yrange [ 0. : 5. ] reverse nowriteback
set zlabel "||Kondition||"
set zlabel  offset character 0, 0, 0 font "" textcolor lt -0 rotate by 90
set zrange [ -3.2 : 1.10000 ] noreverse nowriteback

DATA = ""
DATA2 = ""
PALETTE = "set palette defined ("

pr(x, y) = sprintf("%f %f\n", x, y)
zero_line(x, y) = DATA.sprintf("\n").DATA2.sprintf("\n%f %f\n", x, y)
# zero_pal(x) = sprintf("%d %.3f %.3f %.3f", x, rand(0), rand(0), rand(0))
zero_pal(x) = sprintf("%d %.3f %.3f %.3f", x, x, x, x)

f(x, y) = ($0 == 0 ? (DATA = zero_line($1, x), DATA2 = pr($1, min), PALETTE = PALETTE.zero_pal(y).", ") : \
        (DATA = DATA.pr($1, x), DATA2 = DATA2.pr($1, min)), x)

plot for [i=2:col+1] 'results.dat' u 1:(f(column(i), i))

DATA = DATA.sprintf("\n").DATA2

set print 'results.tab'
print DATA
set print

# eval(PALETTE.zero_pal(col).")")
       set palette model RGB
       set palette defined ( 0 "blue", 3 "green", 6 "yellow", 10 "red" )
       
set view 50, 335, 1, 1

#set terminal pngcairo enhanced size 1024,768

#set output 'fenceModell3x3.png'


splot for [i=0:col-1] 'results.tab' every :::(2*i)::(2*i+1) u 1:(i):2:(i+2) w pm3d

# splot for[i=0:col-1] 'results.tab' every :::(2*i)::(2*i+1) u 1:(i):2 w l lt -1
