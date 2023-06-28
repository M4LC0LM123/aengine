import pygame
import pygame_gui
from drawText import *
import tkinter as tk
from tkinter import filedialog
from saveTileMap import *
from loadTileMap import *
from object import Object
from saveScene import *
from loadScene import *

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

objects = []

x = 0
y = 0
gridOriginX = 0
gridOriginY = 0
width = 70
height = 70
tileValue = 1
fontsize = 32

mouseX, mouseY = pygame.mouse.get_pos()
mousePressed = False
mouse2Pressed = False

mxv, myv = False, False

panelX = SCREEN_WIDTH - 125
panelY = 10
panel = pygame.Rect(panelX, panelY, 120, 500)

manager = pygame_gui.UIManager((SCREEN_WIDTH, SCREEN_HEIGHT), "../themes/theme.json")
save = pygame_gui.elements.UIButton(relative_rect = pygame.Rect((panelX, panelY), (120, 50)), text = "save", manager = manager)
load = pygame_gui.elements.UIButton(relative_rect = pygame.Rect((panelX, panelY + 50), (120, 50)), text = "load", manager = manager)
gWidthText = pygame_gui.elements.UILabel(relative_rect = pygame.Rect((panelX - 15, panelY + 75 + 12), (120, 50)), text = "grid width", manager = manager)
gWidth = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((panelX, panelY + 125), (120, 25)), manager = manager)
gHeightText = pygame_gui.elements.UILabel(relative_rect = pygame.Rect((panelX - 12.5, panelY + 125 + 12), (120, 50)), text = "grid height", manager = manager)
gHeight = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((panelX, panelY + 175), (120, 25)), manager = manager)
clearBtn = pygame_gui.elements.UIButton(relative_rect = pygame.Rect((panelX, panelY + 200), (120, 50)), text = "clear", manager = manager)
tileValueText = pygame_gui.elements.UILabel(relative_rect = pygame.Rect((panelX - 10, panelY + 225 + 12), (120, 50)), text = "object index", manager = manager)
tileValueInput = pygame_gui.elements.UITextEntryLine(relative_rect = pygame.Rect((panelX, panelY + 275), (120, 25)), manager = manager)
modeBtn = pygame_gui.elements.UIButton(relative_rect = pygame.Rect((panelX, panelY + 300), (120, 50)), text = "edit mode", manager = manager)
selectBtn = pygame_gui.elements.UIButton(relative_rect = pygame.Rect((panelX, panelY + 375), (120, 50)), text = "select mode", manager = manager)

font = pygame.font.Font("../fonts/CascadiaMono.ttf", fontsize)

isTileMap = True
selectMode = False

running = True
while running:
    time_delta = clock.tick(60)/1000.0
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        keys = pygame.key.get_pressed()
        
        if keys[pygame.K_LEFT]:
            gridOriginX -= 50
        if keys[pygame.K_RIGHT]:
            gridOriginX += 50
        if keys[pygame.K_UP]:
            gridOriginY -= 50
        if keys[pygame.K_DOWN]:
            gridOriginY += 50

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

        # if mousePressed and mouseX < (width * gridWidth) and mouseY < (height * gridHeight):
        #     grid[int(mouseY/height)][int(mouseX/width)] = tileValue
        # if mouse2Pressed and mouseX < (width * gridWidth) and mouseY < (height * gridHeight):
        #     grid[int(mouseY/height)][int(mouseX/width)] = 0

        if mousePressed and mouseX < (gridOriginX + (width * gridWidth)) and mouseY < (gridOriginY + (height * gridHeight)) and mouseX >= gridOriginX and mouseY >= gridOriginY:
            mxv = True

            if not selectMode:
                if isTileMap:
                    grid[int((mouseY - gridOriginY)/height)][int((mouseX - gridOriginX)/width)] = tileValue
                else:
                    objects.append(Object(mouseX - gridOriginX - width/2, mouseY - gridOriginY - height/2, 0, width, height, 0, 0, 0, 0, tileValue))
            else:
                for obj in objects:
                    if obj.projRec(gridOriginX, gridOriginY).collidepoint(mouseX, mouseY):
                        obj.selected = True
                    else:
                        obj.selected = False

                    if obj.selected:
                        obj.x = mouseX - obj.width/2
                        obj.y = mouseY - obj.height/2
        else:
            mxv = False
        if mouse2Pressed and mouseX < (gridOriginX + (width * gridWidth)) and mouseY < (gridOriginY + (height * gridHeight)) and mouseX >= gridOriginX and mouseY >= gridOriginY:
            myv = True
            if isTileMap: grid[int((mouseY - gridOriginY)/height)][int((mouseX - gridOriginX)/width)] = 0
            else:
                for obj in objects:
                    if obj.projRec(gridOriginX, gridOriginY).collidepoint(mouseX, mouseY):
                        objects.remove(obj)
        else:
            myv = False

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
                if isTileMap: grid = [ [0] * gridWidth for n in range(gridHeight)]
                else: objects.clear()
            if event.ui_element == save:
                root = tk.Tk()
                root.withdraw()
                path = filedialog.askopenfilename()
                if isTileMap: saveTileMap(grid, path)
                else: saveScene(objects, path)
            if event.ui_element == load:
                root = tk.Tk()
                root.withdraw()
                path = filedialog.askopenfilename()
                if isTileMap: grid = loadTileMap(path)
                else: objects = loadScene(path)
            if event.ui_element == modeBtn:
                isTileMap = not isTileMap
            if event.ui_element == selectBtn:
                selectMode = not selectMode

        mouseX, mouseY = pygame.mouse.get_pos()

        manager.process_events(event)

    pygame.display.update()
    clock.tick(60)

    screen.fill("#282C34")

    if isTileMap:
        y = gridOriginY
        for row in grid:
            for col in row:
                pygame.draw.rect(screen, WHITE, (x, y, width, height), 1)
                if col != 0:
                    pygame.draw.rect(screen, RED, (x, y, width, height))
                    drawText(screen, col, x + width/1.5, y + height/1.5, font, WHITE, None)
                x = x + width
            y = y + height
            x = gridOriginX
    else:
        for obj in objects:
            obj.width = width
            obj.height = height
            obj.render(screen, RED, gridOriginX, gridOriginY)


    pygame.draw.rect(screen, GREEN, (gridOriginX, gridOriginY, gridWidth * width, gridHeight * height), 1)

    pygame.draw.rect(screen, "#32628A", panel)

    if isTileMap:
        drawText(screen, "Mode: TileMap", panelX + 55, panelY + 365, pygame.font.Font("../fonts/CascadiaMono.ttf", 14), BLACK, None)
    else:
        drawText(screen, "Mode: Scene", panelX + 55, panelY + 365, pygame.font.Font("../fonts/CascadiaMono.ttf", 14), BLACK, None)

    if selectMode:
        drawText(screen, "Mode: Select", panelX + 55, panelY + 365 + 75, pygame.font.Font("../fonts/CascadiaMono.ttf", 14), BLACK, None)
    else:
        drawText(screen, "Mode: Place", panelX + 55, panelY + 365 + 75, pygame.font.Font("../fonts/CascadiaMono.ttf", 14), BLACK, None)

    manager.draw_ui(screen)
    manager.update(time_delta)
    
pygame.quit()
quit()
