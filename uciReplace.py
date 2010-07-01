import sys
from uci import *

def usage ():
	print 'Usage:\n\tpython uciReplace.py uciTheme.uci iconIndex newIcon.bmp'
	exit(0)

print 'uciReplace Alpha\n(C) 2010 The Lemon Man'

if len(sys.argv) < 4:
	usage()

try:
	uciFile = open(sys.argv[1], 'r+b')
except:
	usage()
	
myTheme = uciTheme(uciFile)
try:
	newBmp = open(sys.argv[3], 'rb')
except:
	exit(0)
if myTheme.updateIconData(int(sys.argv[2]), newBmp.read()) != 1:
	print 'Failed to update icon data %s @ %i' % (sys.argv[3], int(sys.argv[2]))
	exit(0)
myTheme.updateIconCoord(int(sys.argv[2]), [100, 100])
if myTheme.updateIconTableEntry(int(sys.argv[2])) != 1:
	print 'Failed to update the table %s @ %i' % (sys.argv[3], int(sys.argv[2]))
	exit(0)
newBmp.close()
print 'Imported...'