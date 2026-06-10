#!/bin/bash
set -e

CHARTS_DIR="/home/z/my-project/download/multi-lang-viz-repo/bash/charts"
OUTPUT_DIR="/home/z/my-project/download/multi-lang-viz-repo/output/bash"

mkdir -p "$OUTPUT_DIR"

echo "=== Running Bash Charts ==="

bash "$CHARTS_DIR/01_svg_bar_chart.sh"
echo ""

bash "$CHARTS_DIR/02_ascii_bar_chart.sh"
echo ""

bash "$CHARTS_DIR/03_svg_line_chart.sh"
echo ""

echo "=== Bash Charts Complete ==="
