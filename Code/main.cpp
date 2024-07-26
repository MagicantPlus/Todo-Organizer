// TODO: 
// Create: command to return from selected list

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <stdio.h>
#include <string>
#include <filesystem>
#include <fcntl.h>
#include <io.h>
#include <Windows.h>
#include <codecvt>
#include <locale>
#include "GlobalVariables.h"
#include "UI.h"
#include "Screens.h"
#include <unordered_map>
#include "TodoList.h"
#include <utility>

class cmpTLI
{
public:
    bool operator()(const TodoListItem& a, const TodoListItem& b) const
    {
        return priorityScreen(a, b);
    }
};

int main()
{
    // init();

    int mainScreenMode = 69;
    bool goMainScreen = true, goSelectScreen = false;
    std::filesystem::path chosenPath;

    bool quitAfterEdit = 0;

    while(!quitAfterEdit)
    {   
        while(goMainScreen)
        {   
            if(!goSelectScreen)
                mainScreenMode = mainScreen();

            if(mainScreenMode == -1)
                return 0;
            
            chosenPath = selectScreen(goMainScreen);
            
            if(goMainScreen)
                goSelectScreen = false;
        }

        TodoList<cmpTLI> currentList;

        currentList.setPath(chosenPath);
        currentList.genItemList();

        quitAfterEdit = editListScreen(currentList);

        std::filesystem::path savePath = BACKUP_PATH / currentList.getPath().stem();
        savePath += ".backup";

        currentList.writeToFile(savePath);
        currentList.writeToFile(chosenPath);

        goSelectScreen = true;
    }

    return 0;
}
