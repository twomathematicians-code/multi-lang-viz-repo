"""Stacked area chart from timeseries.csv showing all languages."""

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.font_manager as fm
import pandas as pd

fm.fontManager.addfont('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf')
plt.rcParams['font.sans-serif'] = ['DejaVu Sans']

DATA_PATH = '/home/z/my-project/download/multi-lang-viz-repo/data/timeseries.csv'
OUTPUT_PATH = '/home/z/my-project/download/multi-lang-viz-repo/output/python/07_stacked_area.png'

df = pd.read_csv(DATA_PATH)

plt.style.use('dark_background')
BG_COLOR = '#16213e'
fig, ax = plt.subplots(figsize=(13, 7), facecolor=BG_COLOR)
ax.set_facecolor(BG_COLOR)

lang_colors = ['#00d2ff', '#f7df1e', '#00b09b', '#f953c6', '#4caf50']
lang_names = ['Python', 'JavaScript', 'C++', 'Java', 'Go']
lang_cols = ['Python', 'JavaScript', 'C_plus_plus', 'Java', 'Go']

ax.stackplot(df['year'], *[df[col] for col in lang_cols],
             labels=lang_names, colors=lang_colors, alpha=0.8, zorder=3)

ax.set_title('Stacked Area: Language Popularity Over Time', fontsize=16,
             fontweight='bold', color='white', pad=15)
ax.set_xlabel('Year', fontsize=13, color='#aaaaaa')
ax.set_ylabel('Cumulative Popularity', fontsize=13, color='#aaaaaa')
ax.legend(loc='upper left', fontsize=11, facecolor='#1a1a3e', edgecolor='#444')
ax.grid(alpha=0.15, linestyle='--', zorder=0)
ax.tick_params(colors='#cccccc')
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)

fig.tight_layout()
fig.savefig(OUTPUT_PATH, dpi=150, facecolor=BG_COLOR)
print(f"✅ 07_stacked_area saved")
