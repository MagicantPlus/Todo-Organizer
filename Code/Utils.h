#pragma once

#include <string>
#include <chrono>

void init();
std::wstring listenL();
std::wstring listenL(std::wifstream& fin);
bool invalidName(std::wstring input);
std::wstring time_point_to_iso8601(const std::chrono::system_clock::time_point tp);
