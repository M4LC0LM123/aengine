import pygame
import pygame_gui
from dataclasses import *
from drawText import *
from object import Object

SCREEN_WIDTH = 1280
SCREEN_HEIGHT = 720

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
class ObjectInfo():
    panel: pygame.Rect
    # xInput: pygame_gui.elements.UITextEntryLine
    # yInput: pygame_gui.elements.UITextEntryLine
    # zInput: pygame_gui.elements.UITextEntryLine
    # sxInput: pygame_gui.elements.UITextEntryLine
    # syInput: pygame_gui.elements.UITextEntryLine
    # syInput: pygame_gui.elements.UITextEntryLine
    # rxInput: pygame_gui.elements.UITextEntryLine
    # ryInput: pygame_gui.elements.UITextEntryLine
    # ryInput: pygame_gui.elements.UITextEntryLine
    # idInput: pygame_gui.elements.UITextEntryLine
    boundObj: Object

    def __init__(self, manager, boundObj, panelRec = pygame.Rect(SCREEN_WIDTH - 250, 10, 120, 350)):
        self.panel = panelRec
        self.boundObj = boundObj
        # self.xInput = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((self.panel.x, self.panel.y + 25), (120, 25)), manager = manager)
        # self.yInput = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((self.panel.x, self.panel.y + 50), (120, 25)), manager = manager)
        # self.zInput = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((self.panel.x, self.panel.y + 75), (120, 25)), manager = manager)
        # self.sxInput = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((self.panel.x, self.panel.y + 125), (120, 25)), manager = manager)
        # self.syInput = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((self.panel.x, self.panel.y + 150), (120, 25)), manager = manager)
        # self.szInput = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((self.panel.x, self.panel.y + 175), (120, 25)), manager = manager)
        # self.rxInput = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((self.panel.x, self.panel.y + 225), (120, 25)), manager = manager)
        # self.ryInput = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((self.panel.x, self.panel.y + 250), (120, 25)), manager = manager)
        # self.rzInput = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((self.panel.x, self.panel.y + 275), (120, 25)), manager = manager)
        # self.idInput = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((self.panel.x, self.panel.y + 325), (120, 25)), manager = manager)

    def set(self, manager, boundObj, panelRec = pygame.Rect(SCREEN_WIDTH - 250, 10, 120, 350)):
        self.panel = panelRec
        self.boundObj = boundObj
        # self.xInput = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((self.panel.x, self.panel.y + 25), (120, 25)), manager = manager)
        # self.yInput = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((self.panel.x, self.panel.y + 50), (120, 25)), manager = manager)
        # self.zInput = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((self.panel.x, self.panel.y + 75), (120, 25)), manager = manager)
        # self.sxInput = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((self.panel.x, self.panel.y + 125), (120, 25)), manager = manager)
        # self.syInput = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((self.panel.x, self.panel.y + 150), (120, 25)), manager = manager)
        # self.szInput = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((self.panel.x, self.panel.y + 175), (120, 25)), manager = manager)
        # self.rxInput = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((self.panel.x, self.panel.y + 225), (120, 25)), manager = manager)
        # self.ryInput = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((self.panel.x, self.panel.y + 250), (120, 25)), manager = manager)
        # self.rzInput = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((self.panel.x, self.panel.y + 275), (120, 25)), manager = manager)
        # self.idInput = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((self.panel.x, self.panel.y + 325), (120, 25)), manager = manager)

    def show(self, shown):
        pass
        # if shown:
        #     self.xInput.show()
        #     self.xInput.enable()
        #     self.yInput.show()
        #     self.yInput.enable()
        #     self.zInput.show()
        #     self.zInput.enable()

        #     self.sxInput.show()
        #     self.sxInput.enable()
        #     self.syInput.show()
        #     self.syInput.enable()
        #     self.szInput.show()
        #     self.szInput.enable()

        #     self.rxInput.show()
        #     self.rzInput.enable()
        #     self.ryInput.show()
        #     self.rzInput.enable()
        #     self.rzInput.show()
        #     self.rzInput.enable()
            
        #     self.idInput.show()
        #     self.idInput.enable()
        # else:
        #     self.xInput.hide()
        #     self.xInput.disable()
        #     self.yInput.hide()
        #     self.yInput.disable()
        #     self.zInput.hide()
        #     self.zInput.disable()

        #     self.sxInput.hide()
        #     self.sxInput.disable()
        #     self.syInput.hide()
        #     self.syInput.disable()
        #     self.szInput.hide()
        #     self.szInput.disable()

        #     self.rxInput.hide()
        #     self.rzInput.disable()
        #     self.ryInput.hide()
        #     self.rzInput.disable()
        #     self.rzInput.hide()
        #     self.rzInput.disable()
            
        #     self.idInput.hide()
        #     self.idInput.disable()

    def render(self, screen):
        pygame.draw.rect(screen, "#32628A", self.panel)
        self.show(True)
        drawText(screen, "x: " + str(self.boundObj.x), self.panel.x + 55, self.panel.y + 10, pygame.font.Font("../fonts/CascadiaMono.ttf", 14), BLACK, None)
        drawText(screen, "y: " + str(self.boundObj.y), self.panel.x + 55, self.panel.y + 30, pygame.font.Font("../fonts/CascadiaMono.ttf", 14), BLACK, None)
        drawText(screen, "z: " + str(self.boundObj.z), self.panel.x + 55, self.panel.y + 50, pygame.font.Font("../fonts/CascadiaMono.ttf", 14), BLACK, None)
        drawText(screen, "w: " + str(self.boundObj.w), self.panel.x + 55, self.panel.y + 70, pygame.font.Font("../fonts/CascadiaMono.ttf", 14), BLACK, None)
        drawText(screen, "h: " + str(self.boundObj.h), self.panel.x + 55, self.panel.y + 90, pygame.font.Font("../fonts/CascadiaMono.ttf", 14), BLACK, None)
        drawText(screen, "d: " + str(self.boundObj.d), self.panel.x + 55, self.panel.y + 110, pygame.font.Font("../fonts/CascadiaMono.ttf", 14), BLACK, None)
        drawText(screen, "rx: " + str(self.boundObj.rx), self.panel.x + 55, self.panel.y + 130, pygame.font.Font("../fonts/CascadiaMono.ttf", 14), BLACK, None)
        drawText(screen, "ry: " + str(self.boundObj.ry), self.panel.x + 55, self.panel.y + 150, pygame.font.Font("../fonts/CascadiaMono.ttf", 14), BLACK, None)
        drawText(screen, "rz: " + str(self.boundObj.rz), self.panel.x + 55, self.panel.y + 170, pygame.font.Font("../fonts/CascadiaMono.ttf", 14), BLACK, None)
        drawText(screen, "id: " + str(self.boundObj.id), self.panel.x + 55, self.panel.y + 190, pygame.font.Font("../fonts/CascadiaMono.ttf", 14), BLACK, None)
        # print(str(self.boundObj))

        
