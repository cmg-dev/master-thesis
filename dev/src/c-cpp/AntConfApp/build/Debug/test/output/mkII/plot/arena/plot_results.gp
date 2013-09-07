#
set view map

set cbrange [0:.5]

load '~/dev/gnuplot-colorbrewer/sequential/PuBuGn.plt
#load '~/dev/gnuplot-colorbrewer/sequential/Reds.plt
#load '~/dev/gnuplot-colorbrewer/sequential/BuGn.plt

set palette negativ

d=1.259 
splot 'VectorStats_2000_2090_A0.dat' u 6:3:(($10<d) ? 1-($10/d) : 1-(d/$10)) w image
d=1.894 
splot 'VectorStats_2000_2090_A1.dat' u 6:3:(($10<d) ? 1-($10/d) : 1-(d/$10)) w image
d=2.334
splot 'VectorStats_2000_2090_A2.dat' u 6:3:(($10<d) ? 1-($10/d) : 1-(d/$10)) w image
d=1.661
splot 'VectorStats_2000_2090_A3.dat' u 6:3:(($10<d) ? 1-($10/d) : 1-(d/$10)) w image
d=2.399
splot 'VectorStats_2000_2090_A4.dat' u 6:3:(($10<d) ? 1-($10/d) : 1-(d/$10)) w image
d=1.851
splot 'VectorStats_2000_2090_A5.dat' u 6:3:(($10<d) ? 1-($10/d) : 1-(d/$10)) w image
d=2.055
splot 'VectorStats_2000_2090_A6.dat' u 6:3:(($10<d) ? 1-($10/d) : 1-(d/$10)) w image
d=1.574
splot 'VectorStats_2000_2090_A7.dat' u 6:3:(($10<d) ? 1-($10/d) : 1-(d/$10)) w image


