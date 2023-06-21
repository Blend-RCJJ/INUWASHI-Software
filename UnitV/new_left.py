# generated by maixhub, tested on maixpy3 v0.4.8
# copy files to TF card and plug into board and power on
import sensor, image, time
import KPU as kpu
import gc, sys
from machine import UART
from fpioa_manager import fm
from modules import ws2812

ws = ws2812(8,1)

fm.register(34,fm.fpioa.UART1_TX)
fm.register(35,fm.fpioa.UART1_RX)
uart = UART(UART.UART1, 115200, 8, None, 1, timeout=1000, read_buf_len=4096)

input_size = (224, 224)
labels = ['H', 'S', 'U']
anchors = [2.72, 2.84, 2.12, 2.56, 2.06, 2.19, 2.91, 2.02, 2.53, 2.25]

def lcd_show_except(e):
    import uio
    err_str = uio.StringIO()
    sys.print_exception(e, err_str)
    err_str = err_str.getvalue()
    img = image.Image(size=input_size)
    img.draw_string(0, 10, err_str, scale=1, color=(0xff,0x00,0x00))

def main(anchors, labels = None, model_addr="/sd/m.kmodel", sensor_window=input_size, lcd_rotation=0, sensor_hmirror=False, sensor_vflip=False):
    sensor.reset()
    sensor.set_pixformat(sensor.RGB565)
    sensor.set_framesize(sensor.QVGA)
    sensor.set_windowing(sensor_window)
    sensor.set_hmirror(180)
    #sensor.set_vflip(180)
    sensor.run(1)
    sensor.set_auto_gain(10)
    sensor.set_auto_whitebal(False, (160,110,200))
    sensor.set_auto_exposure(False)
    gc.collect()

    green = (57, 64, -46, -39, 15, 24)
    red = (55, 59, 64, 70, 61, 69)
    yellow = (89, 97, -24, -6, 81, 88)

    led = 0

    if not labels:
        with open('labels.txt','r') as f:
            exec(f.read())
    if not labels:
        print("no labels.txt")
        img = image.Image(size=(320, 240))
        img.draw_string(90, 110, "no labels.txt", color=(255, 0, 0), scale=2)
        return 1
    try:
        img = image.Image("startup.jpg")
    except Exception:
        img = image.Image(size=(320, 240))
        img.draw_string(90, 110, "loading model...", color=(255, 255, 255), scale=2)

    try:
        task = None
        task = kpu.load(model_addr)
        kpu.init_yolo2(task, 0.5, 0.3, 5, anchors) # threshold:[0,1], nms_value: [0, 1]
        while(True):
            led += 1
            if led == 1:
                r,g,b = 100,100,100
                ws.set_led(0, (r,g,b))
                ws.display()
                time.sleep(1)

                r,g,b = 0,0,0
                ws.set_led(0, (r,g,b))
                ws.display()

            img = sensor.snapshot()
            objects = kpu.run_yolo2(task, img)
            GREEN = img.find_blobs([green])
            RED = img.find_blobs([red])
            YELLOW = img.find_blobs([yellow])
            if objects:
                for obj in objects:
                    if obj.classid() == 2:
                        if obj.value() >= 0.85:

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
                            #time.sleep(2.3)

                    if obj.classid() == 0:
                        #print(obj.value())
                        if obj.value() >= 0.70:

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


                    if obj.classid() == 1:
                        #print(obj.value())
                        if obj.value() >= 0.70:

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

            if GREEN:
                for b in reversed(GREEN):
                    if (b[2]*b[3] >= 500):

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
                    if (b[2]*b[3] >= 400):

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

    except Exception as e:
        raise e
    finally:
        if not task is None:
            kpu.deinit(task)


if __name__ == "__main__":
    try:
        main(anchors = anchors, labels=labels, model_addr="/sd/model-35541.kmodel")

    except Exception as e:
        sys.print_exception(e)
        lcd_show_except(e)
    finally:
        gc.collect()