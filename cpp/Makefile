CXX = g++
CXXFLAGS = -std=c++17 -O2
COMMON = charts/stb_image_write.h

all: ../output/cpp/01_bar_chart.png ../output/cpp/02_scatter_plot.png ../output/cpp/03_line_chart.png ../output/cpp/04_histogram.png ../output/cpp/05_pie_chart.png

../output/cpp/%.png: charts/%.cpp $(COMMON)
	$(CXX) $(CXXFLAGS) $< -o /tmp/cpp_chart -lm && /tmp/cpp_chart

clean:
	rm -f /tmp/cpp_chart
