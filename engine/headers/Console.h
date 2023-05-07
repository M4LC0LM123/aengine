#pragma once
#define GUI_LAYOUT_NAME_IMPLEMENTATION
#include "raylib.h"

class Console;

struct CommandEntry
{
    const char* command;
    void (*function)(Console*);
};

class Console
{
    public:
        int opened;
        int bind = KEY_GRAVE;
        CommandEntry commands[256];
        bool CommandEntryEditMode = false;
        char CommandEntryText[128] = "";
        bool ConsoleOutputEditMode = false;
        char ConsoleOutputText[128] = "DEVELOPER CONSOLE";

        Console();
        void update();
        void render();
        bool isActive();
        void addCommand(CommandEntry commandEntry, int value);
        void submitButton();

    private:
        char* m_endOfOutputText = nullptr;
};