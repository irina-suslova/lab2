import pygame
from cell import Cell
from text import Text
from declaration import Declaration


class Grid:
    '''
    Сетка игры
    '''
    def __init__(self):
        self.coords_x = [173, 294, 415]
        self.coords_y = [202, 330, 458]
        self.cells = []
        self.chances = []
        self.declaration = Declaration()
        self.load_cells()
        self.load_chances()

    def checker(self):
        """
        Проверка окончания игры
        :return:
        0 - игра продолжается
        1 - победа
        2 - поражение
        """
        for i in range(3):
            if self.cells[0 + i * 3].state == self.cells[1 + i * 3].state and self.cells[1 + i * 3].state == \
                self.cells[2 + i * 3].state:
                if self.cells[0 + i * 3].state == 'O':
                    return 2
                if self.cells[0 + i * 3].state == 'X':
                    return 1
            if self.cells[0 + i].state == self.cells[3 + i].state and self.cells[3 + i].state == \
                self.cells[6 + i].state:
                if self.cells[0 + i].state == 'O':
                    return 2
                if self.cells[0 + i].state == 'X':
                    return 1

        if self.cells[0].state == self.cells[4].state and self.cells[4].state == \
                self.cells[8].state:
            if self.cells[0].state == 'O':
                return 2
            if self.cells[0].state == 'X':
                return 1

        if self.cells[2].state == self.cells[4].state and self.cells[4].state == \
                self.cells[6].state:
            if self.cells[2].state == 'O':
                return 2
            if self.cells[2].state == 'X':
                return 1
        return 0

    def load_cells(self):
        self.cells = []
        fileCells = open('field.txt', 'r')
        cells = [item for item in fileCells.read().split()]
        if cells == ['0', '0', '0', '0', '0', '0', '0', '0', '0']:
            self.declaration.state = 0
        index = 0
        for y in self.coords_y:
            for x in self.coords_x:
                self.cells.append(Cell(x, y, cells[index], index))
                index += 1

    def load_chances(self):
        self.chances = []
        fileChances = open('chances.txt', 'r')
        chances = [item for item in fileChances.read().split()]
        index = 0
        for y in self.coords_y:
            for x in self.coords_x:
                text = "Win: " + chances[2 * index] + "%" + "\n" + "Lose: " + chances[2 * index + 1] + "%"
                if self.cells[index].state == '0':
                    self.chances.append(Text(x + 5, y + 5, text))
                index += 1

    def check_click(self, mouse_x, mouse_y):
        self.load_cells()
        check_changes = False
        for cell in self.cells:
            check_changes = check_changes | cell.check_click(mouse_x, mouse_y)
        if check_changes:
            fileField = open('field.txt', 'w')
            for cell in self.cells:
                fileField.write(cell.state)
                fileField.write(' ')
                if cell.index % 3 == 2:
                    fileField.write('\n')
            fileField.close()
            self.declaration.state = self.checker()
        self.load_chances()
        return False

    def draw(self, screen):
        for cell in self.cells:
            cell.draw(screen)
        fileMode = open('chanceMode.txt', 'r')
        changeMode = fileMode.read()
        fileMode.close()
        if changeMode == '1':
            for chance in self.chances:
                chance.draw(screen)
        self.declaration.draw(screen)
