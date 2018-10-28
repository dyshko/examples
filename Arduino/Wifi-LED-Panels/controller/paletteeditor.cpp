#include "paletteeditor.h"

#include <QPainter>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>

PaletteEditor::PaletteEditor(QWidget* parent):
    QWidget(parent)
{
    m_model = Model(8, vector<bool>(32, false));
    m_penRed = QPen(QBrush(Qt::black), 1);
}

int PaletteEditor::boxSize()
{
    return min(width()/32, height()/8);
}

void PaletteEditor::resizePalette(int rows, int columns)
{
    //shrink here
    m_rows = rows;
    m_columns = columns;
}

void PaletteEditor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    int size = boxSize();

    painter.setPen(m_penRed);

    for (int r = 0; r < m_rows; ++r){
        for (int c = 0; c < m_columns; ++c){
            int posY = r*size;
            int posX = c*size;

            painter.setBrush(QBrush((m_model[r][c] ? Qt::red : Qt::transparent)));

            if (r < m_rows && c < m_columns)
                painter.setPen(QColor(Qt::black));
            else
                painter.setPen(QColor(Qt::gray));
            painter.drawEllipse(QRectF(posX, posY, size, size));
            //painter.drawRect(QRectF(posX, posY, size, size));
        }
    }
}

void PaletteEditor::drawAtPixel(const QPoint& pos, bool value){
    int x = pos.x();
    int y = pos.y();

    int c = x/boxSize();
    int r = y/boxSize();

    if (c >= m_columns || c< 0)
        return;
    if (r >= m_rows || r < 0)
        return;

    m_model[r][c] = value;

    m_lastR = r;
    m_lastC = c;

    update();
}

void PaletteEditor::swapAtPixel(const QPoint& pos, bool trackSame){

    int x = pos.x();
    int y = pos.y();

    int c = x/boxSize();
    int r = y/boxSize();

    if (trackSame && m_lastC == c && m_lastR == r)
        return;

    if (c >= m_columns || c< 0)
        return;
    if (r >= m_rows || r < 0)
        return;

    m_model[r][c] = !m_model[r][c];

    m_lastR = r;
    m_lastC = c;

    update();
}

void PaletteEditor::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton)
        swapAtPixel(event->pos(), false);
}

void PaletteEditor::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
        drawAtPixel(event->pos(), true);
    else if (event->buttons() & Qt::RightButton)
        drawAtPixel(event->pos(), false);
}

void PaletteEditor::clear(){
    m_model = Model(m_rows, vector<bool>(m_columns, false));
    update();
}
