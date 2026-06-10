#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <cstdint>
#include <cmath>
#include <cstring>

const int W = 1200, H = 700;
uint8_t img[W * H * 3];

const char* languages[] = {"Python","JS","C++","Java","Go","R","Julia","Gnu","Bash"};
int chart_types[] = {65,55,30,22,14,45,38,20,8};

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
        else if (ch == '-') {
            for (int sx = 0; sx < 3 * scale; sx++)
                set_pixel(cx + sx, y + 2 * scale, r, g, b);
            cx += 4 * scale; continue;
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
    draw_text(420, 20, "CHART TYPES", 255, 255, 255, 3);
    draw_text(440, 50, "HISTOGRAM", 200, 200, 220, 2);

    // Compute histogram: 8 bins from 0 to 70
    const int n_bins = 8;
    const int bin_width = 10; // each bin covers 10 units: 0-9, 10-19, 20-29, 30-39, 40-49, 50-59, 60-69, 70+
    int bins[n_bins] = {};
    for (int i = 0; i < 9; i++) {
        int b = chart_types[i] / bin_width;
        if (b >= n_bins) b = n_bins - 1;
        bins[b]++;
    }

    // Find max count for scaling
    int max_count = 0;
    for (int i = 0; i < n_bins; i++) if (bins[i] > max_count) max_count = bins[i];

    int left = 120, top = 90, right = 1000, bottom = 560;
    int chart_w = right - left, chart_h = bottom - top;

    // Gridlines and Y-axis
    for (int v = 0; v <= max_count; v++) {
        int y = bottom - (v * chart_h / max_count);
        for (int x = left; x <= right; x++) set_pixel(x, y, 50, 60, 90);
        char buf[8]; snprintf(buf, sizeof(buf), "%d", v);
        draw_text(left - 25, y - 7, buf, 180, 190, 210, 1);
    }

    // Axes
    for (int x = left; x <= right; x++) set_pixel(x, bottom, 200, 210, 230);
    for (int y = top; y <= bottom; y++) set_pixel(left, y, 200, 210, 230);

    // Bar colors - gradient from cool to warm
    uint8_t bar_colors[n_bins][3] = {
        {52, 152, 219},   // blue
        {41, 128, 185},   // darker blue
        {46, 204, 113},   // green
        {39, 174, 96},    // darker green
        {241, 196, 15},   // yellow
        {230, 126, 34},   // orange
        {231, 76, 60},    // red
        {192, 57, 43},    // dark red
    };

    int bar_w = chart_w / n_bins;

    for (int i = 0; i < n_bins; i++) {
        int bx = left + i * bar_w;
        int bar_h = bins[i] * chart_h / max_count;
        int by = bottom - bar_h;

        // Draw bar with gradient
        for (int dy = 0; dy < bar_h; dy++) {
            float t = (float)dy / (bar_h > 0 ? bar_h : 1);
            uint8_t cr = bar_colors[i][0] * (0.5f + 0.5f * t);
            uint8_t cg = bar_colors[i][1] * (0.5f + 0.5f * t);
            uint8_t cb = bar_colors[i][2] * (0.5f + 0.5f * t);
            for (int dx = 0; dx < bar_w - 6; dx++)
                set_pixel(bx + 3 + dx, by + dy, cr, cg, cb);
        }

        // Top border
        if (bar_h > 0)
            for (int dx = 0; dx < bar_w - 6; dx++)
                set_pixel(bx + 3 + dx, by, 255, 255, 255);

        // Count on top
        if (bins[i] > 0) {
            char buf[8]; snprintf(buf, sizeof(buf), "%d", bins[i]);
            draw_text(bx + bar_w / 2 - 5, by - 12, buf, 255, 255, 255, 1);
        }

        // Bin label at bottom
        char label[16];
        int bin_start = i * bin_width;
        int bin_end = bin_start + bin_width - 1;
        if (i == n_bins - 1) {
            snprintf(label, sizeof(label), "%d+", bin_start);
        } else {
            snprintf(label, sizeof(label), "%d-%d", bin_start, bin_end);
        }
        draw_text(bx + bar_w / 2 - 12, bottom + 8, label, 180, 190, 210, 1);
    }

    // X-axis label
    draw_text(500, bottom + 35, "CHART TYPES RANGE", 200, 210, 230, 2);
    // Y-axis label
    draw_text(15, 320, "COUNT", 200, 210, 230, 2);

    // Data info panel
    int info_x = 1020, info_y = 100;
    fill_rect(info_x - 10, info_y - 10, 170, 280, 30, 45, 75);
    draw_rect(info_x - 10, info_y - 10, 170, 280, 80, 90, 120);
    draw_text(info_x, info_y, "DATA POINTS", 255, 255, 255, 2);
    for (int i = 0; i < 9; i++) {
        char buf[32];
        snprintf(buf, sizeof(buf), "%s: %d", languages[i], chart_types[i]);
        // Find which bin this falls in
        int b = chart_types[i] / bin_width;
        if (b >= n_bins) b = n_bins - 1;
        draw_text(info_x, info_y + 25 + i * 25, buf,
                  bar_colors[b][0], bar_colors[b][1], bar_colors[b][2], 1);
    }

    stbi_write_png("/home/z/my-project/download/multi-lang-viz-repo/output/cpp/04_histogram.png", W, H, 3, img, W * 3);
    return 0;
}
