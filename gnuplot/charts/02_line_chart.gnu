# 02_line_chart.gnu - Multi-line trend chart
set terminal svg size 1200,700 enhanced font "DejaVu Sans,14" background rgb "#16213e"
set output "/home/z/my-project/download/multi-lang-viz-repo/output/gnuplot/02_line_chart.svg"

set title "Language Popularity Trends (2018-2024)" textcolor rgb "white" font ",16"
set xlabel "Year" textcolor rgb "white" font ",13"
set ylabel "Popularity Index" textcolor rgb "white" font ",13"

set yrange [0:100]
set xrange [2017.5:2024.5]
set grid y linestyle 1 linecolor rgb "#333355" linewidth 0.5
set grid x linestyle 1 linecolor rgb "#333355" linewidth 0.5

set border linecolor rgb "#555577"
set xtics textcolor rgb "white" font ",11"
set ytics textcolor rgb "white" font ",11"

set key top left textcolor rgb "white" font ",12"

$DATA << EOD
2018  68  80  55  25  10
2019  72  82  56  30  15
2020  78  84  57  35  22
2021  83  85  58  38  28
2022  87  86  59  42  32
2023  90  87  60  44  35
2024  92  88  60  45  38
EOD

plot "$DATA" using 1:2 with linespoints linewidth 2.5 pointtype 7 pointsize 1.5 linecolor rgb "#ff6b6b" title "Python", \
     "$DATA" using 1:3 with linespoints linewidth 2.5 pointtype 7 pointsize 1.5 linecolor rgb "#4ecdc4" title "JavaScript", \
     "$DATA" using 1:4 with linespoints linewidth 2.5 pointtype 7 pointsize 1.5 linecolor rgb "#ffc300" title "C++", \
     "$DATA" using 1:5 with linespoints linewidth 2.5 pointtype 7 pointsize 1.5 linecolor rgb "#00a8ff" title "Go", \
     "$DATA" using 1:6 with linespoints linewidth 2.5 pointtype 7 pointsize 1.5 linecolor rgb "#a973ff" title "Rust"
