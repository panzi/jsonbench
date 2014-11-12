#!/usr/bin/python

from __future__ import print_function, division

import io
import os
from glob import glob
from collections import OrderedDict
from subprocess import check_output

benchs = [
	('ajson number',     lambda repeat, slice, filename: ['./ajson/ajsonbench_number',     str(repeat), str(slice), filename]),
	('ajson integer',    lambda repeat, slice, filename: ['./ajson/ajsonbench_integer',    str(repeat), str(slice), filename]),
	('ajson string',     lambda repeat, slice, filename: ['./ajson/ajsonbench_string',     str(repeat), str(slice), filename]),
	('ajson components', lambda repeat, slice, filename: ['./ajson/ajsonbench_components', str(repeat), str(slice), filename]),
	('yajl',    lambda repeat, slice, filename: ['./yajl/yajlbench', str(repeat), str(slice), filename]),
	('python2', lambda repeat, slice, filename: ['python2', 'jsonbench.py', str(repeat), filename]),
	('python3', lambda repeat, slice, filename: ['python3', 'jsonbench.py', str(repeat), filename]),
	('ruby',    lambda repeat, slice, filename: ['ruby',    'jsonbench.rb', str(repeat), filename])
]

files = sorted(glob("data/*.json"))

def avg(values):
	return sum(values) / len(values)

def median(values):
	n = len(values)
	i = n // 2
	if n % 2:
		return values[i]
	else:
		return (values[i] + values[i - 1]) / 2

def run(repeat=500, slice=io.DEFAULT_BUFFER_SIZE):
	stats = OrderedDict()
	for name, setup in benchs:
		this_stats = OrderedDict()
		print("\n%s:" % name)
		for filename in files:
			duration = int(check_output(setup(repeat, slice, filename)))
			filename = os.path.split(filename)[1]
			this_stats[filename] = duration
			print("%-22s: %5dms (avg. %5dms)" % (filename, duration, duration / repeat))

		stats[name] = this_stats

	# TODO: generate fancy output with tables and diagrams

if __name__ == '__main__':
	run()
