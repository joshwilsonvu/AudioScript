#ifndef CLASSWIDGET_H
#define CLASSWIDGET_H

#include "sidewidgetbase.h"
#include "scriptwindow.h"
#include "classloader.h"

#include <QDialog>

class QListWidget;
class QListWidgetItem;
class QGroupBox;
class ClassLoader;

// The graphical interface that displays the available classes and allows
// users to open them. Also provides a directory selector. Corresponding
// frontend component for ClassLoader
class ClassDialog : public QDialog
{
    Q_OBJECT

public:
    ClassDialog(ClassLoader* classLoader, QWidget* parent = 0, Qt::WindowFlags flags = 0);
    virtual ~ClassDialog();

    QString selectedClass() const;

private slots:
    void onDoubleClicked(QListWidgetItem* item);

private:
    QListWidget* m_classes;
    QGroupBox* m_groupBox;
    QString m_selectedClass;
};

#endif // CLASSWIDGET_H
