#i=0
#j=0
#a=9
#m=5
#n=20

load "init.gp"

print "** " , m , " Trails with " , n , " runs"
print "** " , a  , " Objectives/plot "
print ""

print "**** Plotting Boxes"
load "kondensierte_boxen.gp"

print "**** Plotting Scatter"
load "scatter.gp"

#print "**** Plotting Points"
#load "kondensierte_punkte.gp"

print "**** Plotting Lines"
load "kondensierte_linien.gp"

print "**** Plotting Candles"
load "kondensierte_kerzen.gp"

