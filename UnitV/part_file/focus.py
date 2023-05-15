#refer  to http://blog.sipeed.com/p/675.html
import sensor
import json
import time

from machine import UART
from fpioa_manager import fm
from modules import ws2812

class_ws2812 = ws2812(8, 1)

# シリアル通信の設定
fm.register(34, fm.fpioa.UART1_TX, force=True)
fm.register(35, fm.fpioa.UART1_RX, force=True)
uart = UART(UART.UART1, 115200,8,0,0, timeout=1000, read_buf_len=4096)

# カメラモジュールの準備
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_vflip(True) # 上下反転
# sensor.set_hmirror(True) # 左右反転
sensor.run(1)

black_threshold = (0, 14, -2, 4, -1, 7)

# 画面解像度 320x240

target_letter_position_x = 160 #
target_letter_position_y = 120 # 中心:120、顔の位置を高くしたいときは小さくする

focus_counter = 0
list = []
#num = 0

while(True):

   img = sensor.snapshot()
   blobs4 = img.find_blobs([black_threshold])
   lines = img.find_lines(threshold = 1500, max_theta_difference = 10)
   A = len(lines)

   if blobs4:
       for i in blobs4:
           #for num in range(1000):
           data = json.loads(json.dumps(i))
           letter_center_x = round(data['x'] + data['w'] / 2)
           letter_center_y = round(data['y'] + data['h'] / 2)
           print(str(letter_center_x) + ',' + str(letter_center_y))
           if abs(letter_center_x - target_letter_position_x) >= 40:
               focus_counter = 0
               if letter_center_x > target_letter_position_x:
                   # uart.write('L'+'\n')
                   print('L')
                   #b = class_ws2812.set_led(0,(10,0,0)) # 赤 追従中
                   #b = class_ws2812.display()
               elif letter_center_x < target_letter_position_x:
                   # uart.write('R'+'\n')
                   print('R')
                   #b = class_ws2812.set_led(0,(10,0,0)) # 赤 追従中
                   #b = class_ws2812.display()
           elif abs(letter_center_y - target_letter_position_y) >= 40:
               if letter_center_y > target_letter_position_y:
                   # uart.write('D'+'\n')
                   print('down')
                   #b = class_ws2812.set_led(0,(10,10,0)) # 黄 追従中
                   #b = class_ws2812.display()
               elif letter_center_y < target_letter_position_y:
                   # uart.write('U'+'\n')
                   print('up')
                   #b = class_ws2812.set_led(0,(10,10,0)) # 黄 追従中
                   #b = class_ws2812.display()
           else:
               # uart.write('S'+'\n')
               print('shot')
               #b = class_ws2812.set_led(0,(0,10,0)) #緑  フォーカス時
               #b = class_ws2812.display()

               focus_counter += 1
               if focus_counter > 3:
                   focus_counter = 0
                   #b = class_ws2812.set_led(0,(255,255,255)) #白  撮影
                   #b = class_ws2812.display()

                   if(A >= 6):
                       uart.write('H\n')
                       img.draw_string(40,20, "H",color = (0,255,0),scale = 5)
                       print("H")
                       list.append('H')
                   if(A == 3 or A == 4):
                       uart.write('U\n')
                       img.draw_string(40,20,"U",color = (0,255,0),scale = 5)
                       print("U")
                       list.append('U')
                   if(A <= 1):
                       uart.write('S\n')
                       img.draw_string(40,20,"S",color = (0,255,0),scale = 5)
                       print('S')
                       list.append('S')

                   continue

               if len(list) == 10:
                   print(list)
                   time.sleep(5)
                   list.clear()

               #mode = statistics.mode(list)
               #img.draw_string(100,80,str(mode),color = (125,0,0),scale = 5)


           a = img.draw_rectangle(i.rect())
           a = img.draw_circle(target_letter_position_x, target_letter_position_y, 5)

           


