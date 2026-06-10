"""Scatter plot of chart_types vs performance for all languages."""

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.font_manager as fm
import pandas as pd

fm.fontManager.addfont('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf')
plt.rcParams['font.sans-serif'] = ['DejaVu Sans']

DATA_PATH = '/home/z/my-project/download/multi-lang-viz-repo/data/sample_data.csv'
OUTPUT_PATH = '/home/z/my-project/download/multi-lang-viz-repo/output/python/08_scatter.png'

df = pd.read_csv(DATA_PATH)

plt.style.use('dark_background')
BG_COLOR = '#16213e'
fig, ax = plt.subplots(figsize=(10, 8), facecolor=BG_COLOR)
ax.set_facecolor(BG_COLOR)

colors = ['#00d2ff', '#f7df1e', '#00b09b', '#f953c6', '#4caf50',
          '#e44d26', '#955196', '#c62828', '#ff6f00']

ax.scatter(df['chart_types'], df['performance'], c=colors, s=180,
           edgecolors='white', linewidths=1.2, zorder=3, alpha=0.9)

for i, lang in enumerate(df['language']):
    ax.annotate(lang, (df['chart_types'].iloc[i], df['performance'].iloc[i]),
                textcoords='offset points', xytext=(8, 8), fontsize=10,
                color='#cccccc', fontweight='bold')

ax.set_title('Chart Types vs Performance by Language', fontsize=16,
             fontweight='bold', color='white', pad=15)
ax.set_xlabel('Chart Types', fontsize=13, color='#aaaaaa')
ax.set_ylabel('Performance Score', fontsize=13, color='#aaaaaa')
ax.grid(alpha=0.15, linestyle='--', zorder=0)
ax.tick_params(colors='#cccccc')
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)

fig.tight_layout()
fig.savefig(OUTPUT_PATH, dpi=150, facecolor=BG_COLOR)
print(f"✅ 08_scatter saved")
