import pygame
import pygame_gui
from dataclasses import *
from drawText import *
from object import Object

SCREEN_WIDTH = 1280
SCREEN_HEIGHT = 720

@dataclass
class ObjectInfo():
    panel: pygame.Rect()
    posInfo: pygame_gui.elements.UILabel
    xInput: pygame_gui.elements.UITextEntryLine
    yInput: pygame_gui.elements.UITextEntryLine
    zInput: pygame_gui.elements.UITextEntryLine
    scaleInfo: pygame_gui.elements.UILabel
    sxInput: pygame_gui.elements.UITextEntryLine
    syInput: pygame_gui.elements.UITextEntryLine
    syInput: pygame_gui.elements.UITextEntryLine
    rotInfo: pygame_gui.elements.UILabel
    rxInput: pygame_gui.elements.UITextEntryLine
    ryInput: pygame_gui.elements.UITextEntryLine
    ryInput: pygame_gui.elements.UITextEntryLine
    idInfo: pygame_gui.elements.UILabel
    idInput: pygame_gui.elements.UITextEntryLine
    boundObj: Object

    def __init__(self, manager, boundObj, panelRec = pygame.Rect(SCREEN_WIDTH - 250, 510, 120, 220)):
        self.panel = panelRec
        self.boundObj = boundObj
        self.posInfo = pygame_gui.elements.UILabel(relative_rect = pygame.Rect((self.panel.x, self.panel.y), (120, 50)), text = "x: y: z: ", manager = manager)
        
