set terminal latex
set output 'tikz_sin_cos-exmpl-gnuplottex-fig1.tex'
set terminal epslatex color % WICHTIG: diese Zeile teilt Gnuplot
                                % mit das die Ausgabe in Latex umgeleitet werden soll
    set nokey % ab hier folgt üblicher Gnuplot Code
    set parametric
    set hidden3d
    set view 45,60
    set isosamples 200,15
    splot [-3*pi:3*pi][-pi:pi] cos(u)*cos(v)+3*cos(u)*(1.5+sin(u*5/3)/2),\
    sin(u)*cos(v)+3*sin(u)*(1.5+sin(u*5/3)/2), sin(v)+2*cos(u*5/3)
  
