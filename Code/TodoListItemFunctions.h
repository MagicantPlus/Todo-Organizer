#pragma once

#include "TodoListItem.h"
#include <filesystem>
#include <fstream>
#include "Utils.h"

TodoListItem readTodoListItem(std::wifstream& fin)
{
    TodoListItem temp;
    std::wstring name, note;
    bool ticked;
    std::chrono::time_point<std::chrono::system_clock> dateAdded, deadline;
    long long dateAddedNum, deadlineNum;

    fin >> ticked >> name;
    note = listenL(fin);
    note = listenL(fin);
    fin >> dateAddedNum >> deadlineNum;
    
    dateAdded = std::chrono::time_point<std::chrono::system_clock>(std::chrono::milliseconds(dateAddedNum));
    deadline = std::chrono::time_point<std::chrono::system_clock>(std::chrono::milliseconds(deadlineNum));

    temp.setTick(ticked);
    temp.setName(name);
    temp.setNote(note);
    temp.setDateAdded(dateAdded);
    temp.setDeadline(deadline);

    return temp;
}
