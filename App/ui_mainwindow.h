/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionClose;
    QAction *actionQuit;
    QAction *actionOpenEditor;
    QAction *actionOpenPlugin;
    QAction *actionBuild;
    QAction *actionStart;
    QAction *actionStop;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuPlugins;
    QMenu *menuDeveloper;
    QMenu *menuAudio;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionOpenEditor = new QAction(MainWindow);
        actionOpenEditor->setObjectName(QStringLiteral("actionOpenEditor"));
        actionOpenPlugin = new QAction(MainWindow);
        actionOpenPlugin->setObjectName(QStringLiteral("actionOpenPlugin"));
        actionBuild = new QAction(MainWindow);
        actionBuild->setObjectName(QStringLiteral("actionBuild"));
        actionStart = new QAction(MainWindow);
        actionStart->setObjectName(QStringLiteral("actionStart"));
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName(QStringLiteral("actionStop"));
        actionStop->setEnabled(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuPlugins = new QMenu(menubar);
        menuPlugins->setObjectName(QStringLiteral("menuPlugins"));
        menuDeveloper = new QMenu(menubar);
        menuDeveloper->setObjectName(QStringLiteral("menuDeveloper"));
        menuAudio = new QMenu(menubar);
        menuAudio->setObjectName(QStringLiteral("menuAudio"));
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuAudio->menuAction());
        menubar->addAction(menuPlugins->menuAction());
        menubar->addAction(menuDeveloper->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);
        menuFile->addAction(actionQuit);
        menuPlugins->addAction(actionOpenPlugin);
        menuDeveloper->addAction(actionOpenEditor);
        menuDeveloper->addAction(actionBuild);
        menuAudio->addAction(actionStart);
        menuAudio->addAction(actionStop);
        toolBar->addAction(actionStart);
        toolBar->addAction(actionStop);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionNew->setText(QApplication::translate("MainWindow", "New", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("MainWindow", "Open...", Q_NULLPTR));
        actionSave->setText(QApplication::translate("MainWindow", "Save", Q_NULLPTR));
        actionClose->setText(QApplication::translate("MainWindow", "Close", Q_NULLPTR));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", Q_NULLPTR));
        actionOpenEditor->setText(QApplication::translate("MainWindow", "Open Editor", Q_NULLPTR));
        actionOpenPlugin->setText(QApplication::translate("MainWindow", "Open", Q_NULLPTR));
        actionBuild->setText(QApplication::translate("MainWindow", "Build", Q_NULLPTR));
        actionStart->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        actionStop->setText(QApplication::translate("MainWindow", "Stop", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuPlugins->setTitle(QApplication::translate("MainWindow", "Plugins", Q_NULLPTR));
        menuDeveloper->setTitle(QApplication::translate("MainWindow", "Developer", Q_NULLPTR));
        menuAudio->setTitle(QApplication::translate("MainWindow", "Audio", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
