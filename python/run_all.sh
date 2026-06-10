#!/bin/bash
echo "🐍 Running all 20 Python visualizations..."
cd "$(dirname "$0")/../.."
for script in python/charts/*.py; do
    echo "  ▸ $(basename $script)"
    python3 "$script"
done
echo "✅ Python: $(ls output/python/*.png 2>/dev/null | wc -l) charts generated"
