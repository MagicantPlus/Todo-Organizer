#include "Utils.h"

#include <string>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <fstream>
#include <chrono>
#include <sstream>
#include <iomanip>

void init()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    // SetConsoleOutputCP(CP_UTF8);
}
std::wstring listenL()
{
    std::wstring input;

    std::getline(std::wcin, input);

    return input;
}
std::wstring listenL(std::wifstream& fin)
{
    std::wstring input;

    std::getline(fin, input);

    return input;
}
bool invalidName(std::wstring input)
{
    if (input.size() == 0)
        return true;

    if (input[0] == L'.' || input == L"-1" || input == L"0" || input == L"1" || input == L"2" || input == L"3" || input[0] == L'/' || input[0] == L'\\'
        || input[0] == '$')
    {
        return true;
    }

    return false;
}
std::wstring time_point_to_iso8601(const std::chrono::system_clock::time_point& tp) {

    std::time_t time = std::chrono::system_clock::to_time_t(tp);
    
    std::tm tm;

    localtime_s(&tm, &time);
    
    std::wostringstream woss;
    woss << std::put_time(&tm, L"%Y-%m-%dT%H:%M:%SZ"); // ISO 8601 format

    return woss.str();
}
