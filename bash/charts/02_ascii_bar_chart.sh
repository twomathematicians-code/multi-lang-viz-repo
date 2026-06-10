#!/bin/bash
# 02_ascii_bar_chart.sh - Pure ASCII/Unicode text bar chart

OUTPUT_DIR="/home/z/my-project/download/multi-lang-viz-repo/output/bash"
mkdir -p "$OUTPUT_DIR"

TXT_FILE="$OUTPUT_DIR/ascii_bar_chart.txt"

# Data
LANGS=("Python" "JavaScript" "C++" "Java" "Go" "Rust" "TypeScript" "Swift" "Kotlin")
CT=(85 78 65 72 55 50 70 45 58)
POP=(92 88 60 75 45 38 68 42 52)
PERF=(45 55 95 70 88 92 52 80 75)

# Clear output file
> "$TXT_FILE"

echo "" >> "$TXT_FILE"
echo "============================================================================================================" >> "$TXT_FILE"
echo "        PROGRAMMING LANGUAGE COMPARISON - ASCII BAR CHART                                                   " >> "$TXT_FILE"
echo "============================================================================================================" >> "$TXT_FILE"
printf "  %-12s  %-8s  %-9s  %-11s\n" "Language" "Chart Ty" "Popularity" "Performance" >> "$TXT_FILE"
echo "------------------------------------------------------------------------------------------------------------" >> "$TXT_FILE"

for i in "${!LANGS[@]}"; do
    lang="${LANGS[$i]}"
    ct="${CT[$i]}"
    pop="${POP[$i]}"
    perf="${PERF[$i]}"

    # Create bar strings (1 block = 2 points, each block = 1 char)
    ct_len=$((ct / 2))
    pop_len=$((pop / 2))
    perf_len=$((perf / 2))

    ct_bar=$(printf '\xe2\x96\x88%.0s' $(seq 1 $ct_len 2>/dev/null))
    pop_bar=$(printf '\xe2\x96\x93%.0s' $(seq 1 $pop_len 2>/dev/null))
    perf_bar=$(printf '\xe2\x96\x92%.0s' $(seq 1 $perf_len 2>/dev/null))

    printf "  %-12s  %3d %s  %3d %s  %3d %s\n" "$lang" "$ct" "$ct_bar" "$pop" "$pop_bar" "$perf" "$perf_bar" >> "$TXT_FILE"
done

echo "------------------------------------------------------------------------------------------------------------" >> "$TXT_FILE"
echo "  Legend: blocks represent score (each block ~ 2 points). Max score = 100" >> "$TXT_FILE"
echo "  Characters: Full(\xe2\x96\x88) Medium(\xe2\x96\x93) Light(\xe2\x96\x92)" >> "$TXT_FILE"
echo "============================================================================================================" >> "$TXT_FILE"

echo "" >> "$TXT_FILE"
echo "  Summary Table:" >> "$TXT_FILE"
printf "  %-12s  %6s  %10s  %11s\n" "Language" "Charts" "Popularity" "Performance" >> "$TXT_FILE"
echo "  --------------------------------------------------------" >> "$TXT_FILE"

for i in "${!LANGS[@]}"; do
    printf "  %-12s  %6d  %10d  %11d\n" "${LANGS[$i]}" "${CT[$i]}" "${POP[$i]}" "${PERF[$i]}" >> "$TXT_FILE"
done

echo "  --------------------------------------------------------" >> "$TXT_FILE"
echo "" >> "$TXT_FILE"

echo "ASCII bar chart saved: $TXT_FILE"

# Also print to terminal
echo ""
echo "=== ASCII Bar Chart ==="
cat "$TXT_FILE"
