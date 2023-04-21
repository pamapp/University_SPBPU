from PIL import Image
import numpy as np
import os
from matplotlib import pyplot as plt


def updateCells(old_x_cells, old_y_cells, current_x, current_y, eps, current_e):
    new_y = {n: [] for n in eps}
    new_x = {n: [] for n in eps}
    for n in eps:
        if n < current_e:
            for i_item in old_y_cells[n]:
                for j_item in old_x_cells[n]:
                    if not (i_item % (current_e//n) == current_y and j_item % (current_e//n) == current_x):
                        new_y[n].append(i_item)
                        new_x[n].append(j_item)
        new_y[n] = old_y_cells[n]
        new_x[n] = old_x_cells[n]
    return new_x, new_y


def isFoundBlackInCell(image, x, y, eps):
    # Итерируемся по элементам ячейки
    for l in range(y*eps, ((y+1)*eps) - 1):
        for w in range(x*eps, ((x+1)*eps) - 1):
            if image.getpixel((l, w)) == 0:
                return True
    return False


def countDimension(image):
    length, width = image.size[0], image.size[1]
    epsilons = list(reversed([pow(5, x) for x in range(1, 3)]))
    # Ключ - eps, значение - (N(eps), ln(N(eps), ln(eps))
    eps_data = {n: [0, 0, 0] for n in epsilons}
    # Ключ - eps, значение - список клеток, которые необходимо проверить для каждого eps
    y_cells = {n: list(range(0, length//n)) for n in epsilons}
    x_cells = {n: list(range(0, width//n)) for n in epsilons}
    
    # По ключам
    for e in eps_data:
        # По ячейкам
        for y in y_cells[e]:
            for x in x_cells[e]:
                if isFoundBlackInCell(image, x, y, e):
                    eps_data[e][0] += 1

        eps_data[e][1] = np.log(eps_data[e][0])
        eps_data[e][2] = np.log(e)
        
        # Обновляем клетки, по которым пойдем дальше
        x_cells, y_cells = updateCells(x_cells, y_cells, x, y, epsilons, e)

    ln_e_list = [eps_data[x][2] for x in eps_data]
    ln_n_e_list = [eps_data[x][1] for x in eps_data]

    # По методу наименьших квадратов
    return -np.polyfit(ln_e_list, ln_n_e_list, 1)[0]


def getBlackAndWhiteImage(image):
    black_and_white = image.convert('1')
    return black_and_white


if __name__ == '__main__':
    name = 'image.jpg'
    try:
        image = Image.open(os.path.join(os.path.dirname(__file__), name))
        print(f"Image size: {image.size[0]} x {image.size[1]}\n")
        image = getBlackAndWhiteImage(image)
        dim = countDimension(image)
        print(f"Dimension: {dim}")

        plt.figure(figsize=(5, 5))
        plt.imshow(image)
        plt.show()
    except Exception as e:
        print(e)
