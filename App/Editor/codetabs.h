#ifndef CODETABS_H
#define CODETABS_H

#include <QWidget>
#include <QTabWidget>

#include "codeeditor.h"

class CodeTabs : public QTabWidget
{
    Q_OBJECT

public:
    CodeTabs(QWidget* parent = nullptr);

    CodeEditor* header() const;

    CodeEditor* source() const;

    CodeEditor* current() const;

    bool isHeader() const;

    bool isSource() const;

    // convenience functions
    void setPlainText(QString headerText, QString sourceText);

    void toPlainText(QString& headerText, QString& sourceText) const;

    void setReadOnly(bool ro);

    bool isReadOnly() const;
};

#endif // CODETABS_H
