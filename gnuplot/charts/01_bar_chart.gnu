# 01_bar_chart.gnu - Grouped bar chart of 9 languages
set terminal svg size 1200,700 enhanced font "DejaVu Sans,14" background rgb "#16213e"
set output "/home/z/my-project/download/multi-lang-viz-repo/output/gnuplot/01_bar_chart.svg"

set style data histogram
set style histogram clustered gap 2
set style fill solid 1.0 border -1

set title "Language Comparison: Chart Types, Popularity & Performance" textcolor rgb "white" font ",16"
set xlabel "Programming Languages" textcolor rgb "white" font ",13"
set ylabel "Score" textcolor rgb "white" font ",13"

set yrange [0:100]
set grid y linestyle 1 linecolor rgb "#333355" linewidth 0.5

set border linecolor rgb "#555577"
set xtics textcolor rgb "white" font ",11"
set ytics textcolor rgb "white" font ",11"

set key top left textcolor rgb "white" font ",12"

$DATA << EOD
"Python"        85 92 45
"JavaScript"    78 88 55
"C++"            65 60 95
"Java"           72 75 70
"Go"             55 45 88
"Rust"           50 38 92
"TypeScript"     70 68 52
"Swift"          45 42 80
"Kotlin"         58 52 75
EOD

plot "$DATA" using 2:xtic(1) title "Chart Types" linecolor rgb "#48dbfb" fillcolor rgb "#48dbfb", \
     "" using 3 title "Popularity" linecolor rgb "#ff6b6b" fillcolor rgb "#ff6b6b", \
     "" using 4 title "Performance" linecolor rgb "#6ab04c" fillcolor rgb "#6ab04c"
