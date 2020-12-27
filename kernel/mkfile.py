from sys import argv
from os import sep, makedirs, path

INC = "include"
SRC = "src"


name = argv[1]

parts = name.split(sep)
dirs = parts[0:-1]

file_name = parts[-1]


dir1 = path.join(INC, *dirs)
print(dir1)

exit()

if not path.exists(dirs):
	makedirs(dirs)
else:
	print("Path Exists!")
	
inc_path = 12
