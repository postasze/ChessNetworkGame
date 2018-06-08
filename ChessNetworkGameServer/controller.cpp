#include "controller.h"
#include <string>
#include <sstream>
#include <algorithm>
#include "chesstable.h"

Controller::Controller()
{
    communicator.setController(this);
    currentChessTableID = 0;
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

void Controller::createNewClientHandler(int fullAssociatedSocketDescriptor)
{
    clientHandlers.push_back(new ClientHandler(fullAssociatedSocketDescriptor));
    pthread_create(&clientHandlers.back()->pthreadId, NULL, &communicator.listenToClient, (void*) clientHandlers.back());
}

void Controller::removeClientHandler(ClientHandler *clientHandler)
{
    removeClientFromAllTables(clientHandler);
    clientHandlers.erase(std::find(clientHandlers.begin(), clientHandlers.end(), clientHandler));
    delete clientHandler;
}

void Controller::removeClientFromAllTables(ClientHandler *clientHandler)
{
    std::vector<ClientHandler*>::iterator clientPosition;
    for(unsigned int i = 0; i < chessTables.size(); i++)
    {
        if((clientPosition = std::find(chessTables[i]->clientsOnTable.begin(), chessTables[i]->clientsOnTable.end(), clientHandler)) != chessTables[i]->clientsOnTable.end())
        {
            chessTables[i]->clientsOnTable.erase(clientPosition);
            if(chessTables[i]->clientWithBlackFigures == clientHandler)
            {
                chessTables[i]->clientWithBlackFigures = nullptr;
                chessTables[i]->chessMatch.blackPlayerReady = false;
            }
            if(chessTables[i]->clientWithWhiteFigures == clientHandler)
            {
                chessTables[i]->clientWithWhiteFigures = nullptr;
                chessTables[i]->chessMatch.whitePlayerReady = false;
            }
        }
    }
}

void Controller::handleClientRequest(ClientHandler *clientHandler)
{
    std::string message = clientHandler->inputBuffer;

    if(message.substr(0, 26) == "New client with username: ")
        handleNewClientCreationRequest(clientHandler, message.substr(26, std::string::npos));
    else if(message == "Create new chess table")
        handleNewChessTableCreationRequest(clientHandler);
    else if(message.substr(0, 26) == "Join chess table with id: ")
        handleJoinChessTableRequest(clientHandler, stoi(message.substr(26, std::string::npos)));
    else if(message.substr(0, 67) == "Choose black color seat button clicked by client on table with id: ")
        handleBlackColorSeatChoiceRequest(clientHandler, stoi(message.substr(67, std::string::npos)));
    else if(message.substr(0, 65) == "Free black color seat button clicked by client on table with id: ")
        handleBlackColorSeatReleaseRequest(clientHandler, stoi(message.substr(65, std::string::npos)));
    else if(message.substr(0, 67) == "Choose white color seat button clicked by client on table with id: ")
        handleWhiteColorSeatChoiceRequest(clientHandler, stoi(message.substr(67, std::string::npos)));
    else if(message.substr(0, 65) == "Free white color seat button clicked by client on table with id: ")
        handleWhiteColorSeatReleaseRequest(clientHandler, stoi(message.substr(65, std::string::npos)));
    else if(message.substr(0, 49) == "Start button clicked by client on table with id: ")
        handleStartGameRequest(clientHandler, stoi(message.substr(49, std::string::npos)));
    else if(message.substr(0, 50) == "Resign button clicked by client on table with id: ")
        handleResignGameRequest(clientHandler, stoi(message.substr(50, std::string::npos)));
    else if(message.substr(0, 46) == "User has sent message on chess table with id: ")
        handleUserMessageDeliveryRequest(clientHandler, message.substr(46, std::string::npos));
    else if(message.substr(0, 52) == "User has pressed his figure on chess table with id: ")
        handleUserFigurePressRequest(clientHandler, message.substr(52, std::string::npos));
    else if(message.substr(0, 50) == "User has moved his figure on chess table with id: ")
        handleUserFigureMoveRequest(clientHandler, message.substr(50, std::string::npos));
}

void Controller::handleNewClientCreationRequest(ClientHandler *clientHandler, std::string newUsername)
{
    if (std::any_of(clientHandlers.begin(), clientHandlers.end(),
        [newUsername](ClientHandler* clientHandler) {return clientHandler->userName == newUsername;}))
        communicator.writeReplyToClient(clientHandler, "Username already exists");
    else
    {
        clientHandler->userName = newUsername;
        communicator.writeReplyToClient(clientHandler, "Username accepted");

        for(unsigned int i = 0; i < chessTables.size(); i++)
            communicator.writeReplyToClient(clientHandler, "Chess table created with id = " + std::to_string(chessTables[i]->chessTableId));
    }
}

void Controller::handleNewChessTableCreationRequest(ClientHandler *clientHandler)
{
    chessTables.push_back(new ChessTable(currentChessTableID));
    chessTables.back()->clientsOnTable.push_back(clientHandler);
    communicator.writeReplyToManyClients(clientHandlers, "Chess table created with id = " + std::to_string(currentChessTableID));
    communicator.writeReplyToClient(clientHandler, "Joined to chess table with id = " + std::to_string(currentChessTableID));
    currentChessTableID++;
}

void Controller::handleJoinChessTableRequest(ClientHandler *clientHandler, int chosenChessTableId)
{
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

    if(std::find(chosenChessTable->clientsOnTable.begin(), chosenChessTable->clientsOnTable.end(), clientHandler) != chosenChessTable->clientsOnTable.end())
        return; // client already joined

    chosenChessTable->clientsOnTable.push_back(clientHandler);
    communicator.writeReplyToClient(clientHandler, "Joined to chess table with id = " + std::to_string(chosenChessTableId));

    if(chosenChessTable->clientWithBlackFigures != nullptr)
        communicator.writeReplyToClient(clientHandler, "User has been placed on the seat with black figures on table with id: " + std::to_string(chosenChessTableId) + " " + chosenChessTable->clientWithBlackFigures->userName);

    if(chosenChessTable->clientWithWhiteFigures != nullptr)
        communicator.writeReplyToClient(clientHandler, "User has been placed on the seat with white figures on table with id: " + std::to_string(chosenChessTableId) + " " + chosenChessTable->clientWithWhiteFigures->userName);

    // TO DO
}

void Controller::handleBlackColorSeatChoiceRequest(ClientHandler *clientHandler, int chosenChessTableId)
{
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

    if (chosenChessTable->clientWithBlackFigures != clientHandler &&
        chosenChessTable->clientWithWhiteFigures != clientHandler &&
        chosenChessTable->clientWithBlackFigures == nullptr)
    {
        chosenChessTable->clientWithBlackFigures = clientHandler;
        communicator.writeReplyToManyClients(chosenChessTable->clientsOnTable, "User has been placed on the seat with black figures on table with id: " + std::to_string(chosenChessTableId) + " " + clientHandler->userName);
    }
}

void Controller::handleBlackColorSeatReleaseRequest(ClientHandler *clientHandler, int chosenChessTableId)
{
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

    if (chosenChessTable->clientWithBlackFigures == clientHandler)
    {
        chosenChessTable->clientWithBlackFigures = nullptr;
        chosenChessTable->chessMatch.blackPlayerReady = false;
        communicator.writeReplyToManyClients(chosenChessTable->clientsOnTable, "User has released the seat with black figures on table with id: " + std::to_string(chosenChessTableId));
    }
}

void Controller::handleWhiteColorSeatChoiceRequest(ClientHandler *clientHandler, int chosenChessTableId)
{
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

    if (chosenChessTable->clientWithBlackFigures != clientHandler &&
        chosenChessTable->clientWithWhiteFigures != clientHandler &&
        chosenChessTable->clientWithWhiteFigures == nullptr)
    {
        chosenChessTable->clientWithWhiteFigures = clientHandler;
        communicator.writeReplyToManyClients(chosenChessTable->clientsOnTable, "User has been placed on the seat with white figures on table with id: " + std::to_string(chosenChessTableId) + " " + clientHandler->userName);
    }
}

void Controller::handleWhiteColorSeatReleaseRequest(ClientHandler *clientHandler, int chosenChessTableId)
{
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

    if (chosenChessTable->clientWithWhiteFigures == clientHandler)
    {
        chosenChessTable->clientWithWhiteFigures = nullptr;
        chosenChessTable->chessMatch.whitePlayerReady = false;
        communicator.writeReplyToManyClients(chosenChessTable->clientsOnTable, "User has released the seat with white figures on table with id: " + std::to_string(chosenChessTableId));
    }
}

void Controller::handleStartGameRequest(ClientHandler *clientHandler, int chosenChessTableId)
{
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

    if(chosenChessTable->clientWithBlackFigures == clientHandler)
        chosenChessTable->chessMatch.blackPlayerReady = true;

    if(chosenChessTable->clientWithWhiteFigures == clientHandler)
        chosenChessTable->chessMatch.whitePlayerReady = true;

    if(chosenChessTable->chessMatch.blackPlayerReady && chosenChessTable->chessMatch.whitePlayerReady)
    {
        communicator.writeReplyToClient(chosenChessTable->clientWithBlackFigures, "Game has started on table with id: " + std::to_string(chosenChessTableId));
        communicator.writeReplyToClient(chosenChessTable->clientWithWhiteFigures, "Game has started on table with id: " + std::to_string(chosenChessTableId));
    }
}

void Controller::handleResignGameRequest(ClientHandler *clientHandler, int chosenChessTableId)
{
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

    chosenChessTable->chessMatch.blackPlayerReady = false;
    chosenChessTable->chessMatch.whitePlayerReady = false;
}

void Controller::handleUserMessageDeliveryRequest(ClientHandler *clientHandler, std::string message)
{
    std::size_t spacePosition = message.find(' ');
    int chosenChessTableId = stoi(message.substr(0, spacePosition));
    std::string userMessage = message.substr(spacePosition + 1, std::string::npos);

    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

    communicator.writeReplyToManyClients(chosenChessTable->clientsOnTable, "User has sent message on chess table with id: " + std::to_string(chosenChessTableId) + " " + clientHandler->userName + " " + userMessage);
}

void Controller::handleUserFigurePressRequest(ClientHandler *clientHandler, std::string message)
{
    std::vector<std::pair<int, int>> possibleMoves;
    std::size_t spacePosition;
    std::string reply;

    spacePosition = message.find(' ');
    int chosenChessTableId = stoi(message.substr(0, spacePosition));
    message.erase(0, spacePosition + 1);
    spacePosition = message.find(' ');
    int x = stoi(message.substr(0, spacePosition));
    int y = stoi(message.substr(spacePosition + 1, std::string::npos));

    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});


    possibleMoves = chosenChessTable->chessMatch.getPossibleMovesForFigureOnPosition(x, y);
    reply = createReplyContainingPossibleMoves(chosenChessTableId, possibleMoves);
    communicator.writeReplyToClient(clientHandler, reply);
}

void Controller::handleUserFigureMoveRequest(ClientHandler *clientHandler, std::string message)
{
    std::size_t spacePosition;
    std::pair<int, int> startPoint, destinationPoint;

    spacePosition = message.find(' ');
    int chosenChessTableId = stoi(message.substr(0, spacePosition));
    message.erase(0, spacePosition + 1);
    spacePosition = message.find(' ');
    destinationPoint.first = stoi(message.substr(0, spacePosition));
    destinationPoint.second = stoi(message.substr(spacePosition + 1, std::string::npos));

    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

    startPoint = chosenChessTable->chessMatch.makePlayerMove(destinationPoint);
    communicator.writeReplyToManyClients(chosenChessTable->clientsOnTable, "User has moved his figure on chess table with id: " + std::to_string(chosenChessTableId) + " " + std::to_string(startPoint.first) + " " + std::to_string(startPoint.second) + " " + std::to_string(destinationPoint.first) + " " + std::to_string(destinationPoint.second));
}

std::string Controller::createReplyContainingPossibleMoves(int chosenChessTableId, std::vector<std::pair<int, int>>& possibleMoves)
{
    std::ostringstream replyStream;

    replyStream << "Possible moves points on chess table with id: " << std::to_string(chosenChessTableId);

    for(unsigned int i = 0; i < possibleMoves.size(); i++)
        replyStream << " " << possibleMoves[i].first << " " << possibleMoves[i].second;

    return replyStream.str();
}
