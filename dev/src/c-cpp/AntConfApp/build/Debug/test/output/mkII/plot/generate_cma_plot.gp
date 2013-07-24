set terminal pngcairo enhanced font "arial,10" size 500, 350 
set output 'img/objectVar.0.png'

set key outside right top vertical Right noreverse enhanced nobox 

set grid

plot "data0.dat" u 1:4 w lines title "0", \
		"" u 1:5 w lines title "1", \
		"" u 1:6 w lines title "2", \
		"" u 1:7 w lines title "3", \
		"" u 1:8 w lines title "4", \
		"" u 1:9 w lines title "5", \
		"" u 1:10 w lines title "6", \
		"" u 1:11 w lines title "7", \
		"" u 1:12 w lines title "8"

set output 'img/sigma.0.png'

plot "data0.dat" u 1:2 w lines title "$\sigma$"

