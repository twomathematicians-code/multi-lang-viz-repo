"""Histogram of developer_millions distribution across languages."""

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.font_manager as fm
import pandas as pd
import numpy as np

fm.fontManager.addfont('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf')
plt.rcParams['font.sans-serif'] = ['DejaVu Sans']

DATA_PATH = '/home/z/my-project/download/multi-lang-viz-repo/data/sample_data.csv'
OUTPUT_PATH = '/home/z/my-project/download/multi-lang-viz-repo/output/python/12_histogram.png'

df = pd.read_csv(DATA_PATH)

plt.style.use('dark_background')
BG_COLOR = '#16213e'
fig, ax = plt.subplots(figsize=(11, 7), facecolor=BG_COLOR)
ax.set_facecolor(BG_COLOR)

n, bins, patches = ax.hist(df['developers_millions'], bins=10,
                           color='#00d2ff', edgecolor='white',
                           linewidth=0.8, alpha=0.85, zorder=3)

# Gradient coloring
colormap = plt.cm.cool
bin_centers = 0.5 * (bins[:-1] + bins[1:])
col_norm = (bin_centers - bin_centers.min()) / (bin_centers.max() - bin_centers.min())
for c_val, patch in zip(col_norm, patches):
    patch.set_facecolor(colormap(c_val))

ax.set_title('Distribution of Developer Count (Millions)', fontsize=16,
             fontweight='bold', color='white', pad=15)
ax.set_xlabel('Developers (Millions)', fontsize=13, color='#aaaaaa')
ax.set_ylabel('Frequency', fontsize=13, color='#aaaaaa')
ax.grid(axis='y', alpha=0.15, linestyle='--', zorder=0)
ax.tick_params(colors='#cccccc')
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)

# Add mean line
mean_val = df['developers_millions'].mean()
ax.axvline(mean_val, color='#f953c6', linestyle='--', linewidth=2, label=f'Mean: {mean_val:.1f}M')
ax.legend(facecolor='#1a1a3e', edgecolor='#444', fontsize=11)

fig.tight_layout()
fig.savefig(OUTPUT_PATH, dpi=150, facecolor=BG_COLOR)
print(f"✅ 12_histogram saved")
