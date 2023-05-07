#include "headers/Console.h"
#include "headers/Commands.h"

Console::Console() 
{
    this->opened = 1;
    this->commands[0] = {"echo", CommandEcho};
    this->commands[1] = {"set_res", CommandResolution};
    this->commands[2] = {"debug_mode", CommandDebugMode};
    this->commands[3] = {"bind", CommandBind};
    this->commands[4] = {"close", CommandClose};
    this->commands[5] = {"set_fps", CommandFPS};
    this->commands[6] = {"set_bloom", SetGlobalBloom};
    this->commands[7] = {"print_entity", CommandPrintEntityVector};
    this->commands[8] = {"set_fullscreen", CommandFullScreen};
}

void Console::update()
{
    this->ConsoleOutputEditMode = false;
    if (IsKeyPressed(KEY_ENTER) && this->CommandEntryEditMode)
    {
        for (int i = 0; this->commands[i].command != NULL; i++)
        {
            if (strncmp(this->commands[i].command, this->CommandEntryText, strlen(this->commands[i].command)) == 0)
            {
                // Execute the command function
                this->commands[i].function(this);
                return;
            }
        }

        std::string err = "Command not \"" + std::string(this->CommandEntryText) + "\" found"; 
        strcpy(this->ConsoleOutputText, err.c_str());
        this->CommandEntryText[0] = '\0';

        this->CommandEntryEditMode = true;
    }

    if (this->opened % 2 == 0)
    {
        if (IsKeyPressed(KEY_ESCAPE))
        {
            this->opened++;
        }
    }
}

void Console::render()
{
    if (IsKeyPressed(bind))
    {
        this->opened++;
        if (this->opened % 2 == 0)
        {
            this->CommandEntryEditMode = true;
        }
        else 
        {
            strcpy(this->CommandEntryText, "");
            strcpy(this->ConsoleOutputText, "DEVELOPER CONSOLE");
        }
    }

    if (this->opened % 2 == 0)
    {
        DrawRectangle(0, GetScreenHeight()-80, 550, 80, {69, 69, 69, 200});
        if (GuiTextBox((Rectangle){ 8, (float)GetScreenHeight()-40, 448, 32 }, this->CommandEntryText, 128, this->CommandEntryEditMode)) this->CommandEntryEditMode = !this->CommandEntryEditMode;
        if (GuiButton((Rectangle){ 464, (float)GetScreenHeight()-40, 80, 32 }, "Submit")) this->submitButton();
        if (GuiTextBox((Rectangle){ 8, (float)GetScreenHeight()-76, 536, 32 }, this->ConsoleOutputText, 128, this->ConsoleOutputEditMode)) this->ConsoleOutputEditMode = !this->ConsoleOutputEditMode;
    }
}

bool Console::isActive()
{
    if (this->opened % 2 == 0)
    {
        return true;
    }
    return false;
}

void Console::addCommand(CommandEntry commandEntry, int value)
{   
    this->commands[5 + value + 1] = commandEntry;
}

void Console::submitButton()
{
    // Find the command function based on the input string
    for (int i = 0; this->commands[i].command != NULL; i++)
    {
        if (strncmp(this->commands[i].command, this->CommandEntryText, strlen(this->commands[i].command)) == 0)
        {
            // Execute the command function
            this->commands[i].function(this);
            return;
        }
    }
    // If no command was found, display an error message
    strcpy(this->ConsoleOutputText, "Command not found");
    this->CommandEntryText[0] = '\0';
}