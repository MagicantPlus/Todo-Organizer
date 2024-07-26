// TODO: 
// Create: command to return

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

// struct tliHash
// {
//     long long operator()(const TodoListItem& x) const
//     {
//         std::hash<std::wstring> has;

//         return has(x.getName());
//     }
// };

// class cmpTLI
// {
// private:
//     solveNoopFunc solveNoop;
//     std::unordered_map<TodoListItem, std::unordered_map<TodoListItem, int, tliHash>, tliHash> checked;

// public:
//     bool operator()(const TodoListItem& a, const TodoListItem& b)
//     {
//         TodoListItem aCopy = a, bCopy = b;

//         if(a.getPriority() == -1 || b.getPriority() == -1)
//         {
//             int verdict = checked[aCopy][bCopy];

//             if(verdict == 0)
//             {
//                 verdict = solveNoop(a, b);
//             }
//             else if(verdict == -1)
//             {
//                 verdict = 0;
//             }

//             return verdict;
//         }

//         return a.getPriority() < b.getPriority();
//     }
// };

int main()
{
    init();

    int mainScreenMode;
    bool goback = true;
    std::filesystem::path chosenPath;

    while(goback)
    {
        mainScreenMode = mainScreen();

        if(mainScreenMode == -1)
            return 0;
        
        chosenPath = selectScreen(goback);
    }

    // chosenPath = selectScreen(goback);
    
    TodoList<cmpTLI> currentList;

    currentList.setPath(chosenPath);
    currentList.genItemList();

    currentList.updateList();

    std::filesystem::path savePath = BACKUP_PATH / currentList.getPath().stem();
    savePath += ".backup";

    currentList.writeToFile(savePath);
    currentList.writeToFile(chosenPath);

    return 0;
}
