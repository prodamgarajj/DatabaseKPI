

def showMainMenu():
    print(" KV-02 Voitovych Hlib. Lab Work 3")
    print("  [------MAIN MENU------]")
    print(" [1] Insert data in table")
    print(" [2] Remove data in table")
    print(" [3] Edit data in table  ")
    print(" Please choose operation ")


def getSplitInput():
    inp = input().split(', ')
    return inp


def getInput(string):
    if string is None:
        inp = input(" > ")
    else:
        inp = input(string)
    return inp
