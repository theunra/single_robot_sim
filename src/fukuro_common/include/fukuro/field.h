#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <QGraphicsItem>

class Field : public QGraphicsItem
{
public:
    Field();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:
    QVector<QLineF> lines;
    QVector<QLineF> circle_lines;
    QRectF center_circle;
};

#endif // FIELD_H