import pygame


class Cell:
    def __init__(self, x, y, state, index):
        self.zero = pygame.image.load('static/zero.png')
        self.cross = pygame.image.load('static/cross.png')
        self.rect = self.zero.get_rect()
        self.rect_width, self.rect_height = self.rect.size
        self.rect.x = x
        self.rect.y = y
        self.state = state
        self.index = index

    def check_click(self, mouse_x, mouse_y):
        if self.rect.x <= mouse_x <= self.rect.x + self.rect_width \
                and self.rect.y <= mouse_y <= self.rect.y + self.rect_height:
            if self.state == '0':
                self.state = 'X'
                return True
        return False

    def draw(self, screen):
        if self.state == 'O':
            screen.blit(self.zero, self.rect)
        elif self.state == 'X':
            screen.blit(self.cross, self.rect)
