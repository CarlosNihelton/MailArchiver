#include <QApplication>
#include "QMailArchiver.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QMailArchiver qmailarchiver;
    qmailarchiver.show();
    return app.exec();
}
