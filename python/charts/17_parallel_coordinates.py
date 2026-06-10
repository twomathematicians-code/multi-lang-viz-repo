"""Parallel coordinates plot from features.csv comparing all languages."""

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.font_manager as fm
import pandas as pd
import numpy as np

fm.fontManager.addfont('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf')
plt.rcParams['font.sans-serif'] = ['DejaVu Sans']

DATA_PATH = '/home/z/my-project/download/multi-lang-viz-repo/data/features.csv'
OUTPUT_PATH = '/home/z/my-project/download/multi-lang-viz-repo/output/python/17_parallel_coordinates.png'

df = pd.read_csv(DATA_PATH)
feature_cols = [c for c in df.columns if c != 'language']

plt.style.use('dark_background')
BG_COLOR = '#16213e'
fig, ax = plt.subplots(figsize=(16, 8), facecolor=BG_COLOR)
ax.set_facecolor(BG_COLOR)

colors = ['#00d2ff', '#f7df1e', '#00b09b', '#f953c6', '#4caf50',
          '#e44d26', '#955196', '#c62828', '#ff6f00']

x_positions = np.arange(len(feature_cols))

for idx, (_, row) in enumerate(df.iterrows()):
    values = [row[c] for c in feature_cols]
    ax.plot(x_positions, values, 'o-', linewidth=1.8, color=colors[idx],
            label=row['language'], markersize=5, alpha=0.85)

ax.set_xticks(x_positions)
ax.set_xticklabels([c.replace('_', '\n') for c in feature_cols],
                   fontsize=9, color='#cccccc', rotation=30, ha='right')
ax.set_ylabel('Score', fontsize=13, color='#aaaaaa')
ax.set_ylim(-5, 110)
ax.set_title('Parallel Coordinates: Language Feature Profiles', fontsize=16,
             fontweight='bold', color='white', pad=15)
ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.15), ncol=5,
          fontsize=10, facecolor='#1a1a3e', edgecolor='#444')
ax.grid(axis='y', alpha=0.15, linestyle='--', zorder=0)
ax.tick_params(colors='#cccccc')
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)

# Vertical lines at each axis
for xp in x_positions:
    ax.axvline(x=xp, color='#333366', linewidth=0.8, linestyle='-', zorder=0)

fig.tight_layout()
fig.savefig(OUTPUT_PATH, dpi=150, facecolor=BG_COLOR)
print(f"✅ 17_parallel_coordinates saved")
