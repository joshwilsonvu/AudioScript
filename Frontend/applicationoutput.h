#ifndef APPLICATIONOUTPUT_H
#define APPLICATIONOUTPUT_H

#include "sidewidgetbase.h"

#include <QPlainTextEdit>
#include <QGroupBox>

// Graphical user interface that displays compile and link output of user code
// and provides shortcut buttons to build code.
class ApplicationOutput : public SideWidgetBase
{
    Q_OBJECT
public:
    ApplicationOutput(QWidget* parent = Q_NULLPTR, Qt::WindowFlags flags = 0);
    virtual ~ApplicationOutput();

public slots:
    void append(QString text);

private:
    QPlainTextEdit* m_display;
    QGroupBox* m_groupBox;
};

#endif // APPLICATIONOUTPUT_H
