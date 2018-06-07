#include <QtTest>

// add necessary includes here
#include "../controller.h"

class ServerTest : public QObject
{
    Q_OBJECT

public:
    ServerTest();
    ~ServerTest();

private slots:
    void handle_client_request();
    void handle_new_chess_table_creation_request();
    void handle_join_chess_table_request();
    void handle_black_color_seat_choice_request();
    void handle_white_color_seat_choice_request();
    void handle_white_color_seat_release_request();
    void handle_black_color_seat_release_request();
    void handle_start_game_request();
    void handle_user_message_delivery_request();
    void handle_user_figure_press_request();
    void handle_user_figure_move_Request();

};

ServerTest::ServerTest()
{

}

ServerTest::~ServerTest()
{

}

void ServerTest::handle_client_request()
{
    ClientHandler client;
    std::string message = "New client with username: user";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message.c_str());

    Controller contr;
    contr.handleClientRequest(&client);
    //user name set
    QCOMPARE(client.userName, "user");
    //output set to user name set
    QCOMPARE(client.outputBuffer, "Username accepted");

}

void ServerTest::handle_new_chess_table_creation_request()
{
    ClientHandler client;
    std::string message = "Create new chess table";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message.c_str());

    Controller contr;
    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 0");

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 1");
}

void ServerTest::handle_join_chess_table_request()
{
    ClientHandler client;
    std::string message = "Create new chess table";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message.c_str());

    Controller contr;
    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 0");

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 1");

    std::string message2 = "Join chess table with id: 1";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message2.c_str());

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 1");

}

void ServerTest::handle_black_color_seat_choice_request()
{
    ClientHandler client;
    std::string message = "Create new chess table";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message.c_str());

    Controller contr;
    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 0");

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 1");

    std::string message2 = "Join chess table with id: 1";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message2.c_str());

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 1");

    std::string message3 = "Choose black color seat button clicked by client on table with id: 1";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message3.c_str());

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "User has been placed on the seat with black figures on table with id: 1 ");
}

void ServerTest::handle_white_color_seat_choice_request()
{
    ClientHandler client;
    std::string message = "Create new chess table";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message.c_str());

    Controller contr;
    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 0");

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 1");

    std::string message2 = "Join chess table with id: 1";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message2.c_str());

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 1");

    std::string message3 = "Choose white color seat button clicked by client on table with id: 1";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message3.c_str());

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "User has been placed on the seat with white figures on table with id: 1 ");
}

void ServerTest::handle_white_color_seat_release_request()
{
    ClientHandler client;
    std::string message = "Create new chess table";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message.c_str());

    Controller contr;
    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 0");

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 1");

    std::string message2 = "Join chess table with id: 1";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message2.c_str());

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 1");

    std::string message3 = "Choose white color seat button clicked by client on table with id: 1";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message3.c_str());

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "User has been placed on the seat with white figures on table with id: 1 ");

    std::string message4 = "Free white color seat button clicked by client on table with id: 1";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message4.c_str());

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "User has released the seat with white figures on table with id: 1");
}

void ServerTest::handle_black_color_seat_release_request()
{
    ClientHandler client;
    std::string message = "Create new chess table";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message.c_str());

    Controller contr;
    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 0");

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 1");

    std::string message2 = "Join chess table with id: 1";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message2.c_str());

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 1");

    std::string message3 = "Choose black color seat button clicked by client on table with id: 1";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message3.c_str());

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "User has been placed on the seat with black figures on table with id: 1 ");

    std::string message4 = "Free black color seat button clicked by client on table with id: 1";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message4.c_str());

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "User has released the seat with black figures on table with id: 1");
}

void ServerTest::handle_start_game_request(){
    ClientHandler client;
    std::string message = "Create new chess table";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message.c_str());

    Controller contr;
    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 0");

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 1");

    std::string message2 = "Join chess table with id: 1";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message2.c_str());

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 1");

    std::string message3 = "Choose white color seat button clicked by client on table with id: 1";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message3.c_str());

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "User has been placed on the seat with white figures on table with id: 1 ");

    std::string message4 = "Start button clicked by client on table with id: 1";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message4.c_str());

    contr.handleClientRequest(&client);

    ClientHandler client2;

    std::string message5 = "Choose black color seat button clicked by client on table with id: 1";
    memset(client2.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client2.inputBuffer, message5.c_str());

    contr.handleClientRequest(&client2);

    //QCOMPARE(client2.outputBuffer, "User has been placed on the seat with black figures on table with id: 1 ");

    memset(client2.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client2.inputBuffer, message4.c_str());

    contr.handleClientRequest(&client2);

    QCOMPARE(client.outputBuffer, "Game has started on table with id: 1");
    QCOMPARE(client2.outputBuffer, "Game has started on table with id: 1");
}

void ServerTest::handle_user_message_delivery_request(){
    ClientHandler client;
    std::string message = "Create new chess table";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message.c_str());

    Controller contr;
    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 0");

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 1");


    ClientHandler client2;
    std::string message3 = "Join chess table with id: 1";
    memset(client2.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client2.inputBuffer, message3.c_str());

    contr.handleClientRequest(&client2);
    QCOMPARE(client2.outputBuffer, "Joined to chess table with id = 1");

    std::string message2 = "User has sent message on chess table with id: 1 Wiadomosc";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message2.c_str());

    contr.handleClientRequest(&client);

    QCOMPARE(client2.outputBuffer, "User has sent message on chess table with id: 1  Wiadomosc");
    QCOMPARE(client.outputBuffer, "User has sent message on chess table with id: 1  Wiadomosc");

}

void ServerTest::handle_user_figure_press_request(){
    ClientHandler client;
    std::string message = "Create new chess table";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message.c_str());

    Controller contr;
    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 0");

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 1");

    std::string message2 = "Join chess table with id: 1";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message2.c_str());

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 1");

    std::string message3 = "Choose white color seat button clicked by client on table with id: 1";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message3.c_str());

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "User has been placed on the seat with white figures on table with id: 1 ");

    std::string message4 = "Start button clicked by client on table with id: 1";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message4.c_str());

    contr.handleClientRequest(&client);

    ClientHandler client2;

    std::string message5 = "Choose black color seat button clicked by client on table with id: 1";
    memset(client2.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client2.inputBuffer, message5.c_str());

    contr.handleClientRequest(&client2);

    //QCOMPARE(client2.outputBuffer, "User has been placed on the seat with black figures on table with id: 1 ");

    memset(client2.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client2.inputBuffer, message4.c_str());

    contr.handleClientRequest(&client2);

    QCOMPARE(client.outputBuffer, "Game has started on table with id: 1");
    QCOMPARE(client2.outputBuffer, "Game has started on table with id: 1");

    std::string message6 = "User has pressed his figure on chess table with id: 1 6 6";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message6.c_str());

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Possible moves points on chess table with id: 1 6 5 6 4");

}

void ServerTest::handle_user_figure_move_Request(){
    ClientHandler client;
    std::string message = "Create new chess table";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message.c_str());

    Controller contr;
    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 0");

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 1");

    std::string message2 = "Join chess table with id: 1";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message2.c_str());

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Joined to chess table with id = 1");

    std::string message3 = "Choose white color seat button clicked by client on table with id: 1";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message3.c_str());

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "User has been placed on the seat with white figures on table with id: 1 ");

    std::string message4 = "Start button clicked by client on table with id: 1";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message4.c_str());

    contr.handleClientRequest(&client);

    ClientHandler client2;

    std::string message5 = "Choose black color seat button clicked by client on table with id: 1";
    memset(client2.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client2.inputBuffer, message5.c_str());

    contr.handleClientRequest(&client2);

    //QCOMPARE(client2.outputBuffer, "User has been placed on the seat with black figures on table with id: 1 ");

    memset(client2.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client2.inputBuffer, message4.c_str());

    contr.handleClientRequest(&client2);

    QCOMPARE(client.outputBuffer, "Game has started on table with id: 1");
    QCOMPARE(client2.outputBuffer, "Game has started on table with id: 1");

    std::string message6 = "User has pressed his figure on chess table with id: 1 6 6";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message6.c_str());

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "Possible moves points on chess table with id: 1 6 5 6 4");

    std::string message7 = "User has moved his figure on chess table with id: 1 6 6 6 4";
    memset(client.inputBuffer, 0, BUFFER_SIZE);
    strcpy(client.inputBuffer, message7.c_str());

    contr.handleClientRequest(&client);

    QCOMPARE(client.outputBuffer, "User has moved his figure on chess table with id: 1 6 6 6 6");
}

QTEST_APPLESS_MAIN(ServerTest)

#include "tst_servertest.moc"
