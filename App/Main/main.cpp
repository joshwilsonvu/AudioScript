#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QIcon>

//#define USE_QDARKSTYLE

/*
#include "audioscriptbuffer.h"
float add(float s1, float s2) {
    return s1 + s2;
}

float times2(float s) {
    return s * 2.0f;
}

void test() {
    AudioScriptBuffer x1;
    x1.apply(times2);
    AudioScriptBuffer y1 = x1.applied(times2);
    AudioScriptBuffer z1 = x1 | times2;

    AudioScriptBuffer x2;
    AudioScriptBuffer y2 = x1.applied(x2, add);
    AudioScriptBuffer z2 = (x1 & x2 | add) & (x3 | times2) | add;
}
*/

int main(int argc, char *argv[])
{
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
    m.show();

    return app.exec();
}
