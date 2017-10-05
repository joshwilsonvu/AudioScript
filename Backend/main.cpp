#include "scriptwindow.h"
#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QIcon>

//#define USE_QDARKSTYLE

int main(int argc, char *argv[])
{
    /*Q_INIT_RESOURCE(application);*/

    QApplication app(argc, argv);

    app.setWindowIcon(QIcon(":/icons/application"));

#ifdef USE_QDARKSTYLE
    QFile f(":qdarkstyle/style.qss");
    if (!f.exists()) {
        printf("Unable to set stylesheet, file not found\n");
    } else {
        f.open(QFile::ReadOnly | QFile::Text);
        app.setStyleSheet(f.readAll());
    }
#endif

    QCoreApplication::setOrganizationName("VUSE Solutions");
    QCoreApplication::setApplicationName("AudioScript");

    MainWindow m;
    ScriptWindow s;

    m.show();
    s.show();

    return app.exec();
}
