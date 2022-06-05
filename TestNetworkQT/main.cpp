#include "TestNetworkQT.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestNetworkQT w;
    w.show();
    return a.exec();
}
