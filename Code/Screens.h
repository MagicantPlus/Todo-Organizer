#pragma once

#include "UI.h"

std::filesystem::path selectScreen(bool& goback);
void createDirectoryScreen(std::filesystem::path path);
void createListScreen(std::filesystem::path path);
void deleteItemScreen(std::filesystem::path path);
bool confirmationScreen(std::filesystem::path path);
bool priorityScreen(const TodoListItem& a, const TodoListItem& b);
int mainScreen();
