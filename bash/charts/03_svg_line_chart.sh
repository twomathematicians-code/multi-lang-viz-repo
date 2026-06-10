#!/bin/bash
# 03_svg_line_chart.sh - Pure Bash SVG multi-line chart

OUTPUT_DIR="/home/z/my-project/download/multi-lang-viz-repo/output/bash"
mkdir -p "$OUTPUT_DIR"

SVG_FILE="$OUTPUT_DIR/03_line_chart.svg"
PNG_FILE="$OUTPUT_DIR/03_line_chart.png"

# SVG dimensions
WIDTH=1200
HEIGHT=700
MARGIN_LEFT=80
MARGIN_RIGHT=40
MARGIN_TOP=70
MARGIN_BOTTOM=80

PLOT_W=$((WIDTH - MARGIN_LEFT - MARGIN_RIGHT))
PLOT_H=$((HEIGHT - MARGIN_TOP - MARGIN_BOTTOM))

# Data: 5 languages × 7 years
YEARS=(2018 2019 2020 2021 2022 2023 2024)
NUM_YEARS=${#YEARS[@]}

# Values
PYTHON=(68 72 78 83 87 90 92)
JAVASCRIPT=(80 82 84 85 86 87 88)
CPP=(55 56 57 58 59 60 60)
GO_VALS=(25 30 35 38 42 44 45)
RUST=(10 15 22 28 32 35 38)

MIN_VAL=0
MAX_VAL=100

# Helper: value to Y coordinate (pure bash integer math)
val_to_y() {
    local val=$1
    echo $((MARGIN_TOP + PLOT_H - (val * PLOT_H / (MAX_VAL - MIN_VAL))))
}

# Helper: year to X coordinate (pure bash integer math)
# Years span 2018-2024 (6 years), mapped to plot width
# Use index-based positioning for precision
idx_to_x() {
    local idx=$1
    echo $((MARGIN_LEFT + idx * PLOT_W / (NUM_YEARS - 1)))
}

# Helper to build polyline points string
build_polyline() {
    local -n vals_ref=$1
    local points=""
    for i in $(seq 0 $((NUM_YEARS - 1))); do
        x=$(idx_to_x $i)
        y=$(val_to_y ${vals_ref[$i]})
        if [ -n "$points" ]; then
            points+=","
        fi
        points+="$x,$y"
    done
    echo "$points"
}

# Start SVG
cat > "$SVG_FILE" << SVGHEAD
<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg" width="$WIDTH" height="$HEIGHT">
  <rect width="$WIDTH" height="$HEIGHT" fill="#16213e"/>
SVGHEAD

# Title
echo "  <text x=\"$((WIDTH/2))\" y=\"35\" text-anchor=\"middle\" fill=\"white\" font-size=\"20\" font-weight=\"bold\" font-family=\"DejaVu Sans,sans-serif\">Language Popularity Trends (2018-2024)</text>" >> "$SVG_FILE"

# Y-axis label
echo "  <text x=\"25\" y=\"$((MARGIN_TOP + PLOT_H/2))\" text-anchor=\"middle\" fill=\"white\" font-size=\"14\" font-family=\"DejaVu Sans,sans-serif\" transform=\"rotate(-90,25,$((MARGIN_TOP + PLOT_H/2)))\">Popularity Index</text>" >> "$SVG_FILE"

# X-axis label
echo "  <text x=\"$((MARGIN_LEFT + PLOT_W/2))\" y=\"$((HEIGHT - 20))\" text-anchor=\"middle\" fill=\"white\" font-size=\"14\" font-family=\"DejaVu Sans,sans-serif\">Year</text>" >> "$SVG_FILE"

# Grid lines and Y-axis labels
for tick in 0 20 40 60 80 100; do
    y=$(val_to_y $tick)
    echo "  <line x1=\"$MARGIN_LEFT\" y1=\"$y\" x2=\"$((WIDTH - MARGIN_RIGHT))\" y2=\"$y\" stroke=\"#333355\" stroke-width=\"0.5\" stroke-dasharray=\"4,4\"/>" >> "$SVG_FILE"
    echo "  <text x=\"$((MARGIN_LEFT - 10))\" y=\"$((y + 4))\" text-anchor=\"end\" fill=\"white\" font-size=\"11\" font-family=\"DejaVu Sans,sans-serif\">$tick</text>" >> "$SVG_FILE"
done

# X-axis grid lines and labels
for i in $(seq 0 $((NUM_YEARS - 1))); do
    x=$(idx_to_x $i)
    echo "  <line x1=\"$x\" y1=\"$MARGIN_TOP\" x2=\"$x\" y2=\"$((MARGIN_TOP + PLOT_H))\" stroke=\"#333355\" stroke-width=\"0.5\" stroke-dasharray=\"4,4\"/>" >> "$SVG_FILE"
    echo "  <text x=\"$x\" y=\"$((MARGIN_TOP + PLOT_H + 20))\" text-anchor=\"middle\" fill=\"white\" font-size=\"11\" font-family=\"DejaVu Sans,sans-serif\">${YEARS[$i]}</text>" >> "$SVG_FILE"
done

# Axes
echo "  <line x1=\"$MARGIN_LEFT\" y1=\"$MARGIN_TOP\" x2=\"$MARGIN_LEFT\" y2=\"$((MARGIN_TOP + PLOT_H))\" stroke=\"#888888\" stroke-width=\"1.5\"/>" >> "$SVG_FILE"
echo "  <line x1=\"$MARGIN_LEFT\" y1=\"$((MARGIN_TOP + PLOT_H))\" x2=\"$((WIDTH - MARGIN_RIGHT))\" y2=\"$((MARGIN_TOP + PLOT_H))\" stroke=\"#888888\" stroke-width=\"1.5\"/>" >> "$SVG_FILE"

# Function to draw a data series
draw_series() {
    local -n vals=$1
    local color=$2
    local name=$3

    local pts=$(build_polyline $1)
    echo "  <polyline points=\"$pts\" fill=\"none\" stroke=\"$color\" stroke-width=\"2.5\" stroke-linecap=\"round\" stroke-linejoin=\"round\"/>" >> "$SVG_FILE"
    for i in $(seq 0 $((NUM_YEARS - 1))); do
        x=$(idx_to_x $i)
        y=$(val_to_y ${vals[$i]})
        echo "  <circle cx=\"$x\" cy=\"$y\" r=\"4\" fill=\"$color\" stroke=\"#16213e\" stroke-width=\"1.5\"/>" >> "$SVG_FILE"
    done
}

# Draw lines
draw_series PYTHON "#ff6b6b" "Python"
draw_series JAVASCRIPT "#4ecdc4" "JavaScript"
draw_series CPP "#ffc300" "C++"
draw_series GO_VALS "#00a8ff" "Go"
draw_series RUST "#a973ff" "Rust"

# Legend
legend_x=$((WIDTH - MARGIN_RIGHT - 180))
legend_y=$((MARGIN_TOP + 10))
echo "  <rect x=\"$((legend_x - 10))\" y=\"$((legend_y - 5))\" width=\"170\" height=\"120\" fill=\"#16213e\" fill-opacity=\"0.8\" stroke=\"#555577\" stroke-width=\"1\" rx=\"4\"/>" >> "$SVG_FILE"

LEGEND_ENTRIES=("Python" "#ff6b6b" "JavaScript" "#4ecdc4" "C++" "#ffc300" "Go" "#00a8ff" "Rust" "#a973ff")
li=0
while [ $li -lt ${#LEGEND_ENTRIES[@]} ]; do
    name="${LEGEND_ENTRIES[$li]}"
    color="${LEGEND_ENTRIES[$((li+1))]}"
    ly=$((legend_y + li/2 * 22))
    echo "  <line x1=\"$legend_x\" y1=\"$((ly+8))\" x2=\"$((legend_x + 20))\" y2=\"$((ly+8))\" stroke=\"$color\" stroke-width=\"2.5\" stroke-linecap=\"round\"/>" >> "$SVG_FILE"
    echo "  <circle cx=\"$((legend_x + 10))\" cy=\"$((ly+8))\" r=\"3\" fill=\"$color\"/>" >> "$SVG_FILE"
    echo "  <text x=\"$((legend_x + 28))\" y=\"$((ly + 12))\" fill=\"white\" font-size=\"12\" font-family=\"DejaVu Sans,sans-serif\">$name</text>" >> "$SVG_FILE"
    li=$((li + 2))
done

echo "</svg>" >> "$SVG_FILE"

# Convert to PNG
python3 -c "import cairosvg; cairosvg.svg2png(url='$SVG_FILE', write_to='$PNG_FILE', output_width=1200, output_height=700)"

echo "SVG line chart saved: $SVG_FILE"
echo "PNG line chart saved: $PNG_FILE"
