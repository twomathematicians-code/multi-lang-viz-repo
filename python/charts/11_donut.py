"""Donut chart of community scores across languages."""

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.font_manager as fm
import pandas as pd

fm.fontManager.addfont('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf')
plt.rcParams['font.sans-serif'] = ['DejaVu Sans']

DATA_PATH = '/home/z/my-project/download/multi-lang-viz-repo/data/sample_data.csv'
OUTPUT_PATH = '/home/z/my-project/download/multi-lang-viz-repo/output/python/11_donut.png'

df = pd.read_csv(DATA_PATH)

plt.style.use('dark_background')
BG_COLOR = '#16213e'
fig, ax = plt.subplots(figsize=(10, 10), facecolor=BG_COLOR)

colors = ['#00d2ff', '#f7df1e', '#00b09b', '#f953c6', '#4caf50',
          '#e44d26', '#955196', '#c62828', '#ff6f00']
explode = [0.03] * len(df)

wedges, texts, autotexts = ax.pie(
    df['community'], labels=df['language'], autopct='%1.1f%%',
    colors=colors, explode=explode, startangle=90,
    textprops={'fontsize': 11, 'color': 'white'},
    wedgeprops={'edgecolor': 'white', 'linewidth': 0.8, 'width': 0.45},
    pctdistance=0.80
)

for at in autotexts:
    at.set_fontsize(9)
    at.set_color('#222222')
    at.set_fontweight('bold')

# Center label
ax.text(0, 0, 'Community\nScores', ha='center', va='center',
        fontsize=16, fontweight='bold', color='white')

ax.set_title('Community Score Distribution', fontsize=16,
             fontweight='bold', color='white', pad=20)

fig.tight_layout()
fig.savefig(OUTPUT_PATH, dpi=150, facecolor=BG_COLOR)
print(f"✅ 11_donut saved")
