import sys
import pygame
from game import Game


def main():
    pygame.init()  # Инициализация библиотеки
    game = Game()
    game.main_loop()
    sys.exit()


if __name__ == "__main__":
    main()