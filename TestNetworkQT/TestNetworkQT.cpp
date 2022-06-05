#include "TestNetworkQT.h"


unsigned short port = 25666;


TestNetworkQT::TestNetworkQT(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);


    connect(ui.btnClientConnect, &QPushButton::clicked, this, &TestNetworkQT::OnButtonClientConnectPressed);
    connect(ui.btnClientDisconnect, &QPushButton::clicked, this, &TestNetworkQT::OnButtonClientDisconnectPressed);
    connect(ui.btnServerStart, &QPushButton::clicked, this, &TestNetworkQT::OnButtonServerStartPressed);
    connect(ui.btnServerStop, &QPushButton::clicked, this, &TestNetworkQT::OnButtonServerStopPressed);
}

void TestNetworkQT::OnButtonClientConnectPressed()
{
    _client.ConnectToServer("127.0.0.1", port);
}

void TestNetworkQT::OnButtonClientDisconnectPressed()
{
    _client.DisconnectFromServer();
}

void TestNetworkQT::OnButtonServerStartPressed()
{
    _server.Start(port);
}

void TestNetworkQT::OnButtonServerStopPressed()
{
    _server.Stop();
}

void TestNetworkQT::OnConnectedToServer(BF::IPAdressInfo& adressInfo)
{
    char buffer[1024];

    sprintf(buffer, "[Client] Connected");

    ui.txtClientLog->insertPlainText(buffer);
}

void TestNetworkQT::OnClientConnected(BF::Client& client)
{
    char buffer[1024];

    sprintf(buffer, "[Client] OnClientConnected");

    ui.txtClientLog->insertPlainText(buffer);
}

void TestNetworkQT::OnClientDisconnected(BF::Client& client)
{
    char buffer[1024];

    sprintf(buffer, "[Client] OnClientDisconnected");

    ui.txtClientLog->insertPlainText(buffer);
}

void TestNetworkQT::OnClientAcceptFailure()
{
    char buffer[1024];

    sprintf(buffer, "[Client] OnClientAcceptFailure");

    ui.txtClientLog->insertPlainText(buffer);
}

void TestNetworkQT::OnSocketCreating(const BF::IPAdressInfo& adressInfo, bool& use)
{
}

void TestNetworkQT::OnSocketCreated(const BF::IPAdressInfo& adressInfo, bool& use)
{
}

void TestNetworkQT::OnMessageSend(BF::IOSocketMessage socketMessage)
{
}

void TestNetworkQT::OnMessageReceive(BF::IOSocketMessage socketMessage)
{
}

void TestNetworkQT::OnConnectionListening(const BF::IPAdressInfo& adressInfo)
{
}

void TestNetworkQT::OnConnectionLinked(const BF::IPAdressInfo& adressInfo)
{
}

void TestNetworkQT::OnConnectionEstablished(const BF::IPAdressInfo& adressInfo)
{
}

void TestNetworkQT::OnConnectionTerminated(const BF::IPAdressInfo& adressInfo)
{
}
