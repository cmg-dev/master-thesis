#
#base="VectorStats_2000_2090"

set terminal pngcairo truecolor transparent enhanced font "arial,10" size 800,1600.21

set macros
set output "result.png"

set multiplot layout 4,2 rowsfirst

set view map

set autoscale 
set cbrange [0:.35]
set xrange [-1:9]
set yrange [-1:10]
#load '~/dev/gnuplot-colorbrewer/sequential/PuBuGn.plt
#load '~/dev/gnuplot-colorbrewer/sequential/Reds.plt
load '~/dev/gnuplot-colorbrewer/sequential/BuGn.plt
load '~/dev/gnuplot-colorbrewer/diverging/Spectral.plt
#load '~/dev/gnuplot-colorbrewer/diverging/PiYG.plt
#load '~/dev/gnuplot-colorbrewer/diverging/RdGy.plt
#load '~/dev/gnuplot-colorbrewer/sequential/Purples.plt
#load '~/dev/gnuplot-colorbrewer/qualitative/Accent.plt

unset key
set colorbox
#unset colorbox

set palette negativ
#set palette positiv

set size .5, .25
set origin .0,.75

ROW0="set tmargin at screen .97; set bmargin at screen .77"
ROW1="set tmargin at screen .72; set bmargin at screen .52"
ROW2="set tmargin at screen .48; set bmargin at screen .27"
ROW3="set tmargin at screen .23; set bmargin at screen .02"
COL0="set lmargin at screen .02; set rmargin at screen .42"
COL1="set lmargin at screen .52; set rmargin at screen .92"

D0="d=1.259; print '',d"
D1="d=1.894; print '',d"
D2="d=2.334; print '',d"
D3="d=1.661; print '',d"
D4="d=2.399; print '',d"
D5="d=1.851; print '',d"
D6="d=2.055; print '',d"
D7="d=1.574; print '',d"


F0="f=base.'_A0.dat'"
F1="f=base.'_A1.dat'"
F2="f=base.'_A2.dat'"
F3="f=base.'_A3.dat'"
F4="f=base.'_A4.dat'"
F5="f=base.'_A5.dat'"
F6="f=base.'_A6.dat'"
F7="f=base.'_A7.dat'"

PLOT="splot f u 6:3:(($10>d) ? ($10-d) : (d-$10)) w image"

#timing plot
#PLOT="splot f u 6:3:9 w image"
#PLOT="splot f u 6:3:(($10<d) ? (1-($10/d)) : (1-(d/$10))) w image"
#PLOT="splot f u 6:3:10 w image"

#####################################################
@ROW0
@COL0

set xtics 0,1,8
set ytics 0,1,9
set cbtics
set title "Antenne 1"

@D0
@F0
@PLOT

#####################################################
@COL1
unset ytics
unset xtics
set title "Antenne 2"

@D1
@F1
@PLOT

#####################################################
@ROW1
@COL0
set title "Antenne 3"

@D2
@F2
@PLOT

#####################################################
@COL1
set title "Antenne 4"

@D3
@F3
@PLOT

#####################################################
@COL0
@ROW2
set title "Antenne 5"

@D4
@F4
@PLOT

#####################################################
@COL1
set title "Antenne 6"

@D5
@F5
@PLOT

#####################################################
@COL0
@ROW3
set title "Antenne 7"

@D6
@F6
@PLOT

#####################################################
@COL1
set title "Antenne 8"

@D7
@F7
@PLOT

unset multiplot
