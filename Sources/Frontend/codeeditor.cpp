
#include <QMessageBox>
#include <QDebug>
#include <QDir>
#include <QPainter>
#include <QKeyEvent>
#include <QApplication>

#include "codeeditor.h"

// class CodeEditor
CodeEditor::CodeEditor(QWidget *parent)
    : QPlainTextEdit(parent), lineNumberArea(this), highlighter(this)
{
    QFont font;
    font.setFamily("Courier");
    font.setStyleHint(QFont::Monospace);
    font.setFixedPitch(true);
    setFont(font);
    int tabWidth = 4;
    QFontMetrics metrics(font);
    setTabStopWidth(metrics.width(' ') * tabWidth);

    highlighter.reset();

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

int CodeEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea.setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::keyPressEvent(QKeyEvent *e)
{
    /*
    QString text;
    int spaces(0);
    switch (e->key()) {
    case Qt::Key_Tab:
        spaces = 4 - textCursor().positionInBlock() % 4;
        text = QString(spaces, ' ');
        QPlainTextEdit::insertPlainText(text);
        break;
    default:
        e->ignore();
        break;
    }
    */
    QPlainTextEdit::keyPressEvent(e);
}

void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea.scroll(0, dy);
    else
        lineNumberArea.update(0, rect.y(), lineNumberArea.width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}



void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(220, 255, 255); // light cyan

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(&lineNumberArea);
    painter.fillRect(event->rect(), Qt::white);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::gray);
            painter.drawText(0, top, lineNumberArea.width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}



const TextCharFormatPack& CodeEditor::getTextCharFormatPack() const
{
    return highlighter.formats;
}

void CodeEditor::setTextCharFormatPack(const TextCharFormatPack& format)
{
    highlighter.formats = format;
    highlighter.reset();
}

// class Highlighter
CodeEditor::Highlighter::Highlighter(CodeEditor* editor)
    : QSyntaxHighlighter(editor->document())
{
    formats.keyword.setForeground(Qt::darkMagenta);
    formats.keyword.setFontWeight(QFont::Bold);
    formats.function.setForeground(Qt::darkBlue);
    formats.quotation.setForeground(Qt::darkRed);
    formats.comment.setForeground(Qt::darkGreen);
    formats.comment.setFontItalic(true);
    formats.preprocessor.setForeground(Qt::darkGray);
}

void CodeEditor::Highlighter::highlightBlock(const QString &text)
{
    // All rules
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
    handleMultiLineComments(text);
}

void CodeEditor::Highlighter::handleMultiLineComments(const QString& text)
{
    setCurrentBlockState(0); // state of last highlight: 0 = un-block-commented, 1 = block-commented
    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);
    while (startIndex >= 0) {
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                    + match.capturedLength();
        }
        setFormat(startIndex, commentLength, formats.comment);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}

void CodeEditor::Highlighter::reset()
{
    HighlightingRule rule;

    // Functions
    rule.pattern = QRegularExpression("\\b[A-Za-z_][A-Za-z0-9_]*(?=\\()");
    rule.format = formats.function;
    highlightingRules << rule;

    // Keywords
    rule.pattern = QRegularExpression(
                "\\b(auto|break|case|char|const|continue|default|do|double|" // C
                "else|enum|extern|float|for|goto|if|int|long|register|return|short|"
                "signed|sizeof|static|struct|switch|typedef|union|unsigned|void|"
                "volatile|while|"
                "bool|catch|class|const_cast|delete|dynamic_cast|" // C & C++
                "explicit|false|friend|inline|mutable|namespace|"
                "new|operator|private|protected|public|reinterpret_cast|"
                "static_cast|template|this|throw|true|try|"
                "typeid|typename|using|virtual)\\b");
    rule.format = formats.keyword;
    highlightingRules << rule;

    // Quotations
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = formats.quotation;
    highlightingRules << rule;

    // Comments
    rule.pattern = QRegularExpression("//[^\n]*");
    rule.format = formats.comment;
    highlightingRules << rule;

    // Preprocessor
    rule.pattern = QRegularExpression("^#.*$");
    rule.format = formats.preprocessor;
    highlightingRules << rule;

    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");

    rehighlight(); // apply changes to full document
}
