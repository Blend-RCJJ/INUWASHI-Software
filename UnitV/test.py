# generated by maixhub, tested on maixpy3 v0.4.8
# copy files to TF card and plug into board and power on
import sensor, image, time
import gc
from machine import UART
from fpioa_manager import fm
from modules import ws2812

ws = ws2812(8,1)

fm.register(34,fm.fpioa.UART1_TX)
fm.register(35,fm.fpioa.UART1_RX)
uart = UART(UART.UART1, 115200, 8, None, 1, timeout=1000, read_buf_len=4096)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_hmirror(180)
sensor.set_vflip(180)
sensor.run(1)
sensor.set_auto_gain(10)
sensor.set_auto_whitebal(False, (180,150,200))
sensor.set_auto_exposure(False)
gc.collect()

green = (57, 64, -46, -39, 15, 24)
red = (55, 59, 64, 70, 61, 69)
yellow = (89, 97, -24, -6, 81, 88)
black = (0, 0, 0, -128, 0, -128)

led = 0
list = []

while(True):
    gc.collect()
    led += 1

    if led % 2 == 1:
        r,g,b = 100,100,100
        ws.set_led(0, (r,g,b))
        ws.display()

    if led % 2 == 0:
        r,g,b = 0,0,0
        ws.set_led(0, (r,g,b))
        ws.display()

    img = sensor.snapshot()
    img2 = img.copy((110,0,100,240),copy_to_fb = True)
    #print(R1)

    GREEN = img.find_blobs([green])
    RED = img.find_blobs([red])
    YELLOW = img.find_blobs([yellow])
    BLACK = img2.find_blobs([black])
    if BLACK:
        #time.sleep(1)
        img = sensor.snapshot()

        R0,G0,B0 = img.get_pixel(160,0)
        img.draw_string(160,0, "・", (0,0,0), scale=1)
        R1,G1,B1 = img.get_pixel(160,40)
        img.draw_string(160,40, "・", (0,0,0), scale=1)
        R2,G2,B2 = img.get_pixel(160,80)
        img.draw_string(160, 80, "・", (0,0,0), scale=1)
        R3,G3,B3 = img.get_pixel(160,120)
        img.draw_string(160, 120, "・", (0,0,0), scale=1)
        R4,G4,B4 = img.get_pixel(160,160)
        img.draw_string(160, 160, "・", (0,0,0), scale=1)
        R5,G5,B5 = img.get_pixel(160,200)
        img.draw_string(160, 200, "・", (0,0,0), scale=1)
        R6,G6,B6 = img.get_pixel(160,239)
        img.draw_string(160,239, "・", (0,0,0), scale=1)

        #print(R0,R1,R2,R3,R4,R5,R6)

        if (R0 == 0 or R1 == 0) or R3 == 0 and (R5 == 0 or R6 == 0):
            uart.write('S')
            print("S")
            r,g,b = 0,0,255
            ws.set_led(0, (r,g,b))
            ws.display()

            time.sleep(1)
            r,g,b = 0,0,0
            ws.set_led(0, (r,g,b))
            ws.display()

            uart.write('N')
            continue

        if R2 == 0 or R3 == 0 or R4 == 0:
            uart.write('H')
            print("H")
            r,g,b = 255,0,60
            ws.set_led(0, (r,g,b))
            ws.display()

            time.sleep(1)
            r,g,b = 0,0,0
            ws.set_led(0, (r,g,b))
            ws.display()

            uart.write('N')
            continue

        if R5 == 0 or R5 == 0:
            uart.write('U')
            print("U")
            r,g,b = 255,255,255
            ws.set_led(0, (r,g,b))
            ws.display()

            time.sleep(1)
            r,g,b = 0,0,0
            ws.set_led(0, (r,g,b))
            ws.display()

            uart.write('N')
            continue

    if GREEN:
        for b in reversed(GREEN):
            if (b[2]*b[3] >= 400):

                uart.write('G')
                print("G")
                r,g,b = 0,255,0
                ws.set_led(0, (r,g,b))
                ws.display()

                time.sleep(1)
                r,g,b = 0,0,0
                ws.set_led(0, (r,g,b))
                ws.display()

                uart.write('N')

    if RED:
        for b in reversed(RED):
            if (b[2]*b[3] >= 600):

                uart.write('R')
                print("R")
                r,g,b = 255,0,0
                ws.set_led(0, (r,g,b))
                ws.display()

                time.sleep(1)
                r,g,b = 0,0,0
                ws.set_led(0, (r,g,b))
                ws.display()
                uart.write('N')

    if YELLOW:
        for b in reversed(YELLOW):
            if (b[2]*b[3] >= 100):

                uart.write('Y')
                print("Y")
                r,g,b = 255,125,0
                ws.set_led(0, (r,g,b))
                ws.display()

                time.sleep(1)
                r,g,b = 0,0,0
                ws.set_led(0, (r,g,b))
                ws.display()
                uart.write('N')

    else:
        uart.write("N")
        print("n")
