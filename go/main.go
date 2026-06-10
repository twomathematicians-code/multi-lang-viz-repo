package main

import (
        "fmt"
        "image/color"
        "log"
        "os"

        "gonum.org/v1/plot"
        "gonum.org/v1/plot/plotter"
        "gonum.org/v1/plot/vg"
        "gonum.org/v1/plot/vg/draw"
)

func main() {
        outDir := "/home/z/my-project/download/multi-lang-viz-repo/output/go"
        os.MkdirAll(outDir, 0755)

        languages := []string{"Python", "JavaScript", "C++", "Java", "Go", "Rust", "TypeScript", "Swift", "Kotlin"}
        chartTypes := []float64{85, 78, 65, 72, 55, 50, 70, 45, 58}
        popularity := []float64{92, 88, 60, 75, 45, 38, 68, 42, 52}
        performance := []float64{45, 55, 95, 70, 88, 92, 52, 80, 75}

        if err := makeBarChart(outDir, languages, chartTypes, popularity, performance); err != nil {
                log.Fatalf("Bar chart: %v", err)
        }
        fmt.Println("[1/5] Bar chart saved")

        if err := makeScatterPlot(outDir, chartTypes, performance); err != nil {
                log.Fatalf("Scatter plot: %v", err)
        }
        fmt.Println("[2/5] Scatter plot saved")

        if err := makeLineChart(outDir); err != nil {
                log.Fatalf("Line chart: %v", err)
        }
        fmt.Println("[3/5] Line chart saved")

        if err := makeHistogram(outDir, chartTypes); err != nil {
                log.Fatalf("Histogram: %v", err)
        }
        fmt.Println("[4/5] Histogram saved")

        if err := makeBoxPlot(outDir, popularity, performance); err != nil {
                log.Fatalf("Box plot: %v", err)
        }
        fmt.Println("[5/5] Box plot saved")

        fmt.Println("\nAll 5 Go charts generated successfully!")
}

// Helper: convert RGBA to color.RGBA
func rgba(r, g, b, a uint8) color.RGBA {
        return color.RGBA{R: r, G: g, B: b, A: a}
}

// Helper: make plotter.Values from slice
func makeValues(vals []float64) plotter.Values {
        v := make(plotter.Values, len(vals))
        copy(v, vals)
        return v
}

// Helper: make XYs from two slices
func makeXYs(xs, ys []float64) plotter.XYs {
        pts := make(plotter.XYs, len(xs))
        for i := range xs {
                pts[i].X = xs[i]
                pts[i].Y = ys[i]
        }
        return pts
}

// 1. Grouped Bar Chart
func makeBarChart(outDir string, labels []string, chartTypes, popularity, performance []float64) error {
        p := plot.New()
        p.Title.Text = "Language Comparison: Chart Types, Popularity & Performance"
        p.Y.Label.Text = "Score"
        p.X.Label.Text = "Programming Languages"
        p.NominalX(labels...)

        width := vg.Points(10)
        ctBars, err := plotter.NewBarChart(makeValues(chartTypes), width)
        if err != nil {
                return err
        }
        ctBars.Offset = vg.Points(-12)
        ctBars.Color = rgba(72, 219, 251, 255)

        popBars, err := plotter.NewBarChart(makeValues(popularity), width)
        if err != nil {
                return err
        }
        popBars.Offset = vg.Points(0)
        popBars.Color = rgba(255, 107, 107, 255)

        perfBars, err := plotter.NewBarChart(makeValues(performance), width)
        if err != nil {
                return err
        }
        perfBars.Offset = vg.Points(12)
        perfBars.Color = rgba(106, 176, 76, 255)

        p.Add(ctBars, popBars, perfBars)
        p.Legend.Top = true
        p.Legend.Left = true
        p.Legend.Add("Chart Types", ctBars)
        p.Legend.Add("Popularity", popBars)
        p.Legend.Add("Performance", perfBars)

        return p.Save(12*vg.Inch, 7*vg.Inch, outDir+"/01_bar_chart.png")
}

// 2. Scatter Plot
func makeScatterPlot(outDir string, chartTypes, performance []float64) error {
        p := plot.New()
        p.Title.Text = "Chart Types vs Performance by Language"
        p.X.Label.Text = "Chart Types Score"
        p.Y.Label.Text = "Performance Score"

        s, err := plotter.NewScatter(makeXYs(chartTypes, performance))
        if err != nil {
                return err
        }
        s.Color = rgba(72, 219, 251, 255)
        s.Radius = vg.Points(6)

        p.Add(s)
        return p.Save(10*vg.Inch, 7*vg.Inch, outDir+"/02_scatter_plot.png")
}

// 3. Line Chart (time series)
func makeLineChart(outDir string) error {
        p := plot.New()
        p.Title.Text = "Language Popularity Trends (2018-2024)"
        p.X.Label.Text = "Year"
        p.Y.Label.Text = "Popularity Index"

        years := []float64{2018, 2019, 2020, 2021, 2022, 2023, 2024}

        series := []struct {
                name string
                data []float64
                col  color.RGBA
        }{
                {"Python", []float64{68, 72, 78, 83, 87, 90, 92}, rgba(255, 107, 107, 255)},
                {"JavaScript", []float64{80, 82, 84, 85, 86, 87, 88}, rgba(78, 205, 196, 255)},
                {"C++", []float64{55, 56, 57, 58, 59, 60, 60}, rgba(255, 195, 0, 255)},
                {"Go", []float64{25, 30, 35, 38, 42, 44, 45}, rgba(0, 168, 255, 255)},
                {"Rust", []float64{10, 15, 22, 28, 32, 35, 38}, rgba(169, 115, 255, 255)},
        }

        for _, s := range series {
                l, err := plotter.NewLine(makeXYs(years, s.data))
                if err != nil {
                        return err
                }
                l.Color = s.col
                l.Width = vg.Points(2)
                p.Add(l)
                p.Legend.Add(s.name, l)
        }

        p.Legend.Top = true
        p.Legend.Left = true

        return p.Save(12*vg.Inch, 7*vg.Inch, outDir+"/03_line_chart.png")
}

// 4. Histogram
func makeHistogram(outDir string, chartTypes []float64) error {
        p := plot.New()
        p.Title.Text = "Distribution of Chart Types Scores"
        p.X.Label.Text = "Score"
        p.Y.Label.Text = "Count"

        h, err := plotter.NewHist(makeValues(chartTypes), 8)
        if err != nil {
                return err
        }
        h.FillColor = rgba(106, 176, 76, 180)
        h.LineStyle.Width = vg.Points(1)
        h.LineStyle.Color = rgba(106, 176, 76, 255)

        p.Add(h)
        return p.Save(10*vg.Inch, 7*vg.Inch, outDir+"/04_histogram.png")
}

// 5. Box Plot
func makeBoxPlot(outDir string, popularity, performance []float64) error {
        p := plot.New()
        p.Title.Text = "Box Plot: Popularity vs Performance"
        p.Y.Label.Text = "Score"

        type boxDef struct {
                name  string
                vals  plotter.Values
                xPos  float64
                fill  color.Color
                line  color.Color
        }

        boxDefs := []boxDef{
                {"Popularity", makeValues(popularity), 0.0, rgba(72, 219, 251, 180), rgba(72, 219, 251, 255)},
                {"Performance", makeValues(performance), 1.0, rgba(255, 107, 107, 180), rgba(255, 107, 107, 255)},
        }

        for _, bd := range boxDefs {
                w, err := plotter.NewBoxPlot(vg.Points(40), bd.xPos, bd.vals)
                if err != nil {
                        return err
                }
                w.FillColor = bd.fill
                w.BoxStyle.Color = bd.line
                w.BoxStyle.Width = vg.Points(2)
                w.WhiskerStyle.Color = bd.line
                w.WhiskerStyle.Width = vg.Points(2)
                w.MedianStyle.Color = color.White
                w.MedianStyle.Width = vg.Points(2)
                p.Add(w)
                p.Legend.Add(bd.name, colorBox{c: bd.line})
        }

        p.NominalX("Popularity", "Performance")
        p.Legend.Top = true
        p.X.Tick.Width = 0

        return p.Save(8*vg.Inch, 6*vg.Inch, outDir+"/05_box_plot.png")
}

// colorBox is a simple Thumbnailer that draws a colored rectangle for legends
type colorBox struct {
        c color.Color
}

func (b colorBox) Thumbnail(cv *draw.Canvas) {
        pts := []vg.Point{
                {X: cv.Min.X, Y: cv.Min.Y},
                {X: cv.Min.X, Y: cv.Max.Y},
                {X: cv.Max.X, Y: cv.Max.Y},
                {X: cv.Max.X, Y: cv.Min.Y},
        }
        poly := cv.ClipPolygonY(pts)
        cv.FillPolygon(b.c, poly)
}
