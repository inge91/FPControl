import imageconverter

def main():
	i = 1
	while(True):
		filename = "level" + str(i) +".png"
		print filename
		
		try:
			with open(filename) as f: 
				f.close()
				imageconverter.convert(filename)
		except IOError as e:
			break
		
		i+=1
		


if __name__ == "__main__":
	main()
