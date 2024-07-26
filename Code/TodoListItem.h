#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include "GlobalVariables.h"

class TodoListItem
{
private:
    bool ticked;
    std::wstring name;
    std::wstring note;
    std::chrono::time_point<std::chrono::system_clock> dateAdded, deadline;

public:
    TodoListItem();

    void setName(std::wstring name);
    void setNote(std::wstring note);
    void setTick(bool ticked);
    void setDateAdded(std::chrono::time_point<std::chrono::system_clock> date);
    void setDeadline(std::chrono::time_point<std::chrono::system_clock> date);
    std::wstring getName() const;
    std::wstring getNote() const;
    bool getTick() const;
    std::chrono::time_point<std::chrono::system_clock> getDateAdded() const;
    std::chrono::time_point<std::chrono::system_clock> getDeadline() const;

    void switchTick();
    void operator=(TodoListItem item);
    bool operator==(const TodoListItem x) const;
};
