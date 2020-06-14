"""
---------------------------------------------------------------------------
Script to convert plots from npz format to ASCII

Author: Leonid Burmistrov (Fri Jun 15 14:58:32 JST 2018)
---------------------------------------------------------------------------
"""

import os
import sys
from optparse import Option, OptionValueError, OptionParser
import numpy as np

parser = OptionParser()
parser.add_option('-f', '--npzfile', dest='npzfile', default='xmlarichdatacompilation.npz', help='Name of the input npz file')
parser.add_option('-a', '--arrayname', dest='arrayname', default='total_memory', help='Name of the array to convert in ASCII format')
parser.add_option('-d', '--dump', action="store_true", dest='dump', default=False, help='Dump list of arrays')
parser.add_option('-p', '--printv', dest='printv', default='', help='Name of the array to print')
(options, args) = parser.parse_args()

npzfile = np.load(options.npzfile);

if(options.dump):
    for myarr in npzfile.files:
        print(myarr)

if( len(options.arrayname) > 0):
    outDatFile = options.npzfile + '_' +options.arrayname + '.dat'
    np.savetxt(outDatFile, npzfile[options.arrayname], delimiter=' ')

if( len(options.printv) > 0):
    print(npzfile[options.printv])
