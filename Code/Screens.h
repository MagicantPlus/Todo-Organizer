#pragma once

#include "UI.h"

std::filesystem::path selectScreen(bool& goMainScreen);
void createDirectoryScreen(std::filesystem::path path);
void createListScreen(std::filesystem::path path);
void deleteItemScreen(std::filesystem::path path);
bool confirmationScreen(std::filesystem::path path);
bool priorityScreen(const TodoListItem& a, const TodoListItem& b);
int mainScreen();
template<class cmpTLI> bool editListScreen(TodoList<cmpTLI>& currentList)
{
    bool quit = false;

    while(!quit)
    {
        
    }
}
