import numpy as np

#--------------------------------------------------------------------------------------------------------

import matplotlib as mpl        # Not to occur "QXcbConnection: Could not connect to display"
mpl.use('Agg')                  # Not to occur "QXcbConnection: Could not connect to display"
import matplotlib.pyplot as plt # Not to occur "QXcbConnection: Could not connect to display"
import matplotlib.ticker as tick

def vec2graph(writeName, vecX, vecY):
    plt.clf()
    fig = plt.figure(figsize=(8, 2.5)) # 3*5, 1*5 # アスペクト比の設定
    ax1 = fig.add_subplot(111)
    ax1.plot(vecX, vecY, color='k', linewidth=0.5)
    
    title  = ""
    ax1.set_title(title)
    
    ax1.grid(which='minor', linewidth=0.5, linestyle=':',  color='gainsboro')
    ax1.grid(which='major', linewidth=0.5, linestyle='-',  color='silver'    )
    
    ax1.tick_params(pad=5, which='major', direction='in', bottom=True, top=True, left=True, right=True, length=4) # 軸の余白 # which: major tick と minor tick に対して変更を適用 # tick を内側方向に # tick を bottom, top, left, right に付加 # tick width # tick length
    ax1.tick_params(pad=5, which='minor', direction='in', bottom=True, top=True, left=True, right=True, length=2) # 軸の余白 # which: major tick と minor tick に対して変更を適用 # tick を内側方向に # tick を bottom, top, left, right に付加 # tick width # tick length
    
    ax1.set_xlabel("Physical place [mm]")
    ax1.set_xlim(0-1, 60+1)
    ax1.xaxis.set_major_locator(tick.MultipleLocator(5))
    ax1.xaxis.set_minor_locator(tick.MultipleLocator(1))
    
    ax1.set_ylabel("Amplitude [mm]")
    ax1.set_ylim(-11, 11)
    ax1.yaxis.set_major_locator(tick.MultipleLocator(5))
    ax1.yaxis.set_minor_locator(tick.MultipleLocator(1))
    
    plt.savefig(writeName, bbox_inches="tight") # , dpi=100

#--------------------------------------------------------------------------------------------------------

import glob
from PIL import Image, ImageDraw
def imgDir2GIF(savePath, imgDir, frameRate):
    vecImgPath = sorted(glob.glob(imgDir+"/*.png"))
    vecImg = [Image.open(path) for path in vecImgPath]
    vecImg[0].save(savePath, save_all=True, append_images=vecImg[1:], optimize=False, duration=int(1000/frameRate), loop=0) # duration [milli sec/frame], frameRate [frame/sec]

#--------------------------------------------------------------------------------------------------------

