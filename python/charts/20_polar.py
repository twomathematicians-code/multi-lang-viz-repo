"""Polar bar chart of ease_of_use scores for all languages."""

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.font_manager as fm
import pandas as pd
import numpy as np

fm.fontManager.addfont('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf')
plt.rcParams['font.sans-serif'] = ['DejaVu Sans']

DATA_PATH = '/home/z/my-project/download/multi-lang-viz-repo/data/sample_data.csv'
OUTPUT_PATH = '/home/z/my-project/download/multi-lang-viz-repo/output/python/20_polar.png'

df = pd.read_csv(DATA_PATH)

plt.style.use('dark_background')
BG_COLOR = '#16213e'
fig, ax = plt.subplots(figsize=(10, 10), subplot_kw=dict(polar=True),
                       facecolor=BG_COLOR)

n = len(df)
angles = np.linspace(0, 2 * np.pi, n, endpoint=False).tolist()
values = df['ease_of_use'].values.tolist()
values += values[:1]
angles += angles[:1]

colors = ['#00d2ff', '#f7df1e', '#00b09b', '#f953c6', '#4caf50',
          '#e44d26', '#955196', '#c62828', '#ff6f00']

width = 2 * np.pi / n * 0.8
bars = ax.bar(angles[:-1], df['ease_of_use'].values, width=width,
              color=colors, edgecolor='white', linewidth=0.8, alpha=0.85,
              zorder=3)

# Value labels
for angle, val, bar in zip(angles[:-1], df['ease_of_use'].values, bars):
    ax.text(angle, val + 3, str(val), ha='center', va='bottom',
            fontsize=10, fontweight='bold', color='white')

ax.set_xticks(angles[:-1])
ax.set_xticklabels(df['language'], fontsize=11, color='#cccccc')
ax.set_ylim(0, 110)
ax.set_yticks([20, 40, 60, 80, 100])
ax.set_yticklabels(['20', '40', '60', '80', '100'], fontsize=8, color='#888888')
ax.set_title('Ease of Use: Polar Bar Chart', fontsize=16,
             fontweight='bold', color='white', pad=25, y=1.08)
ax.grid(color='#444444', alpha=0.3)

fig.tight_layout()
fig.savefig(OUTPUT_PATH, dpi=150, facecolor=BG_COLOR)
print(f"✅ 20_polar saved")
