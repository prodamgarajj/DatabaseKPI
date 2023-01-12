#include "dbController.h"
using namespace Controller;

dbController::dbController(void)
{
}

dbController::dbController(Model::dbModel *_mdl, View::dbView *_vw)
{
    viewObj = _vw;
    modObj = _mdl;
}

dbController::~dbController(void)
{
}

int dbController::menuChoiceHandler(void)
{
    while (1)
    {
        int input = viewObj->getInputMenu();
        switch (input)
        {
        case MenuAct::MENU_INSERT:
        case MenuAct::MENU_REMOVE:
        case MenuAct::MENU_EDIT:
        case MenuAct::MENU_RAND:
        case MenuAct::MENU_SEARCH:
        case MenuAct::MENU_SHOWTABLE:
        case MenuAct::MENU_TERMINATE:
            return input;
            break;
        default:
            std::cout << " Wrong action. Try again." << std::endl;
            break;
        }
    }

    return MenuAct::MENU_DEFAULT;
}

int dbController::tableChoiceHandler(void)
{
    std::vector<std::string> lst = modObj->getListTables();
    while (1)
    {
        int input = viewObj->getInput();
        if (input >= 0 && input < lst.size())
        {
            return input;
        }
    }
}

void dbController::concatDataType(std::string *_str, int _iter)
{
    switch (modObj->retvalDataType(_iter))
    {
    case 23:
        *_str += "::integer";
        break;
    case 1043:
        *_str += "::character varying";
        break;
    case 1082:
        *_str += "::date";
        break;
    case 1114:
        *_str += "::timestamp without time zone";
        break;
    case 16:
        *_str += "::bool";
        break;
    default:
        break;
    }
}

void dbController::logicEstablishConnection(void)
{
    std::cout << std::endl
              << "\t\t Voitovych Hlib KV-02. DB_LAB_2\n"
              << std::endl
              << std::endl;
    modObj->dbConnect();
}

void dbController::logicMenu(void)
{
    modObj->setMenuChoice(menuChoiceHandler());
}

void dbController::logicDBOperation(void)
{
    /* Show on screen what user choosed */
    viewObj->showMenuDBOperations(modObj->retvalMenuChoice());

    /* Perform action from choice */
    switch (modObj->retvalMenuChoice())
    {
    case MenuAct::MENU_INSERT:
        /* Begin Insert */
        operationDataInsert();
        break;
    case MenuAct::MENU_REMOVE:
        /* Begin Delete */
        operationDataDelete();
        break;
    case MenuAct::MENU_EDIT:
        /* Begin Edit */
        operationDataEdit();
        break;
    case MenuAct::MENU_RAND:
        /* Begin Insert random */
        operationDataInsertRandom();
        break;
    case MenuAct::MENU_SEARCH:
        /* Begin Search */
        operationDataSearch();
        break;
    case MenuAct::MENU_SHOWTABLE:
        /* Begin Show table*/
        operationDataShow();
        break;
    case MenuAct::MENU_TERMINATE:
        /* Terminate session */
        operationTerminateConnection();
        break;

    default:
        break;
    }
}

void dbController::operationDataInsert(void)
{
    /* Display list of available tables */
    viewObj->showList(modObj->getListTables());
    /* Choose between tables */
    modObj->setTableChoice(tableChoiceHandler());
    /* Display list of available columns */
    viewObj->showList(modObj->getListColums());

    std::string comSQL = "INSERT INTO public.\"" + modObj->retvalTable(modObj->retvalTableChoice()) + "\" (";

    /* Assemle command part 1*/
    for (int i = 1; i < modObj->retvalSizeOfListColumn(); i++)
    {
        comSQL += "\"";
        comSQL += modObj->retvalColumn(i);
        if (i != modObj->retvalSizeOfListColumn() - 1)
        {
            comSQL += "\", ";
        }
        else
        {
            comSQL += "\") ";
        }
    }

    comSQL += "VALUES (";

    for (int i = 1; i < modObj->retvalSizeOfListColumn(); i++)
    {
        std::cout << "Enter value for " << modObj->retvalColumn(i) << " column" << std::endl;
        std::string inp = viewObj->getString();
        comSQL += "'" + inp + "'";

        concatDataType(&comSQL, i);

        if (i != modObj->retvalSizeOfListColumn() - 1)
        {
            comSQL += ", ";
        }
        else
        {
            comSQL += ")";
        }
    }

    /* Show the composed command */
    std::cout << " (##) Result command: ";
    viewObj->showString(comSQL);

    /* Set query string (with command composed above) */
    modObj->setQuery(comSQL);
    /* Send query to database */
    modObj->dbQuerySend();
}

void dbController::operationDataDelete(void)
{
    /* Display list of available tables */
    viewObj->showList(modObj->getListTables());
    /* Choose between tables */
    modObj->setTableChoice(tableChoiceHandler());
    /* Get table contents from the database */
    modObj->dbGetTableContents();

    viewObj->showTableContents(modObj->getListTableContents(), modObj->getListColums());

    std::cout << "Choose ID to delete" << std::endl;
    std::string comSQL = "DELETE FROM public.\"" + modObj->retvalTable(modObj->retvalTableChoice());
    comSQL += "\" WHERE \"" + modObj->retvalColumn(0) + "\"";
    comSQL += " IN (" + viewObj->getString() + ")";

    /* Show the composed command */
    std::cout << " (##) Result command: ";
    viewObj->showString(comSQL);

    /* Set query string (with command composed above) */
    modObj->setQuery(comSQL);
    /* Send query to database */
    modObj->dbQuerySend();
}

void dbController::operationDataInsertRandom(void)
{
    /* Display list of available tables */
    viewObj->showList(modObj->getListTables());
    /* Choose between tables */
    modObj->setTableChoice(tableChoiceHandler());
    /* Get table contents from the database */
    modObj->dbGetTableContents();

    std::string comSQL = "INSERT INTO public.\"" + modObj->retvalTable(modObj->retvalTableChoice()) + "\" (";

    for (int i = 1; i < modObj->retvalSizeOfListColumn(); i++)
    {
        comSQL += "\"";
        comSQL += modObj->retvalColumn(i);
        if (i != modObj->retvalSizeOfListColumn() - 1)
        {
            comSQL += "\", ";
        }
        else
        {
            comSQL += "\") ";
        }
    }

    comSQL += "VALUES (";

    for (int i = 1; i < modObj->retvalSizeOfListColumn(); i++)
    {
        switch (modObj->retvalDataType(i))
        {
        case 23:
            comSQL += "::integer";
            break;
        case 1043:
            comSQL += "substr(md5(random()::text), 0, 10)";
            break;
        case 1082:
            comSQL += "now() - random() * INTERVAL '20000 days'";
            break;
        default:
            break;
        }

        if (i != modObj->retvalSizeOfListColumn() - 1)
        {
            comSQL += ", ";
        }
        else
        {
            comSQL += ")";
        }
    }

    /* Show the composed command */
    std::cout << " (##) Result command: ";
    viewObj->showString(comSQL);

    /* Set query string (with command composed above) */
    modObj->setQuery(comSQL);

    std::cout << " Choose how many rows of random data will be generated: ";
    int _quantity = viewObj->getInput();
    for (int i = 0; i < _quantity; i++)
    {
        /* Send query to database */
        modObj->dbQuerySend();
    }
}

void dbController::operationDataEdit(void)
{
    /* Display list of available tables */
    viewObj->showList(modObj->getListTables());
    /* Choose between tables */
    modObj->setTableChoice(tableChoiceHandler());
    /* Get table contents from the database */
    modObj->dbGetTableContents();

    viewObj->showTableContents(modObj->getListTableContents(), modObj->getListColums());

    std::string comSQL = "UPDATE public.\"" + modObj->retvalTable(modObj->retvalTableChoice()) + "\" SET ";
    std::cout << "Choose ID to edit" << std::endl;
    /* Choose item to edit*/
    std::string strID = viewObj->getString();
    std::cout << "Choose column to edit" << std::endl;
    /* Display list of available columns */
    viewObj->showList(modObj->getListColums());

    /* Choose column to edit*/
    modObj->setColumnChoice(viewObj->getInput());

    comSQL += "\"" + modObj->retvalColumn(modObj->retvalColumnChoice()) + "\" = ";
    std::cout << "Set value: " << std::endl;
    comSQL += "'" + viewObj->getString() + "'";

    /* Detect data type */
    concatDataType(&comSQL, modObj->retvalColumnChoice());

    comSQL += " WHERE \"" + modObj->retvalColumn(0) + "\" = " + strID;

    /* Show the composed command */
    std::cout << " (##) Result command: ";
    viewObj->showString(comSQL);

    /* Set query string (with command composed above) */
    modObj->setQuery(comSQL);
    /* Send query to database */
    modObj->dbQuerySend();
}

void dbController::operationDataSearch(void)
{
    /* Choose option for search */
    viewObj->showSearchOptions();
    /* Set option for search in model */
    modObj->setSearchChoice(viewObj->getInput());

    std::string comSQL;
    switch (modObj->retvalSearchChoice())
    {
    case 1:
        comSQL += "SELECT \"FullName\", \"SessionID\", \"StartDate\" ";
        comSQL += "FROM public.\"Session\" ";
        comSQL += "JOIN public.\"Client\" ON \"Session\".\"ClientID\" = \"Client\".\"ClientID\" ";
        comSQL += "WHERE \"StartDate\" > ";
        std::cout << "Set start date: ";
        comSQL += "'" + viewObj->getString() + "'";
        comSQL += " AND \"StartDate\" < ";
        std::cout << "Set end date: ";
        comSQL += "'" + viewObj->getString() + "'";
        comSQL += " ORDER BY \"FullName\"";
        break;
    case 2:
        comSQL += "SELECT \"FullName\", \"SessionID\", \"Status\" ";
        comSQL += "FROM public.\"Session\" ";
        comSQL += "JOIN public.\"Client\" ON \"Session\".\"ClientID\" = \"Client\".\"ClientID\" ";
        comSQL += "WHERE \"Status\" = ";
        std::cout << "Set status: ";
        comSQL += "'" + viewObj->getString() + "'";
        comSQL += " ORDER BY \"FullName\"";
        break;
    case 3:
        comSQL += "SELECT \"FullName\", \"SessionID\", \"TableID\", \"StartDate\", \"EndDate\", \"Status\" ";
        comSQL += "FROM public.\"Session\" ";
        comSQL += "JOIN public.\"Client\" ON \"Session\".\"ClientID\" = \"Client\".\"ClientID\" ";
        comSQL += "WHERE \"FullName\" = ";
        std::cout << "Set FullName: ";
        comSQL += "'" + viewObj->getString() + "'";
        comSQL += " ORDER BY \"SessionID\"";
        break;
    default:
        break;
    }

    /* Show the composed command */
    std::cout << " (##) Result command: ";
    viewObj->showString(comSQL);

    /* Set query string (with command composed above) */
    modObj->setQuery(comSQL);
    /* Send query and write results to vectors in model */
    modObj->dbGetResultFromQuery();
    /* Show data from table vector in model */
    viewObj->showTableContents(modObj->getListTableContents(), modObj->getListColums());
}

void dbController::operationDataShow(void)
{
    /* Display list of available tables */
    viewObj->showList(modObj->getListTables());
    /* Choose between tables */
    modObj->setTableChoice(tableChoiceHandler());

    /* Start assembling the command for query */
    std::string comSQL = "SELECT * FROM public.\"" + modObj->retvalTable(modObj->retvalTableChoice()) + "\"";
    std::cout << "Set LIMIT: (0 to show everything): " << std::endl;
    /* Set limit for rows */
    int LIMIT = viewObj->getInput();

    switch (LIMIT)
    {
    case 0:

        break;

    default:
        comSQL += " LIMIT " + std::to_string(LIMIT);
        break;
    }

    /* Show the composed command */
    std::cout << " (##) Result command: ";
    viewObj->showString(comSQL);

    /* Set query string (with command composed above) */
    modObj->setQuery(comSQL);
    /* Send query and write results to vectors in model */
    modObj->dbGetResultFromQuery();
    /* Show data from table vector in model */
    viewObj->showTableContents(modObj->getListTableContents(), modObj->getListColums());
}

void dbController::operationTerminateConnection(void)
{
    modObj->dbTerminate();
}