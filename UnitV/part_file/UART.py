import sensor
import image
import lcd
import time
import utime
from machine import UART
from Maix import GPIO
from fpioa_manager import *

fm.register(34,fm.fpioa.UART1_TX)
fm.register(35,fm.fpioa.UART1_RX)
uart_out = UART(UART.UART1, 115200, 8, None, 1, timeout=1000, read_buf_len=4096)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.run(1)
sensor.set_vflip(180)

while False:
    uart_out.write('TEST\n')
    utime.sleep_ms(100)

target_lab_threshold = (36, 69, 4, 32, -67, -41)     #青色
while True:
    img=sensor.snapshot()

    blobs = img.find_blobs([target_lab_threshold], x_stride = 2, y_stride = 2, pixels_threshold = 100, merge = True, margin = 20)
    if blobs:
        uart_out.write('Detected\n')

    else:
         uart_out.write('NOT Detected\n')
