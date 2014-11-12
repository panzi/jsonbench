#!/usr/bin/python

from __future__ import division, print_function, with_statement

from time import clock
from json import loads

def main(args):
	repeat, filename = args
	repeat = int(repeat)
	with open(filename, "rb") as f:
		buf = f.read().decode('utf-8')

	duration = 0
	for _ in range(repeat):
		start = clock()
		loads(buf)
		duration += clock() - start
	print(int(duration * 1000))

if __name__ == '__main__':
	import sys
	main(sys.argv[1:])
