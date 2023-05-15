import sensor
import image
import lcd
import time
import math


lcd.init(freq=15000000)
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.run(1)
sensor.set_vflip(180)

black_threshold = (0, 9, -3, 4, -2, 7)
#white_threshold = (62, 79, -3, 6, -3, 8)

while True:
    img=sensor.snapshot()
    #lines = img.find_lines()
    #img2 = img.copy((70,50,img.width(), img.height()-70))

    blobs4 = img.find_blobs([black_threshold])#,thickness=5)
    #blobbs = img.find_blobs([white_threshold])

    lines = img.find_lines(threshold = 1500, max_theta_difference = 10)#threshold=5000, merge_distance=5, max_theta_difference=2
    #circles = img.find_circles(threshold = 2000)
    #rects = img.find_rects()

    #A = len(lines)
    #B = len(circles)

    #print(A)
    #print(B)

    #lines2 = set(lines)

    if blobs4:
        for b in blobs4:
            print(len(lines))
            for item in lines:
            #print(len(circles))
            #for item in circles:
            #print(len(rects))
            #for item in rects:
                img2 = img.draw_line(item[0], item[1], item[2], item[3], color=(0,255,0), thickness=5)

    #lcd.display(img2)
    #if blobs4:
        #for blob in reversed(blobs4):
            #img2 = img.copy(blob[0:4])
            ##sensor.snapshot()
            #if blobbs:
                #for blobb in reversed(blobbs):
                    #tmp = img2.draw_rectangle(blobb[0:4],color = (0,128,0))
                    #sensor.snapshot()
                    #img3 = sensor.snapshot()
            #bb = blob[0] * blob[4]
            #print(bb)
            #if(blob[6]  < 70 or blob[6] > 50 and blob[5] < 90 or blob[5] > 60):
                ##if(blob[5] < 100 or blob[5] > 50):
            #tmp=img.draw_rectangle(blob[0:4],color=(128,0,0))
                #tmp=img.draw_cross(blob[5], blob[6],color=(128,0,0))

            #認識したノーツを逆順に処理する
            #num = blob[2] * blob[3]
                #print(blob[5],blob[6])
                #img2 = img.draw_string(40, 40, "1",color=(0,255,0), scale=1)
                #img2 = img.draw_string(110, 80, "2",color=(0,255,0), scale=1)

    #if blobs4:
        #A = len(lines)
        #B = len(circles)

        #print(A)
        #print(B)
        ##for item in lines:
            ##print(item[0])
        #if(A >= 3):
            ##if(B <= 2):
                ##img.draw_string(40, 20, "H",color=(0,255,0), scale=5)
                ##print("H")
            #if(B >= 4 and B <= 6):
                #img.draw_string(40, 20, "U",color=(0,255,0), scale=5)
                #print("U")
            #else:
                #img.draw_string(40, 20, "H",color=(0,255,0), scale=5)
                #print("H")
        #if(A == 1 or A == 2):
            #if(B >= 3 and B <= 6):
                #img.draw_string(40, 20, "U",color=(0,255,0), scale=5)
                #print("U")
            #if(B >= 7):
                #img.draw_string(40, 20, "S",color=(0,255,0), scale=5)
                #print("S")

    if blobs4:
        A = len(lines)
        print(A)

        if(A >= 6):
            img.draw_string(40, 20, "H",color=(0,255,0), scale=5)
            print("H")
        if(A == 3 or A == 4):
            img.draw_string(40,20,"U",color = (0,255,0),scale = 5)
            print("U")
        if(A <= 1):
            img.draw_string(40,20,"S",color = (0,255,0),scale = 5)

    lcd.display(img2)
