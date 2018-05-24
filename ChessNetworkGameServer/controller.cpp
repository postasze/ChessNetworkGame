#include "controller.h"
#include <string>
#include <algorithm>
#include "chesstable.h"

Controller::Controller()
{
    communicator.setController(this);
    currentChessTableID = 0;
}

void Controller::createNewClientHandler(int fullAssociatedSocketDescriptor)
{
    clientHandlers.push_back(new ClientHandler(fullAssociatedSocketDescriptor));
    pthread_create(&clientHandlers.back()->pthreadId, NULL, &communicator.listenToClient, (void*) clientHandlers.back());
}

void Controller::handleClientRequest(ClientHandler *clientHandler)
{
    std::string message = clientHandler->inputBuffer;

    if(message.substr(0, 10) == "Username: ")
    {
        std::string newUserName = message.substr(10, std::string::npos);

        if (std::any_of(clientHandlers.begin(), clientHandlers.end(),
            [newUserName](ClientHandler* clientHandler) {return clientHandler->userName == newUserName;}))
            communicator.writeReplyToClient(clientHandler, "Username already exists");
        else
        {
            clientHandler->userName = newUserName;
            communicator.writeReplyToClient(clientHandler, "Username accepted");
        }
    }
    else if(message == "Create new chess table")
    {
        chessTables.push_back(new ChessTable(currentChessTableID));
        chessTables.back()->clientsOnTable.push_back(clientHandler);
        communicator.writeReplyToClient(clientHandler, "Chess table created with id = " + std::to_string(currentChessTableID++));
    }
    else if(message.substr(0, 26) == "Join chess table with id: ")
    {
        int chosenChessTableId = stoi(message.substr(26, std::string::npos));
        ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
            [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});
    }
    else if(message.substr(0, 66) == "Chose black color seat button clicked by client on table with id: ")
    {
        int chosenChessTableId = stoi(message.substr(66, std::string::npos));
        ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
            [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

        if (chosenChessTable->clientWithBlackFigures != clientHandler &&
            chosenChessTable->clientWithWhiteFigures != clientHandler &&
            chosenChessTable->clientWithBlackFigures == nullptr)
        {
            chosenChessTable->clientWithBlackFigures = clientHandler;
            communicator.writeReplyToClient(clientHandler, "User has been placed on the seat with black figures on table with id: " + std::to_string(chosenChessTableId));
        }
    }
    else if(message.substr(0, 65) == "Free black color seat button clicked by client on table with id: ")
    {
        int chosenChessTableId = stoi(message.substr(65, std::string::npos));
        ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
            [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

        if (chosenChessTable->clientWithBlackFigures == clientHandler)
        {
            chosenChessTable->clientWithBlackFigures = nullptr;
            communicator.writeReplyToClient(clientHandler, "User has released the seat with black figures on table with id: " + std::to_string(chosenChessTableId));
        }
    }
    else if(message.substr(0, 66) == "Chose white color seat button clicked by client on table with id: ")
    {
        int chosenChessTableId = stoi(message.substr(66, std::string::npos));
        ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
            [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

        if (chosenChessTable->clientWithBlackFigures != clientHandler &&
            chosenChessTable->clientWithWhiteFigures != clientHandler &&
            chosenChessTable->clientWithWhiteFigures == nullptr)
        {
            chosenChessTable->clientWithWhiteFigures = clientHandler;
            communicator.writeReplyToClient(clientHandler, "User has been placed on the seat with white figures on table with id: " + std::to_string(chosenChessTableId));
        }
    }
    else if(message.substr(0, 65) == "Free white color seat button clicked by client on table with id: ")
    {
        int chosenChessTableId = stoi(message.substr(65, std::string::npos));
        ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
            [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

        if (chosenChessTable->clientWithWhiteFigures == clientHandler)
        {
            chosenChessTable->clientWithWhiteFigures = nullptr;
            communicator.writeReplyToClient(clientHandler, "User has released the seat with white figures on table with id: " + std::to_string(chosenChessTableId));
        }
    }
    else if(message.substr(0, 49) == "Start button clicked by client on table with id: ")
    {
        int chosenChessTableId = stoi(message.substr(49, std::string::npos));
        ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
            [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});
    }
    else if(message.substr(0, 50) == "Resign button clicked by client on table with id: ")
    {
        int chosenChessTableId = stoi(message.substr(50, std::string::npos));
        ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
            [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});
    }
}

void Controller::deleteClientHandler(ClientHandler *clientHandler)
{
    clientHandlers.erase(std::find(clientHandlers.begin(), clientHandlers.end(), clientHandler));
    delete clientHandler;
}

int Controller::openCommunication()
{
    return communicator.openCommunication();
}

void Controller::acceptClientConnections()
{
    communicator.acceptClientConnections();
}

void Controller::closeCommunication()
{
    communicator.closeCommunication();
}
