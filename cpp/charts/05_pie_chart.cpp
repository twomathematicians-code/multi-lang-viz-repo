#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <cstdint>
#include <cmath>
#include <cstring>

const int W = 1200, H = 700;
uint8_t img[W * H * 3];

const char* languages[] = {"Python","JS","C++","Java","Go","R","Julia","Gnu","Bash"};
int popularity[] = {95,90,72,65,55,50,40,25,40};

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

void draw_circle_outline(int cx, int cy, int r, uint8_t R, uint8_t G, uint8_t B) {
    for (int y = -r; y <= r; y++)
        for (int x = -r; x <= r; x++) {
            int d = x*x + y*y;
            if (d <= r*r && d >= (r-1)*(r-1))
                set_pixel(cx+x, cy+y, R, G, B);
        }
}

void draw_arc_filled(int cx, int cy, int r, float start_angle, float end_angle, uint8_t R, uint8_t G, uint8_t B) {
    for (int y = -r; y <= r; y++)
        for (int x = -r; x <= r; x++) {
            if (x*x + y*y > r*r) continue;
            float angle = atan2(y, x);
            if (angle < 0) angle += 2 * M_PI;
            // Handle wrap-around
            if (start_angle < end_angle) {
                if (angle >= start_angle && angle < end_angle)
                    set_pixel(cx+x, cy+y, R, G, B);
            } else {
                if (angle >= start_angle || angle < end_angle)
                    set_pixel(cx+x, cy+y, R, G, B);
            }
        }
}

void draw_arc_outline(int cx, int cy, int r, float start_angle, float end_angle, uint8_t R, uint8_t G, uint8_t B) {
    for (int y = -r; y <= r; y++)
        for (int x = -r; x <= r; x++) {
            int d = x*x + y*y;
            if (d > r*r || d < (r-1)*(r-1)) continue;
            float angle = atan2(y, x);
            if (angle < 0) angle += 2 * M_PI;
            if (start_angle < end_angle) {
                if (angle >= start_angle && angle < end_angle)
                    set_pixel(cx+x, cy+y, R, G, B);
            } else {
                if (angle >= start_angle || angle < end_angle)
                    set_pixel(cx+x, cy+y, R, G, B);
            }
        }
}

void draw_line(int x0, int y0, int x1, int y1, uint8_t r, uint8_t g, uint8_t b) {
    int dx = abs(x1 - x0), dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1, sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;
    while (true) {
        set_pixel(x0, y0, r, g, b);
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
        else if (ch == '%') {
            // render as simple P-like symbol
            for (int sy = 0; sy < 5 * scale; sy++)
                for (int sx = 0; sx < 4 * scale; sx++) {
                    int bx = sx / scale, by = sy / scale;
                    if ((by == 0 || by == 4) && bx >= 1 && bx <= 2 ||
                        (by >= 1 && by <= 3) && bx == 0 ||
                        (by == 2) && bx == 3)
                        set_pixel(cx + sx, y + sy, r, g, b);
                }
            cx += 5 * scale; continue;
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
    draw_text(400, 15, "LANGUAGE POPULARITY", 255, 255, 255, 3);
    draw_text(460, 48, "PIE CHART", 200, 200, 220, 2);

    // Calculate total and angles
    int total = 0;
    for (int i = 0; i < 9; i++) total += popularity[i];

    // Pie chart colors
    uint8_t colors[9][3] = {
        {255, 211, 42},   // Python - gold
        {255, 159, 28},   // JS - orange
        {0, 173, 239},    // C++ - blue
        {237, 28, 36},    // Java - red
        {0, 166, 81},     // Go - green
        {128, 0, 128},    // R - purple
        {255, 105, 180},  // Julia - pink
        {165, 42, 42},    // Gnu - brown
        {144, 238, 144},  // Bash - light green
    };

    int cx = 420, cy = 370, radius = 220;

    // Draw filled slices
    float current_angle = 0.0f;
    float angles[9], mid_angles[9];
    for (int i = 0; i < 9; i++) {
        float slice_angle = (float)popularity[i] / total * 2 * M_PI;
        angles[i] = slice_angle;
        mid_angles[i] = current_angle + slice_angle / 2;
        draw_arc_filled(cx, cy, radius, current_angle, current_angle + slice_angle,
                       colors[i][0], colors[i][1], colors[i][2]);
        current_angle += slice_angle;
    }

    // Draw slice borders
    current_angle = 0.0f;
    for (int i = 0; i < 9; i++) {
        float start_angle = current_angle;
        float end_angle = current_angle + angles[i];
        // Separator lines from center
        int ex = cx + (int)(radius * cos(start_angle));
        int ey = cy + (int)(radius * sin(start_angle));
        draw_line(cx, cy, ex, ey, 22, 33, 62);
        current_angle = end_angle;
    }

    // Draw circle outline
    draw_circle_outline(cx, cy, radius, 200, 210, 230);

    // Inner circle (donut effect for style)
    fill_rect(0, 0, 0, 0, 0, 0, 0); // no-op
    // Small center circle
    draw_circle(cx, cy, 40, 22, 33, 62);
    draw_circle_outline(cx, cy, 40, 200, 210, 230);

    // Labels with lines pointing to slices
    for (int i = 0; i < 9; i++) {
        float mid = mid_angles[i];
        float pct = (float)popularity[i] / total * 100;
        int label_r = radius + 50;
        int lx = cx + (int)(label_r * cos(mid));
        int ly = cy + (int)(label_r * sin(mid));

        // Line from edge to label
        int edge_x = cx + (int)(radius * cos(mid));
        int edge_y = cy + (int)(radius * sin(mid));
        draw_line(edge_x, edge_y, lx, ly, colors[i][0], colors[i][1], colors[i][2]);

        // Language name
        draw_text(lx + 5, ly - 6, languages[i], colors[i][0], colors[i][1], colors[i][2], 1);

        // Percentage
        char pbuf[16];
        snprintf(pbuf, sizeof(pbuf), "%.0f%%", pct);
        draw_text(lx + 5, ly + 4, pbuf, 220, 220, 230, 1);
    }

    // Legend panel on the right
    int legend_x = 850, legend_y = 80;
    fill_rect(legend_x - 10, legend_y - 10, 280, 300, 30, 45, 75);
    draw_rect(legend_x - 10, legend_y - 10, 280, 300, 80, 90, 120);
    draw_text(legend_x + 40, legend_y, "LEGEND", 255, 255, 255, 2);

    for (int i = 0; i < 9; i++) {
        int ly = legend_y + 30 + i * 28;
        fill_rect(legend_x, ly, 14, 14, colors[i][0], colors[i][1], colors[i][2]);
        draw_rect(legend_x, ly, 14, 14, 255, 255, 255);
        draw_text(legend_x + 20, ly, languages[i], 220, 220, 230, 1);
        char valbuf[24];
        float pct = (float)popularity[i] / total * 100;
        snprintf(valbuf, sizeof(valbuf), "%d (%.1f%%)", popularity[i], pct);
        draw_text(legend_x + 100, ly, valbuf, 180, 190, 210, 1);
    }

    // Total
    draw_text(legend_x + 40, legend_y + 285, "TOTAL", 200, 210, 230, 2);
    char totalbuf[16];
    snprintf(totalbuf, sizeof(totalbuf), "%d", total);
    draw_text(legend_x + 130, legend_y + 285, totalbuf, 255, 255, 255, 2);

    stbi_write_png("/home/z/my-project/download/multi-lang-viz-repo/output/cpp/05_pie_chart.png", W, H, 3, img, W * 3);
    return 0;
}
