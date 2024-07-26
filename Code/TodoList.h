#pragma once

#include <iostream>
#include <filesystem>
#include "TodoListItem.h"
#include <map>
#include <fstream>
#include "TodoListItemFunctions.h"

template<class cmpTodoListItem> class TodoList
{
private:
    std::filesystem::path listPath;
    std::vector<TodoListItem> itemList;
    int position;

public:
    TodoList();
    void setPath(std::filesystem::path path);
    void genItemList();
    std::filesystem::path getPath();
    std::vector<TodoListItem> getItemList() const;

    void add(TodoListItem item);
    void remove(std::wstring itemName);
    void updatePriority(std::wstring itemName);
    void switchTick(std::wstring itemName);

    void updateList();

    void writeToFile(std::filesystem::path path);
};

template<class cmpTodoListItem> TodoList<cmpTodoListItem>::TodoList()
{

}
template<class cmpTodoListItem> void TodoList<cmpTodoListItem>::setPath(std::filesystem::path path)
{
    this->listPath = path;
}
template<class cmpTodoListItem> void TodoList<cmpTodoListItem>::genItemList()
{
    std::wifstream fin(this->listPath);
    TodoListItem item;
    int n;

    fin >> n;

    for (int i = 1; i <= n; i++)
    {
        item = readTodoListItem(fin);
        this->itemList.push_back(item);
    }
}
template<class cmpTodoListItem> std::filesystem::path TodoList<cmpTodoListItem>::getPath()
{
    return this->listPath;
}
template<class cmpTodoListItem> std::vector<TodoListItem> TodoList<cmpTodoListItem>::getItemList() const
{
    return this->itemList;
}
template<class cmpTodoListItem> void TodoList<cmpTodoListItem>::add(TodoListItem item)
{
    int left = 0, right = this->itemList.size(), middle, pos = left;
    cmpTodoListItem prio;

    while(left <= right)
    {
        middle = (left + right) / 2;

        if(middle == this->itemList.size())
        {
            pos = middle;
            break;
        }

        if(prio(item, this->itemList[middle]))
        {
            pos = middle;
            right = middle - 1;
        }
        else
        {
            left = middle + 1;
        }
    }

    if(pos == this->itemList.size())
    {
        this->itemList.push_back(item);
    }
    else
    {
        this->itemList.insert(this->itemList.begin() + pos, item);
    }
}
template<class cmpTodoListItem> void TodoList<cmpTodoListItem>::remove(std::wstring itemName)
{
    for (auto it = this->itemList.begin(); it != this->itemList.end(); it++)
    {
        if ((*it).getName() == itemName)
        {
            this->itemList.erase(it);
            break;
        }
    }
}
template<class cmpTodoListItem> void TodoList<cmpTodoListItem>::updatePriority(std::wstring itemName)
{
    TodoListItem temp;

    for (auto it = this->itemList.begin(); it != this->itemList.end(); it++)
    {
        if ((*it).getName() == itemName)
        {
            temp = *it;
            this->itemList.erase(it);
            break;
        }
    }

    this->add(temp);
}
template<class cmpTodoListItem> void TodoList<cmpTodoListItem>::switchTick(std::wstring itemName)
{
    for (auto it = this->itemList.begin(); it != this->itemList.end(); it++)
    {
        if ((*it).getName() == itemName)
        {
            (*it).switchTick();
            break;
        }
    }
}
template<class cmpTodoListItem> void TodoList<cmpTodoListItem>::updateList()
{
    std::vector<TodoListItem> itemListCopy = this->itemList;

    this->itemList.clear();

    for(auto item : itemListCopy)
    {
        this->add(item);
    }
}
template <class cmpTodoListItem> void TodoList<cmpTodoListItem>::writeToFile(std::filesystem::path path)
{
    std::wofstream fout(path);

    fout << this->itemList.size() << '\n';

    for(auto item : this->itemList)
    {
        fout << item.getTick() << ' ' << item.getName() << '\n';
        fout << item.getNote() << '\n';

        auto timePoint = item.getDateAdded();
        auto epoch = timePoint.time_since_epoch();
        auto aux = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);

        fout << aux.count() << ' ';

        timePoint = item.getDeadline();
        epoch = timePoint.time_since_epoch();
        aux = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);

        fout << aux.count() << '\n';
    }
}
