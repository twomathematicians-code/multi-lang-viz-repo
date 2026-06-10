"""Vertical bar chart comparing all 9 languages by chart_types metric."""

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.font_manager as fm
import pandas as pd
import numpy as np

fm.fontManager.addfont('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf')
plt.rcParams['font.sans-serif'] = ['DejaVu Sans']

DATA_PATH = '/home/z/my-project/download/multi-lang-viz-repo/data/sample_data.csv'
OUTPUT_PATH = '/home/z/my-project/download/multi-lang-viz-repo/output/python/01_bar_vertical.png'

# Read data
df = pd.read_csv(DATA_PATH)

# Dark professional styling
plt.style.use('dark_background')
BG_COLOR = '#16213e'
fig, ax = plt.subplots(figsize=(12, 7), facecolor=BG_COLOR)
ax.set_facecolor(BG_COLOR)

colors = ['#00d2ff', '#3a7bd5', '#f953c6', '#00b09b', '#e44d26',
          '#f7df1e', '#955196', '#c62828', '#4caf50']

bars = ax.bar(df['language'], df['chart_types'], color=colors, edgecolor='white',
              linewidth=0.5, width=0.7, zorder=3)

# Value labels on top
for bar, val in zip(bars, df['chart_types']):
    ax.text(bar.get_x() + bar.get_width() / 2, bar.get_height() + 0.8,
            str(val), ha='center', va='bottom', fontsize=11, fontweight='bold',
            color='white')

ax.set_title('Chart Types Supported by Programming Language', fontsize=16,
             fontweight='bold', color='white', pad=15)
ax.set_xlabel('Language', fontsize=13, color='#aaaaaa')
ax.set_ylabel('Number of Chart Types', fontsize=13, color='#aaaaaa')
ax.set_ylim(0, max(df['chart_types']) * 1.15)
ax.grid(axis='y', alpha=0.15, linestyle='--', zorder=0)
ax.tick_params(colors='#cccccc')
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)
ax.spines['left'].set_color('#444444')
ax.spines['bottom'].set_color('#444444')

fig.tight_layout()
fig.savefig(OUTPUT_PATH, dpi=150, facecolor=BG_COLOR)
print(f"✅ 01_bar_vertical saved")
