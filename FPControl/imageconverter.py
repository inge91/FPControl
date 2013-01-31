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
	# open txt file of the same name
	filed = open( filename[:-3] + "txt", "a")
	filee = open( filename[:-4] + "coords.txt", "a")
	[x,y] = l.size
	wall = False
	# Loop through all the pixels
	for i in range (0, x):
		for j in range (0, y):
			if l.mode == "RGB":
				(r,g,b) = l.getpixel((j,i))
			else:
				(r, _, _, _) = l.getpixel((j,i))
			# In case of non-black pixel
			if r > 0:
				filed.write("1 ")
			# In case of black pixel
			else:
				# Find value of next pixel
				if j != x-1:
					if l.mode == "RGB":
						(r2,g,b) = l.getpixel((j+1,i))
					else:
						(r2, _, _, _) = l.getpixel((j+1,i))
				# if no next pixel just set it to white
				else:
					r2 = 99
				# we did not yet detect a wall
				if wall == False:
					# If next element is white there is no wall
					if r2 > 1:
						pass
					# Else write the begin coordinate down and set true
					else:
						wall = True
						filee.write(str(j) + "," + str(i) + " ")
				# in case we were already walling
				elif wall == True:
					if r2 > 0:
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
			if r > 0:
				pass
			# In case of black pixel
			else:
				# Find value of next pixel
				if j != y-1:
					if l.mode == "RGB":
						(r2,_,_) = l.getpixel((i,j+1))		
					else:
						(r2,_,_, _) = l.getpixel((i,j+1))		
				# if no next pixel just set it to white
				else:
					print "There is no next element"
					r2 = 99
				# we did not yet detect a wall
				if wall == False:
					print "value of r2", 
					print r2
					# If next element is white there is no wall
					if r2 > 1:
						pass
					# Else write the begin coordinate down and set true
					else:
						print "Two black elements"
						wall = True
						filee.write(str(i) + "," + str(j) + " ")
				# in case we were already walling
				elif wall == True:
					if r2 > 0:
						wall = False
						filee.write(str(i) + "," + str(j) + "\n")
					else:
						pass

				



