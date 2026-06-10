"""Box plot of all numeric columns from sample_data.csv."""

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.font_manager as fm
import pandas as pd
import numpy as np

fm.fontManager.addfont('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf')
plt.rcParams['font.sans-serif'] = ['DejaVu Sans']

DATA_PATH = '/home/z/my-project/download/multi-lang-viz-repo/data/sample_data.csv'
OUTPUT_PATH = '/home/z/my-project/download/multi-lang-viz-repo/output/python/13_box_plot.png'

df = pd.read_csv(DATA_PATH)

# Select numeric columns (excluding year_established as it's on a different scale)
numeric_cols = ['chart_types', 'popularity', 'performance', 'ease_of_use',
                'community', 'web_export']

plt.style.use('dark_background')
BG_COLOR = '#16213e'
fig, ax = plt.subplots(figsize=(13, 7), facecolor=BG_COLOR)
ax.set_facecolor(BG_COLOR)

data_for_box = [df[col].values for col in numeric_cols]
colors = ['#00d2ff', '#f953c6', '#4caf50', '#f7df1e', '#ff6f00', '#e44d26']

bp = ax.boxplot(data_for_box, labels=[c.replace('_', ' ').title() for c in numeric_cols],
                patch_artist=True, widths=0.5,
                boxprops=dict(linewidth=1.5),
                whiskerprops=dict(linewidth=1.5, color='#aaaaaa'),
                capprops=dict(linewidth=1.5, color='#aaaaaa'),
                medianprops=dict(linewidth=2.5, color='#ff4444'),
                flierprops=dict(marker='o', markerfacecolor='#ff6f00',
                                markeredgecolor='white', markersize=7))

for patch, color in zip(bp['boxes'], colors):
    patch.set_facecolor(color)
    patch.set_alpha(0.7)
    patch.set_edgecolor('white')

ax.set_title('Box Plot of Language Metrics', fontsize=16,
             fontweight='bold', color='white', pad=15)
ax.set_xlabel('Metric', fontsize=13, color='#aaaaaa')
ax.set_ylabel('Score', fontsize=13, color='#aaaaaa')
ax.grid(axis='y', alpha=0.15, linestyle='--', zorder=0)
ax.tick_params(colors='#cccccc')
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)
plt.xticks(rotation=20, ha='right')

fig.tight_layout()
fig.savefig(OUTPUT_PATH, dpi=150, facecolor=BG_COLOR)
print(f"✅ 13_box_plot saved")
