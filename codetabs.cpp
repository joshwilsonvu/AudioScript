#include <QtDebug>
#include <QCoreApplication>

#include "codetabs.h"

CodeTabs::CodeTabs(QWidget* parent) : QTabWidget(parent)
{
    setTabsClosable(false);
    addTab(new CodeEditor(this), "Header");
    addTab(new CodeEditor(this), "Source");
}

CodeEditor* CodeTabs::header() const
{
   CodeEditor* h = qobject_cast<CodeEditor*>(widget(0));
   if (!h) {
       qDebug() << "widget(0) failed cast to CodeEditor*";
       h = (CodeEditor*) widget(0);
   }

   return h;
}

CodeEditor* CodeTabs::source() const
{
    CodeEditor* s = qobject_cast<CodeEditor*>(widget(1));
    if (!s) {
        qDebug() << "widget(1) failed cast to CodeEditor*";
        s = (CodeEditor*) widget(1);
    }
    return s;
}

CodeEditor* CodeTabs::current() const
{
    return qobject_cast<CodeEditor*>(currentWidget());
}

bool CodeTabs::isHeader() const
{
    return !currentIndex();
}

bool CodeTabs::isSource() const
{
    return currentIndex();
}

void CodeTabs::setPlainText(const QString &headerText, const QString &sourceText)
{
    header()->setPlainText(headerText);
    source()->setPlainText(sourceText);
}

void CodeTabs::toPlainText(QString &headerText, QString &sourceText) const
{
    headerText = header()->toPlainText();
    sourceText = source()->toPlainText();
}

void CodeTabs::setReadOnly(bool ro)
{
    header()->setReadOnly(ro);
    source()->setReadOnly(ro);
}

bool CodeTabs::isReadOnly() const {
    return header()->isReadOnly() && source()->isReadOnly();
}
