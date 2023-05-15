import sensor
import image
import lcd
import time

lcd.init(freq=15000000)
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.run(1)
sensor.set_vflip(180)               
sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(time = 1000)
clock = time.clock()

img2 = sensor.snapshot()   

while True:  
    img1 = sensor.snapshot()        
    dis = img1.find_displacement(img2)   #img1とimg2を比較
    print("displacement:")
    print(dis.x_translation())           #xの変化量
    img2 = img1.copy()
    #img = sensor.snapshot()
    #lines = img.find_lines()            #線を探す
    #img.draw_line(x0,y0,x1,y1,color,thickness)                 #線を描画
    #img.draw_rectangle(0,0,50,50)                              #デフォルトは黒で描画，塗りつぶしなし
    #img.draw_rectangle(150,100, 50,10,(0,0,0), fill=True)      #黒で描画して塗りつぶす
    #img.draw_rectangle(20,20,100,80,(0,0,200), thickness=3)    #青で描画，線の太さは3ピクセル
    #lcd.display(img)
