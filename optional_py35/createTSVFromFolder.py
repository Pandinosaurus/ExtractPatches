# createTSVFromFolder.py
# Using Python3
#
# Author : Rémi Ratajczak
# Email : remi.ratajczak@gmail.com
# License : MIT

import os
import csv
import argparse

# Add parsing arguments
parser = argparse.ArgumentParser(description='Write a tsv file for each file in the given path this/is/a/path')
parser.add_argument('-path',
                    '--path',
                    required=False,
                    default='../data/outputColorGray_bis',
                    help='the path to the folder that contains the files to record (e.g. ../data/images)')
parser.add_argument('-extension',
                    '--extension',
                    default='.jpg',
                    required=False,
                    help='the extension of the files to record (e.g. .jpg)')

# Parse
args = parser.parse_args()


# List images with ".jpg" extension in given path
images = []
for root, dirs, files in os.walk(args.path):
    for file in files:
        if file.endswith(args.extension): #only get files with required extension
            images.append(file)

# Open a tsv file according to the path name and write it as follow
# [id] [image]
#   1  name1.jpg
#   2  name2.jpg
with open(args.path+'.tsv', 'w') as tsvfile:
    id=0
    writer = csv.writer(tsvfile, delimiter='\t') #writer
    for image in images:
        if id == 0:
            writer.writerow(['id', 'image'])
        else:
            writer.writerow([id, image])
        id = id+1