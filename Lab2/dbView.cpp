#include "dbView.h"
#include "dbController.h"

using namespace View;

dbView::dbView(void)
{
}

dbView::~dbView(void)
{
}

void dbView::showString(const std::string _str)
{
    std::cout << _str << std::endl;
}

void dbView::showMenuMain(void)
{
    std::cout << std::endl;
    std::cout << "[-------- MAIN MENU --------]" << std::endl;
    std::cout << "[1] Insert data" << std::endl;
    std::cout << "[2] Remove data" << std::endl;
    std::cout << "[3] Edit data" << std::endl;
    std::cout << "[4] Insert random data" << std::endl;
    std::cout << "[5] Search data" << std::endl;
    std::cout << "[6] Show table" << std::endl;
    std::cout << std::endl
              << "[7] Terminate connection" << std::endl;
}

void dbView::showList(const std::vector<std::string> _lst)
{
    for (int i = 0; i < _lst.size(); i++)
    {
        std::cout << "[" << i << "] " << _lst.at(i) << std::endl;
    }
}

std::string dbView::getString(void)
{
    std::string str;
    std::cout << " > ";
    std::getline(std::cin >> std::ws, str);
    return str;
}

int dbView::getInput(void)
{
    int inp = 0;
    std::cout << " > ";
    std::cin >> inp;
    return inp;
}

int dbView::getInputMenu(void)
{
    showMenuMain();
    return getInput();
}

void dbView::showMenuDBOperations(const int _ch)
{
    switch (_ch)
    {
    case MenuAct::MENU_INSERT:
        std::cout << "Your choice was: Insert to database" << std::endl;
        std::cout << "Choose table:" << std::endl;
        break;
    case MenuAct::MENU_REMOVE:
        std::cout << "Your choice was: Remove from database" << std::endl;
        std::cout << "Choose table:" << std::endl;
        break;
    case MenuAct::MENU_EDIT:
        std::cout << "Your choice was: Edit database" << std::endl;
        std::cout << "Choose table:" << std::endl;
        break;
    case MenuAct::MENU_RAND:
        std::cout << "Your choice was: Fill database with random data" << std::endl;
        std::cout << "Choose table:" << std::endl;
        break;
    case MenuAct::MENU_SEARCH:
        std::cout << "Your choice was: Search in database" << std::endl;
        break;
    case MenuAct::MENU_SHOWTABLE:
        std::cout << "Your choice was: Show table" << std::endl;
        std::cout << "Choose table:" << std::endl;
        break;
    case MenuAct::MENU_TERMINATE:
        std::cout << "Your choice was: Terminate Connection" << std::endl;
        break;

    default:
        std::cout << " Wrong action. Try again." << std::endl;
        break;
    }
}

void dbView::showSearchOptions(void)
{
    std::cout << std::endl;
    std::cout << "[1] Search Sessions by date interval" << std::endl;
    std::cout << "[2] Search Sessions by N Status" << std::endl;
    std::cout << "[3] Search Sessions by Client Name" << std::endl;
}

void dbView::showTableContents(const std::vector<std::vector<std::string>> _lst1, const std::vector<std::string> _lst2)
{
    int spaces = 30;

    for (int i = 0; i < _lst2.size(); i++)
    {
        std::cout << std::setw(spaces) << _lst2.at(i);
    }
    std::cout << std::endl
              << std::endl;
    for (int i = 0; i < _lst1.size(); i++)
    {
        for (int j = 0; j < _lst1[i].size(); j++)
        {
            std::cout << std::setw(spaces) << _lst1[i][j];
        }
        std::cout << std::endl;
        for (int k = 0; k < _lst2.size() * spaces; k++)
        {
            if (k > 8)
            {
                std::cout << "-";
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}