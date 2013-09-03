#!/usr/bin/python

import os
import subprocess
import sys
import shutil

path = sys.argv[1]

files = os.listdir(path)

find_cmd = ['find', path, '-name','*']
files = subprocess.check_output(find_cmd).split()

for file in files:
  try:
    path, filename = os.path.split(file)
    name, format = filename.split(".")[-2:]
    
  except:
    continue # not a texture
  try:    
    dest_dir = path.replace('materials/textures', 'meshes')
    dest_path = "%s/%s.png" % (dest_dir, name)
    if dest_path == file:
      continue
    cmd = None
    if format.lower() in ['tif', 'tga', 'tiff', 'jpeg', 'jpg', 'gif', 'png']:
      cmd = ['convert', file, dest_path]
      if format.lower() == 'png':
        cmd = ['cp', file, dest_dir] 
      print cmd
      subprocess.check_call(cmd)
          
    if format.lower() in ['dae']:
      sed_cmd = ["sed", "-i", "-e", 's/\.tga/\.png/g', "-e",
          's/\.tiff/\.png/g', "-e", 's/\.tif/\.png/g',
          "-e", 's/\.jpg/\.png/g', "-e", 's/\.jpeg/\.png/g',
          "-e", 's/\.gif/\.png/g', file]
      print sed_cmd
      subprocess.check_call(sed_cmd)  
  except Exception, e:
      print "error %s" % e
      raise