#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <cstdint>
#include <cmath>
#include <cstring>

const int W = 1200, H = 700;
uint8_t img[W * H * 3];

int years[] = {2016,2017,2018,2019,2020,2021,2022,2023,2024,2025,2026};
int pyTrend[] = {70,73,78,82,88,92,94,95,96,97,98};
int jsTrend[] = {75,78,82,85,88,90,92,94,95,96,97};
int cppTrend[] = {78,78,77,76,75,74,73,72,72,72,72};
int javaTrend[] = {80,78,75,72,68,65,62,60,58,56,54};
int goTrend[] = {20,28,38,48,55,62,68,72,75,78,80};

const char* langNames[] = {"Python","JS","C++","Java","Go"};

void set_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    if (x >= 0 && x < W && y >= 0 && y < H) {
        int idx = (y * W + x) * 3;
        img[idx] = r; img[idx+1] = g; img[idx+2] = b;
    }
}

void fill_rect(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b) {
    for (int dy = 0; dy < h; dy++)
        for (int dx = 0; dx < w; dx++)
            set_pixel(x + dx, y + dy, r, g, b);
}

void draw_rect(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b) {
    for (int dx = 0; dx < w; dx++) { set_pixel(x+dx,y,r,g,b); set_pixel(x+dx,y+h-1,r,g,b); }
    for (int dy = 0; dy < h; dy++) { set_pixel(x,y+dy,r,g,b); set_pixel(x+w-1,y+dy,r,g,b); }
}

void draw_circle(int cx, int cy, int r, uint8_t R, uint8_t G, uint8_t B) {
    for (int y = -r; y <= r; y++)
        for (int x = -r; x <= r; x++)
            if (x*x + y*y <= r*r)
                set_pixel(cx+x, cy+y, R, G, B);
}

// Bresenham-like thick line
void draw_line(int x0, int y0, int x1, int y1, uint8_t r, uint8_t g, uint8_t b, int thickness = 2) {
    int dx = abs(x1 - x0), dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1, sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;
    while (true) {
        for (int ty = -thickness/2; ty <= thickness/2; ty++)
            for (int tx = -thickness/2; tx <= thickness/2; tx++)
                set_pixel(x0 + tx, y0 + ty, r, g, b);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
}

static const uint8_t font[26][5] = {
    {0x7C,0x44,0x44,0x44,0x7C},{0x7E,0x42,0x7E,0x42,0x7E},{0x3E,0x42,0x42,0x42,0x24},
    {0x7E,0x42,0x42,0x42,0x3C},{0x7E,0x40,0x7E,0x40,0x7E},{0x7E,0x40,0x7E,0x40,0x40},
    {0x3E,0x40,0x4E,0x42,0x3E},{0x42,0x42,0x7E,0x42,0x42},{0x7E,0x08,0x08,0x08,0x7E},
    {0x02,0x02,0x02,0x42,0x3C},{0x42,0x48,0x70,0x48,0x42},{0x40,0x40,0x40,0x40,0x7E},
    {0x42,0x6C,0x54,0x42,0x42},{0x42,0x62,0x52,0x4A,0x42},{0x3C,0x42,0x42,0x42,0x3C},
    {0x7E,0x44,0x7E,0x40,0x40},{0x3C,0x42,0x42,0x52,0x34},{0x7E,0x48,0x48,0x48,0x44},
    {0x24,0x42,0x42,0x42,0x24},{0x7E,0x10,0x10,0x10,0x7E},{0x42,0x42,0x42,0x42,0x3C},
    {0x42,0x42,0x24,0x18,0x18},{0x42,0x42,0x5A,0x66,0x42},{0x42,0x24,0x18,0x24,0x42},
    {0x42,0x24,0x18,0x10,0x10},{0x7E,0x04,0x08,0x10,0x7E},
};
static const uint8_t digits[10][5] = {
    {0x3C,0x42,0x42,0x42,0x3C},{0x08,0x18,0x08,0x08,0x1E},{0x3C,0x42,0x04,0x08,0x7E},
    {0x3C,0x04,0x1C,0x04,0x3C},{0x04,0x0C,0x14,0x7E,0x04},{0x7E,0x40,0x7C,0x02,0x7C},
    {0x3C,0x40,0x7C,0x42,0x3C},{0x7E,0x04,0x08,0x10,0x10},{0x3C,0x42,0x3C,0x42,0x3C},
    {0x3C,0x42,0x3C,0x02,0x3C},
};

void draw_text(int x, int y, const char* text, uint8_t r, uint8_t g, uint8_t b, int scale = 1) {
    int cx = x;
    for (int i = 0; text[i]; i++) {
        char ch = text[i];
        int ch_idx = -1, is_digit = 0;
        if (ch >= 'A' && ch <= 'Z') ch_idx = ch - 'A';
        else if (ch >= 'a' && ch <= 'z') ch_idx = ch - 'a';
        else if (ch >= '0' && ch <= '9') { ch_idx = ch - '0'; is_digit = 1; }
        else if (ch == ' ') { cx += 4 * scale; continue; }
        else if (ch == '+') {
            for (int sy = 0; sy < 5 * scale; sy++)
                for (int sx = 0; sx < 5 * scale; sx++) {
                    int bx = sx / scale, by = sy / scale;
                    if ((bx == 2 && (by == 1 || by == 2 || by == 3)) || (by == 2 && (bx == 0 || bx == 1 || bx == 3 || bx == 4)))
                        set_pixel(cx + sx, y + sy, r, g, b);
                }
            cx += 6 * scale; continue;
        }
        if (ch_idx >= 0) {
            const uint8_t* glyph = is_digit ? digits[ch_idx] : font[ch_idx];
            for (int sy = 0; sy < 5 * scale; sy++)
                for (int sx = 0; sx < 4 * scale; sx++) {
                    int bx = sx / scale, by = sy / scale;
                    if (glyph[by] & (0x80 >> bx))
                        set_pixel(cx + sx, y + sy, r, g, b);
                }
            cx += 5 * scale;
        } else { cx += 3 * scale; }
    }
}

int main() {
    memset(img, 0, sizeof(img));
    fill_rect(0, 0, W, H, 22, 33, 62);

    // Title
    draw_text(400, 15, "LANGUAGE POPULARITY TRENDS", 255, 255, 255, 3);
    draw_text(490, 48, "LINE CHART 2016-2026", 200, 200, 220, 2);

    int left = 100, top = 85, right = 1080, bottom = 570;
    int chart_w = right - left, chart_h = bottom - top;
    int n_points = 11;
    int y_min = 0, y_max = 100;

    // Gridlines
    for (int v = 0; v <= 100; v += 10) {
        int y = bottom - (v * chart_h / (y_max - y_min));
        for (int x = left; x <= right; x++) set_pixel(x, y, 50, 60, 90);
        char buf[8]; snprintf(buf, sizeof(buf), "%d", v);
        draw_text(left - 35, y - 7, buf, 180, 190, 210, 1);
    }

    // X-axis year labels
    for (int i = 0; i < n_points; i++) {
        int x = left + (i * chart_w / (n_points - 1));
        for (int y = top; y <= bottom; y++) set_pixel(x, y, 50, 60, 90);
        char buf[8]; snprintf(buf, sizeof(buf), "%d", years[i]);
        draw_text(x - 10, bottom + 8, buf, 180, 190, 210, 1);
    }

    // Axes
    for (int x = left; x <= right; x++) set_pixel(x, bottom, 200, 210, 230);
    for (int y = top; y <= bottom; y++) set_pixel(left, y, 200, 210, 230);

    // Line colors
    uint8_t line_colors[5][3] = {
        {255, 211, 42},   // Python - gold
        {255, 159, 28},   // JS - orange
        {0, 173, 239},    // C++ - blue
        {237, 28, 36},    // Java - red
        {0, 166, 81},     // Go - green
    };

    int* trends[5] = {pyTrend, jsTrend, cppTrend, javaTrend, goTrend};

    for (int i = 0; i < 5; i++) {
        // Draw line
        for (int j = 0; j < n_points - 1; j++) {
            int x0 = left + (j * chart_w / (n_points - 1));
            int y0 = bottom - (trends[i][j] * chart_h / (y_max - y_min));
            int x1 = left + ((j + 1) * chart_w / (n_points - 1));
            int y1 = bottom - (trends[i][j + 1] * chart_h / (y_max - y_min));
            draw_line(x0, y0, x1, y1, line_colors[i][0], line_colors[i][1], line_colors[i][2], 3);
        }
        // Draw data points
        for (int j = 0; j < n_points; j++) {
            int px = left + (j * chart_w / (n_points - 1));
            int py = bottom - (trends[i][j] * chart_h / (y_max - y_min));
            draw_circle(px, py, 5, line_colors[i][0], line_colors[i][1], line_colors[i][2]);
            draw_circle(px - 1, py - 1, 2, 255, 255, 255);
        }
    }

    // Legend
    int legend_x = 910, legend_y = 95;
    fill_rect(legend_x - 10, legend_y - 10, 185, 140, 30, 45, 75);
    draw_rect(legend_x - 10, legend_y - 10, 185, 140, 80, 90, 120);
    for (int i = 0; i < 5; i++) {
        fill_rect(legend_x, legend_y + i * 25, 20, 4, line_colors[i][0], line_colors[i][1], line_colors[i][2]);
        draw_circle(legend_x + 10, legend_y + 2 + i * 25, 3, line_colors[i][0], line_colors[i][1], line_colors[i][2]);
        draw_text(legend_x + 26, legend_y + i * 25, langNames[i], 220, 220, 230, 1);
    }

    // Y-axis label
    draw_text(15, 320, "POPULARITY", 200, 210, 230, 2);
    // X-axis label
    draw_text(520, bottom + 35, "YEAR", 200, 210, 230, 2);

    // Data value annotations at end of lines
    for (int i = 0; i < 5; i++) {
        int px = right + 5;
        int py = bottom - (trends[i][n_points - 1] * chart_h / (y_max - y_min));
        char buf[8]; snprintf(buf, sizeof(buf), "%d", trends[i][n_points - 1]);
        draw_text(px, py - 6, buf, line_colors[i][0], line_colors[i][1], line_colors[i][2], 1);
    }

    stbi_write_png("/home/z/my-project/download/multi-lang-viz-repo/output/cpp/03_line_chart.png", W, H, 3, img, W * 3);
    return 0;
}
