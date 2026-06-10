#!/bin/bash
set -e

GNUPLOT="/home/z/my-project/tools/gnuplot-install/bin/gnuplot"
CHARTS_DIR="/home/z/my-project/download/multi-lang-viz-repo/gnuplot/charts"
OUTPUT_DIR="/home/z/my-project/download/multi-lang-viz-repo/output/gnuplot"

mkdir -p "$OUTPUT_DIR"

echo "=== Running Gnuplot Charts ==="

for script in "$CHARTS_DIR"/*.gnu; do
    echo "Running: $(basename "$script")"
    "$GNUPLOT" "$script"
done

echo ""
echo "=== Converting SVG to PNG ==="

for svg in "$OUTPUT_DIR"/*.svg; do
    if [ -f "$svg" ]; then
        png="${svg%.svg}.png"
        echo "Converting: $(basename "$svg") -> $(basename "$png")"
        python3 -c "import cairosvg; cairosvg.svg2png(url='$svg', write_to='$png', output_width=1200, output_height=700)"
    fi
done

echo ""
echo "=== Gnuplot Charts Complete ==="
