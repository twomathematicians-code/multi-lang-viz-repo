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

void draw_circle(int cx, int cy, int r, uint8_t R, uint8_t G, uint8_t B) {
    for (int y = -r; y <= r; y++)
        for (int x = -r; x <= r; x++)
            if (x*x + y*y <= r*r) {
                int px = cx+x, py = cy+y;
                if (px >= 0 && px < W && py >= 0 && py < H) {
                    int idx = (py * W + px) * 3;
                    img[idx]=R; img[idx+1]=G; img[idx+2]=B;
                }
            }
}

void draw_circle_outline(int cx, int cy, int r, uint8_t R, uint8_t G, uint8_t B) {
    for (int y = -r; y <= r; y++)
        for (int x = -r; x <= r; x++) {
            int d = x*x + y*y;
            if (d <= r*r && d >= (r-1)*(r-1)) {
                int px = cx+x, py = cy+y;
                if (px >= 0 && px < W && py >= 0 && py < H) {
                    int idx = (py * W + px) * 3;
                    img[idx]=R; img[idx+1]=G; img[idx+2]=B;
                }
            }
        }
}

// Simple text rendering with 3x5 bitmap font
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
    draw_text(380, 20, "CHART TYPES VS PERFORMANCE", 255, 255, 255, 3);
    draw_text(460, 50, "SCATTER PLOT", 200, 200, 220, 2);

    // Chart area
    int left = 100, top = 90, right = 1100, bottom = 580;
    int chart_w = right - left, chart_h = bottom - top;

    int x_max = 70, y_max = 100;

    // Gridlines
    for (int v = 0; v <= x_max; v += 10) {
        int x = left + (v * chart_w / x_max);
        for (int yy = top; yy <= bottom; yy++) set_pixel(x, yy, 50, 60, 90);
        char buf[8]; snprintf(buf, sizeof(buf), "%d", v);
        draw_text(x - 7, bottom + 8, buf, 180, 190, 210, 1);
    }
    for (int v = 0; v <= y_max; v += 10) {
        int y = bottom - (v * chart_h / y_max);
        for (int xx = left; xx <= right; xx++) set_pixel(xx, y, 50, 60, 90);
        char buf[8]; snprintf(buf, sizeof(buf), "%d", v);
        draw_text(left - 35, y - 7, buf, 180, 190, 210, 1);
    }

    // Axes
    for (int x = left; x <= right; x++) { set_pixel(x, bottom, 200, 210, 230); set_pixel(x, top, 200, 210, 230); }
    for (int y = top; y <= bottom; y++) { set_pixel(left, y, 200, 210, 230); set_pixel(right, y, 200, 210, 230); }

    // X-axis label
    draw_text(500, bottom + 35, "CHART TYPES", 200, 210, 230, 2);
    // Y-axis label
    draw_text(15, 320, "PERFORMANCE", 200, 210, 230, 2);

    // Colors for each language
    uint8_t colors[9][3] = {
        {255,99,71},{30,144,255},{50,205,50},{255,215,0},{255,140,0},
        {147,112,219},{0,206,209},{255,105,180},{144,238,144}
    };

    // Draw scatter points
    for (int i = 0; i < 9; i++) {
        int px = left + (chart_types[i] * chart_w / x_max);
        int py = bottom - (performance[i] * chart_h / y_max);

        // Glow effect
        draw_circle(px, py, 14, colors[i][0]/4, colors[i][1]/4, colors[i][2]/4);
        // Outer ring
        draw_circle(px, py, 9, colors[i][0], colors[i][1], colors[i][2]);
        // Inner highlight
        draw_circle(px - 1, py - 1, 4, 255, 255, 255);

        // Label
        draw_text(px + 12, py - 6, languages[i], colors[i][0], colors[i][1], colors[i][2], 1);
    }

    // Legend
    int legend_x = 920, legend_y = 100;
    fill_rect(legend_x - 10, legend_y - 10, 190, 250, 30, 45, 75);
    draw_rect(legend_x - 10, legend_y - 10, 190, 250, 80, 90, 120);
    for (int i = 0; i < 9; i++) {
        draw_circle(legend_x + 6, legend_y + 8 + i * 26, 5, colors[i][0], colors[i][1], colors[i][2]);
        draw_text(legend_x + 18, legend_y + i * 26, languages[i], 220, 220, 230, 1);
    }

    stbi_write_png("/home/z/my-project/download/multi-lang-viz-repo/output/cpp/02_scatter_plot.png", W, H, 3, img, W * 3);
    return 0;
}
