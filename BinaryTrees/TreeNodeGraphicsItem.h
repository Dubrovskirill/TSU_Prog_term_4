#ifndef TREENODEGRAPHICSITEM_H
#define TREENODEGRAPHICSITEM_H

#include <QGraphicsSimpleTextItem>

class TreeNodeGraphicsItem : public QGraphicsSimpleTextItem
{
public:
    explicit TreeNodeGraphicsItem(const QString &text = "", QGraphicsItem *parent = nullptr);

    int fontSize() const;
    QColor textColor() const;
    QColor borderColor() const;
    QColor fillColor() const;

    void setFontSize(int size);
    void setTextColor(const QColor &color);
    void setBorderColor(const QColor &color);
    void setFillColor(const QColor &color);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QColor m_textColor = Qt::black;
    QColor m_borderColor = Qt::black;
    QColor m_fillColor = Qt::white;
};

#endif // TREENODEGRAPHICSITEM_H
