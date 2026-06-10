"""Line chart from timeseries.csv showing a single language trend (Python)."""

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.font_manager as fm
import pandas as pd

fm.fontManager.addfont('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf')
plt.rcParams['font.sans-serif'] = ['DejaVu Sans']

DATA_PATH = '/home/z/my-project/download/multi-lang-viz-repo/data/timeseries.csv'
OUTPUT_PATH = '/home/z/my-project/download/multi-lang-viz-repo/output/python/05_line_chart.png'

df = pd.read_csv(DATA_PATH)

plt.style.use('dark_background')
BG_COLOR = '#16213e'
fig, ax = plt.subplots(figsize=(12, 6), facecolor=BG_COLOR)
ax.set_facecolor(BG_COLOR)

ax.plot(df['year'], df['Python'], color='#00d2ff', linewidth=2.5,
        marker='o', markersize=6, markerfacecolor='#00d2ff',
        markeredgecolor='white', markeredgewidth=1, zorder=3)

ax.fill_between(df['year'], df['Python'], alpha=0.15, color='#00d2ff', zorder=2)

for x_val, y_val in zip(df['year'], df['Python']):
    ax.annotate(str(y_val), (x_val, y_val), textcoords='offset points',
                xytext=(0, 10), ha='center', fontsize=9, color='#cccccc')

ax.set_title('Python Popularity Trend (2016-2026)', fontsize=16,
             fontweight='bold', color='white', pad=15)
ax.set_xlabel('Year', fontsize=13, color='#aaaaaa')
ax.set_ylabel('Popularity Score', fontsize=13, color='#aaaaaa')
ax.set_ylim(60, 105)
ax.grid(alpha=0.15, linestyle='--', zorder=0)
ax.tick_params(colors='#cccccc')
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)

fig.tight_layout()
fig.savefig(OUTPUT_PATH, dpi=150, facecolor=BG_COLOR)
print(f"✅ 05_line_chart saved")
