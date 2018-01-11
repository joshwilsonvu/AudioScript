#ifndef DIALOGS_H
#define DIALOGS_H

#include <QObject>
#include <QDialog>
#include <QFileDialog>

class QLabel;
class QLineEdit;
class QPushButton;
class ClassLoader;

class NameDialog : public QDialog
{
    Q_OBJECT

public:
    NameDialog(ClassLoader* classLoader, QWidget* parent = nullptr);
    QString getName() const;

private slots:
    void validate(QString className);

private:
    QLabel* m_label;
    QLineEdit* m_classInput;
    QPushButton* m_okay;
    ClassLoader* m_classLoader; // non-owning
    QString m_name;
};

class DirDialog : public QFileDialog
{
    Q_OBJECT

public:
    DirDialog(QString directory = QString(), QWidget* parent = nullptr);
    ~DirDialog();
};

#endif // DIALOGS_H
