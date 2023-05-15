# Hello World Example
#
# Welcome to the MaixPy IDE!
# 1. Conenct board to computer
# 2. Select board at the top of MaixPy IDE: `tools->Select Board`
# 3. Click the connect buttion below to connect board
# 4. Click on the green run arrow button below to run the script!

import sensor
import image
import lcd
import time

"""
from modules import ws2812

led_io, led_num = 8, 1

ws = ws2812(led_io, led_num)
r,g,b =100,100,100           #LEDの光らせたい色の値
ws.set_led(0, (r,g,b))
ws.display()

time.sleep_ms(10000)

ws = ws2812(led_io, led_num)
r,g,b =0,0,0
ws.set_led(0, (r,g,b))
ws.display()
"""

lcd.init(freq=15000000)
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.run(1)
sensor.set_vflip(180)
#sensor.skip_frames(360)
sensor.set_windowing((1080,1080))

green_threshold  =  (56, 97, -29, -17, 34, 51) #緑色認識範囲
red_threshold  =  (59, 72, 38, 61, -13, 33)    #赤色認識範囲
blue_threshold  =  (36, 69, 4, 32, -67, -41)   #青色認識範囲
#red_threshold  =  (0, 30, 24, 72, 4, 27)
#blue_threshold  =  (0, 100, -55, 31, -60, -13)

while True:
    img=sensor.snapshot()

    blobs1 = img.find_blobs([green_threshold])
    blobs2 = img.find_blobs([red_threshold])
    blobs3 = img.find_blobs([blue_threshold])

    if blobs1:
        for b in blobs1:
            tmp=img.draw_rectangle(b[0:4],color=(153,204,51))        #四角を描画
            tmp=img.draw_cross(b[5], b[6],color=(153,204,51))        #×マークを描画
            c=img.get_pixel(b[5], b[6])                              #ピクセル取得
            img.draw_string(60, 50, "GREEN",color=(0,0,0), scale=2)  #文字描画

    if blobs2:
        for b in blobs2:
            tmp=img.draw_rectangle(b[0:4],color=(255,0,0))
            tmp=img.draw_cross(b[5], b[6],color=(255,0,0))
            c=img.get_pixel(b[5], b[6])
            img.draw_string(60, 100, "RED",color=(0,0,0), scale=2)

    if blobs3:
        for b in blobs3:
            tmp=img.draw_rectangle(b[0:4],color=(0,255,255))
            tmp=img.draw_cross(b[5], b[6],color=(0,255,255))
            c=img.get_pixel(b[5], b[6])
            img.draw_string(60, 150, "BLUE",color=(0,0,0), scale=2)


    lcd.display(img)

