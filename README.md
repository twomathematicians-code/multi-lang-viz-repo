# Multi-Language Visualization Showcase

**48 Charts Across 7 Programming Languages | Zero-Framework | Production-Ready**

A comprehensive demonstration of data visualization capabilities across different programming ecosystems. Each language generates multiple chart types from the same sample dataset, showcasing the unique strengths and trade-offs of each approach. Every visualization is generated with runnable code that can be executed directly from this repository.

---

## Quick Start

```bash
# Clone and run everything
git clone <repo-url> && cd multi-lang-viz-repo
chmod +x run_all.sh && ./run_all.sh
```

That single command generates all 48 visualizations across 7 languages. You can also run each language independently:

```bash
cd python && bash run_all.sh          # 20 charts
cd cpp && make                        # 5 charts
cd go && go run main.go               # 5 charts
cd gnuplot && bash run_all.sh         # 5 charts
cd bash && bash run_all.sh            # 3 charts
# JavaScript: open javascript/index.html in a browser
```

---

## Repository Structure

```
multi-lang-viz-repo/
├── README.md                    # This file — full documentation
├── run_all.sh                   # Master script — generates everything
├── .gitignore
│
├── data/                        # Shared sample datasets (CSV)
│   ├── sample_data.csv         # Language metrics (9 languages × 9 features)
│   ├── timeseries.csv           # Historical trends (2016–2026, 5 languages)
│   └── features.csv             # Feature comparison matrix (9 languages × 10 features)
│
├── python/                      # 🐍 20 charts — Matplotlib, Seaborn, Plotly
│   ├── requirements.txt
│   ├── run_all.sh
│   └── charts/
│       ├── 01_bar_vertical.py
│       ├── 02_bar_horizontal.py
│       ├── 03_grouped_bar.py
│       ├── 04_stacked_bar.py
│       ├── 05_line_chart.py
│       ├── 06_multi_line.py
│       ├── 07_stacked_area.py
│       ├── 08_scatter.py
│       ├── 09_bubble.py
│       ├── 10_pie.py
│       ├── 11_donut.py
│       ├── 12_histogram.py
│       ├── 13_box_plot.py
│       ├── 14_violin.py
│       ├── 15_heatmap.py
│       ├── 16_radar.py
│       ├── 17_parallel_coordinates.py
│       ├── 18_pairplot.py
│       ├── 19_3d_surface.py
│       └── 20_polar.py
│
├── javascript/                  # 🌐 10 charts — Chart.js v4
│   ├── index.html               # Self-contained interactive dashboard
│   └── run_all.sh
│
├── cpp/                         # ⚡ 5 charts — Pure C++ (stb_image_write)
│   ├── Makefile
│   ├── run_all.sh
│   └── charts/
│       ├── stb_image_write.h   # Single-header PNG writer (public domain)
│       ├── 01_bar_chart.cpp
│       ├── 02_scatter_plot.cpp
│       ├── 03_line_chart.cpp
│       ├── 04_histogram.cpp
│       └── 05_pie_chart.cpp
│
├── go/                          # 🔷 5 charts — gonum/plot
│   ├── go.mod
│   ├── go.sum
│   ├── main.go                  # Single program generates all 5 charts
│   └── run_all.sh
│
├── gnuplot/                     # 📈 5 charts — Gnuplot 6.0
│   ├── run_all.sh
│   └── charts/
│       ├── 01_bar_chart.gnu
│       ├── 02_line_chart.gnu
│       ├── 03_scatter.gnu
│       ├── 04_contour.gnu
│       └── 05_surface.gnu
│
├── bash/                        # 🐚 3 charts — Pure Bash (SVG + ASCII)
│   ├── run_all.sh
│   └── charts/
│       ├── 01_svg_bar_chart.sh
│       ├── 02_ascii_bar_chart.sh
│       └── 03_svg_line_chart.sh
│
└── output/                      # All generated visualizations
    ├── python/                  # 20 PNG files
    ├── javascript/              # HTML interactive dashboard
    ├── cpp/                     # 5 PNG files
    ├── go/                      # 5 PNG files
    ├── gnuplot/                 # 5 PNG + 5 SVG files
    └── bash/                    # 2 PNG + 2 SVG + 1 TXT files
```

---

## Prerequisites

| Language | Minimum Version | Installation |
|----------|-----------------|--------------|
| **Python** | 3.8+ | `sudo apt install python3 python3-pip` |
| **JavaScript** | Any modern browser | No install needed (runs in browser) |
| **C++** | g++ with C++17 | `sudo apt install g++` |
| **Go** | 1.21+ | `go mod download` (automatic) |
| **Gnuplot** | 5.0+ (6.0+ recommended) | `sudo apt install gnuplot` |
| **Bash** | 4.0+ | Pre-installed on Linux/macOS |

### Python Dependencies

```bash
pip install -r python/requirements.txt
```

Contents: `matplotlib`, `seaborn`, `numpy`, `pandas`, `plotly`, `pygal`, `cairosvg`

### Go Dependencies

Go modules are managed automatically. Running `go run main.go` will download `gonum.org/v1/plot` and dependencies.

### SVG to PNG Conversion

The Gnuplot and Bash scripts generate SVG files and convert them to PNG using Python's `cairosvg` library. If cairosvg is not installed:

```bash
pip install cairosvg
```

---

## Dataset

All visualizations use the same consistent dataset stored in CSV format under `data/`:

### `sample_data.csv` — Language Metrics
Compares 9 programming languages (Python, JavaScript, C++, Java, Go, R, Julia, Gnuplot, Bash) across 9 dimensions: chart types available, popularity index, performance score, ease of use, community size, web export capability, year established, and developer count in millions.

### `timeseries.csv` — Historical Trends
Tracks the popularity and capability scores of 5 major languages (Python, JavaScript, C++, Java, Go) from 2016 to 2026, illustrating the rise of Python and Go alongside the plateau of C++ and the gradual decline of Java in visualization contexts.

### `features.csv` — Feature Comparison Matrix
A detailed 10-dimensional comparison of all 9 languages across features like chart variety, interactivity, performance, ease of use, community size, 3D support, web export, data science capability, real-time performance, and documentation quality. Used primarily for radar charts, heatmaps, and parallel coordinate plots.

---

## Chart Catalog

### Python — 20 Charts (Matplotlib + Seaborn)

Python delivers the widest variety of chart types with the richest ecosystem. These 20 charts span basic statistical plots to advanced 3D rendering and multi-dimensional analysis.

| # | Script | Chart Type | Library | Description |
|---|--------|-----------|---------|-------------|
| 01 | `01_bar_vertical.py` | Vertical Bar Chart | Matplotlib | Compares chart type counts across all 9 languages with color-coded bars and value annotations. A fundamental chart for categorical comparison. |
| 02 | `02_bar_horizontal.py` | Horizontal Bar Chart | Matplotlib | Displays popularity index as horizontal bars, ideal for comparing long language names side by side with gradient fills. |
| 03 | `03_grouped_bar.py` | Grouped Bar Chart | Matplotlib | Places three metrics (chart types, popularity, performance) side by side for each language, enabling direct multi-dimensional comparison. |
| 04 | `04_stacked_bar.py` | Stacked Bar Chart | Matplotlib | Stacks multiple metrics into single bars per language, showing the relative composition and total magnitude of each language's capabilities. |
| 05 | `05_line_chart.py` | Line Chart | Matplotlib | Traces Python's growth trajectory from 2016 to 2026, demonstrating trend visualization with area fill and data point markers. |
| 06 | `06_multi_line.py` | Multi-Line Chart | Matplotlib | Overlays trend lines for 5 languages, revealing crossover points and relative growth patterns over an 11-year period. |
| 07 | `07_stacked_area.py` | Stacked Area Chart | Matplotlib | Fills the area between each trend line, visualizing cumulative scores and how each language contributes to the total over time. |
| 08 | `08_scatter.py` | Scatter Plot | Matplotlib | Plots chart types against performance with color-coded points, revealing the inverse relationship between variety and raw speed. |
| 09 | `09_bubble.py` | Bubble Chart | Matplotlib | Extends the scatter plot with variable-sized bubbles representing a third dimension (community size), creating a 3-attribute visualization. |
| 10 | `10_pie.py` | Pie Chart | Matplotlib | Shows the proportion of popularity held by each language as slices of a circle, with percentage labels and exploded segments. |
| 11 | `11_donut.py` | Donut Chart | Matplotlib | A hollow variant of the pie chart focusing attention on the relative proportions while allowing annotations inside the ring. |
| 12 | `12_histogram.py` | Histogram | Matplotlib | Bins the developer count data into ranges, showing the frequency distribution of language adoption across millions of developers. |
| 13 | `13_box_plot.py` | Box Plot | Matplotlib | Displays statistical summaries (median, quartiles, outliers) for each numeric column, revealing distributional differences at a glance. |
| 14 | `14_violin.py` | Violin + Swarm Plot | Seaborn | Combines kernel density estimation with individual data points, providing both the distribution shape and raw data visibility. |
| 15 | `15_heatmap.py` | Correlation Heatmap | Seaborn | Color-maps the correlation matrix from features.csv, highlighting strong positive (red) and negative (blue) relationships between capabilities. |
| 16 | `16_radar.py` | Radar / Spider Chart | Matplotlib | Maps 7 features onto radial axes for the top 5 languages, creating overlapping polygons that instantly reveal each language's strengths. |
| 17 | `17_parallel_coordinates.py` | Parallel Coordinates | Matplotlib | Draws 10 vertical axes (one per feature) with line bundles connecting each language's values, revealing multi-dimensional patterns. |
| 18 | `18_pairplot.py` | Pair Plot | Seaborn | Generates a matrix of scatter plots for all numeric pairs from sample_data.csv, with histograms on the diagonal for self-comparison. |
| 19 | `19_3d_surface.py` | 3D Surface Plot | Matplotlib | Renders a mathematical function as a colored 3D surface, demonstrating Matplotlib's mplot3d toolkit with viridis colormap. |
| 20 | `20_polar.py` | Polar Bar Chart | Matplotlib | Plots ease-of-use scores as radial bars emanating from a center point, offering an alternative to the standard Cartesian bar chart. |

---

### JavaScript — 10 Charts (Chart.js v4)

A single self-contained HTML file with 10 interactive charts. Open `javascript/index.html` in any modern browser. All charts feature hover tooltips, click legends to toggle datasets, and responsive resizing.

| # | Chart Type | Description |
|---|-----------|-------------|
| 01 | Bar Chart | Vertical bars comparing chart type availability across all 9 programming languages. |
| 02 | Line Chart | Multi-line trend visualization tracking 5 languages from 2016 to 2026, showing their relative growth trajectories. |
| 03 | Pie Chart | Proportional breakdown of language popularity, with hoverable slices showing exact values. |
| 04 | Doughnut Chart | Community score distribution rendered as a donut, emphasizing the dominant position of Python and JavaScript. |
| 05 | Radar Chart | Six-axis feature comparison for the top 5 languages, with interactive toggling of each language's polygon. |
| 06 | Polar Area Chart | Performance scores as varying-radius polar segments, where segment angle is equal but radius encodes the value. |
| 07 | Bubble Chart | Three-dimensional scatter: x-axis is chart types, y-axis is popularity, bubble radius represents performance. |
| 08 | Scatter Chart | Two-dimensional scatter of chart types versus ease of use, revealing the tradeoff between capability breadth and simplicity. |
| 09 | Stacked Bar Chart | Bars where chart types, popularity, and performance stack vertically, showing both individual contributions and totals. |
| 10 | Mixed Chart | Dual-axis chart combining bars (chart types, left axis) with a line (popularity, right axis), demonstrating Chart.js' mixed chart capabilities. |

---

### C++ — 5 Charts (Pure C++ + stb_image_write)

All charts are rendered pixel-by-pixel in C++ without any external graphics libraries. The single-header `stb_image_write.h` (public domain, by Sean Barrett) handles PNG encoding. Text is rendered using a custom 5x7 bitmap font. These demonstrate the raw performance and zero-dependency nature of C++ visualization.

| # | Script | Chart Type | Description |
|---|--------|-----------|-------------|
| 01 | `01_bar_chart.cpp` | Grouped Bar Chart | Renders 9 languages with 3 colored bars each (green/blue/red) on a dark background. Includes y-axis gridlines, value labels above bars, and a color-coded legend. All rendering is done via direct pixel buffer manipulation. |
| 02 | `02_scatter_plot.cpp` | Scatter Plot | Plots chart types (x) against performance (y) with color-coded filled circles for each language. Gridlines and axis labels provide context. Circle rendering uses the midpoint circle algorithm. |
| 03 | `03_line_chart.cpp` | Multi-Line Chart | Traces 5 language trends from 2016 to 2026 using thick colored polylines with circle markers at each data point. Demonstrates Bresenham-style line drawing on the pixel buffer. |
| 04 | `04_histogram.cpp` | Histogram | Bins the chart type values into 8 ranges (0 to 70+), counts languages per bin, and renders gradient-filled bars. Includes a data panel showing which language falls into each bin. |
| 05 | `05_pie_chart.cpp` | Pie / Donut Chart | Renders popularity data as filled arc wedges using polar coordinate math (atan2). Each slice is a different color with percentage labels and a legend panel on the right side. |

---

### Go — 5 Charts (gonum/plot)

All 5 charts are generated by a single Go program (`main.go`) using the `gonum.org/v1/plot` library. Go's strong type system and compiled nature make these visualizations fast and reliable. Charts are saved as PNG via the gonum plotter's built-in vg (vector graphics) backend.

| # | Chart Type | Description |
|---|-----------|-------------|
| 01 | Grouped Bar Chart | Three offset bar series (chart types, popularity, performance) for 9 languages. Uses `plotter.NewBarChart` with negative, zero, and positive offsets for grouping. |
| 02 | Scatter Plot | Scatter plot of chart types versus performance with circular glyphs, demonstrating gonum's `plotter.NewScatter` and `draw.CircleGlyph`. |
| 03 | Line Chart | Multi-line trend chart tracking Python, JavaScript, and C++ over time using `plotter.NewLine` with colored line series and custom tick formatting. |
| 04 | Histogram | Frequency distribution of chart type scores using `plotter.NewHistogram`, automatically binning values and displaying the distribution shape. |
| 05 | Box Plot | Statistical box-and-whisker plot showing the spread of performance scores with custom color thumbnails, created using `plotter.NewBoxPlot` with a custom `Thumbnailer`. |

---

### Gnuplot — 5 Charts (Gnuplot 6.0)

Gnuplot scripts generate SVG output which is automatically converted to PNG. Gnuplot excels at scientific plotting with its concise command-driven interface, especially for mathematical functions and 3D surfaces.

| # | Script | Chart Type | Description |
|---|--------|-----------|-------------|
| 01 | `01_bar_chart.gnu` | Grouped Bar Chart | Clustered histogram comparing chart types, popularity, and performance for all 9 languages. Uses `set style histogram clustered` with gap spacing for clear separation between groups. |
| 02 | `02_line_chart.gnu` | Multi-Line Chart | Five trend lines with distinct colors and point markers (`linespoints`), tracking language evolution from 2016 to 2026. Custom range and grid settings for clarity. |
| 03 | `03_scatter.gnu` | Scatter Plot | Labeled scatter plot of chart types versus performance. Each point is annotated with the language name using `with labels`, providing immediate identification. |
| 04 | `04_contour.gnu` | Contour Plot | Mathematical contour visualization of the function f(x,y) = x^2 + y^2, rendered with 10 contour levels. Uses `set contour base` with `set cntrparam levels` to control the density of iso-lines. |
| 05 | `05_surface.gnu` | 3D Surface Plot | Renders sin(x) * cos(y) as a colored 3D mesh surface viewed at 45-degree azimuth and 30-degree elevation. Demonstrates Gnuplot's `splot` command with `set view` for camera positioning. |

---

### Bash — 3 Charts (Pure Shell Script)

These visualizations are generated entirely in Bash without any external tools, libraries, or interpreters beyond the shell itself. SVG files are created by writing markup directly, and the ASCII chart uses Unicode block characters.

| # | Script | Chart Type | Description |
|---|--------|-----------|-------------|
| 01 | `01_svg_bar_chart.sh` | SVG Grouped Bar Chart | A complete SVG document generated via shell variable expansion and heredoc syntax. Includes dark background, gradient fills (linearGradient), rounded-rect bars with drop shadow filters, gridlines, axis labels, and a floating legend panel. |
| 02 | `02_ascii_bar_chart.sh` | ASCII Text Bar Chart | A terminal-friendly visualization using Unicode block characters (full block, dark shade, medium shade, light shade) to draw horizontal bars for chart types and popularity. Outputs a .txt file viewable in any terminal or text editor. |
| 03 | `03_svg_line_chart.sh` | SVG Multi-Line Chart | SVG polylines drawn via Bash arithmetic for coordinate calculation. Includes axes, gridlines, circle markers at data points, a color-coded legend, and the same dark professional theme as the bar chart. |

---

## Total Chart Count

| Language | Charts | Library / Method | Output Format |
|----------|--------|------------------|---------------|
| Python | 20 | Matplotlib, Seaborn | PNG |
| JavaScript | 10 | Chart.js v4 | Interactive HTML |
| C++ | 5 | stb_image_write (pure pixel) | PNG |
| Go | 5 | gonum/plot | PNG |
| Gnuplot | 5 | Gnuplot 6.0 (SVG -> PNG) | PNG + SVG |
| Bash | 3 | Pure shell (SVG + ASCII) | PNG + SVG + TXT |
| **Total** | **48** | **7 languages** | **Multiple formats** |

---

## Design System

All visualizations share a consistent professional dark theme:

- **Background**: `#16213e` (dark navy) / `#0d1117` (GitHub dark)
- **Text**: `#dddddd` (light gray) / `#00d4ff` (cyan accents)
- **Palette**: `#2ecc71` (green), `#3498db` (blue), `#e74c3c` (red), `#f39c12` (orange), `#00bcd4` (teal), `#9b59b6` (purple), `#ff6b6b` (coral), `#1abc9c` (mint), `#795548` (brown)
- **Grid**: Subtle dashed lines at `#3a3a5c`
- **Resolution**: 1200 x 700 pixels at 150 DPI (Python); native resolution (other languages)

---

## Running Individual Languages

### Python

```bash
pip install -r python/requirements.txt
cd python && bash run_all.sh
# Or run individual charts:
python3 python/charts/01_bar_vertical.py
python3 python/charts/16_radar.py
```

### JavaScript

```bash
# Simply open in any browser:
open javascript/index.html          # macOS
xdg-open javascript/index.html     # Linux
start javascript/index.html        # Windows
```

### C++

```bash
cd cpp && make
# Or compile individually:
g++ -std=c++17 -O2 cpp/charts/01_bar_chart.cpp -o /tmp/chart -lm && /tmp/chart
```

### Go

```bash
cd go
go mod download     # First time only
go run main.go       # Generates all 5 charts
```

### Gnuplot

```bash
cd gnuplot && bash run_all.sh
# Or individually:
gnuplot gnuplot/charts/01_bar_chart.gnu
```

### Bash

```bash
cd bash && bash run_all.sh
# View ASCII chart in terminal:
cat output/bash/ascii_bar_chart.txt
```

---

## Language Comparison Matrix

This repository demonstrates the practical trade-offs between visualization approaches:

| Aspect | Python | JavaScript | C++ | Go | Gnuplot | Bash |
|--------|--------|-----------|-----|----|---------|------|
| **Chart Variety** | Excellent (20+) | Good (10+) | Basic (3-5) | Basic (3-5) | Moderate (5+) | Minimal (1-3) |
| **Interactivity** | Moderate (Plotly) | Excellent | None | None | None | None |
| **Performance** | Moderate | Good | Excellent | Excellent | Good | Excellent |
| **Ease of Setup** | pip install | Browser only | g++ + header | go mod | apt install | Zero |
| **3D Support** | Yes (mplot3d) | Limited | Manual | No | Yes (splot) | No |
| **Output Quality** | Publication | Web/Dashboard | Pixel-art | Clean | Publication | Basic |
| **Code Complexity** | Low | Low | Very High | Moderate | Low | Medium |
| **Dependencies** | Heavy | CDN only | stb only | gonum | None | None |

---

## Extending the Repository

To add a new chart to any language:

1. **Python**: Create a new `.py` file in `python/charts/`, follow the existing pattern (Agg backend, dark theme, save to `output/python/`).
2. **JavaScript**: Add a new `<canvas>` element and Chart.js configuration block in `javascript/index.html`.
3. **C++**: Create a new `.cpp` file in `cpp/charts/`, include `stb_image_write.h`, render to a pixel buffer, and save with `stbi_write_png`.
4. **Go**: Add a new plot to `go/main.go` following the existing pattern.
5. **Gnuplot**: Create a new `.gnu` script in `gnuplot/charts/`.
6. **Bash**: Create a new `.sh` script in `bash/charts/` that outputs SVG or text.

To add a **new language**: Create a new top-level directory with its own `charts/` subdirectory and `run_all.sh`, following the existing patterns. Update this README and the master `run_all.sh`.

---

## License

This repository is released under the MIT License. The `stb_image_write.h` library by Sean Barrett is public domain. All other code and data are provided as-is for educational and demonstration purposes.

---

## Acknowledgments

- **stb_image_write.h** by Sean Barrett — Single-header PNG writer (no license, public domain)
- **Matplotlib** — Python plotting library (BSD license)
- **Seaborn** — Statistical visualization (BSD license)
- **Chart.js** — JavaScript charting library (MIT license)
- **gonum/plot** — Go plotting framework (BSD license)
- **Gnuplot** — Scientific plotting tool (gnuplot license)
- **cairosvg** — SVG to PNG conversion (LGPL license)
