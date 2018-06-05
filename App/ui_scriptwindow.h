/********************************************************************************
** Form generated from reading UI file 'scriptwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCRIPTWINDOW_H
#define UI_SCRIPTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScriptWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionAbout;
    QAction *actionAbout_Qt;
    QAction *actionClose;
    QAction *actionQuit;
    QAction *actionBuild;
    QAction *actionSet_Directory;
    QGridLayout *gridLayout;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QMenu *menuBuild;

    void setupUi(QWidget *ScriptWindow)
    {
        if (ScriptWindow->objectName().isEmpty())
            ScriptWindow->setObjectName(QStringLiteral("ScriptWindow"));
        ScriptWindow->resize(600, 600);
        ScriptWindow->setMinimumSize(QSize(300, 300));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/application"), QSize(), QIcon::Normal, QIcon::Off);
        ScriptWindow->setWindowIcon(icon);
        actionNew = new QAction(ScriptWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionOpen = new QAction(ScriptWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(ScriptWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionAbout = new QAction(ScriptWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionAbout_Qt = new QAction(ScriptWindow);
        actionAbout_Qt->setObjectName(QStringLiteral("actionAbout_Qt"));
        actionClose = new QAction(ScriptWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionQuit = new QAction(ScriptWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionBuild = new QAction(ScriptWindow);
        actionBuild->setObjectName(QStringLiteral("actionBuild"));
        actionSet_Directory = new QAction(ScriptWindow);
        actionSet_Directory->setObjectName(QStringLiteral("actionSet_Directory"));
        gridLayout = new QGridLayout(ScriptWindow);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        menuBar = new QMenuBar(ScriptWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuBuild = new QMenu(menuBar);
        menuBuild->setObjectName(QStringLiteral("menuBuild"));

        gridLayout->addWidget(menuBar, 0, 0, 1, 1);


        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuBar->addAction(menuBuild->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionSet_Directory);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);
        menuFile->addAction(actionQuit);
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionAbout_Qt);
        menuBuild->addAction(actionBuild);

        retranslateUi(ScriptWindow);

        QMetaObject::connectSlotsByName(ScriptWindow);
    } // setupUi

    void retranslateUi(QWidget *ScriptWindow)
    {
        ScriptWindow->setWindowTitle(QApplication::translate("ScriptWindow", "ScriptWindow", Q_NULLPTR));
        actionNew->setText(QApplication::translate("ScriptWindow", "New", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("ScriptWindow", "Open...", Q_NULLPTR));
        actionSave->setText(QApplication::translate("ScriptWindow", "Save", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("ScriptWindow", "About", Q_NULLPTR));
        actionAbout_Qt->setText(QApplication::translate("ScriptWindow", "About Qt", Q_NULLPTR));
        actionClose->setText(QApplication::translate("ScriptWindow", "Close", Q_NULLPTR));
        actionQuit->setText(QApplication::translate("ScriptWindow", "Quit", Q_NULLPTR));
        actionBuild->setText(QApplication::translate("ScriptWindow", "Build", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionBuild->setToolTip(QApplication::translate("ScriptWindow", "Build", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSet_Directory->setText(QApplication::translate("ScriptWindow", "Set Directory", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("ScriptWindow", "File", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("ScriptWindow", "Help", Q_NULLPTR));
        menuBuild->setTitle(QApplication::translate("ScriptWindow", "Build", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ScriptWindow: public Ui_ScriptWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCRIPTWINDOW_H
