"""Radar/spider chart comparing top 5 languages across all features."""

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.font_manager as fm
import pandas as pd
import numpy as np

fm.fontManager.addfont('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf')
plt.rcParams['font.sans-serif'] = ['DejaVu Sans']

DATA_PATH = '/home/z/my-project/download/multi-lang-viz-repo/data/features.csv'
OUTPUT_PATH = '/home/z/my-project/download/multi-lang-viz-repo/output/python/16_radar.png'

df = pd.read_csv(DATA_PATH)

# Top 5 by community_size
top5 = df.nlargest(5, 'community_size')
feature_cols = [c for c in df.columns if c not in ['language']]

plt.style.use('dark_background')
BG_COLOR = '#16213e'
fig, ax = plt.subplots(figsize=(10, 10), subplot_kw=dict(polar=True),
                       facecolor=BG_COLOR)

angles = np.linspace(0, 2 * np.pi, len(feature_cols), endpoint=False).tolist()
angles += angles[:1]

colors = ['#00d2ff', '#f7df1e', '#00b09b', '#f953c6', '#4caf50']

for idx, (_, row) in enumerate(top5.iterrows()):
    values = [row[c] for c in feature_cols]
    values += values[:1]
    ax.plot(angles, values, 'o-', linewidth=2, label=row['language'],
            color=colors[idx], markersize=5)
    ax.fill(angles, values, alpha=0.1, color=colors[idx])

ax.set_xticks(angles[:-1])
ax.set_xticklabels([c.replace('_', '\n') for c in feature_cols],
                   fontsize=9, color='#cccccc')
ax.set_ylim(0, 105)
ax.set_yticks([20, 40, 60, 80, 100])
ax.set_yticklabels(['20', '40', '60', '80', '100'], fontsize=8, color='#888888')
ax.set_title('Top 5 Languages: Feature Radar Chart', fontsize=16,
             fontweight='bold', color='white', pad=25, y=1.08)
ax.legend(loc='upper right', bbox_to_anchor=(1.3, 1.1), fontsize=11,
          facecolor='#1a1a3e', edgecolor='#444')
ax.grid(color='#444444', alpha=0.3)

fig.tight_layout()
fig.savefig(OUTPUT_PATH, dpi=150, facecolor=BG_COLOR)
print(f"✅ 16_radar saved")
