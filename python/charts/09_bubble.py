"""Bubble chart: x=chart_types, y=popularity, bubble size=performance."""

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.font_manager as fm
import pandas as pd
import numpy as np

fm.fontManager.addfont('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf')
plt.rcParams['font.sans-serif'] = ['DejaVu Sans']

DATA_PATH = '/home/z/my-project/download/multi-lang-viz-repo/data/sample_data.csv'
OUTPUT_PATH = '/home/z/my-project/download/multi-lang-viz-repo/output/python/09_bubble.png'

df = pd.read_csv(DATA_PATH)

plt.style.use('dark_background')
BG_COLOR = '#16213e'
fig, ax = plt.subplots(figsize=(12, 8), facecolor=BG_COLOR)
ax.set_facecolor(BG_COLOR)

colors = ['#00d2ff', '#f7df1e', '#00b09b', '#f953c6', '#4caf50',
          '#e44d26', '#955196', '#c62828', '#ff6f00']

# Scale bubble sizes
bubble_sizes = df['performance'].values * 8

for i, lang in enumerate(df['language']):
    ax.scatter(df['chart_types'].iloc[i], df['popularity'].iloc[i],
               s=bubble_sizes[i], c=colors[i], edgecolors='white',
               linewidths=1.2, alpha=0.75, zorder=3)
    ax.annotate(lang, (df['chart_types'].iloc[i], df['popularity'].iloc[i]),
                textcoords='offset points', xytext=(10, 5), fontsize=10,
                color='#cccccc', fontweight='bold')

ax.set_title('Bubble Chart: Chart Types vs Popularity (size = Performance)',
             fontsize=15, fontweight='bold', color='white', pad=15)
ax.set_xlabel('Chart Types', fontsize=13, color='#aaaaaa')
ax.set_ylabel('Popularity', fontsize=13, color='#aaaaaa')
ax.grid(alpha=0.15, linestyle='--', zorder=0)
ax.tick_params(colors='#cccccc')
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)

fig.tight_layout()
fig.savefig(OUTPUT_PATH, dpi=150, facecolor=BG_COLOR)
print(f"✅ 09_bubble saved")
