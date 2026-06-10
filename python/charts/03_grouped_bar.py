"""Grouped bar chart with chart_types, popularity, and performance side by side."""

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.font_manager as fm
import pandas as pd
import numpy as np

fm.fontManager.addfont('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf')
plt.rcParams['font.sans-serif'] = ['DejaVu Sans']

DATA_PATH = '/home/z/my-project/download/multi-lang-viz-repo/data/sample_data.csv'
OUTPUT_PATH = '/home/z/my-project/download/multi-lang-viz-repo/output/python/03_grouped_bar.png'

df = pd.read_csv(DATA_PATH)

plt.style.use('dark_background')
BG_COLOR = '#16213e'
fig, ax = plt.subplots(figsize=(14, 7), facecolor=BG_COLOR)
ax.set_facecolor(BG_COLOR)

languages = df['language'].tolist()
x = np.arange(len(languages))
width = 0.25

metric_colors = {
    'chart_types': '#00d2ff',
    'popularity': '#f953c6',
    'performance': '#4caf50'
}

b1 = ax.bar(x - width, df['chart_types'], width, label='Chart Types',
            color=metric_colors['chart_types'], edgecolor='white', linewidth=0.4, zorder=3)
b2 = ax.bar(x, df['popularity'], width, label='Popularity',
            color=metric_colors['popularity'], edgecolor='white', linewidth=0.4, zorder=3)
b3 = ax.bar(x + width, df['performance'], width, label='Performance',
            color=metric_colors['performance'], edgecolor='white', linewidth=0.4, zorder=3)

ax.set_title('Grouped Comparison: Chart Types, Popularity & Performance',
             fontsize=15, fontweight='bold', color='white', pad=15)
ax.set_xlabel('Language', fontsize=13, color='#aaaaaa')
ax.set_ylabel('Score / Count', fontsize=13, color='#aaaaaa')
ax.set_xticks(x)
ax.set_xticklabels(languages, rotation=30, ha='right')
ax.legend(loc='upper right', fontsize=11, facecolor='#1a1a3e', edgecolor='#444')
ax.grid(axis='y', alpha=0.15, linestyle='--', zorder=0)
ax.tick_params(colors='#cccccc')
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)

fig.tight_layout()
fig.savefig(OUTPUT_PATH, dpi=150, facecolor=BG_COLOR)
print(f"✅ 03_grouped_bar saved")
