#ifndef GRAPHICSNODE_H
#define GRAPHICSNODE_H

#include <QGraphicsSimpleTextItem>

class GraphicsNode : public QGraphicsSimpleTextItem
{
public:
    GraphicsNode(const QString &text,QGraphicsItem *parent = nullptr);
    QColor textColor() const;
    QColor borderColor() const;
    QColor fillColor() const;

    int fontSize() const;
    void setTextColor(const QColor &color) ;
    void setBorderColor(const QColor &color);
    void setFillColor(const QColor &color);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void setFontSize(int size);
    QRectF boundingRect() const override;

private:
    QColor m_textColor = Qt::black;
    QColor m_borderColor = Qt::black;
    QColor m_fillColor = Qt::white;
};


#endif // GRAPHICSNODE_H
