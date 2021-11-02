import pygame
from constants import size
from background import Background
from button import Button
from grid import Grid


class Game:
    def __init__(self):
        self.screen = pygame.display.set_mode(size)  # Установка размеров окна
        self.gameover = False
        self.prepare()
        self.background = Background()
        self.randomMode = Button('static/randomButtonOff.png', 'static/randomButtonOn.png')
        self.bestDecMode = Button('static/bestDecButtonOff.png', 'static/bestDecButtonOn.png')
        self.chanceMode = Button('static/Off.png', 'static/On.png')
        self.grid = Grid()

    def prepare(self):
        pass

    def main_loop(self):
        while not self.gameover:  # Основной цикл
            self.process_events()
            self.process_logic()
            self.process_draw()
            pygame.time.wait(10)  # Ожидание отрисовки

    def process_events(self):
        for event in pygame.event.get():  # Получение всех событий
            if event.type == pygame.QUIT:  # Событие выхода
                self.gameover = True
            if event.type == pygame.MOUSEBUTTONDOWN:
                if event.button == 1:
                    mouse_x, mouse_y = event.pos
                    self.gameover = self.randomMode.check_click(mouse_x, mouse_y, self.screen) or \
                               self.bestDecMode.check_click(mouse_x, mouse_y, self.screen) or \
                               self.chanceMode.check_click(mouse_x, mouse_y, self.screen) or \
                               self.grid.check_click(mouse_x, mouse_y)


    def process_logic(self):
        pass

    def process_draw(self):
        self.background.draw(self.screen)
        self.randomMode.draw(self.screen)
        self.bestDecMode.draw(self.screen)
        self.chanceMode.draw(self.screen)
        self.grid.draw(self.screen)
        pygame.display.flip()  # Double buffering