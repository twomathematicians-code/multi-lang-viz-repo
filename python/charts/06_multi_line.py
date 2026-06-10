"""Multi-line chart from timeseries.csv showing all languages' trends."""

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.font_manager as fm
import pandas as pd

fm.fontManager.addfont('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf')
plt.rcParams['font.sans-serif'] = ['DejaVu Sans']

DATA_PATH = '/home/z/my-project/download/multi-lang-viz-repo/data/timeseries.csv'
OUTPUT_PATH = '/home/z/my-project/download/multi-lang-viz-repo/output/python/06_multi_line.png'

df = pd.read_csv(DATA_PATH)

plt.style.use('dark_background')
BG_COLOR = '#16213e'
fig, ax = plt.subplots(figsize=(13, 7), facecolor=BG_COLOR)
ax.set_facecolor(BG_COLOR)

lang_colors = {
    'Python': '#00d2ff',
    'JavaScript': '#f7df1e',
    'C_plus_plus': '#00b09b',
    'Java': '#f953c6',
    'Go': '#4caf50'
}

for col, name in [('Python', 'Python'), ('JavaScript', 'JavaScript'),
                   ('C_plus_plus', 'C++'), ('Java', 'Java'), ('Go', 'Go')]:
    ax.plot(df['year'], df[col], color=lang_colors[col], linewidth=2.2,
            marker='o', markersize=5, markeredgecolor='white',
            markeredgewidth=0.8, label=name, zorder=3)

ax.set_title('Language Popularity Trends (2016-2026)', fontsize=16,
             fontweight='bold', color='white', pad=15)
ax.set_xlabel('Year', fontsize=13, color='#aaaaaa')
ax.set_ylabel('Popularity Score', fontsize=13, color='#aaaaaa')
ax.legend(loc='center right', fontsize=11, facecolor='#1a1a3e', edgecolor='#444')
ax.grid(alpha=0.15, linestyle='--', zorder=0)
ax.tick_params(colors='#cccccc')
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)

fig.tight_layout()
fig.savefig(OUTPUT_PATH, dpi=150, facecolor=BG_COLOR)
print(f"✅ 06_multi_line saved")
