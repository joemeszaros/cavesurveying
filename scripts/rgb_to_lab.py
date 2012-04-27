from colormath.color_objects import RGBColor, LabColor

def colour_difference(r1,g1,b1, labreference) :
	rgbcolor1 = RGBColor();
	rgbcolor1.rgb_r = r1; rgbcolor1.rgb_g = g1; rgbcolor1.rgb_b = b1;
	#rgbcolor2 = RGBColor();
	#rgbcolor2.rgb_r = r2; rgbcolor2.rgb_g = g2; rgbcolor2.rgb_b = b2;
	#rgbcolor1.set_from_rgb_hex('#FFF1FF')
	#rgbcolor2.set_from_rgb_hex('#FF03FF')

	#print color.rgb_r,color.rgb_g,color.rgb_b
	#lab = color.convert_to('lab')
	#print lab.lab_l, lab.lab_a,lab.lab_b

	color1 = rgbcolor1.convert_to('lab')
	# Color to be compared to the reference.
	#color2 = rgbcolor2.convert_to('lab')

	#print "== Delta E Colors =="
	#print " COLOR1: %s" % color1
	#print " COLOR2: %s" % color2
	#print "== Results =="
	#print " CIE1976: %.3f" % color1.delta_e(color2, mode='cie1976')
	#print " CIE1994: %.3f (Graphic Arts)" % color1.delta_e(color2, mode='cie1994')
	# Different values for textiles.
	#print " CIE1994: %.3f (Textiles)" % color1.delta_e(color2, mode='cie1994', 
#							   K_1=0.048, K_2=0.014, 
#							   K_L=2)
	#print " CIE2000: %.3f" % color1.delta_e(color2, mode='cie2000')
	return color1.delta_e(labreference, mode='cie1976')

#rgbcolor1 = RGBColor();
#rgbcolor1.rgb_r = 132; rgbcolor1.rgb_g = 0; rgbcolor1.rgb_b = 0;
#lab = rgbcolor1.convert_to('lab')
#print lab.lab_l, lab.lab_a,lab.lab_b
