#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QObject>
#include <QSyntaxHighlighter>
#include <QVector>
#include <QRegularExpression>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QSize>
#include <QWidget>
#include <QTextCharFormat>

struct TextCharFormatPack
{
    QTextCharFormat keyword;
    QTextCharFormat comment;
    QTextCharFormat quotation;
    QTextCharFormat function;
    QTextCharFormat preprocessor;
};

// CodeEditor
class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEditor(QWidget* parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    const TextCharFormatPack& getTextCharFormatPack() const;
    void setTextCharFormatPack(const TextCharFormatPack&);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect&, int);

private:

    // LineNumberArea
    class LineNumberArea : public QWidget
    {
    public:
        LineNumberArea(CodeEditor *editor) : QWidget(editor), codeEditor(editor)
        {}

        QSize sizeHint() const override {
            return QSize(codeEditor->lineNumberAreaWidth(), 0);
        }

    protected:
        void paintEvent(QPaintEvent *event) override {
            codeEditor->lineNumberAreaPaintEvent(event);
        }

    private:
        CodeEditor* codeEditor;
    };

    // Highlighter
    class Highlighter : public QSyntaxHighlighter
    {
    public:
        Highlighter(CodeEditor* editor);
        void reset();

        // Text formats
        TextCharFormatPack formats;

    protected:
        virtual void highlightBlock(QString text) override;

    private:
        void handleMultiLineComments(QString text);

        struct HighlightingRule
        {
            QRegularExpression pattern;
            QTextCharFormat format;
        };
        QRegularExpression commentStartExpression;
        QRegularExpression commentEndExpression;

        QVector<HighlightingRule> highlightingRules;
    };

    LineNumberArea lineNumberArea;
    Highlighter highlighter;
};



#endif
