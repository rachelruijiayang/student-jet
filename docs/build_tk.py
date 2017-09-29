#To build a .zip of the teaching kit slides, run this using:
#
#python build_tk.py directory
#
#Where 'directory' is the path to the teaching kit

import zipfile
import sys
import os, datetime
from os import listdir, makedirs
from os.path import isfile, join, dirname, exists

#if these strings are in the directory/filename, then exclude
exclude_list = ["Icon", ".DS", "Resources"]

#get current working directory
cwd = os.path.dirname(os.path.realpath(__file__))

#get teaching kit directory
if len(sys.argv) != 2: 
    print "Usage: python build_teaching_kit.py teaching_kit_directory (provide full path to teaching kit)"
    exit()
tk_dir = os.path.normpath(sys.argv[1])
base_tk_dir = os.path.basename(tk_dir)

#check if teaching kit directory exists
if not os.path.exists(tk_dir):
    print "Error directory does not exist"
    exit()

modules = [m for m in listdir(tk_dir) if "Module" in m]

outfile = "Robotics_with_Jetson_Teaching_Kit_" + datetime.date.today().strftime("%B_%d_%Y") + ".zip"
zf = zipfile.ZipFile(outfile, "w")

#add all the module directories
for m in modules:
    print "Adding " + m
    for dirname, subdirs, files in os.walk(os.path.join(tk_dir,m)):
        #remove the Google Drive directory from the path name in the zip file
        zip_path = dirname.split("Drive/")[1]

        exclude = [f for f in exclude_list if f in os.path.basename(dirname)]
        if len(exclude) == 0:
            zf.write(dirname, zip_path)

            for filename in files:
                exclude = [f for f in exclude_list if f in filename]
                if len(exclude) == 0:
                    zf.write(os.path.join(dirname, filename), zip_path + "/" + filename)


#add the files in the root directory
print "Adding files in root directory"
for dirname, subdirs, files in os.walk(tk_dir):
    #remove the Google Drive directory from the path name in the zip file
    zip_path = dirname.split("Drive/")[1]

    for filename in files:
        if os.path.isfile(os.path.join(tk_dir,filename)): #add files, but not directories
            exclude = [f for f in exclude_list if f in filename]
            if len(exclude) == 0:
                zf.write(os.path.join(dirname, filename), zip_path + "/" + filename)

zf.close()

# vim: ai ts=4 sts=4 et sw=4 ft=python
