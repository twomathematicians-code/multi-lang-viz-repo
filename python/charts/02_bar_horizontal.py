"""Horizontal bar chart comparing popularity across all languages."""

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.font_manager as fm
import pandas as pd

fm.fontManager.addfont('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf')
plt.rcParams['font.sans-serif'] = ['DejaVu Sans']

DATA_PATH = '/home/z/my-project/download/multi-lang-viz-repo/data/sample_data.csv'
OUTPUT_PATH = '/home/z/my-project/download/multi-lang-viz-repo/output/python/02_bar_horizontal.png'

df = pd.read_csv(DATA_PATH)
df = df.sort_values('popularity', ascending=True)

plt.style.use('dark_background')
BG_COLOR = '#16213e'
fig, ax = plt.subplots(figsize=(11, 7), facecolor=BG_COLOR)
ax.set_facecolor(BG_COLOR)

colors = ['#4caf50', '#f7df1e', '#c62828', '#955196', '#e44d26',
          '#00b09b', '#f953c6', '#3a7bd5', '#00d2ff']

bars = ax.barh(df['language'], df['popularity'], color=colors,
               edgecolor='white', linewidth=0.5, height=0.65, zorder=3)

for bar, val in zip(bars, df['popularity']):
    ax.text(bar.get_width() + 0.8, bar.get_y() + bar.get_height() / 2,
            str(val), ha='left', va='center', fontsize=11, fontweight='bold',
            color='white')

ax.set_title('Popularity Index by Programming Language', fontsize=16,
             fontweight='bold', color='white', pad=15)
ax.set_xlabel('Popularity Score', fontsize=13, color='#aaaaaa')
ax.set_ylabel('Language', fontsize=13, color='#aaaaaa')
ax.set_xlim(0, max(df['popularity']) * 1.12)
ax.grid(axis='x', alpha=0.15, linestyle='--', zorder=0)
ax.tick_params(colors='#cccccc')
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)
ax.spines['left'].set_color('#444444')
ax.spines['bottom'].set_color('#444444')

fig.tight_layout()
fig.savefig(OUTPUT_PATH, dpi=150, facecolor=BG_COLOR)
print(f"✅ 02_bar_horizontal saved")
