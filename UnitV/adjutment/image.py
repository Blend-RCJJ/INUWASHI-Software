import sensor
import image
import lcd
import json
import time
import utime
from machine import UART
from Maix import GPIO
from fpioa_manager import *
from modules import ws2812

#uart setup
fm.register(34,fm.fpioa.UART1_TX)
fm.register(35,fm.fpioa.UART1_RX)
uart_out = UART(UART.UART1, 115200, 8, None, 1, timeout=1000, read_buf_len=4096)

ws = ws2812(8,1)

#LED
for LED in range(5):
    r,g,b = 100,100,100
    ws.set_led(0, (r,g,b))
    ws.display()
    time.sleep(0.1)

    r,g,b = 0,0,0
    ws.set_led(0, (r,g,b))
    ws.display()
    time.sleep(0.1)

#camera setup
lcd.init(freq=15000000)
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.run(1)
sensor.set_vflip(180)

#color serup
green_threshold  =  (13, 49, -41, -10, 3, 41)
red_threshold  =  (0, 41, 48, 60, 39, 53)
yellow_threshold  =  (47, 71, -24, -7, 33, 59)

black_threshold = (0, 2, -3, 2, -1, 2)

target_letter_position_x = 160 #
target_letter_position_y = 120 # 中心:120、顔の位置を高くしたいときは小さくする

focus_counter = 0

list = []

ledStatus = 0

while True:
    #ledStatus += 1
    #if ledStatus % 2:
        #ws.set_led(0, (100,100,100))
        #ws.display()
    #else :
        #ws.set_led(0, (0,0,0))
        #ws.display()

    img=sensor.snapshot()

    blobs1 = img.find_blobs([green_threshold])
    blobs2 = img.find_blobs([red_threshold])
    blobs3 = img.find_blobs([yellow_threshold])

    blobs4 = img.find_blobs([black_threshold])

    lines = img.find_lines(threshold = 1500, max_theta_difference = 10)
    A = len(lines)

    #color find
    if blobs1:
        for b in blobs1:
            if (b[2]*b[3]>15000):
                uart_out.write('G\n')
                tmp=img.draw_rectangle(b[0:4],color=(153,204,51))
                img=img.draw_string(40, 20, "GREEN",color=(0,0,0), scale=2)

        continue

    if blobs2:
        for b in blobs2:
            if (b[2]*b[3]>15000):
                uart_out.write('R\n')
                tmp=img.draw_rectangle(b[0:4],color=(255,0,0))
                img = img.draw_string(40, 20, "RED",color=(0,0,0), scale=2)

        continue

    if blobs3:
        for b in blobs3:
            if (b[2]*b[3]>15000):
                uart_out.write('B\n')
                tmp=img.draw_rectangle(b[0:4],color=(0,255,255))
                img = img.draw_string(40, 20, "YELLOW",color=(0,0,0), scale=2)

        continue

    #letter setup
    if blobs4:
        for i in reversed(blobs4):
            if (i[2]*i[3]>15000):
                data = json.loads(json.dumps(i))
                letter_center_x = round(data['x'] + data['w'] / 2)
                letter_center_y = round(data['y'] + data['h'] / 2)
                print(str(letter_center_x) + ',' + str(letter_center_y))
                if abs(letter_center_x - target_letter_position_x) >= 80:
                    focus_counter = 0
                    if letter_center_x > target_letter_position_x:
                        uart_out.write('L\n')
                        print('L')

                    elif letter_center_x < target_letter_position_x:
                        uart_out.write('Y\n')
                        print('R')

                elif abs(letter_center_y - target_letter_position_y) >= 50:
                    if letter_center_y > target_letter_position_y:
                        uart_out.write('Z\n')
                        print('down')

                    elif letter_center_y < target_letter_position_y:
                        uart_out.write('Z\n')
                        print('up')

                else:
                    uart_out.write('T\n')
                    print('shot')

                    focus_counter += 1
                    if focus_counter > 2:
                        focus_counter = 0

                        if(A >= 4):
                            uart_out.write('H\n')
                            img.draw_string(40,20, "H",color = (0,255,0),scale = 5)
                            print("H")
                            list.append('H')
                        if(A == 2):
                            uart_out.write('U\n')
                            img.draw_string(40,20,"U",color = (0,255,0),scale = 5)
                            print("U")
                            list.append('U')
                        if(A <= 1):
                            uart_out.write('S\n')
                            img.draw_string(40,20,"S",color = (0,255,0),scale = 5)
                            print('S')
                            list.append('S')

                        #continue

                    if len(list) == 7:
                        uart_out.write(str(list)+'\n')
                        print(list)
                        #time.sleep(5)
                        list.clear()

                a = img.draw_rectangle(i.rect())
                a = img.draw_circle(target_letter_position_x, target_letter_position_y, 5)


