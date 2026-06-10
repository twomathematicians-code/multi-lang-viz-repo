#!/bin/bash
# 01_svg_bar_chart.sh - Pure Bash SVG grouped bar chart

OUTPUT_DIR="/home/z/my-project/download/multi-lang-viz-repo/output/bash"
mkdir -p "$OUTPUT_DIR"

SVG_FILE="$OUTPUT_DIR/01_bar_chart.svg"
PNG_FILE="$OUTPUT_DIR/01_bar_chart.png"

# Data
LANGUAGES=("Python" "JavaScript" "C++" "Java" "Go" "Rust" "TypeScript" "Swift" "Kotlin")
CHART_TYPES=(85 78 65 72 55 50 70 45 58)
POPULARITY=(92 88 60 75 45 38 68 42 52)
PERFORMANCE=(45 55 95 70 88 92 52 80 75)

# SVG dimensions
WIDTH=1200
HEIGHT=700
MARGIN_LEFT=80
MARGIN_RIGHT=40
MARGIN_TOP=70
MARGIN_BOTTOM=100

PLOT_W=$((WIDTH - MARGIN_LEFT - MARGIN_RIGHT))
PLOT_H=$((HEIGHT - MARGIN_TOP - MARGIN_BOTTOM))

MAX_VAL=100
NUM_LANGS=${#LANGUAGES[@]}

# Calculate bar positioning
GROUP_WIDTH=$((PLOT_W / NUM_LANGS))
BAR_WIDTH=$((GROUP_WIDTH / 4))
BAR_GAP=$((BAR_WIDTH / 4))

# Helper function: map value to Y coordinate
val_to_y() {
    local val=$1
    echo $((MARGIN_TOP + PLOT_H - (val * PLOT_H / MAX_VAL)))
}

# Start SVG
cat > "$SVG_FILE" << SVGHEAD
<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg" width="$WIDTH" height="$HEIGHT">
  <rect width="$WIDTH" height="$HEIGHT" fill="#16213e"/>
  <defs>
    <linearGradient id="g1" x1="0%" y1="0%" x2="0%" y2="100%">
      <stop offset="0%" style="stop-color:#48dbfb;stop-opacity:1"/>
      <stop offset="100%" style="stop-color:#0984e3;stop-opacity:1"/>
    </linearGradient>
    <linearGradient id="g2" x1="0%" y1="0%" x2="0%" y2="100%">
      <stop offset="0%" style="stop-color:#ff6b6b;stop-opacity:1"/>
      <stop offset="100%" style="stop-color:#ee5a24;stop-opacity:1"/>
    </linearGradient>
    <linearGradient id="g3" x1="0%" y1="0%" x2="0%" y2="100%">
      <stop offset="0%" style="stop-color:#6ab04c;stop-opacity:1"/>
      <stop offset="100%" style="stop-color:#27ae60;stop-opacity:1"/>
    </linearGradient>
  </defs>
SVGHEAD

# Title
echo "  <text x=\"$((WIDTH/2))\" y=\"35\" text-anchor=\"middle\" fill=\"white\" font-size=\"20\" font-weight=\"bold\" font-family=\"DejaVu Sans,sans-serif\">Language Comparison: Chart Types, Popularity &amp; Performance</text>" >> "$SVG_FILE"

# Y-axis label
echo "  <text x=\"25\" y=\"$((MARGIN_TOP + PLOT_H/2))\" text-anchor=\"middle\" fill=\"white\" font-size=\"14\" font-family=\"DejaVu Sans,sans-serif\" transform=\"rotate(-90,25,$((MARGIN_TOP + PLOT_H/2)))\">Score</text>" >> "$SVG_FILE"

# Y-axis gridlines and labels
for tick in 0 20 40 60 80 100; do
    y=$(val_to_y $tick)
    echo "  <line x1=\"$MARGIN_LEFT\" y1=\"$y\" x2=\"$((WIDTH - MARGIN_RIGHT))\" y2=\"$y\" stroke=\"#333355\" stroke-width=\"0.5\" stroke-dasharray=\"4,4\"/>" >> "$SVG_FILE"
    echo "  <text x=\"$((MARGIN_LEFT - 10))\" y=\"$((y + 4))\" text-anchor=\"end\" fill=\"white\" font-size=\"11\" font-family=\"DejaVu Sans,sans-serif\">$tick</text>" >> "$SVG_FILE"
done

# Draw axes
echo "  <line x1=\"$MARGIN_LEFT\" y1=\"$MARGIN_TOP\" x2=\"$MARGIN_LEFT\" y2=\"$((MARGIN_TOP + PLOT_H))\" stroke=\"#888888\" stroke-width=\"1.5\"/>" >> "$SVG_FILE"
echo "  <line x1=\"$MARGIN_LEFT\" y1=\"$((MARGIN_TOP + PLOT_H))\" x2=\"$((WIDTH - MARGIN_RIGHT))\" y2=\"$((MARGIN_TOP + PLOT_H))\" stroke=\"#888888\" stroke-width=\"1.5\"/>" >> "$SVG_FILE"

# Draw bars for each language
for i in $(seq 0 $((NUM_LANGS - 1))); do
    group_x=$((MARGIN_LEFT + i * GROUP_WIDTH + GROUP_WIDTH / 4))

    # Chart Types bar
    ct_y=$(val_to_y ${CHART_TYPES[$i]})
    ct_h=$((MARGIN_TOP + PLOT_H - ct_y))
    echo "  <rect x=\"$group_x\" y=\"$ct_y\" width=\"$BAR_WIDTH\" height=\"$ct_h\" fill=\"url(#g1)\" rx=\"2\"/>" >> "$SVG_FILE"

    # Popularity bar
    pop_x=$((group_x + BAR_WIDTH + BAR_GAP))
    pop_y=$(val_to_y ${POPULARITY[$i]})
    pop_h=$((MARGIN_TOP + PLOT_H - pop_y))
    echo "  <rect x=\"$pop_x\" y=\"$pop_y\" width=\"$BAR_WIDTH\" height=\"$pop_h\" fill=\"url(#g2)\" rx=\"2\"/>" >> "$SVG_FILE"

    # Performance bar
    perf_x=$((pop_x + BAR_WIDTH + BAR_GAP))
    perf_y=$(val_to_y ${PERFORMANCE[$i]})
    perf_h=$((MARGIN_TOP + PLOT_H - perf_y))
    echo "  <rect x=\"$perf_x\" y=\"$perf_y\" width=\"$BAR_WIDTH\" height=\"$perf_h\" fill=\"url(#g3)\" rx=\"2\"/>" >> "$SVG_FILE"

    # Value labels on top of bars
    echo "  <text x=\"$((group_x + BAR_WIDTH/2))\" y=\"$((ct_y - 4))\" text-anchor=\"middle\" fill=\"white\" font-size=\"9\" font-family=\"DejaVu Sans,sans-serif\">${CHART_TYPES[$i]}</text>" >> "$SVG_FILE"
    echo "  <text x=\"$((pop_x + BAR_WIDTH/2))\" y=\"$((pop_y - 4))\" text-anchor=\"middle\" fill=\"white\" font-size=\"9\" font-family=\"DejaVu Sans,sans-serif\">${POPULARITY[$i]}</text>" >> "$SVG_FILE"
    echo "  <text x=\"$((perf_x + BAR_WIDTH/2))\" y=\"$((perf_y - 4))\" text-anchor=\"middle\" fill=\"white\" font-size=\"9\" font-family=\"DejaVu Sans,sans-serif\">${PERFORMANCE[$i]}</text>" >> "$SVG_FILE"

    # X-axis labels
    label_x=$((group_x + (3 * BAR_WIDTH + 2 * BAR_GAP) / 2))
    echo "  <text x=\"$label_x\" y=\"$((MARGIN_TOP + PLOT_H + 20))\" text-anchor=\"middle\" fill=\"white\" font-size=\"11\" font-family=\"DejaVu Sans,sans-serif\" transform=\"rotate(-30,$label_x,$((MARGIN_TOP + PLOT_H + 20)))\">${LANGUAGES[$i]}</text>" >> "$SVG_FILE"
done

# Legend
legend_x=$((WIDTH - MARGIN_RIGHT - 200))
legend_y=$((MARGIN_TOP + 10))
echo "  <rect x=\"$((legend_x - 10))\" y=\"$((legend_y - 5))\" width=\"190\" height=\"80\" fill=\"#16213e\" fill-opacity=\"0.8\" stroke=\"#555577\" stroke-width=\"1\" rx=\"4\"/>" >> "$SVG_FILE"
echo "  <rect x=\"$legend_x\" y=\"$legend_y\" width=\"15\" height=\"15\" fill=\"url(#g1)\" rx=\"2\"/>" >> "$SVG_FILE"
echo "  <text x=\"$((legend_x + 22))\" y=\"$((legend_y + 12))\" fill=\"white\" font-size=\"12\" font-family=\"DejaVu Sans,sans-serif\">Chart Types</text>" >> "$SVG_FILE"
echo "  <rect x=\"$legend_x\" y=\"$((legend_y + 22))\" width=\"15\" height=\"15\" fill=\"url(#g2)\" rx=\"2\"/>" >> "$SVG_FILE"
echo "  <text x=\"$((legend_x + 22))\" y=\"$((legend_y + 34))\" fill=\"white\" font-size=\"12\" font-family=\"DejaVu Sans,sans-serif\">Popularity</text>" >> "$SVG_FILE"
echo "  <rect x=\"$legend_x\" y=\"$((legend_y + 44))\" width=\"15\" height=\"15\" fill=\"url(#g3)\" rx=\"2\"/>" >> "$SVG_FILE"
echo "  <text x=\"$((legend_x + 22))\" y=\"$((legend_y + 56))\" fill=\"white\" font-size=\"12\" font-family=\"DejaVu Sans,sans-serif\">Performance</text>" >> "$SVG_FILE"

echo "</svg>" >> "$SVG_FILE"

# Convert to PNG
python3 -c "import cairosvg; cairosvg.svg2png(url='$SVG_FILE', write_to='$PNG_FILE', output_width=1200, output_height=700)"

echo "SVG bar chart saved: $SVG_FILE"
echo "PNG bar chart saved: $PNG_FILE"
