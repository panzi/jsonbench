#!/usr/bin/python

import sys
import json

if len(sys.argv) > 1:
	with open(sys.argv[1],"r") as fp:
		obj = json.load(fp)
else:
	obj = json.load(sys.stdin)

json.dump(obj,sys.stdout,indent=4)
sys.stdout.write('\n')
