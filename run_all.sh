#!/bin/bash
set -e

echo "╔══════════════════════════════════════════════════════════════╗"
echo "║  Multi-Language Visualization Showcase — Build & Run All    ║"
echo "║  7 Languages | 48 Charts | 1 Command                      ║"
echo "╚══════════════════════════════════════════════════════════════╝"
echo ""

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# Create output directories
mkdir -p output/{python,javascript,cpp,go,gnuplot,bash}

echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "📊 [1/7] Python — 20 charts (Matplotlib + Seaborn)"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
if command -v python3 &>/dev/null; then
    pip install -r python/requirements.txt -q 2>/dev/null || true
    for script in python/charts/*.py; do
        python3 "$script"
    done
    echo "✅ Python complete: $(ls output/python/*.png 2>/dev/null | wc -l) charts"
else
    echo "⚠️  Python not found — skipping"
fi
echo ""

echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "🌐 [2/7] JavaScript — 10 charts (Chart.js)"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
cp javascript/index.html output/javascript/10_charts_showcase.html
echo "✅ JavaScript complete: open output/javascript/10_charts_showcase.html in browser"
echo ""

echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "⚡ [3/7] C++ — 5 charts (Pure C++ + stb_image_write)"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
if command -v g++ &>/dev/null; then
    cd cpp
    make clean 2>/dev/null; make
    cd "$SCRIPT_DIR"
    echo "✅ C++ complete: $(ls output/cpp/*.png 2>/dev/null | wc -l) charts"
else
    echo "⚠️  g++ not found — skipping"
fi
echo ""

echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "🔷 [4/7] Go — 5 charts (gonum/plot)"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
if command -v go &>/dev/null; then
    cd go && go run main.go && cd "$SCRIPT_DIR"
    echo "✅ Go complete: $(ls output/go/*.png 2>/dev/null | wc -l) charts"
else
    echo "⚠️  Go not found — skipping"
fi
echo ""

echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "📈 [5/7] Gnuplot — 5 charts"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
if command -v gnuplot &>/dev/null; then
    cd gnuplot && bash run_all.sh && cd "$SCRIPT_DIR"
    echo "✅ Gnuplot complete: $(ls output/gnuplot/*.png 2>/dev/null | wc -l) charts"
else
    echo "⚠️  Gnuplot not found — skipping"
fi
echo ""

echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "🐚 [6/7] Bash — 3 charts (Pure Shell Script)"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
cd bash && bash run_all.sh && cd "$SCRIPT_DIR"
echo "✅ Bash complete: $(ls output/bash/* 2>/dev/null | wc -l) files"
echo ""

echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "📋 [7/7] Summary"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
TOTAL_PY=$(ls output/python/*.png 2>/dev/null | wc -l)
TOTAL_JS=$(ls output/javascript/*.html 2>/dev/null | wc -l)
TOTAL_CPP=$(ls output/cpp/*.png 2>/dev/null | wc -l)
TOTAL_GO=$(ls output/go/*.png 2>/dev/null | wc -l)
TOTAL_GP=$(ls output/gnuplot/*.png 2>/dev/null | wc -l)
TOTAL_BASH=$(ls output/bash/* 2>/dev/null | wc -l)
TOTAL=$((TOTAL_PY + TOTAL_JS + TOTAL_CPP + TOTAL_GO + TOTAL_GP + TOTAL_BASH))
echo "  Python:     $TOTAL_PY charts"
echo "  JavaScript: $TOTAL_JS charts"
echo "  C++:        $TOTAL_CPP charts"
echo "  Go:         $TOTAL_GO charts"
echo "  Gnuplot:    $TOTAL_GP charts"
echo "  Bash:       $TOTAL_BASH files"
echo "  ─────────────────────"
echo "  TOTAL:      $TOTAL files"
echo ""
echo "🎉 All visualizations generated successfully!"
