# 05_surface.gnu - 3D surface plot
set terminal svg size 1200,700 enhanced font "DejaVu Sans,14" background rgb "#16213e"
set output "/home/z/my-project/download/multi-lang-viz-repo/output/gnuplot/05_surface.svg"

set title "3D Surface: sin(x)*cos(y)" textcolor rgb "white" font ",16"
set xlabel "X" textcolor rgb "white" font ",13"
set ylabel "Y" textcolor rgb "white" font ",13"
set zlabel "Z" textcolor rgb "white" font ",13"

set view 45,30
set isosamples 30,30
set samples 30,30

set border linecolor rgb "#555577"
set xtics textcolor rgb "white" font ",11"
set ytics textcolor rgb "white" font ",11"
set ztics textcolor rgb "white" font ",11"

unset key

splot [-3:3] [-3:3] sin(x)*cos(y) with lines palette
