import pygame
from constants import width, height


class Button:
    '''
    Кнопки
    '''
    def __init__(self, picture_1, picture_2):
        self.picture_1 = picture_1
        self.picture_2 = picture_2
        self.image_1 = pygame.image.load(self.picture_1)
        self.image_2 = pygame.image.load(self.picture_2)
        self.rect = self.image_1.get_rect()
        self.rect_width, self.rect_height = self.rect.size
        self.rect.y = (height - self.rect_height)
        self.set_x()

    def set_x(self):
        if self.picture_1 == 'static/randomButtonOff.png':
            self.rect.x = 0
        elif self.picture_1 == 'static/bestDecButtonOff.png':
            self.rect.x = width - self.rect_width
        elif self.picture_1 == 'static/Off.png':
            self.rect.x = width // 2 - self.rect_width // 2 + 5

    def draw_click(self, screen):
        screen.blit(self.image_2, self.rect)
        pygame.display.flip()
        pygame.time.wait(50)

    def check_click(self, mouse_x, mouse_y, screen):
        if self.rect.x <= mouse_x <= self.rect.x + self.rect_width \
                and self.rect.y <= mouse_y <= self.rect.y + self.rect_height:
            self.draw_click(screen)
            if self.picture_1 == 'static/randomButtonOff.png':
                self.setMode('0')
                self.setField()
            elif self.picture_1 == 'static/bestDecButtonOff.png':
                self.setMode('1')
                self.setField()
            elif self.picture_1 == 'static/Off.png':
                self.changeMode()
        return False

    def changeMode(self):
        fileMode = open('chanceMode.txt', 'r')
        changeMode = fileMode.read()
        newMode = str(int(not int(changeMode)))
        fileMode.close()
        fileMode = open('chanceMode.txt', 'w')
        fileMode.write(newMode)
        fileMode.close()

    def setMode(self, mode):
        fileMode = open('mode.txt', 'w')
        fileMode.write(mode)
        fileMode.close()

    def setField(self):
        fileField = open('field.txt', 'w')
        fileField.write('0 0 0 \n0 0 0 \n0 0 0 \n')
        fileField.close()

    def draw(self, screen):
        if self.picture_1 == 'static/Off.png':
            fileMode = open('chanceMode.txt', 'r')
            changeMode = int(fileMode.read())
            fileMode.close()
            if changeMode == 1:
                screen.blit(self.image_2, self.rect)
                return
        screen.blit(self.image_1, self.rect)
