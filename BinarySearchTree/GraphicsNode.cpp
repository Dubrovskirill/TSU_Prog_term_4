#include "GraphicsNode.h"

#include <QPainter>
#include <QtMath>

GraphicsNode::GraphicsNode(const QString &text,QGraphicsItem *parent)
    :QGraphicsSimpleTextItem(text, parent)
{
}

QColor GraphicsNode::textColor() const
{
    return m_textColor;
}
QColor GraphicsNode::borderColor() const
{
    return m_borderColor;
}
QColor GraphicsNode::fillColor() const
{
    return m_fillColor;
}

int GraphicsNode::fontSize() const
{
    return font().pointSize();
}

void GraphicsNode::setTextColor(const QColor &color)
{
    m_textColor = color;
    update();
}
void GraphicsNode::setBorderColor(const QColor &color)
{
    m_borderColor = color;
    update();
}
void GraphicsNode::setFillColor(const QColor &color)
{
    m_fillColor = color;
    update();
}

void GraphicsNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF textRect = QGraphicsSimpleTextItem::boundingRect();
    textRect.moveTo((boundingRect().width() - textRect.width()) / 2, (boundingRect().height() - textRect.height()) / 2);
    painter->setBrush(QBrush(m_fillColor));
    painter->drawEllipse(boundingRect());
    painter->translate(textRect.x(), textRect.y());
    QGraphicsSimpleTextItem::paint(painter, option, widget);
}

void GraphicsNode::setFontSize(int size)
{
    QFont font = this->font();
    font.setPointSize(size);
    this->setFont(font);
}

QRectF GraphicsNode::boundingRect() const
{
    QRectF rect = QGraphicsSimpleTextItem::boundingRect();
    int width = rect.width() * sqrt(2);
    int height = rect.height() * sqrt(2);
    rect.setWidth(qMax(width,height));
    rect.setHeight(qMax(width,height));
    return rect;
}
