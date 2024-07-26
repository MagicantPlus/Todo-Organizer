#pragma once

#include <string>

void init();
std::wstring listenL();
std::wstring listenL(std::wifstream& fin);
bool invalidName(std::wstring input);
