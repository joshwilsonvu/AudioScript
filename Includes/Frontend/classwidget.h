#ifndef CLASSWIDGET_H
#define CLASSWIDGET_H

#include "sidewidgetbase.h"
#include "mainwindow.h"
#include "classloader.h"

class QListWidget;
class QListWidgetItem;
class QGroupBox;
class QComboBox;
class ClassLoader;

// The graphical interface that displays the available classes and allows
// users to open them. Also provides a directory selector. Corresponding
// frontend component for ClassLoader
class ClassWidget : public SideWidgetBase
{
    Q_OBJECT

public:
    ClassWidget(QWidget* parent = 0, Qt::WindowFlags flags = 0);
    virtual ~ClassWidget();

public slots:
    void onDirectoryChanged(ClassLoader* classLoader);

private slots:
    void onDoubleClicked(QListWidgetItem* item);

signals:
    void doubleClicked(QString);
    void directoryChanged(QString);

private:
    QListWidget* m_classes;
    QGroupBox* m_groupBox;
    QComboBox* m_comboBox;
};

#endif // CLASSWIDGET_H
