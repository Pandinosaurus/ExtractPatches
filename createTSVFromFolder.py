import os
import csv

# List images with ".jpg" extension in given path
path = './data/outputColorGray_bis'
images = []
extension = '.jpg'
for root, dirs, files in os.walk(path):
    for file in files:
        if file.endswith(extension):
            images.append(file)
            print(file)

with open(path+'.tsv', 'w') as tsvfile:
    writer = csv.writer(tsvfile, delimiter='\t')
    id=0
    for record in files:
        if id == 0:
            writer.writerow(['id', 'image'])
        else:
            writer.writerow([id, file])
        id = id+1