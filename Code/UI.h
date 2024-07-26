#pragma once

#include <filesystem>
#include <string>
#include "GlobalVariables.h"
#include "TodoListItem.h"
#include "Utils.h"

void print(std::wstring text, std::wstring color = RESET);
void clearscreen();
void printLogo();
void printSelectScreen(std::filesystem::path& path, bool valid);
void printDirectories(std::filesystem::path& path);
void printMainScreen(bool valid);
void printCreateDirectoryScreen(int mode);
void printCreateListScreen(int mode);
void printDeleteItemScreen(std::filesystem::path path, int mode);
void printConfirmationScreen(int stage, int mode, std::filesystem::path path);
void printPriorityScreen(const TodoListItem& a, const TodoListItem& b, int mode);
