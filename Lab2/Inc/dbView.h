#pragma once
#include <iostream>
#include <string>
#include <iomanip>

namespace View
{
    class dbView
    {
    private:
       public:
        dbView();
        ~dbView();

        /* ---------- UI ---------- */

        /* Show main menu */
        void showMenuMain(void);
        /* Show what user chose in menu */
        void showMenuDBOperations(const int _ch);
        /* Show text for search options */
        void showSearchOptions(void);

        /* ------- Show variables ------- */

        /* Show string in console */
        void showString(const std::string _str);
        /* Show vector contents in console */
        void showList(const std::vector<std::string> _lst);
        /* Show 2-d vector contents in console */
        void showTableContents(const std::vector<std::vector<std::string>> _lst1, const std::vector<std::string> _lst2);

        /* -------- User Interaction -------- */
        /* Get string input from user */
        std::string getString(void);
        /* Get int input from user */
        int getInput(void);
        /* Get int input from user in menu */
        int getInputMenu(void);
    };
};