#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TestNetworkQT.h"


#include <Network/Protocol/SBP/SBPClient.h>
#include <Network/Protocol/SBP/SBPServer.h>

class TestNetworkQT :   public QMainWindow, 
                        protected BF::IClientListener,
                        protected BF::IServerListener,
                        protected BF::ISocketListener
{
    Q_OBJECT

    public:
    TestNetworkQT(QWidget *parent = Q_NULLPTR);

    private:
    BF::SBPServer _server;
    BF::SBPClient _client;

    Ui::TestNetworkQTClass ui;

    void OnButtonClientConnectPressed();
    void OnButtonClientDisconnectPressed();
    void OnButtonServerStartPressed();
    void OnButtonServerStopPressed();

    // Geerbt über IClientListener
    virtual void OnConnectedToServer(BF::IPAdressInfo& adressInfo) override;

    // Geerbt über IServerListener
    virtual void OnClientConnected(BF::Client& client) override;
    virtual void OnClientDisconnected(BF::Client& client) override;
    virtual void OnClientAcceptFailure() override;

    // Geerbt über ISocketListener
    virtual void OnSocketCreating(const BF::IPAdressInfo& adressInfo, bool& use) override;
    virtual void OnSocketCreated(const BF::IPAdressInfo& adressInfo, bool& use) override;
    virtual void OnMessageSend(BF::IOSocketMessage socketMessage) override;
    virtual void OnMessageReceive(BF::IOSocketMessage socketMessage) override;
    virtual void OnConnectionListening(const BF::IPAdressInfo& adressInfo) override;
    virtual void OnConnectionLinked(const BF::IPAdressInfo& adressInfo) override;
    virtual void OnConnectionEstablished(const BF::IPAdressInfo& adressInfo) override;
    virtual void OnConnectionTerminated(const BF::IPAdressInfo& adressInfo) override;
};
