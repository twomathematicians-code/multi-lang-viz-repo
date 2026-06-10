#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <cstdint>
#include <cmath>
#include <cstring>

const int W = 1200, H = 700;
uint8_t img[W * H * 3];

const char* languages[] = {"Python","JS","C++","Java","Go","R","Julia","Gnu","Bash"};
int chart_types[] = {65,55,30,22,14,45,38,20,8};
int popularity[] = {95,90,72,65,55,50,40,25,40};
int performance[] = {60,50,98,75,92,45,88,70,85};

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

// Render text as small colored block letters (5x7 pixel font approximation)
void draw_text_pixelated(int x, int y, const char* text, uint8_t r, uint8_t g, uint8_t b, int scale = 1) {
    // Simple 3x5 bitmap font for uppercase letters and digits
    static const uint8_t font[26][5] = {
        {0x7C,0x44,0x44,0x44,0x7C}, // A
        {0x7E,0x42,0x7E,0x42,0x7E}, // B  (simplified)
        {0x3E,0x42,0x42,0x42,0x24}, // C
        {0x7E,0x42,0x42,0x42,0x3C}, // D
        {0x7E,0x40,0x7E,0x40,0x7E}, // E
        {0x7E,0x40,0x7E,0x40,0x40}, // F
        {0x3E,0x40,0x4E,0x42,0x3E}, // G
        {0x42,0x42,0x7E,0x42,0x42}, // H
        {0x7E,0x08,0x08,0x08,0x7E}, // I
        {0x02,0x02,0x02,0x42,0x3C}, // J
        {0x42,0x48,0x70,0x48,0x42}, // K
        {0x40,0x40,0x40,0x40,0x7E}, // L
        {0x42,0x6C,0x54,0x42,0x42}, // M
        {0x42,0x62,0x52,0x4A,0x42}, // N
        {0x3C,0x42,0x42,0x42,0x3C}, // O
        {0x7E,0x44,0x7E,0x40,0x40}, // P
        {0x3C,0x42,0x42,0x52,0x34}, // Q
        {0x7E,0x48,0x48,0x48,0x44}, // R
        {0x24,0x42,0x42,0x42,0x24}, // S
        {0x7E,0x10,0x10,0x10,0x7E}, // T
        {0x42,0x42,0x42,0x42,0x3C}, // U
        {0x42,0x42,0x24,0x18,0x18}, // V
        {0x42,0x42,0x5A,0x66,0x42}, // W
        {0x42,0x24,0x18,0x24,0x42}, // X
        {0x42,0x24,0x18,0x10,0x10}, // Y
        {0x7E,0x04,0x08,0x10,0x7E}, // Z
    };
    static const uint8_t digits[10][5] = {
        {0x3C,0x42,0x42,0x42,0x3C}, // 0
        {0x08,0x18,0x08,0x08,0x1E}, // 1
        {0x3C,0x42,0x04,0x08,0x7E}, // 2
        {0x3C,0x04,0x1C,0x04,0x3C}, // 3
        {0x04,0x0C,0x14,0x7E,0x04}, // 4
        {0x7E,0x40,0x7C,0x02,0x7C}, // 5
        {0x3C,0x40,0x7C,0x42,0x3C}, // 6
        {0x7E,0x04,0x08,0x10,0x10}, // 7
        {0x3C,0x42,0x3C,0x42,0x3C}, // 8
        {0x3C,0x42,0x3C,0x02,0x3C}, // 9
    };

    int cx = x;
    for (int i = 0; text[i]; i++) {
        char ch = text[i];
        int ch_idx = -1;
        int is_digit = 0;
        if (ch >= 'A' && ch <= 'Z') ch_idx = ch - 'A';
        else if (ch >= 'a' && ch <= 'z') ch_idx = ch - 'a';
        else if (ch >= '0' && ch <= '9') { ch_idx = ch - '0'; is_digit = 1; }
        else if (ch == ' ') { cx += 4 * scale; continue; }
        else if (ch == '+') { // render plus as a small cross
            for (int sy = 0; sy < 5 * scale; sy++)
                for (int sx = 0; sx < 5 * scale; sx++) {
                    int bx = sx / scale, by = sy / scale;
                    if ((bx == 2 && (by == 1 || by == 2 || by == 3)) ||
                        (by == 2 && (bx == 0 || bx == 1 || bx == 3 || bx == 4)))
                        set_pixel(cx + sx, y + sy, r, g, b);
                }
            cx += 6 * scale;
            continue;
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
        } else {
            cx += 3 * scale;
        }
    }
}

int main() {
    // Background
    memset(img, 0, sizeof(img));
    fill_rect(0, 0, W, H, 22, 33, 62);

    // Title
    draw_text_pixelated(400, 20, "LANGUAGE METRICS", 255, 255, 255, 3);
    draw_text_pixelated(440, 50, "GROUPED BAR CHART", 200, 200, 220, 2);

    // Chart area
    int left = 100, top = 90, right = 1100, bottom = 580;
    int chart_w = right - left, chart_h = bottom - top;

    // Y-axis max
    int max_val = 100;

    // Gridlines and Y-axis labels
    for (int v = 0; v <= max_val; v += 10) {
        int y = bottom - (v * chart_h / max_val);
        // Gridline
        for (int x = left; x <= right; x++) set_pixel(x, y, 60, 70, 100);
        // Label
        char buf[8];
        snprintf(buf, sizeof(buf), "%d", v);
        draw_text_pixelated(left - 35, y - 7, buf, 180, 190, 210, 1);
    }

    // Axes
    for (int x = left; x <= right; x++) set_pixel(x, bottom, 200, 210, 230);
    for (int y = top; y <= bottom; y++) set_pixel(left, y, 200, 210, 230);

    // Bar colors: green, blue, red
    uint8_t bar_colors[3][3] = {{46,204,113}, {52,152,219}, {231,76,60}};

    int n_langs = 9;
    int n_metrics = 3;
    int group_width = chart_w / n_langs;
    int bar_width = group_width / (n_metrics + 1);

    int* metrics[3] = {chart_types, popularity, performance};
    const char* metric_names[] = {"Chart Types", "Popularity", "Performance"};

    for (int i = 0; i < n_langs; i++) {
        int group_x = left + i * group_width;
        for (int m = 0; m < n_metrics; m++) {
            int val = metrics[m][i];
            int bar_h = val * chart_h / max_val;
            int bx = group_x + (m + 1) * bar_width;
            int by = bottom - bar_h;

            // Draw bar with slight gradient effect
            for (int dy = 0; dy < bar_h; dy++) {
                float t = (float)dy / bar_h;
                uint8_t cr = bar_colors[m][0] * (0.6f + 0.4f * t);
                uint8_t cg = bar_colors[m][1] * (0.6f + 0.4f * t);
                uint8_t cb = bar_colors[m][2] * (0.6f + 0.4f * t);
                for (int dx = 0; dx < bar_width - 2; dx++)
                    set_pixel(bx + dx, by + dy, cr, cg, cb);
            }

            // Value on top
            char valbuf[8];
            snprintf(valbuf, sizeof(valbuf), "%d", val);
            draw_text_pixelated(bx + 2, by - 12, valbuf, 220, 220, 230, 1);
        }

        // Language label at bottom
        draw_text_pixelated(group_x + group_width / 2 - 15, bottom + 8, languages[i], 200, 210, 230, 1);
    }

    // Legend
    int legend_x = 880, legend_y = 100;
    fill_rect(legend_x - 10, legend_y - 10, 220, 90, 30, 45, 75);
    draw_rect(legend_x - 10, legend_y - 10, 220, 90, 80, 90, 120);
    for (int m = 0; m < n_metrics; m++) {
        fill_rect(legend_x, legend_y + m * 25, 16, 12, bar_colors[m][0], bar_colors[m][1], bar_colors[m][2]);
        draw_text_pixelated(legend_x + 22, legend_y + m * 25, metric_names[m], 220, 220, 230, 1);
    }

    stbi_write_png("/home/z/my-project/download/multi-lang-viz-repo/output/cpp/01_bar_chart.png", W, H, 3, img, W * 3);
    return 0;
}
