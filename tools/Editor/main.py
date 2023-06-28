import pygame
import pygame_gui
from drawText import *
import tkinter as tk
from tkinter import filedialog

pygame.init()

SCREEN_WIDTH = 1280
SCREEN_HEIGHT = 720

screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT), pygame.RESIZABLE)
pygame.display.set_caption("aengine-editor")
clock = pygame.time.Clock()

#colors
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

gridWidth = 8
gridHeight = 8
grid = [ [0] * gridWidth for n in range(gridHeight)]
gridString = str(grid)

x = 0
y = 0
width = 70
height = 70
tileValue = 1

mouseX, mouseY = pygame.mouse.get_pos()
mousePressed = False
mouse2Pressed = False

panelX = SCREEN_WIDTH - 125
panelY = 10
panel = pygame.Rect(panelX, panelY, 120, 500)

manager = pygame_gui.UIManager((SCREEN_WIDTH, SCREEN_HEIGHT), "../themes/theme.json")
save = pygame_gui.elements.UIButton(relative_rect = pygame.Rect((panelX, panelY), (120, 50)), text = "save", manager = manager)
gWidthText = pygame_gui.elements.UILabel(relative_rect = pygame.Rect((panelX - 15, panelY + 50 - 12), (120, 50)), text = "grid width", manager = manager)
gWidth = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((panelX, panelY + 75), (120, 25)), manager = manager)
gHeightText = pygame_gui.elements.UILabel(relative_rect = pygame.Rect((panelX - 12.5, panelY + 100 - 12), (120, 50)), text = "grid height", manager = manager)
gHeight = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((panelX, panelY + 125), (120, 25)), manager = manager)
clearBtn = pygame_gui.elements.UIButton(relative_rect = pygame.Rect((panelX, panelY + 150), (120, 50)), text = "clear", manager = manager)
tileValueText = pygame_gui.elements.UILabel(relative_rect = pygame.Rect((panelX - 10, panelY + 200 - 12), (120, 50)), text = "object index", manager = manager)
tileValueInput = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((panelX, panelY + 225), (120, 25)), manager = manager)

font = pygame.font.Font("../fonts/CascadiaMono.ttf", 32)

running = True
while running:
    time_delta = clock.tick(60)/1000.0
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        if event.type == pygame.VIDEORESIZE:
            screen = pygame.display.set_mode((event.w, event.h), pygame.RESIZABLE)

        if event.type == pygame.MOUSEBUTTONDOWN:
            if pygame.mouse.get_pressed()[0] and mouseX < (width * gridWidth) and mouseY < (height * gridHeight):
                mousePressed = True
            if pygame.mouse.get_pressed()[2] and mouseX < (width * gridWidth) and mouseY < (height * gridHeight):
                mouse2Pressed = True

        if event.type == pygame.MOUSEBUTTONUP:
            if not pygame.mouse.get_pressed()[0]:
                mousePressed = False
            if not pygame.mouse.get_pressed()[2]:
                mouse2Pressed = False

        if mousePressed and mouseX < (width * gridWidth) and mouseY < (height * gridHeight):
            grid[int(mouseY/height)][int(mouseX/width)] = tileValue
        if mouse2Pressed and mouseX < (width * gridWidth) and mouseY < (height * gridHeight):
            grid[int(mouseY/height)][int(mouseX/width)] = 0

        if event.type == pygame.MOUSEWHEEL:
            width += event.y
            height += event.y

        if event.type == pygame_gui.UI_TEXT_ENTRY_FINISHED:
            if event.ui_element == gWidth:
                gridWidth = int(event.text)
                grid = [ [0] * gridWidth for n in range(gridHeight)]
            if event.ui_element == gHeight:
                gridHeight = int(event.text)
                grid = [ [0] * gridWidth for n in range(gridHeight)]
            if event.ui_element == tileValueInput:
                tileValue = int(tileValueInput.text)

        if event.type == pygame_gui.UI_BUTTON_PRESSED:
            if event.ui_element == clearBtn:
                grid = [ [0] * gridWidth for n in range(gridHeight)]
            if event.ui_element == save:
                root = tk.Tk()
                root.withdraw()
                file_path = filedialog.askopenfilename()

        mouseX, mouseY = pygame.mouse.get_pos()

        manager.process_events(event)

    pygame.display.update()
    clock.tick(60)

    screen.fill("#282C34")

    pygame.draw.rect(screen, "#32628A", panel)

    y = 0
    for row in grid:
        for col in row:
            pygame.draw.rect(screen, WHITE, (x, y, width, height), 1)
            if col != 0:
                pygame.draw.rect(screen, RED, (x, y, width, height))
                # text = font.render(str(col), True, WHITE, None)
                # textRec = text.get_rect()
                # textRec.center = (x + width/1.5, y + height/1.5);
                # screen.blit(text, textRec)
                drawText(screen, col, x + width/1.5, y + height/1.5, font, WHITE, None)
            x = x + width
        y = y + height
        x = 0

    manager.draw_ui(screen)
    manager.update(time_delta)
    
pygame.quit()
quit()
