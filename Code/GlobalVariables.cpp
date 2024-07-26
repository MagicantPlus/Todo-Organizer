#include "GlobalVariables.h"

//ANSI Codes
extern const std::wstring RED = L"\033[1;31m";
extern const std::wstring GREEN = L"\033[1;32m";
extern const std::wstring YELLOW = L"\033[1;33m";
extern const std::wstring BLUE = L"\033[1;34m";
extern const std::wstring RESET = L"\033[0m";

extern const std::filesystem::path START_PATH = std::filesystem::path("..");
extern const std::filesystem::path BACKUP_PATH = std::filesystem::path("../Backups");
extern const int CONFIRMATION_STAGES = 2;
