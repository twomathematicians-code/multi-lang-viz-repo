# 04_contour.gnu - Contour plot using math function
set terminal svg size 1200,700 enhanced font "DejaVu Sans,14" background rgb "#16213e"
set output "/home/z/my-project/download/multi-lang-viz-repo/output/gnuplot/04_contour.svg"

set title "Contour Plot: x^2 + y^2" textcolor rgb "white" font ",16"
set xlabel "X" textcolor rgb "white" font ",13"
set ylabel "Y" textcolor rgb "white" font ",13"

set view map
set contour base
set cntrparam levels 10
set isosamples 50

set grid front linestyle 1 linecolor rgb "#333355" linewidth 0.3

set border linecolor rgb "#555577"
set xtics textcolor rgb "white" font ",11"
set ytics textcolor rgb "white" font ",11"
set ztics textcolor rgb "white" font ",11"
set cbtics textcolor rgb "white" font ",11"

unset key

splot [-5:5] [-5:5] (x**2 + y**2)
