#pragma once
#include "string.h"
#include "engine.h"
#include "Console.h"
#include "engine.h"

void CommandEcho(Console* console)
{
    // Get the argument string after the "echo" command
    char *arg = console->CommandEntryText + strlen("echo");
    // Trim whitespace at the beginning of the argument string
    while (strcmp(arg, " ") == 0)
    {
        arg++;
    }
    // Copy the argument string to the console output
    strcpy(console->ConsoleOutputText, arg);
    console->CommandEntryText[0] = '\0';
}

void CommandResolution(Console* console)
{
    int w;
    int h;
    if (sscanf(console->CommandEntryText, "set_res %i %i", &w, &h) == 2)
    {
        SetWindowSize(w, h);
        strcpy(console->ConsoleOutputText, "Set window resolution!");
        console->CommandEntryText[0] = '\0';
    }
}

void CommandFullScreen(Console* console)
{
    if (strcmp(console->CommandEntryText, "set_fullscreen") == 0)
    {
        ToggleFullscreen();
        
        if (IsWindowFullscreen())
        {
            strcpy(console->ConsoleOutputText, "set fullscreen");
        }
        else
        {
            strcpy(console->ConsoleOutputText, "set minimized");
        }
        console->CommandEntryText[0] = '\0';
    }
}

void CommandDebugMode(Console* console)
{
    int dm;
    if (sscanf(console->CommandEntryText, "debug_mode %i", &dm) == 1)
    {
        if (dm == 1)
        {
            Debug::mode(true);
            strcpy(console->ConsoleOutputText, "Debug mode on");
            console->CommandEntryText[0] = '\0';
        }
        else if (dm == 0)
        {
            Debug::mode(false);
            strcpy(console->ConsoleOutputText, "Debug mode off");
            console->CommandEntryText[0] = '\0';
        }
        else
        {
            strcpy(console->ConsoleOutputText, "Invalid usage of command 'debug mode' ");
            console->CommandEntryText[0] = '\0';
        }
    }
}

void CommandBind(Console* console)
{
    int bind;
    if (sscanf(console->CommandEntryText, "bind %i", &bind) == 1)
    {
        console->bind = bind;
    }
}

void CommandClose(Console* console)
{
    if (strcmp(console->CommandEntryText, "close") == 0)
    {
        EntityManager::dispose();
        CloseWindow();
    }
}

void CommandFPS(Console* console)
{
    int targetFPS;
    if (sscanf(console->CommandEntryText, "set_fps %i", &targetFPS) == 1)
    {
        SetTargetFPS(targetFPS);
        strcpy(console->ConsoleOutputText, "Set fps");
        console->CommandEntryText[0] = '\0';
    }
}

void SetGlobalBloom(Console* console)
{
    int targetBloom;
    if (sscanf(console->CommandEntryText, "set_bloom %i", &targetBloom) == 1)
    {
        BLOOM_INTENSITY = targetBloom;
        strcpy(console->ConsoleOutputText, "Set bloom intesity");
        console->CommandEntryText[0] = '\0';
        for (Entity* entity : EntityManager::entities)
        {
            entity->resetBloom();
        }   
    }
}

void CommandPrintEntityVector(Console* console)
{
    if (strcmp(console->CommandEntryText, "print_entity") == 0)
    {
        for (int i = 0; i < (int) EntityManager::entities.size(); i++)
        {
            std::cout << EntityManager::entities[i]->getZ() << "\n";
        }
        strcpy(console->ConsoleOutputText, "Printed the list of entities");
        console->CommandEntryText[0] = '\0';
    }
}