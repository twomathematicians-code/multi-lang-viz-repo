# 03_scatter.gnu - Scatter plot chart_types vs performance
set terminal svg size 1200,700 enhanced font "DejaVu Sans,14" background rgb "#16213e"
set output "/home/z/my-project/download/multi-lang-viz-repo/output/gnuplot/03_scatter.svg"

set title "Chart Types vs Performance by Language" textcolor rgb "white" font ",16"
set xlabel "Chart Types Score" textcolor rgb "white" font ",13"
set ylabel "Performance Score" textcolor rgb "white" font ",13"

set xrange [40:95]
set yrange [35:100]
set grid y linestyle 1 linecolor rgb "#333355" linewidth 0.5
set grid x linestyle 1 linecolor rgb "#333355" linewidth 0.5

set border linecolor rgb "#555577"
set xtics textcolor rgb "white" font ",11"
set ytics textcolor rgb "white" font ",11"

set key top left textcolor rgb "white" font ",12"

$DATA << EOD
"Python"        85 45
"JavaScript"    78 55
"C++"            65 95
"Java"           72 70
"Go"             55 88
"Rust"           50 92
"TypeScript"     70 52
"Swift"          45 80
"Kotlin"         58 75
EOD

plot "$DATA" using 2:3:xticlabels(1) with points pt 7 ps 2.5 lc rgb "#48dbfb" title "Languages"
