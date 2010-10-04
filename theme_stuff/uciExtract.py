import sys
from uci import *

print 'uciExtract Alpha\n(C) 2010 The Lemon Man'

try:
	uciFile = open(sys.argv[1], 'r+b')
except:
	print 'Usage:\n\tpython uci.py uciTheme.uci'
	exit(0)
	
try:
	os.mkdir(sys.argv[1] + '_icons')
except:
	pass
	
myTheme = uciTheme(uciFile)
myTheme.dumpImages(sys.argv[1] + '_icons')
myTheme.dumpTags()