#include "lecteurdiaporama.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    lecteurDiaporama w;
    w.show();
    return a.exec();
}