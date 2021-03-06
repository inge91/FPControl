from PIL import Image
import sys
import os


def convert(filename):

	l = Image.open(filename)

	try:
		with open(filename[:-3] +"txt") as f: 
			f.close()
			os.remove(filename[:-3] + "txt")
	except IOError as e:
		pass

	try:
		with open(filename[:-4] +"coords.txt") as f: 
			f.close()
			os.remove(filename[:-4] + "coords.txt")
	except IOError as e:
		pass
	try:
		with open(filename[:-4] +"whitecoords.txt") as f: 
			f.close()
			os.remove(filename[:-4] + "whitecoords.txt")
	except IOError as e:
		pass
	# open txt file of the same name
	filed = open( filename[:-3] + "txt", "a")
	filee = open( filename[:-4] + "coords.txt", "a")
	filef = open( filename[:-4] + "whitecoords.txt", "a")
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
			if r == 255 and g == 255 and b == 255:
				filed.write("1 ")
				filef.write(str(j) + "," + str(i) + "\n")
			# In case of black pixel
			elif r == 0 and g == 0 and b == 0 :
				# Find value of next pixel
				if j != x-1:
					if l.mode == "RGB":
						(r2,g2,b2) = l.getpixel((j+1,i))
					else:
						(r2, g2, b2, _) = l.getpixel((j+1,i))
				# if no next pixel just set it to white
				else:
					r2 = 255
					g2 = 255
					b2 = 255
				# we did not yet detect a wall
				if wall == False:
					# If next element is white there is no wall
					if r2 > 0 or g2 > 0 or b2 > 0:
						pass
					# Else write the begin coordinate down and set true
					elif r2 == 0 and b2 == 0 and g2 == 0:
						wall = True
						filee.write(str(j) + "," + str(i) + " ")
				# in case we were already walling
				elif wall == True:
					if r2 > 0 or b2 > 0 or g2 > 0:
						wall = False
						filee.write(str(j) + "," + str(i) + "\n")
					else:
						pass
				filed.write("0 ")

		filed.write("\n")

	# Loop through the pixels in vertical direction
	for i in range (0, x):
		for j in range (0, y):
			if l.mode == "RGB":
				(r,g,b) = l.getpixel((i,j))		
			else:
				(r,g,b, _) = l.getpixel((i,j))		

			# In case of non-black pixel
			if x == 0:
				print i,
				print " ",
				print j
			if r == 255 and g == 255 and b == 255:
				pass
			# In case of black pixel
			elif r == 0 and g == 0 and b == 0:
				# Find value of next pixel
				if j != y-1:
					if l.mode == "RGB":
						(r2, g2, b2) = l.getpixel((i,j+1))		
					else:
						(r2, g2, b2, _) = l.getpixel((i,j+1))		
				# if no next pixel just set it to white
				else:
					print "There is no next element"
					r2 = 255
					b2 = 255
					g2 = 255
				# we did not yet detect a wall
				if wall == False:
					print "value of r2", 
					print r2
					# If next element is white there is no wall
					if r2 > 0 or g2 > 0 or b2 > 0:
						pass
					# Else write the begin coordinate down and set true
					elif r2 == 0 and b2 == 0 and g2 == 0:
						print "Two black elements"
						wall = True
						filee.write(str(i) + "," + str(j) + " ")
				# in case we were already walling
				elif wall == True:
					if r2 > 0 or b2 > 0 or g2 > 0:
						wall = False
						filee.write(str(i) + "," + str(j) + "\n")
					else:
						pass

				



