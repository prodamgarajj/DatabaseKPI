#include "dbModel.h"

using namespace Model;

dbModel::dbModel(/* args */)
{
}

dbModel::dbModel(const std::string usr, const std::string pswd, const std::string db)
{
    dbUsername = usr;
    dbPassword = pswd;
    dbName = db;

    dbConnection = nullptr;
}

dbModel::~dbModel(void)
{
}

void dbModel::setMenuChoice(int _ch)
{
    storeMenuChoice = _ch;
}

void dbModel::setTableChoice(int _ch)
{
    storeTableChoice = _ch;
    dbModel::dbGetColumnsFromChoice();
}

void dbModel::setColumnChoice(int _ch)
{
    storeColumnChoice = _ch;
}

void dbModel::setSearchChoice(int _ch)
{
    storeSearchChoice = _ch;
}

void dbModel::setQuery(std::string _str)
{
    query = _str;
}

int dbModel::retvalTableChoice(void)
{
    return storeTableChoice;
}

int dbModel::retvalMenuChoice(void)
{
    return storeMenuChoice;
}

int dbModel::retvalColumnChoice(void)
{
    return storeColumnChoice;
}

int dbModel::retvalSearchChoice(void)
{
    return storeSearchChoice;
}

std::string dbModel::retvalQuery(void)
{
    return query;
}

std::vector<std::string> dbModel::getListTables(void)
{
    dbModel::dbGetTablesFromChoice();
    return listTables;
}

std::vector<std::string> dbModel::getListColums(void)
{
    return listColumns;
}

std::vector<std::vector<std::string>> dbModel::getListTableContents(void)
{
    return listTableContents;
}

std::string dbModel::retvalColumn(int _ind)
{
    return listColumns.at(_ind);
}

std::string dbModel::retvalTable(int _ind)
{
    return listTables.at(_ind);
}

int dbModel::retvalDataType(int _ind)
{
    return listColumnDataTypes.at(_ind);
}

int dbModel::retvalSizeOfListColumn(void)
{
    return listColumns.size();
}

dbClientFunction dbModel::dbConnect(void)
{
    std::string result = "user=" + dbUsername;
    if (dbPassword != "0")
    {
        result = result + " dbPassword=" + dbPassword;
    }

    result = result + " dbname=" + dbName;

    std::cout << " > Connecting with params: " << result << std::endl;

    dbConnection = PQconnectdb(result.c_str());

    if (PQstatus(dbConnection) == CONNECTION_BAD)
    {
        std::cout << "(!) Connection failed!" << std::endl;
    }

    std::cout << "(*) Connection successfull!" << std::endl;
    std::cout << std::endl;
}

dbClientFunction dbModel::dbTerminate(void)
{
    PQfinish(dbConnection);
    std::cout << "(*) Connection terminated!" << std::endl;
    exit(0);
}

dbClientFunction dbModel::dbGetTablesFromChoice(void)
{
    listTables.clear();
    PGresult *res = PQexec(dbConnection, "SELECT table_name FROM information_schema.tables "
                                         "WHERE table_schema = 'public'");

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        std::cout << PQresultErrorMessage(res) << std::endl;
        PQclear(res);
    }

    int rows = PQntuples(res);

    for (int i = 0; i < PQntuples(res); i++)
    {
        listTables.push_back(PQgetvalue(res, i, 0));
    }
}

dbClientFunction dbModel::dbGetColumnsFromChoice(void)
{
    listColumns.clear();
    listColumnDataTypes.clear();
    std::string path = "SELECT * FROM public.\"" + listTables.at(storeTableChoice) + "\"";
    PGresult *res = PQexec(dbConnection, path.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        std::cout << std::endl
                  << " >> No data retrieved from " << dbName << ". Abort function << " << std::endl;
        PQclear(res);
    }

    for (int i = 0; i < PQnfields(res); i++)
    {
        listColumns.push_back(PQfname(res, i));
        listColumnDataTypes.push_back(PQftype(res, i));
    }

    PQclear(res);
}

dbClientFunction dbModel::dbGetColumnsFromQuery(void)
{
    listColumns.clear();
    listColumnDataTypes.clear();
    PGresult *res = PQexec(dbConnection, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        std::cout << PQresultErrorMessage(res) << std::endl;
        PQclear(res);
    }

    for (int i = 0; i < PQnfields(res); i++)
    {
        listColumns.push_back(PQfname(res, i));
        listColumnDataTypes.push_back(PQftype(res, i));
    }

    PQclear(res);
}

dbClientFunction dbModel::dbQuerySend(void)
{
    PGresult *res = PQexec(dbConnection, "BEGIN");

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        printf("BEGIN command failed\n");
        PQclear(res);
    }

    res = PQexec(dbConnection, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        std::cout << std::endl
                  << PQerrorMessage(dbConnection) << std::endl;
        PQclear(res);
    }

    res = PQexec(dbConnection, "COMMIT");

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        printf("COMMIT command failed\n");
        PQclear(res);
    }
}

dbClientFunction dbModel::dbGetTableContents(void)
{
    listTableContents.clear();
    dbGetTablesFromChoice();
    dbGetColumnsFromChoice();
    std::string path = "SELECT * FROM public.\"" + listTables.at(storeTableChoice) + "\"";
    path += " ORDER BY \"" + listColumns.at(0) + "\"";
    PGresult *res = PQexec(dbConnection, path.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        std::cout << "No data retrieved. Abort function" << std::endl;
        PQclear(res);
    }

    storeCountRow = PQntuples(res);
    storeCountColumn = PQnfields(res);

    std::vector<std::string> lsttmp;
    for (uint16_t i = 0; i < storeCountRow; i++)
    {
        for (uint16_t j = 0; j < storeCountColumn; j++)
        {
            lsttmp.push_back(PQgetvalue(res, i, j));
        }
        listTableContents.push_back(lsttmp);
        lsttmp.clear();
    }

    PQclear(res);
}

dbClientFunction dbModel::dbGetResultFromQuery(void)
{
    listTableContents.clear();
    dbGetColumnsFromQuery();
    PGresult *res = PQexec(dbConnection, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        std::cout << std::endl
                  << PQerrorMessage(dbConnection) << "FUCK" << std::endl;
        PQclear(res);
    }

    storeCountRow = PQntuples(res);
    storeCountColumn = PQnfields(res);

    std::vector<std::string> lsttmp;
    for (uint16_t i = 0; i < storeCountRow; i++)
    {
        for (uint16_t j = 0; j < storeCountColumn; j++)
        {
            lsttmp.push_back(PQgetvalue(res, i, j));
        }
        listTableContents.push_back(lsttmp);
        lsttmp.clear();
    }
}