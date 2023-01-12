#pragma once
#include <iostream>
#include <vector>
#include "libpq-fe.h"

typedef void dbClientFunction;

namespace Model
{
    class dbModel
    {
    private:
        /* ---------- Variables that contain data about PG ---------- */

        PGconn *dbConnection;
        PGresult *dbQueryResult;

        std::string dbUsername;
        std::string dbPassword;
        std::string dbName;

        std::string query;

        /* ----- Saved values for use in functions ----- */

        int storeMenuChoice;
        int storeTableChoice;
        int storeColumnChoice;
        int storeSearchChoice;

        int storeCountRow;
        int storeCountColumn;

        /* --- Vectors for containing data from database --- */

        std::vector<std::string> listTables;
        std::vector<std::string> listColumns;
        std::vector<std::vector<std::string>> listTableContents;
        std::vector<int> listColumnDataTypes;

    public:
        dbModel(/* args */);
        dbModel(const std::string usr, const std::string pswd, const std::string db);
        ~dbModel();

        /* ----- Database info setters and getters ----- */

        std::vector<std::string> getListTables(void);
        std::vector<std::string> getListColums(void);
        std::vector<std::vector<std::string>> getListTableContents(void);

        /* -------- Setters and Getters -------- */

        std::string retvalTable(int _ind);
        std::string retvalColumn(int _ind);

        int retvalDataType(int _ind);
        int retvalSizeOfListColumn(void);

        void setMenuChoice(int _ch);
        int retvalMenuChoice(void);

        void setTableChoice(int _ch);
        int retvalTableChoice(void);

        void setColumnChoice(int _ch);
        int retvalColumnChoice(void);

        void setSearchChoice(int _ch);
        int retvalSearchChoice(void);

        void setQuery(std::string _str);
        std::string retvalQuery(void);

        /* -------- SQL specific -------- */

        /* Connect to database */
        dbClientFunction dbConnect(void);
        /* Terminate connection to database */
        dbClientFunction dbTerminate(void);

        /* Get list of tables from database */
        dbClientFunction dbGetTablesFromChoice(void);
        /* Get list of columns from database. Depends on user choice of table */
        dbClientFunction dbGetColumnsFromChoice(void);

        /* Send query to database */
        dbClientFunction dbQuerySend(void);
        /* Get list of columns from database. Depends on query string */
        dbClientFunction dbGetColumnsFromQuery(void);
        /* Get table data from database. Depends on query string */
        dbClientFunction dbGetResultFromQuery(void);
        /* Get table data from database. Depends on user choice */
        dbClientFunction dbGetTableContents(void);
    };
};