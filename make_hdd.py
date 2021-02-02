from sys import argv
from math import ceil

if len(argv) >= 1:
	DATA = " ".join(argv[1:])
else:
	DATA = ""

SECT = 256

FILE = "test.txt"



sects = 0

data_length = len(DATA)

sects = ceil(data_length/SECT)

full_length = SECT * sects

extra_len = full_length - data_length

padding = extra_len*chr(0)

data = DATA.encode() + padding.encode()

with open(FILE, "wb") as f:
	f.write(data)


print(f"Wrote {sects} sects to {FILE}")
