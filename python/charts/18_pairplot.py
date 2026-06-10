"""Seaborn pairplot from sample_data.csv numeric columns."""

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.font_manager as fm
import pandas as pd
import seaborn as sns
import numpy as np

fm.fontManager.addfont('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf')
plt.rcParams['font.sans-serif'] = ['DejaVu Sans']

DATA_PATH = '/home/z/my-project/download/multi-lang-viz-repo/data/sample_data.csv'
OUTPUT_PATH = '/home/z/my-project/download/multi-lang-viz-repo/output/python/18_pairplot.png'

df = pd.read_csv(DATA_PATH)
numeric_cols = ['chart_types', 'popularity', 'performance', 'ease_of_use',
                'community', 'web_export']
plot_df = df[numeric_cols]

plt.style.use('dark_background')
BG_COLOR = '#16213e'

g = sns.pairplot(plot_df, diag_kind='kde', corner=True,
                 plot_kws={'color': '#00d2ff', 'alpha': 0.7, 's': 40,
                           'edgecolor': 'white', 'linewidth': 0.5},
                 diag_kws={'color': '#f953c6', 'fill': True, 'alpha': 0.5},
                 height=2.5, aspect=1)

g.figure.set_facecolor(BG_COLOR)
g.fig.suptitle('Pairplot of Language Metrics', fontsize=18,
               fontweight='bold', color='white', y=1.02)

for ax in g.axes.flat:
    if ax:
        ax.set_facecolor(BG_COLOR)
        ax.tick_params(colors='#888888', labelsize=8)
        ax.xaxis.label.set_color('#aaaaaa')
        ax.yaxis.label.set_color('#aaaaaa')
        for spine in ax.spines.values():
            spine.set_color('#444444')

g.tight_layout()
g.savefig(OUTPUT_PATH, dpi=150, facecolor=BG_COLOR)
print(f"✅ 18_pairplot saved")
