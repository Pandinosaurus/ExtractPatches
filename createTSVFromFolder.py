import os

images = []
for root, dirs, files in os.walk(r'data/outputColorGray_bis/'):
    for file in files:
        if file.endswith('.png'):
            images.append(file)
			print(file)