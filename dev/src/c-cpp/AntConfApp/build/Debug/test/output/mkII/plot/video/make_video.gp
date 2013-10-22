#!/usr/local/bin/gnuplot
#
# Creating a video animation with the do command
#
# AUTHOR: Hagen Wierstorf
# GNUPLOT: 4.6 patchlevel 0

reset

# png
set terminal pngcairo size 1024,1024 enhanced font 'Verdana,10'

# color definitions
set style line 1 lc rgb '#0060ad' lt 1 pt 7 lw 3 # --- blue
set style line 2 lc rgb '#2f4f4f' lt 1 lw 2 pt 10
set style line 3 lc rgb '#708090' pt 4 ps 3 
# border
set style line 101 lc rgb '#404040' lt 5 lw 2
set border 127 back ls 101
set tics out nomirror scale 0
set format ''

unset key
set view 45,140
#set xtics 0.1
#set ytics 0.15
#set lmargin screen 0.02
#set rmargin screen 0.98

do for [jj=0:7] {
    set autoscale
    fname=sprintf('../../E100.%1i_0.dat',jj)
    stats fname u 4 name "Test"
    print "reading from "
    print "reading from ".fname." with ",Test_records," Lines"

    LOWERX=-6;UPPERX=6;
    LOWERY=-6;UPPERY=6;
    LOWERZ=0;UPPERZ=2;

    #do for [ii=1:Test_records] {
    do for [ii=1:100] {
        set output sprintf('hrir_frame%03.0f.png',ii)
        set multiplot layout 2,2

        #zoom in
        if(ii>20) {
            LOWERX=-1.2;UPPERX=2.2;
            LOWERY=-2;UPPERY=2.2;
            LOWERZ=0;UPPERZ=2;
        }
      
        unset key

        set grid
        set ticslevel 0

        set title "x-y View"
        set xrange [LOWERX:UPPERX]
        set yrange [LOWERY:UPPERY]
        plot fname u 4:5 every ::1::ii w lp ls 2, \
            fname u 4:5 every ::ii::ii w p ls 1, \
            '../data/coord_plot.dat' u 1:2 w p ls 3

        set title "x-z View"
        set xrange [LOWERX:UPPERX]
        set yrange [0:2]
        plot fname u 4:6 every ::1::ii w lp ls 2, \
            fname u 4:6 every ::ii::ii w p ls 1, \
            '../data/coord_plot.dat' u 1:3 w p ls 3

        set title "y-z View"
        set xrange [LOWERY:UPPERY]
        set yrange [LOWERZ:UPPERZ]
        plot fname u 5:6 every ::1::ii w lp ls 2, \
            fname u 5:6 every ::ii::ii w p ls 1, \
            '../data/coord_plot.dat' u 2:3 w p ls 3

        set title "3D View"
        #3d plot
        set xrange [-2:2]
        set yrange [-2:2]
        set zrange [0:2]
        set view 50, 110
        splot fname u 4:5:6 every ::1::ii w lp ls 2, \
            fname u 4:5:6 every ::ii::ii w p ls 1, \
            '../data/coord_plot.dat' u 1:2:3 w p ls 3

        unset multiplot
        #splot fname u 4:5:6 every ::1::ii w l ls 1, \
                 #fname u 4:5:6 every ::ii::ii w p ls 1
    }
    ## Create movie with mencoder
    ENCODER=system('which mencoder');
    aviout=sprintf('hrir%i.avi',jj)
    webmout = sprintf('hrir%i.webm',jj)
    #if (strlen(ENCODER)==0){ print '=== mencoder not found ==='; exit}
    CMD = 'mencoder mf://*.png -mf fps=8:type=png -ovc lavc -lavcopts vcodec=mpeg4:mbd=2:trell -oac copy -o '.aviout
    system(CMD)

    # Create webm
    ENCODER = system('which ffmpeg')
    #if (strlen(ENCODER)==0){ print '=== ffmpeg not found, exit ==='; exit}
    CMD = 'ffmpeg -i '.aviout.' '.webmout
    print " ".CMD

    system(CMD)
}


# Clear directory
system('rm *.png')
