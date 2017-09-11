#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QSettings>
#include <QtDebug>
#include <QIcon>

int main(int argc, char *argv[])
{
    /*Q_INIT_RESOURCE(application);*/

    QApplication app(argc, argv);

    app.setWindowIcon(QIcon(":/icons/application"));

    QCoreApplication::setOrganizationName("VUSE Solutions");
    QCoreApplication::setApplicationName("AudioScript");

    MainWindow w;

    w.show();

    return app.exec();
}
