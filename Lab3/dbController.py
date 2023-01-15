import dbModel as Model
import dbView as View


def operationInsert(userChoice):
    print("Enter values for " + userChoice + " table (using ,)")
    val = View.getSplitInput()

    conn = Model.makerSession()
    if userChoice == "Room":
        res = Model.Room(Number=val[0])
        conn.add(res)
        conn.commit()
    elif userChoice == "Table":
        res = Model.Table(TableID=val[0], Number=val[1])
        conn.add(res)
        conn.commit()
    elif userChoice == "Computer":
        res = Model.Computer(TableID=val[0], Serial=val[1], Number=val[2], Brand=val[3])
        conn.add(res)
        conn.commit()
    elif userChoice == "Client":
        res = Model.Client(FullName=val[0], RegDate=val[1], BirthDate=val[2])
        conn.add(res)
        conn.commit()
    elif userChoice == "Session":
        res = Model.Session(ClientID=val[0], TableID=val[1], StartDate=val[2], EndDate=val[3], Status=int(val[4]))
        conn.add(res)
        conn.commit()
    conn.close()


def operationDelete(userChoice):
    print("Enter ID in " + userChoice + " table")

    val = View.getInput(None)

    conn = Model.makerSession()
    if userChoice == "Room":
        res = conn.query(Model.Room).filter(Model.Room.RoomID == val).first()
        conn.delete(res)
        conn.commit()
    elif userChoice == "Table":
        res = conn.query(Model.Table).filter(Model.Table.TableID == val).first()
        conn.delete(res)
        conn.commit()
    elif userChoice == "Computer":
        res = conn.query(Model.Computer).filter(Model.Computer.ComputerID == val).first()
        conn.delete(res)
        conn.commit()
    elif userChoice == "Client":
        res = conn.query(Model.Client).filter(Model.Client.ClientID == val).first()
        conn.delete(res)
        conn.commit()
    elif userChoice == "Session":
        res = conn.query(Model.Session).filter(Model.Session.SessionID == val).first()
        conn.delete(res)
        conn.commit()
    conn.close()


def operationEdit(userChoice):
    print("Enter ID in " + userChoice + " table")
    valID = View.getInput(None)
    print("Enter values for " + userChoice + " table (using ,)")
    val = View.getSplitInput()

    conn = Model.makerSession()
    if userChoice == "Room":
        res = conn.query(Model.Room).filter(Model.Room.RoomID == valID).first()
        res.Number = val[0]
        conn.commit()
    elif userChoice == "Table":
        res = conn.query(Model.Table).filter(Model.Table.TableID == valID).first()
        res.RoomID = val[0]
        res.Number = val[1]
        conn.commit()
    elif userChoice == "Computer":
        res = conn.query(Model.Computer).filter(Model.Computer.ComputerID == valID).first()
        res.TableID = val[0]
        res.Serial = val[1]
        res.Number = val[2]
        res.Brand = val[3]
        conn.commit()
    elif userChoice == "Client":
        res = conn.query(Model.Client).filter(Model.Client.ClientID == valID).first()
        res.FullName = val[0]
        res.RegDate = val[1]
        res.BirthDate = val[2]
        conn.commit()
    elif userChoice == "Session":
        res = conn.query(Model.Session).filter(Model.Session.SessionID == valID).first()
        res.ClientID = val[0]
        res.TableID = val[1]
        res.StartDate = val[2]
        res.EndDate = val[3]
        res.Status = int(val[4])
        conn.commit()

    conn.close()


def mainMenu():
    View.showMainMenu()
    choiceMenu = View.getInput(None)
    choiceTable = View.getInput(" (?) Write table name: ")

    if choiceMenu == '1':
        operationInsert(choiceTable)
    elif choiceMenu == '2':
        operationDelete(choiceTable)
    elif choiceMenu == '3':
        operationEdit(choiceTable)

