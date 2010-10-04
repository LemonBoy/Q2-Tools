from uci import *

myTheme = uciTheme(open('Q2UCI_Night.UCI', 'rb'))
"""s = open('45.bmp', 'rb').read()
print 'CHECK IT %x' % len(s)
myTheme.updateIconData(47, s)"""
myTheme.save('out.uci')