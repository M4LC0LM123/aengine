import pygame
from dataclasses import *
from drawText import *

BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
GREEN = (0, 255, 0)
RED = (255, 0, 0)
BLUE = (0, 0, 255)
YELLOW = (255, 255, 0)
ORANGE = (255, 127, 80)
PINK = (255, 0, 177)
PURPLE = (107, 0, 179)
CYAN = (102, 255, 255)
DARKPURPLE = (102, 0, 102)

@dataclass
class Object():
    x: float
    y: float
    z: float
    w: float
    h: float
    d: float
    rx: float
    ry: float
    rz: float
    id: int
    selected: bool

    def __init__(self, x, y, z, w, h, d, rx, ry, rz, id):
        self.x = x
        self.y = y
        self.z = z
        self.w = w
        self.h = h
        self.d = d
        self.rx = rx
        self.ry = ry
        self.rz = rz
        self.id = id
        self.selected = False

    def rect(self):
        return pygame.Rect(self.x, self.y, self.w, self.h)
    
    def projRec(self, gridOriginX, gridOriginY):
        return pygame.Rect(self.x + gridOriginX, self.y + gridOriginY, self.w, self.h)
    
    def render(self, screen, color, gridOriginX, gridOriginY):
        pygame.draw.rect(screen, color, pygame.Rect(self.x + gridOriginX, self.y + gridOriginY, self.w, self.h))
        drawText(screen, self.id, self.x + gridOriginX + 15, self.y + gridOriginY + 15, pygame.font.Font("../fonts/CascadiaMono.ttf", 32), WHITE, None)

        if self.selected:
            pygame.draw.rect(screen, YELLOW, pygame.Rect(self.x + gridOriginX, self.y + gridOriginY, self.w, self.h), 1)