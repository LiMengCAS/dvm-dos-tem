#!/usr/bin/env python

import os
import glob
import json
import logging


import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

import selutil


# The directory to look for json files.
TMPDIR = '/tmp/cal-dvmdostem'

# some logging stuff
LOG_FORMAT = '%(levelname)-7s %(name)-8s %(message)s'
logging.basicConfig(level=logging.DEBUG, format=LOG_FORMAT)

class FixedWindow(object):
  pass


if __name__ == '__main__':

  traces = [
    # pnum: which sub plot to be on, 0 based  
    { 'jsontag': 'Rainfall', 'pnum': 0, },
    { 'jsontag': 'Snowfall', 'pnum': 0, },
    { 'jsontag': 'WaterTable', 'pnum': 1, },
  ]


  logging.warn("Starting main app...")
  
  #testing that the module importing works...
  selutil.jfname2idx('0000_00.json')
  
  logging.info("Done with main app...")

