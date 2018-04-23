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
                    default='../data/outputColorRGB_bis',
                    help='the path to the folder that contains the files to record (e.g. ../data/images)')
parser.add_argument('-extension',
                    '--extension',
                    default='.jpg',
                    required=False,
                    help='the extension of the files to record (e.g. .jpg)')

# List images with ".jpg" extension in given path
def get_image_list_with_id(path, extension):
    images = []
    id = 0
    for root, dirs, files in os.walk(path):
        for file in files:
            if file.endswith(extension): #only get files with required extension
                images.append({
                    'id': id,
                    'image': file
                })
                id = id+1
    return images

# Open a tsv file according to the path name and write it as follow
# [header1] [header2]
#     1     name1.jpg
#     2     name2.jpg
def write_tsv(headers, data, file):
    with open(file, 'w') as output:
        w = csv.DictWriter(
            output, fieldnames=headers, delimiter='\t',
            lineterminator='\n')
        w.writeheader()
        w.writerows(data)


args = parser.parse_args()
images = get_image_list_with_id(args.path, args.extension)
write_tsv(['id','image'], images, args.path+'.tsv')