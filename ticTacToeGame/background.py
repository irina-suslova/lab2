import pygame


class Background:
    '''
    Задний фон, рисунок поля
    '''
    def __init__(self):
        self.picture = 'static/field.png'
        self.image = pygame.image.load(self.picture)
        self.rect = self.image.get_rect()
        self.rect_width, self.rect_height = self.rect.size
        self.rect.x = 0
        self.rect.y = 0

    def draw(self, screen):
        screen.blit(self.image, self.rect)
