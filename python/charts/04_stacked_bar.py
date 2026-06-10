"""Stacked bar chart with multiple metrics per language."""

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.font_manager as fm
import pandas as pd
import numpy as np

fm.fontManager.addfont('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf')
plt.rcParams['font.sans-serif'] = ['DejaVu Sans']

DATA_PATH = '/home/z/my-project/download/multi-lang-viz-repo/data/sample_data.csv'
OUTPUT_PATH = '/home/z/my-project/download/multi-lang-viz-repo/output/python/04_stacked_bar.png'

df = pd.read_csv(DATA_PATH)

plt.style.use('dark_background')
BG_COLOR = '#16213e'
fig, ax = plt.subplots(figsize=(12, 7), facecolor=BG_COLOR)
ax.set_facecolor(BG_COLOR)

languages = df['language'].tolist()
metrics = ['chart_types', 'popularity', 'ease_of_use', 'community', 'web_export']
colors = ['#00d2ff', '#f953c6', '#4caf50', '#f7df1e', '#ff6f00']

bottoms = np.zeros(len(languages))
for metric, color in zip(metrics, colors):
    vals = df[metric].values
    ax.bar(languages, vals, bottom=bottoms, label=metric.replace('_', ' ').title(),
           color=color, edgecolor='white', linewidth=0.3, width=0.65, zorder=3)
    bottoms += vals

ax.set_title('Stacked Metrics by Programming Language', fontsize=16,
             fontweight='bold', color='white', pad=15)
ax.set_xlabel('Language', fontsize=13, color='#aaaaaa')
ax.set_ylabel('Cumulative Score', fontsize=13, color='#aaaaaa')
ax.legend(loc='upper right', fontsize=10, facecolor='#1a1a3e', edgecolor='#444',
          ncol=2)
ax.grid(axis='y', alpha=0.15, linestyle='--', zorder=0)
ax.tick_params(colors='#cccccc', axis='x', rotation=30)
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)

plt.xticks(rotation=30, ha='right')
fig.tight_layout()
fig.savefig(OUTPUT_PATH, dpi=150, facecolor=BG_COLOR)
print(f"✅ 04_stacked_bar saved")
