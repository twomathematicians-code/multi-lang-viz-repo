"""Violin plot of chart_types distribution with swarm overlay."""

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.font_manager as fm
import pandas as pd
import numpy as np

fm.fontManager.addfont('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf')
plt.rcParams['font.sans-serif'] = ['DejaVu Sans']

DATA_PATH = '/home/z/my-project/download/multi-lang-viz-repo/data/sample_data.csv'
OUTPUT_PATH = '/home/z/my-project/download/multi-lang-viz-repo/output/python/14_violin.png'

df = pd.read_csv(DATA_PATH)

plt.style.use('dark_background')
BG_COLOR = '#16213e'
fig, ax = plt.subplots(figsize=(14, 7), facecolor=BG_COLOR)
ax.set_facecolor(BG_COLOR)

numeric_cols = ['chart_types', 'popularity', 'performance', 'ease_of_use',
                'community', 'web_export']
colors = ['#00d2ff', '#f953c6', '#4caf50', '#f7df1e', '#ff6f00', '#e44d26']

# Prepare data for violin: each metric value with a category label
all_vals = []
all_cats = []
for col in numeric_cols:
    for v in df[col]:
        all_vals.append(v)
        all_cats.append(col.replace('_', ' ').title())

# Violin plot
positions = range(len(numeric_cols))
parts = ax.violinplot([df[col].values for col in numeric_cols], positions=positions,
                      showmeans=False, showmedians=True, showextrema=False)

for i, pc in enumerate(parts['bodies']):
    pc.set_facecolor(colors[i])
    pc.set_alpha(0.7)
    pc.set_edgecolor('white')

parts['cmedians'].set_color('#ff4444')
parts['cmedians'].set_linewidth(2)

# Swarm overlay
for i, col in enumerate(numeric_cols):
    jitter = np.random.uniform(-0.15, 0.15, len(df))
    ax.scatter([i] * len(df) + jitter, df[col].values, c=colors[i],
               s=30, alpha=0.8, edgecolors='white', linewidth=0.5, zorder=4)

ax.set_xticks(positions)
ax.set_xticklabels([c.replace('_', ' ').title() for c in numeric_cols], rotation=20, ha='right')
ax.set_title('Violin Plot with Swarm Overlay', fontsize=16,
             fontweight='bold', color='white', pad=15)
ax.set_xlabel('Metric', fontsize=13, color='#aaaaaa')
ax.set_ylabel('Score', fontsize=13, color='#aaaaaa')
ax.grid(axis='y', alpha=0.15, linestyle='--', zorder=0)
ax.tick_params(colors='#cccccc')
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)

fig.tight_layout()
fig.savefig(OUTPUT_PATH, dpi=150, facecolor=BG_COLOR)
print(f"✅ 14_violin saved")
