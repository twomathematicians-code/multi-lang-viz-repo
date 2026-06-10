"""Correlation heatmap from features.csv (all numeric columns)."""

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.font_manager as fm
import pandas as pd
import numpy as np

fm.fontManager.addfont('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf')
plt.rcParams['font.sans-serif'] = ['DejaVu Sans']

DATA_PATH = '/home/z/my-project/download/multi-lang-viz-repo/data/features.csv'
OUTPUT_PATH = '/home/z/my-project/download/multi-lang-viz-repo/output/python/15_heatmap.png'

df = pd.read_csv(DATA_PATH)
numeric_df = df.select_dtypes(include=[np.number])
corr = numeric_df.corr()

plt.style.use('dark_background')
BG_COLOR = '#16213e'
fig, ax = plt.subplots(figsize=(13, 11), facecolor=BG_COLOR)

im = ax.imshow(corr, cmap='RdYlBu_r', vmin=-1, vmax=1, aspect='auto')

# Labels
labels = [c.replace('_', '\n') for c in corr.columns]
ax.set_xticks(range(len(labels)))
ax.set_yticks(range(len(labels)))
ax.set_xticklabels(labels, rotation=45, ha='right', fontsize=9, color='#cccccc')
ax.set_yticklabels(labels, fontsize=9, color='#cccccc')

# Annotation
for i in range(len(corr)):
    for j in range(len(corr)):
        text_color = 'white' if abs(corr.iloc[i, j]) > 0.5 else '#333333'
        ax.text(j, i, f'{corr.iloc[i, j]:.2f}', ha='center', va='center',
                fontsize=8, color=text_color, fontweight='bold')

cbar = fig.colorbar(im, ax=ax, shrink=0.8, pad=0.02)
cbar.ax.tick_params(colors='#cccccc')
cbar.set_label('Correlation', color='#aaaaaa', fontsize=11)

ax.set_title('Feature Correlation Heatmap', fontsize=16,
             fontweight='bold', color='white', pad=15)

fig.tight_layout()
fig.savefig(OUTPUT_PATH, dpi=150, facecolor=BG_COLOR)
print(f"✅ 15_heatmap saved")
