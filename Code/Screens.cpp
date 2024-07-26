#include "Screens.h"
#include <fstream>

std::filesystem::path selectScreen(bool& goMainScreen)
{
    bool quit = false, validInput = true;
    std::wstring input;
    std::filesystem::path path(START_PATH);

    while (!quit)
    {
        printSelectScreen(path, validInput);
        input = listenL();

        validInput = false;

        if (input == L"-1")
        {
            validInput = true;

            exit(0);
        }
        else if (input == L"0")
        {
            validInput = true;
            goMainScreen = true;
            return path;
        }
        else if (input == L"..")
        {
            validInput = true;

            if (path != START_PATH)
            {
                path = path.parent_path();
            }
        }
        else if (input == L"1")
        {
            validInput = true;

            createDirectoryScreen(path);
        }
        else if (input == L"2")
        {
            validInput = true;

            createListScreen(path);
        }
        else if (input == L"3")
        {
            validInput = true;

            deleteItemScreen(path);
        }
        else if (invalidName(input))
        {
            validInput = false;
        }
        else
        {
            for (auto& entry : std::filesystem::directory_iterator(path))
            {
                if (entry.path().stem().wstring() == input)
                {
                    if (entry.is_regular_file())
                        quit = true;

                    path = entry.path();
                    validInput = true;
                    break;
                }
            }
        }
    }

    goMainScreen = false;
    return path;
}
void createDirectoryScreen(std::filesystem::path path)
{
    bool quit = false;
    int mode = 0;
    std::wstring input;
    std::filesystem::path temp;

    while (!quit)
    {
        printCreateDirectoryScreen(mode);
        input = listenL();
        temp = path;

        mode = 0;

        if (input == L"0")
        {
            quit = true;
            mode = -1;
        }
        else if (invalidName(input))
        {
            mode = 1;
        }
        else if (std::filesystem::exists(temp.append(input)))
        {
            mode = 2;
        }

        if (mode == 0)
        {
            quit = true;

            path.append(input);
            std::filesystem::create_directory(path);
        }
    }
}
void createListScreen(std::filesystem::path path)
{
    bool quit = false;
    int mode = 0;
    std::wstring input;
    std::filesystem::path temp;

    while (!quit)
    {
        printCreateListScreen(mode);
        input = listenL();
        temp = path;

        mode = 0;

        if (input == L"0")
        {
            quit = true;
            mode = -1;
        }
        else if (invalidName(input))
        {
            mode = 1;
        }
        else if (std::filesystem::exists(temp.append(input)))
        {
            mode = 2;
        }

        if (mode == 0)
        {
            quit = true;

            path.append(input);

            std::ofstream outfile(path.wstring() + L".txt");
        }
    }
}
void deleteItemScreen(std::filesystem::path path)
{
    bool quit = false, confirmed;
    int mode = 0;
    std::wstring input;
    std::filesystem::path temp;

    while (!quit)
    {
        printDeleteItemScreen(path, mode);
        input = listenL();
        temp = path;

        mode = 0;
        confirmed = false;

        if (input == L"0")
        {
            quit = true;
        }
        else if (invalidName(input))
        {
            mode = 1;
        }
        else if (!std::filesystem::exists(temp.append(input + L".txt")) && !std::filesystem::exists(temp.replace_extension()))
        {
            mode = 2;
        }
        else
        {
            temp = path;

            if (!std::filesystem::exists(temp.append(input + L".txt")))
                temp.replace_extension();

            confirmed = confirmationScreen(temp);

            if (!confirmed)
                continue;

            quit = true;

            if (temp.extension().wstring() == L"")
                std::filesystem::remove_all(temp);
            else
                std::filesystem::remove(temp);
        }
    }
}
bool confirmationScreen(std::filesystem::path path)
{
    std::wstring input;
    bool quit = false, verdict = false;
    int mode = 0, stage = 0;

    while (!quit)
    {
        printConfirmationScreen(stage, mode, path);
        input = listenL();
        std::transform(input.begin(), input.end(), input.begin(), [](wchar_t& c)
            {
                return std::tolower(c, std::locale());
            });

        mode = 0;

        if (input == L"no")
        {
            quit = true;
            verdict = false;
        }
        else if (input == L"yes")
        {
            stage++;

            if (stage >= CONFIRMATION_STAGES)
            {
                quit = true;
                verdict = true;
            }

        }
        else
        {
            mode = 1;
        }
    }

    return verdict;
}
bool priorityScreen(const TodoListItem& a, const TodoListItem& b)
{
    bool quit = false, verdict;
    int mode = 0;

    while (!quit)
    {
        printPriorityScreen(a, b, mode);

        mode = 0;

        std::wstring input = listenL();

        std::transform(input.begin(), input.end(), input.begin(), [](const wchar_t& a)
            {
                return std::tolower(a);
            });

        if (input == L"yes")
        {
            quit = true;
            verdict = true;
        }
        else if (input == L"no")
        {
            quit = true;
            verdict = false;
        }
        else
        {
            mode = 1;
        }
    }

    return verdict;
}
int mainScreen()
{
    std::wstring input;
    bool valid = true;

    while (true)
    {
        printMainScreen(valid);
        input = listenL();

        valid = true;

        if (input == L"-1")
        {
            return -1;
        }
        else if (input == L"0")
        {
            return 0;
        }
        else
        {
            valid = false;
        }
    }
}
