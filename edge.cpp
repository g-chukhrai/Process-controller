#include <QtGui>
#include "edge.h"
#include <math.h>

// конструктор дуги
Edge::Edge(Vertex *startItem, Vertex *endItem,QGraphicsItem *parent, QGraphicsScene *scene): QGraphicsLineItem(parent, scene)
{
    // начальная и конечная вершина
    myStartItem = startItem;
    myEndItem = endItem;

    // добавление дуги к начальной и конечной вершине
    startItem->addArrow(this);
    endItem->addArrow(this);

    // установка возможности выделения дуги
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

// функция возвращающая прямоугольник отрисовки
QRectF Edge::boundingRect() const
{
    qreal extra = 20;
    // возврат прямоугольника между вершинами
    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),line().p2().y() - line().p1().y()))
    .normalized().adjusted(-extra, -extra, extra, extra);
}

// функция возвращающая область взаимойдествия с дугой
QPainterPath Edge::shape() const
{
    // получаем форму линии
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(poly);
    // добавляем к форме окончание дуги
    path.addPolygon(arrowHead);
    return path;
}

// функция отрисоки дуги
void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                 QWidget *)
{
    // при пересечении вершин дуга не отрисовывается
    if (myStartItem->collidesWithItem(myEndItem))
        return;

    // установка размера конца дуги
    qreal arrowSize = 15;
    painter->setRenderHint(QPainter::Antialiasing);

    // если дуга выделена
    if (isSelected())
    {
        // изменить цвет отрисовки
        painter->setPen(QPen(Qt::lightGray,2));
        painter->setBrush(Qt::lightGray);
    }
    // иначе
    else
    {
        // установить стандартный цвет отрисовки
        painter->setPen(QPen(Qt::black,2));
        painter->setBrush(Qt::black);
    }

    QLineF centerLine(myStartItem->pos(), myEndItem->pos());
    // определение формы конечной вершины
    QPolygonF endPolygon = myEndItem->boundingRect();
    // задание точки соприкосновения дуги и конечной вершины
    QPointF p1 = endPolygon.first() + myEndItem->pos();
    QPointF p2;
    QPointF intersectPoint;
    QLineF polyLine;
    // выравнивание дуги по полигону конечной вершины
    for (int i = 1; i < endPolygon.count(); ++i)
    {
        p2 = endPolygon.at(i) + myEndItem->pos();
        polyLine = QLineF(p1, p2);
        QLineF::IntersectType intersectType =
                polyLine.intersect(centerLine, &intersectPoint);
        if (intersectType == QLineF::BoundedIntersection)
            break;
        p1 = p2;
    }
    // установка новой линии
    setLine(QLineF(intersectPoint, myStartItem->pos()));

    // высчитывание угла наклона линии
    const qreal Pi = 3.14;
    double angle = ::acos(line().dx() / line().length());
    if (line().dy() >= 0)
        angle = (Pi * 2) - angle;

    // нахождение точек конца дуги
    QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
                                            cos(angle + Pi / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                            cos(angle + Pi - Pi / 3) * arrowSize);

    arrowHead.clear();
    // создание конца дуги
    arrowHead << line().p1() << arrowP1 << arrowP2;
    // отрисовка линии
    painter->drawLine(line());
    // отрисовка конца дуги
    painter->drawPolygon(arrowHead);
}

// функция обновление координат дуги
void Edge::updatePosition()
{
    // установка новой линии в зависимости от координат объектов
    QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
    setLine(line);
}
