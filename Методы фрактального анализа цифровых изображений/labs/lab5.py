# Для произвольного цветного изображения RGB выбрать одну из составляющих палитры. Показать полученное монохромное изображение. Преобразовать цветное изображение в полутоновое.

from PIL import Image
import os
from matplotlib import pyplot as plt


if __name__ == '__main__':
    name = 'image_5.jpg'
    color = input()
    try:
        if color not in ['R', 'G', 'B']:
            raise KeyError("Wrong color")
        im = Image.open(os.path.join(os.path.dirname(__file__), name))

        data = im.getdata()
        colors_info = {
            'R': [(d[0], 0, 0) for d in data],
            'G': [(0, d[1], 0) for d in data],
            'B': [(0, 0, d[2]) for d in data]
        }

        im.putdata(colors_info[color])
        plt.figure(figsize=(5, 5))
        plt.imshow(im)
        plt.show()
        
    except Exception as e:
        print(e)
