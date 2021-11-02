import pygame


class Declaration:
    def __init__(self):
        self.win = pygame.image.load('static/win.png')
        self.lose = pygame.image.load('static/lose.png')
        self.rect = self.win.get_rect()
        self.rect_width, self.rect_height = self.rect.size
        self.rect.x = 0
        self.rect.y = 182
        self.state = 0

    def draw(self, screen):
        if self.state == 1:
            screen.blit(self.win, self.rect)
        elif self.state == 2:
            pygame.time.wait(500)
            screen.blit(self.lose, self.rect)
