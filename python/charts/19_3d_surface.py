"""3D surface plot of a mathematical function (sin + cos combination)."""

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.font_manager as fm
import numpy as np

fm.fontManager.addfont('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf')
plt.rcParams['font.sans-serif'] = ['DejaVu Sans']

OUTPUT_PATH = '/home/z/my-project/download/multi-lang-viz-repo/output/python/19_3d_surface.png'

plt.style.use('dark_background')
BG_COLOR = '#16213e'
fig = plt.figure(figsize=(13, 9), facecolor=BG_COLOR)
ax = fig.add_subplot(111, projection='3d', facecolor=BG_COLOR)

# Generate mathematical function data
x = np.linspace(-5, 5, 100)
y = np.linspace(-5, 5, 100)
X, Y = np.meshgrid(x, y)
Z = np.sin(np.sqrt(X**2 + Y**2)) * np.cos(X * 0.5) + np.sin(Y * 0.5)

# Surface plot
surf = ax.plot_surface(X, Y, Z, cmap='plasma', alpha=0.85,
                       edgecolor='none', antialiased=True, zorder=3)

# Wireframe overlay
ax.plot_wireframe(X, Y, Z, color='white', linewidth=0.15, alpha=0.2, zorder=2)

ax.set_title('3D Surface: sin(sqrt(x²+y²)) * cos(x/2) + sin(y/2)',
             fontsize=14, fontweight='bold', color='white', pad=20)
ax.set_xlabel('X', fontsize=12, color='#aaaaaa', labelpad=10)
ax.set_ylabel('Y', fontsize=12, color='#aaaaaa', labelpad=10)
ax.set_zlabel('Z', fontsize=12, color='#aaaaaa', labelpad=10)

# Style 3D axes
ax.tick_params(colors='#888888')
ax.xaxis.pane.fill = False
ax.yaxis.pane.fill = False
ax.zaxis.pane.fill = False
ax.xaxis.pane.set_edgecolor('#333333')
ax.yaxis.pane.set_edgecolor('#333333')
ax.zaxis.pane.set_edgecolor('#333333')
ax.view_init(elev=30, azim=45)

fig.tight_layout()
fig.savefig(OUTPUT_PATH, dpi=150, facecolor=BG_COLOR)
print(f"✅ 19_3d_surface saved")
