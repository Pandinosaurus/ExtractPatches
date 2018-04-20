import os
import csv

# List images with ".jpg" extension in given path
path = './data/outputColorGray_bis'
images = []
extension = '.jpg'
for root, dirs, files in os.walk(path):
    for file in files:
        if file.endswith(extension): #only get files with required extension
            images.append(file)

# Open a tsv file according to the path name and write it as follow
# [id] [image]
#  1   name1.jpg
#  2   name2.jpg
with open(path+'.tsv', 'w') as tsvfile:
    id=0
    writer = csv.writer(tsvfile, delimiter='\t') #writer
    for image in images:
        if id == 0:
            writer.writerow(['id', 'image'])
        else:
            writer.writerow([id, image])
        id = id+1