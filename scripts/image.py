#!/usr/bin/env python

import Image
import ImageEnhance
import ImageFilter
import ImageFont, ImageDraw
import rgb_to_lab

arr={ 0 : 0, 1 : 0}


def novel(x) : 
	print "novel called with " + str(x)
	global cnt
	cnt=cnt+1
	return 128


def colorswap(pixel, x, y, w, h, pixels):
    """Shifts the channels of the image."""
    
    #if (abs(pixel[0] - 132) < 120 and abs(pixel[1] - 1) < 50 and abs(pixel[2] -0) < 50) :
    if (rgb_to_lab.colour_difference(pixel[0], pixel[1], pixel[2], 132, 0 , 0) < 70) :
        #print rgb_to_lab.colour_difference(pixel[0], pixel[1], pixel[2], 132, 0 , 0) 
        return (255,255,255) #pixel
    else :
        return (0,0,0)

def removenoise(pixel, x, y, w, h, pixels) :
    """Remove noise"""
    if (pixel == (0,0,0)) : return (0, 0, 0)
    allblack=0
    if (x > 3 and pixels[x-4,y] == (0, 0, 0)) :
        allblack = allblack + 1;
    if (y > 3 and pixels[x,y-4] == (0, 0, 0)) :
        allblack = allblack + 1;
    if (x < w-3 and pixels[x+3,y] == (0, 0, 0)) :
        allblack = allblack + 1;
    if (y < h-3 and pixels[x,y+3] == (0, 0, 0)) :
        allblack = allblack + 1;

    haswhite=0
    if (x > 0 and pixels[x-1,y] == (255,255,255)) :
        haswhite = haswhite + 1;
    if (y > 0 and pixels[x,y-1] == (255,255,255)) :
        haswhite = haswhite + 1;
    if (x < w-1 and pixels[x+1,y] == (255,255,255)) :
        haswhite = haswhite + 1;
    if (y < h-1 and pixels[x,y+1] == (255,255,255)) :
        haswhite = haswhite + 1;

    
    if (allblack == 4 and not haswhite>0)  :
        return (0,0,0) #pixel
    else :
        return (255,255,255)
        
        
def removenoisemedian(pixel, x, y, w, h, pixels):
    """Remove noise with avg of the neighbours"""
    
    if (pixel == (0,0,0)) : return (0, 0, 0)
    
    global whitepixel_cnt
    
    whitepixel_cnt = whitepixel_cnt + 1
    
    startx = 0
    stopx = w-1
    starty = 0
    stopy = h-1
    
    if (x >= 3) :
        startx = x - 3; 
    if (x < w-3) :
        stopx = x + 3;
    if (y >= 3) :
        starty = y-3;
    if (y < h-3) :
        stopy = y+3;
    
    iterations = 0
    whitepixels = 0
    for _x in range(startx,stopx+1) :
        for _y in range(starty, stopy + 1) :
            if (_x != x and _y != y) :
                iterations = iterations + 1
                if (pixels[_x,_y] == (255,255,255)) : whitepixels = whitepixels + 1;
    #arr[whitepixels]=arr[whitepixels]+1
    #value = arr[whitepixels]
    #arr[whitepixels] = 4
    #print whitepixels

    if (whitepixels == 0) :
        #print iterations, whitepixels 
        return (0,0,0) #pixel
    else :
        return (255,255,255)
    


def applyfilter(image, func):
    """ Applies a function to each pixel of an image."""
    print "applyfilter"
    width,height = image.size
    pixel = image.load()
    print "width : " + str(width) + " height : " + str(height)
    
    for y in range(0, height):
        for x in range(0, width) :
##print "[" + str(x) + " " + str(y) + " = " + str(pixel[x,y]) + " ] ",
		pixel[x,y] = func(pixel[x,y], x, y, width, height, pixel)


    print "finished apply filter"


font = ImageFont.truetype("/usr/share/fonts/truetype/msttcorefonts/arial.ttf", 15)
im = Image.open("/work/cave/map/mecsek/14-114.jpg")
frame = im.crop(((600, 600, 1000, 1000)))
#blur = frame.filter(ImageFilter.EDGE_ENHANCE)
#blur.show()
#orig=frame.copy()
#orig.show()
frame = ImageEnhance.Contrast(frame).enhance(10)

#enha=ImageEnhance.Contrast(blur).enhance(10)
#enha.show()
#frame.show()
modified=frame.copy()
#enmo=enha.copy()
applyfilter(modified, colorswap)
modified.show()
#-applyfilter(modified, removenoise)

#-draw = ImageDraw.Draw(modified)
#-draw.text((40, 40), "world", font=font)

#-modified.show()

#-whitepixel_cnt = 0

#-applyfilter(modified, removenoisemedian)
#-w,h = modified.size
#-print "Sum of pixels : " + str(w*h) + "\nWhite pixels : " + str(whitepixel_cnt)
#-modified.show()

#applyfilter(enmo, colorswap)
#enmo.show()
#enh = ImageEnhance.Contrast(modified)
#enh.enhance(1.3).show("30% more contrast")

frame.show()