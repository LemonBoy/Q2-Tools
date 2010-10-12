from uci import *

myTheme = uciTheme()
myTheme.load('Q2UCI_Night.UCI')
print '%s' % myTheme
for img in myTheme.images:
    open('l.bmp', 'w+b').write(img.getData())
myTheme.save('ohai.uci')
