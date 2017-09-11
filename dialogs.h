#ifndef DIALOGS_H
#define DIALOGS_H

#include <QObject>
#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;

class NameDialog : public QDialog
{
    Q_OBJECT

public:
    NameDialog(QString* value, QWidget* parent = Q_NULLPTR);

private slots:
    void validate(const QString& className);

private:
    QLabel* m_label;
    QLineEdit* m_classInput;
    QPushButton* m_okay;
    QString* m_value; // non-owning
};

class DirDialog : public QDialog
{
    Q_OBJECT

public:
    DirDialog(QString* value, QWidget* parent = Q_NULLPTR);

private slots:

};

#endif // DIALOGS_H
