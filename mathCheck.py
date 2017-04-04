#!/usr/local/bin/python2.7

import sys
import combinadic

print( sys.path )
n = combinadic.HtMath.choose(25,2)

print ('5 choose 2 equals: ')
print ("%.0ld" % n)
