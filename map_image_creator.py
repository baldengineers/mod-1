import pyautogui
import time
from PIL import Image, ImageGrab
import sys

#INSTRUCTIONS
#1. open up commandos (in fullscreen 1280x720 ONLY), and go to the map of your choosing 
#   level codes: https://www.gamespot.com/commandos-behind-enemy-lines/cheats/
#2. move the view to the topmost leftmost of the map.
#3. alt tab to this script, run it, and quickly alt tab back
#4. place your in-game cursor on the belt at the top of the screen, but not so it touches
#   the very top of the screen, causing panning
#5. wait for the program to run its course. the image will be output in the dir of this script

time.sleep(5) #initial sleep for alt tab to game
#screengrab size-- 1247,655
vert_list = []
while True:
    image_height = 654
    image_width = 1244
    total_im = ImageGrab.grab(bbox=(2,65,1246,719))
    last_im = total_im.copy()
    while True:
        pyautogui.keyDown("down")
        time.sleep(1)
        pyautogui.keyUp("down")
        time.sleep(1)
        cur_im = ImageGrab.grab(bbox=(2,65,1246,719))
        simcount = 0
        for y in range(654):
            for x in range(1244):
                if cur_im.getpixel((x,y)) == last_im.getpixel((x,y)):
                    simcount += 1
        if simcount/(654*1244) > .35:
            keep_going = False
            break
        else:
            last_im = cur_im.copy()
        latest_image_topline = []

        for i in range(image_width):
            latest_image_topline.append(cur_im.getpixel((i,0)))
        for i in range(image_height):
            count = 0
            for j in range(image_width):
                if total_im.getpixel((j,i)) == latest_image_topline[j]:
                    count += 1
            if count >= .3*1244: #DEPENDING ON THE MAP, THIS VALUE MUST BE CHANGED. GENERALLY HIGHER IF THERE ARE FEWER MOVING PIECES (WATER, DIFFERENT DISTANCE PIECES, ETC)
                seam = i
        print(seam)
        total_im = total_im.crop( (0,0,image_width,seam))
        total_im_new = Image.new("RGB",(image_width, 654 + seam))
        total_im_new.paste(total_im, (0,0))
        total_im_new.paste(cur_im, (0,seam))
        total_im = total_im_new.copy()
        image_height = total_im.height
    vert_list.append(total_im.copy())
    temp_im = ImageGrab.grab(bbox=(2,65,1246,719))
    pyautogui.keyDown("right")
    time.sleep(1.6)
    pyautogui.keyUp("right")
    time.sleep(1)
    new_im = ImageGrab.grab(bbox=(2,65,1246,719))
    simcount = 0
    for y in range(654):
        for x in range(1244):
            if temp_im.getpixel((x,y)) == new_im.getpixel((x,y)):
                simcount += 1
    if simcount/(654*1244) > .3: #DEPENDING ON THE MAP'S LAST FRAME, THIS VALUE MUST BE CHANGED. GENERALLY HIGHER IF THERE ARE FEWER MOVING PIECES (WATER, DIFFERENT DISTANCE PIECES, ETC)
        total_im = vert_list[0]
        for i in range(1,len(vert_list)):
            vert_last =[]
            for y in range(total_im.height):
                vert_last.append(vert_list[i].getpixel((0,y)))
            for x in range(total_im.width):
                count = 0
                for y in range(total_im.height):
                    if total_im.getpixel((x,y)) == vert_last[y]:
                        count += 1
                if count >= .4*image_height:
                    seam = x
            total_im = total_im.crop( (0,0,seam,total_im.height))
            total_im_new = Image.new("RGB", (total_im.width + vert_list[i].width, total_im.height))
            total_im_new.paste(total_im, (0,0))
            total_im_new.paste(vert_list[i], (seam,0))
            total_im = total_im_new.copy()
        print("done stitching")
        break
    pyautogui.keyDown("up")
    time.sleep(5.5)
    pyautogui.keyUp("up")


total_im.save("commandos_map_full_stitched.png","PNG")
