#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>
#include <QObject>

class Edge;
class GraphWidget;
class QGraphicsSceneMouseEvent;

class Node :  public QGraphicsItem
{
public:
    Node();

    void addEdge(Edge *edge);
    QList<Edge *> edges() const;

    enum { Type = UserType + 1 };
    int type() const { return Type; }

    void calculateForces();
    bool advance();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    double posOfCenterX();
    double posOfCenterY();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QList<Edge *> edgeList;
    QPointF newPos;
};

#endif // NODE_H
