#include <QtMath>
#include <QPainter>

#include "TreeNodeGraphicsItem.h"

TreeNodeGraphicsItem::TreeNodeGraphicsItem(const QString &text, QGraphicsItem *parent)
    : QGraphicsSimpleTextItem(text, parent)
{}

int TreeNodeGraphicsItem::fontSize() const
{
    return font().pointSize();
}

QColor TreeNodeGraphicsItem::textColor() const
{
    return m_textColor;
}

QColor TreeNodeGraphicsItem::borderColor() const
{
    return m_borderColor;
}

QColor TreeNodeGraphicsItem::fillColor() const
{
    return m_fillColor;
}

void TreeNodeGraphicsItem::setFontSize(int size)
{
    QFont font = this->font();
    font.setPointSize(size);
    this->setFont(font);
}

void TreeNodeGraphicsItem::setTextColor(const QColor &color)
{
    m_textColor = color;
    update();
}

void TreeNodeGraphicsItem::setBorderColor(const QColor &color)
{
    m_borderColor = color;
    update();
}

void TreeNodeGraphicsItem::setFillColor(const QColor &color)
{
    m_fillColor = color;
    update();
}

QRectF TreeNodeGraphicsItem::boundingRect() const
{
    QRectF rect = QGraphicsSimpleTextItem::boundingRect();
    int width = rect.width() * sqrt(2);
    int height = rect.height() * sqrt(2);
    rect.setWidth(qMax(width, height));
    rect.setHeight(qMax(width, height));
    return rect;
}

void TreeNodeGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF textRect = QGraphicsSimpleTextItem::boundingRect();
    textRect.moveTo((boundingRect().width() - textRect.width()) / 2,
                    (boundingRect().height() - textRect.height()) / 2);
    painter->setBrush(QBrush(m_fillColor));
    painter->drawEllipse(boundingRect());
    painter->translate(textRect.x(), textRect.y());
    QGraphicsSimpleTextItem::paint(painter, option, widget);
}
