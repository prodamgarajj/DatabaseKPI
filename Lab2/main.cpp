#include <iostream>
#include "dbController.h"

int main()
{
    std::string username = "postgres";
    std::string password = "0";
    std::string databasename = "computerclub";

    Model::dbModel mdl(username, password, databasename);
    View::dbView vw;
    Controller::dbController ctrl(&mdl, &vw);

    ctrl.logicEstablishConnection();

    while (1)
    {
        ctrl.logicMenu();
        ctrl.logicDBOperation();
    }

    return 0;
}