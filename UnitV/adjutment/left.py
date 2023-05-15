# Original: https://iotdiary.blogspot.com/2019/07/maixpy-go-mobilenet-transfer-learning.html
import sensor
import image
import time
from machine import UART
from fpioa_manager import fm
import KPU as kpu
from modules import ws2812
import gc

ws = ws2812(8,1)

fm.register(34,fm.fpioa.UART1_TX)
fm.register(35,fm.fpioa.UART1_RX)
uart = UART(UART.UART1, 115200, 8, None, 1, timeout=1000, read_buf_len=4096)

gc.collect()
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
#sensor.set_brightness(0)
#sensor.set_saturation(0)
#sensor.set_contrast(0)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False, (50,40,90))
sensor.set_auto_exposure(False)
sensor.run(1)
sensor.set_hmirror(180)
#sensor.set_vflip(180)

r,g,b =100,100,100
ws.set_led(0, (r,g,b))
ws.display()

time.sleep(1)

r,g,b =0,0,0
ws.set_led(0, (r,g,b))
ws.display()

f = open('labels.txt', 'r')
labels = f.readlines()
f.close()
print(labels)

list = []
led = 0

green = (22, 59, -38, -17, -14, 14)
red = (8, 76, 51, 67, 16, 54)
yellow = (51, 76, -20, -3, 49, 64)
#shiro = (51, 70, -12, 10, -15, 9)

try:
    task = kpu.load("/sd/model.kmodel")
except:
    a = 1

while(True):
    led += 1

    if led % 2 == 1:
        r,g,b = 100,100,100
        ws.set_led(0, (r,g,b))
        ws.display()

    if led % 2 == 0:
        r,g,b = 0,0,0
        ws.set_led(0, (r,g,b))
        ws.display()

    gc.collect()
    img = sensor.snapshot()

    GREEN = img.find_blobs([green])
    RED = img.find_blobs([red])
    YELLOW = img.find_blobs([yellow])
    #SHIRO = img.find_blobs([shiro])

    if GREEN:
        for b in reversed(GREEN):
            if (b[2]*b[3] >= 600):
                #list.append("G")
                #A = len(list)

                #if A == 2:
                uart.write('G\n')
                print("G")
                r,g,b = 0,255,0
                ws.set_led(0, (r,g,b))
                ws.display()

                time.sleep(6)
                r,g,b = 0,0,0
                ws.set_led(0, (r,g,b))
                ws.display()

                uart.write('n\n')
                time.sleep(2.3)

                list = []

    #if RED:
        #for b in reversed(RED):
            #if (b[2]*b[3] >= 600):
                ##list.append("R")
                ##A = len(list)

                ##if A == 2:
                #uart.write('R\n')
                #print("R")
                #r,g,b = 255,0,0
                #ws.set_led(0, (r,g,b))
                #ws.display()

                #time.sleep(6)
                #r,g,b = 0,0,0
                #ws.set_led(0, (r,g,b))
                #ws.display()
                #uart.write('n\n')
                #time.sleep(3)

                #list = []

    if YELLOW:
        for b in reversed(YELLOW):
            if (b[2]*b[3] >= 600):
                #list.append("Y")
                #A = len(list)

                #if A == 2:
                uart.write('Y\n')
                print("Y")
                r,g,b = 255,125,0
                ws.set_led(0, (r,g,b))
                ws.display()

                time.sleep(6)
                r,g,b = 0,0,0
                ws.set_led(0, (r,g,b))
                ws.display()
                uart.write('n\n')
                time.sleep(3)

                list = []

    img = sensor.snapshot()
    #img2 = img.copy((0,100,240,120))
    #img3 = img2.resize(224, 224)
    #img3.pix_to_ai()
    #fmap = kpu.forward(task, img3)

    img2 = img.resize(224, 224)
    img2.pix_to_ai()
    fmap = kpu.forward(task, img2)
    plist = fmap[:]
    #pmax = max(plist)
    pmax11 = plist[0]
    pmax2 = plist[1]
    pmax3 = plist[2]
    #print(plist)
    pmax1 = round(pmax11,5)

    #if SHIRO:
        #for b in reversed(SHIRO):
            #if (b[2]*b[3] >= 20 and b[2]*b[3] <= 90):
    if pmax1 >= 0.90 and pmax1 <= 1.0:
        #rects = img.find_rects()#threshold = 1500
        #B = len(rects)
        max_index = plist.index(pmax11)
        mozi = labels[max_index].strip()
        print(labels[max_index].strip())

        list.append(mozi)
        A = len(list)

        #if B <= 2:
        if A == 2:
            uart.write("H\n")
            r,g,b = 255,0,60
            ws.set_led(0, (r,g,b))
            ws.display()

            time.sleep(6)
            r,g,b = 0,0,0
            ws.set_led(0, (r,g,b))
            ws.display()

            uart.write('n\n')
            time.sleep(3.5)

            list = []

    if pmax2 >= 0.80 and pmax2 <= 1.0:
        max_index = plist.index(pmax2)
        mozi = labels[max_index].strip()
        print(labels[max_index].strip())

        list.append(mozi)
        A = len(list)

        if A == 2:
            #if mozi == "S":
            uart.write("S\n")
            r,g,b = 0,0,255
            ws.set_led(0, (r,g,b))
            ws.display()

            time.sleep(6)
            r,g,b = 0,0,0
            ws.set_led(0, (r,g,b))
            ws.display()

            uart.write('n\n')
            time.sleep(3)

            list = []

    if pmax3 >= 0.999995 and pmax3 <= 1.0:
        max_index = plist.index(pmax3)
        mozi = labels[max_index].strip()
        print(labels[max_index].strip())

        list.append(mozi)
        A = len(list)

        if A == 2:
        #if mozi == "U":
            uart.write("U\n")
            r,g,b = 255,255,255
            ws.set_led(0, (r,g,b))
            ws.display()

            time.sleep(6)
            r,g,b = 0,0,0
            ws.set_led(0, (r,g,b))
            ws.display()

            uart.write('n\n')
            time.sleep(2.3)

            list = []


    else:
        uart.write("n\n")
        print("n")

        if led % 5 == 0:
            list = []
        elif list == "S" and A == 1:
            a = 1

