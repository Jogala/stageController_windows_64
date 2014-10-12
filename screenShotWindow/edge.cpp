#include "edge.h"
#include "node.h"

#include <math.h>

#include <QPainter>
#include <QDebug>
static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

Edge::Edge(Node *sourceNode, Node *destNode)
    : arrowSize(10)
{
    this->setZValue(1);
    setAcceptedMouseButtons(0);
    source = sourceNode;
    dest = destNode;
    source->addEdge(this);
    dest->addEdge(this);
    adjust();
}

Node *Edge::sourceNode() const
{
    return source;
}

Node *Edge::destNode() const
{
    return dest;
}

void Edge::adjust()
{
     double radiusOfNode = 5;

    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, -5,-5), mapFromItem(dest, -5, -5));

    prepareGeometryChange();


    if (line.length() > radiusOfNode) {


        sourcePoint = line.p1();
        destPoint = line.p2();

    } else {
        sourcePoint = destPoint = line.p1();
    }
}

QRectF Edge::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    // Draw the line itself
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

//    // Draw the arrows
//    double angle = ::acos(line.dx() / line.length());
//    if (line.dy() >= 0)
//        angle = TwoPi - angle;


//    QPointF destArrowP1 = destPoint + QPointF(sin(angle - Pi / 3) * arrowSize,
//                                              cos(angle - Pi / 3) * arrowSize);
//    QPointF destArrowP2 = destPoint + QPointF(sin(angle - Pi + Pi / 3) * arrowSize,
//                                              cos(angle - Pi + Pi / 3) * arrowSize);

//    painter->setBrush(Qt::black);
//    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
}
