#pragma once

#include "TodoListItem.h"
#include <filesystem>
#include <fstream>
#include "Utils.h"

TodoListItem readTodoListItem(std::wifstream& fin);
