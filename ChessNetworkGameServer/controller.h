#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "communicator.h"
#include "clienthandler.h"

class ChessTable;

class Controller
{
public:
    Controller();

    int openCommunication();
    void acceptClientConnections();
    void closeCommunication();

    void createNewClientHandler(int fullAssociatedSocketDescriptor);
    void removeClientHandler(ClientHandler *clientHandler);
    void removeClientFromAllTables(ClientHandler *clientHandler);
    void handleClientRequest(ClientHandler *clientHandler);
    void handleNewClientCreationRequest(ClientHandler *clientHandler, std::string newUsername);
    void handleNewChessTableCreationRequest(ClientHandler *clientHandler);
    void handleJoinChessTableRequest(ClientHandler *clientHandler, int chosenChessTableId);
    void handleBlackColorSeatChoiceRequest(ClientHandler *clientHandler, int chosenChessTableId);
    void handleBlackColorSeatReleaseRequest(ClientHandler *clientHandler, int chosenChessTableId);
    void handleWhiteColorSeatChoiceRequest(ClientHandler *clientHandler, int chosenChessTableId);
    void handleWhiteColorSeatReleaseRequest(ClientHandler *clientHandler, int chosenChessTableId);
    void handleStartGameRequest(ClientHandler *clientHandler, int chosenChessTableId);
    void handleResignGameRequest(ClientHandler *clientHandler, int chosenChessTableId);
    void handleUserMessageDeliveryRequest(ClientHandler *clientHandler, std::string message);

private:
    Communicator communicator;
    std::vector<ClientHandler*> clientHandlers;
    std::vector<ChessTable*> chessTables;
    int currentChessTableID;
};

#endif // CONTROLLER_H
