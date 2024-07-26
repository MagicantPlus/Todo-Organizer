#include "UI.h"
#include <set>

void print(std::wstring text, std::wstring color)
{
    std::wcout << color << text << RESET;
}
void clearscreen()
{
    system("cls");
}
void printLogo()
{
    // std::wcout << "\n\n\n";
    print(L"\n\n\n");

    //     std::wcout << R"(  _______        _          ____                        _              
    //  |__   __|      | |        / __ \                      (_)             
    //     | | ___   __| | ___   | |  | |_ __ __ _  __ _ _ __  _ _______ _ __ 
    //     | |/ _ \ / _` |/ _ \  | |  | | '__/ _` |/ _` | '_ \| |_  / _ \ '__|
    //     | | (_) | (_| | (_) | | |__| | | | (_| | (_| | | | | |/ /  __/ |   
    //     |_|\___/ \__,_|\___/   \____/|_|  \__, |\__,_|_| |_|_/___\___|_|   
    //                                        __/ |                           
    //                                       |___/                            )" << "\n\n\n\n";

    print(LR"(  _______        _          ____                        _              
 |__   __|      | |        / __ \                      (_)             
    | | ___   __| | ___   | |  | |_ __ __ _  __ _ _ __  _ _______ _ __ 
    | |/ _ \ / _` |/ _ \  | |  | | '__/ _` |/ _` | '_ \| |_  / _ \ '__|
    | | (_) | (_| | (_) | | |__| | | | (_| | (_| | | | | |/ /  __/ |   
    |_|\___/ \__,_|\___/   \____/|_|  \__, |\__,_|_| |_|_/___\___|_|   
                                       __/ |                           
                                      |___/                            )", BLUE);
    print(L"\n\n\n\n");
}
void printSelectScreen(std::filesystem::path& path, bool valid)
{
    clearscreen();
    printLogo();
    printDirectories(path);

    // std::wcout << L'\n';
    print(L"\n");

    if (!valid)
    {
        // std::wcout << L"INVALID INPUT\n";
        print(L"INVALID INPUT\n");
    }

    // std::wcout << L"-1 = ";
    print(L"-1 = ");
    print(L"Quit\n", RED);
    print(L"0 = ");
    print(L"Go to main screen\n", YELLOW);
    print(L"1 = ");
    print(L"Create folder\n", YELLOW);
    print(L"2 = ");
    print(L"Create Todo List\n", YELLOW);
    print(L"3 = ");
    print(L"Delete item\n", YELLOW);
    print(L".. = ");
    print(L"Back\n", YELLOW);

    // std::wcout << L"Type the name of the folder, file or command: ";
    print(L"Type the name of the folder, file or command: ");
}
void printDirectories(std::filesystem::path& path)
{
    struct dircmp
    {
        bool operator()(const std::filesystem::directory_entry& a, const std::filesystem::directory_entry& b) const
        {
            bool adir = a.is_directory(), bdir = b.is_directory();

            if (adir != bdir)
            {
                return adir > bdir;
            }

            return a.path() < b.path();
        }
    };

    std::set<std::filesystem::directory_entry, dircmp> sortedEntries;

    for (auto& entry : std::filesystem::directory_iterator(path))
    {
        sortedEntries.insert(entry);
    }

    if (sortedEntries.size() == 0)
    {
        print(L"[ Folder Empty! ]\n", GREEN);
        return;
    }

    for (auto& entry : sortedEntries)
    {
        if (entry.is_directory())
        {
            // std::wcout << L"[\xD83D\xDCC1]  ";
            print(L"[\xD83D\xDCC1]  ");
        }
        else
        {
            // std::wcout << L"[\xD83D\xDDCE]  ";
            print(L"[\xD83D\xDDCE]  ");
        }

        // std::wcout << entry.path().filename().wstring() << '\n';
        print(entry.path().stem().wstring() + L"\n");
    }
}
void printMainScreen(bool valid)
{
    clearscreen();
    printLogo();

    print(L"A unqiue way to sort your lists!", BLUE);
    print(L"\n\n");

    if (!valid)
        print(L"INVALID MODE\n");

    print(L"-1 = ");
    print(L"Quit\n", RED);
    print(L"0 = ");
    print(L"Start\n", YELLOW);

    print(L"Select mode: ");
}
void printCreateDirectoryScreen(int mode)
{
    clearscreen();
    printLogo();

    if (mode == 1)
    {
        print(L"INVALID NAME\n");
    }
    else if (mode == 2)
    {
        print(L"NAME ALREADY EXISTS\n");
    }

    print(L"0 = ");
    print(L"Go back\n", YELLOW);
    print(L"Enter folder name: ", GREEN);
}
void printCreateListScreen(int mode)
{
    clearscreen();
    printLogo();

    if (mode == 1)
    {
        print(L"INVALID NAME\n");
    }
    else if (mode == 2)
    {
        print(L"NAME ALREADY EXISTS\n");
    }

    print(L"0 = ");
    print(L"Go back\n", YELLOW);
    print(L"Enter Todo List name: ", GREEN);
}
void printDeleteItemScreen(std::filesystem::path path, int mode)
{
    clearscreen();
    printLogo();
    printDirectories(path);
    print(L"\n");

    if (mode == 1)
    {
        print(L"INVALID NAME\n");
    }
    else if (mode == 2)
    {
        print(L"NAME DOESN'T EXIST\n");
    }

    print(L"0 = ");
    print(L"Go back\n", YELLOW);

    print(L"Delete folder/Todo list with name: ");
}
void printConfirmationScreen(int stage, int mode, std::filesystem::path path)
{
    clearscreen();
    printLogo();

    if (mode == 1)
    {
        print(L"INVALID ANSWER\n");
    }

    if (stage == 0)
    {
        print(L"ARE YOU SURE YOU WANT TO DELETE THIS ITEM?\n");
    }
    else if (stage == 1)
    {
        print(L"ARE YOU DOUBLY, TRIPLY SURE YOU WANT TO DELETE THIS ITEM?\n");
    }

    print(L"THIS ACTION CANNOT BE UNDONE!\n\n", RED);
    print(L"ITEM TO BE DELETED: " + path.replace_extension().wstring() + L"\n\n");
    print(L"Answer (YES/NO): ");
}
void printPriorityScreen(const TodoListItem& a, const TodoListItem& b, int mode)
{
    clearscreen();
    printLogo();

    if (mode == 1)
    {
        print(L"INVALID ANSWER\n");
    }

    print(L"Does \"");
    print(a.getName());
    print(L"\" have ");
    print(L"more priority ", YELLOW);
    print(L"than \"");
    print(b.getName());
    print(L"\"?\n");
    print(L"Answer (YES/NO): ");
}
