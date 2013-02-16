
from PIL import Image
import sys
import os


def set_positions(filename):

	l = Image.open(filename)

	try:
		with open(filename[:-4] +"start.txt") as f: 
			f.close()
			os.remove(filename[:-4] + "start.txt")
	except IOError as e:
		pass

	try:
		with open(filename[:-4] +"end.txt") as f: 
			f.close()
			os.remove(filename[:-4] + "end.txt")
	except IOError as e:
		pass
	# open txt file of the same name
	filed = open( filename[:-4] + "start.txt", "a")
	filee = open( filename[:-4] + "end.txt", "a")
	[x,y] = l.size
	wall = False
	# Loop through all the pixels
	for i in range (0, x):
		for j in range (0, y):
			if l.mode == "RGB":
				(r,g,b) = l.getpixel((j,i))
			else:
				(r, g, b, _) = l.getpixel((j,i))
			# In case of non-black pixel
			if g == 255 and r == 0 and b == 0:
				filed.write(str(j) + "," + str(i))
			elif b == 255 and r == 0 and g == 0:
				filee.write(str(j) + "," + str(i) + "\n")
			# In case of black pixel
			else:
				pass