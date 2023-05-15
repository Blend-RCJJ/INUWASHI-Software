import sensor
import image
import time
from machine import UART
from fpioa_manager import fm
import KPU as kpu

fm.register(34,fm.fpioa.UART1_TX)
fm.register(35,fm.fpioa.UART1_RX)
uart = UART(UART.UART1, 115200, 8, None, 1, timeout=1000, read_buf_len=4096)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.run(1)
sensor.set_vflip(180)

f = open('labels.txt', 'r')
labels = f.readlines()
f.close()
print(labels)

list = []

green  =  (17, 38, -19, -6, -13, 4)
red  =  (22, 31, 21, 46, 11, 28)
yellow  =  (32, 54, -20, -3, 32, 42)

try:
    task = kpu.load("/sd/model.kmodel")
except:
    a = 1

while(True):
    img = sensor.snapshot()

    GREEN = img.find_blobs([green])
    RED = img.find_blobs([red])
    YELLOW = img.find_blobs([yellow])

    if GREEN:
        #for b in reversed(GREEN):
            #if (b[2]*b[3] > 15000):
        #print("GREEEEEN")
        list.append("G")
        A = len(list)

        if A == 2:
            uart.write('G\n')
            print("G")
            time.sleep(6)
            uart.write('\n')
            time.sleep(2)

            list = []

        continue

    if RED:
        #for b in reversed(RED):
            #if (b[2]*b[3] > 15000):
        list.append("R")
        A = len(list)

        if A == 3:
            uart.write('R\n')
            print("R")
            time.sleep(6)
            uart.write('\n')
            time.sleep(2)

            list = []

        continue

    if YELLOW:
        #for b in reversed(YELLOW):
            #if (b[2]*b[3] > 15000):
        list.append("Y")
        A = len(list)

        if A == 3:
            uart.write('Y\n')
            print("Y")
            time.sleep(6)
            uart.write('\n')
            time.sleep(2)

            list = []

        continue

    img2 = img.resize(224, 224)

    img2.pix_to_ai()

    fmap = kpu.forward(task, img2)

    plist = fmap[:]

    pmax = max(plist)

    if pmax >= 0.8 and pmax <= 1:
        max_index = plist.index(pmax)
        mozi = labels[max_index].strip()
        print(labels[max_index].strip())

        list.append(mozi)
        A = len(list)

        if A == 2:

            if mozi == "H":
                uart.write("H\n")
                time.sleep(6)
                uart.write('\n')
                time.sleep(2)

                list = []

            if mozi == "S":
                uart.write("S\n")
                time.sleep(6)
                uart.write('\n')
                time.sleep(2)

                list = []

            if mozi == "U":
                uart.write("U\n")
                time.sleep(6)
                uart.write('\n')
                time.sleep(2)

                list = []

    else:
        print("N")

        list = []

