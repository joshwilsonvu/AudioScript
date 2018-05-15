#ifndef APPLICATIONOUTPUT_H
#define APPLICATIONOUTPUT_H

#include <QWidget>

class QPlainTextEdit;

/// Graphical user interface that displays compile and link output of user code
/// and provides shortcut buttons to build code.
class ApplicationOutput : public QWidget
{
    Q_OBJECT
public:
    ApplicationOutput(QWidget* parent = nullptr, Qt::WindowFlags flags = 0);
    virtual ~ApplicationOutput();

public slots:
    void append(QString text);

private:
    QPlainTextEdit* m_display;
};

#endif // APPLICATIONOUTPUT_H
