#pragma once
#include <iostream>
#include <unordered_map>
#include "dbModel.h"
#include "dbView.h"

namespace MenuAct
{
    enum userAction : int
    {
        MENU_INSERT = 1,
        MENU_REMOVE,
        MENU_EDIT,
        MENU_RAND,
        MENU_SEARCH,
        MENU_SHOWTABLE,
        MENU_TERMINATE,
        MENU_DEFAULT
    };
};

namespace Controller
{
    class dbController
    {
    private:
        /* View object pointer */
        View::dbView *viewObj;
        /* Model object pointer */
        Model::dbModel *modObj;

    public:
        dbController(/* args */);
        dbController(Model::dbModel *_mdl, View::dbView *_vw);
        ~dbController();

        /* Menu choice function */
        int menuChoiceHandler(void);
        /* Table choice function */
        int tableChoiceHandler(void);
        /* Define datatypes that were recieved for database */
        void concatDataType(std::string *_str, int _iter);

        /* ------- Logic steps ------- */

        /* In this step you establish connection with database */
        void logicEstablishConnection(void);
        /* In this step you choose what operation will be executed with database */
        void logicMenu(void);
        /* In this step the chosen operation will be executed with database */
        void logicDBOperation(void);

        /* -------- Database operations -------- */

        /* Perform data insert in database */
        void operationDataInsert(void);
        /* Perform data deletion in database */
        void operationDataDelete(void);
        /* Perform random data insert in database */
        void operationDataInsertRandom(void);
        /* Perform data edit in database */
        void operationDataEdit(void);
        /* Perform data search in database */
        void operationDataSearch(void);
        /* Perform data show in database */
        void operationDataShow(void);
        /* Perform disconnection from database */
        void operationTerminateConnection(void);
    };

};