"""
Просто текст
"""
from random import randint
import pygame
from constants import width, height, green


class Text:
    """
    Класс текста
    """
    def __init__(self, x, y, text='Hello, Pygame!', state=True,
                 font="Comic Sans MS", size=27, color=green, bold=False, italic=True):
        self.x = x
        self.y = y
        self.text_win, self.text_lose = text.split('\n')
        self.font = font
        self.size = size
        self.color = color
        self.bold = bold
        self.italic = italic
        self.font_object = pygame.font.SysFont(self.font, self.size, self.bold, self.italic)
        self.text_win_surface = self.font_object.render(self.text_win, True, self.color)
        self.text_lose_surface = self.font_object.render(self.text_lose, True, self.color)
        self.speed = [randint(0, 1) * 2 - 1, randint(0, 1) * 2 - 1]
        self.state = state  # Необходимость отображения текста

    def draw(self, screen):
        if self.state:
            screen.blit(self.text_win_surface, (int(self.x), int(self.y)))
            screen.blit(self.text_lose_surface, (int(self.x), int(self.y) + self.size))
