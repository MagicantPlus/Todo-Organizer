#include "TodoListItem.h"

TodoListItem::TodoListItem()
{

}
void TodoListItem::setName(std::wstring name)
{
    this->name = name;
}
void TodoListItem::setNote(std::wstring note)
{
    this->note = note;
}
void TodoListItem::setTick(bool ticked)
{
    this->ticked = ticked;
}
std::wstring TodoListItem::getName() const
{
    return this->name;
}
std::wstring TodoListItem::getNote() const
{
    return this->note;
}
bool TodoListItem::getTick() const
{
    return this->ticked;
}
void TodoListItem::switchTick()
{
    this->ticked = !this->ticked;
}
void TodoListItem::setDateAdded(std::chrono::time_point<std::chrono::system_clock> date)
{
    this->dateAdded = date;
}
void TodoListItem::setDeadline(std::chrono::time_point<std::chrono::system_clock> date)
{
    this->deadline = date;
}
std::chrono::time_point<std::chrono::system_clock> TodoListItem::getDateAdded() const
{
    return this->dateAdded;
}
std::chrono::time_point<std::chrono::system_clock> TodoListItem::getDeadline() const
{
    return this->deadline;
}
void TodoListItem::operator=(TodoListItem item)
{
    this->setName(item.getName());
    this->setNote(item.getNote());
    this->setTick(item.getTick());
    this->setDateAdded(item.getDateAdded());
    this->setDeadline(item.getDeadline());
}
bool TodoListItem::operator==(const TodoListItem x) const
{
    return (this->name == x.getName()) && (this->note == x.getNote())
    && (this->deadline == x.getDeadline()) && (this->dateAdded == x.getDateAdded()) && (this->ticked == x.getTick());
}
