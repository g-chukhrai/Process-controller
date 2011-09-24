#include <QtGui>
#include "edge.h"
#include "vertex.h"
#include "math.h"
#include "graphscene.h"
#include "mainwindow.h"

// конструктор вершины
Vertex::Vertex(QMenu *contextMenu, QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsItem(parent, scene)
{
    // установка флагов перемещения и выделения объекта
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    myContextMenu = contextMenu;
    name="";
}

// функция, возвращающая ограничивающий прямоугольник для отрисовки
QRectF Vertex::boundingRect() const
{
    return QRectF(-maxWidth/2,-12,maxWidth,maxWidth);
}

// фукнция отрисовки вершины
void Vertex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // если вершина выделена установить другую кисть
    if (isSelected())
    {
        painter->setPen(Qt::lightGray);
        painter->setBrush(Qt::lightGray);
    }

    painter->setRenderHint(QPainter::Antialiasing, true);

    double nameWidth = name.length() * 8;
    double valueWidth = value.length() * 8;

    // нахождение минимальной ширины вершины
    maxWidth = (nameWidth > valueWidth) ? nameWidth : valueWidth;
    maxWidth = (maxWidth > 40) ? maxWidth : 40;

    //maxWidth += 20;

    // если вершина не выделена установка кисти и карандаша
    if (!isSelected())
    {
        painter->setPen(Qt::black);
        painter->setBrush(Qt::black);
    }
    // отрисовка большего квадрата
    painter->drawRoundedRect(QRectF(-maxWidth/2,-12,maxWidth,maxWidth),5,5);

    if (!isSelected())
    {
        painter->setPen(Qt::blue);
        painter->setBrush(Qt::blue);
    }
    // отрисовка меньшего прямоугольника
    painter->drawRoundedRect(QRectF(-maxWidth/2,-12,maxWidth,24),5,5);

    // установка цвета карандаша
    painter->setPen(Qt::white);
    painter->setFont(QFont("Arial",8,QFont::Bold));
    // отрисовка имени на вершине
    painter->drawText(QPoint(-nameWidth  *.75 / 2  , 5),name);
    painter->setFont(QFont("Arial",11,QFont::Bold));
    // отрисовка веса на вершине
    painter->drawText(QPoint(-valueWidth *.8 / 2  , maxWidth/2 + 5),value);
}

// функция добавления дуги к списку дуг
void Vertex::addArrow(Edge *edge)
{
    edges.append(edge);
}

// функция удаления дуги из списка дуг вершины
void Vertex::removeArrow(Edge *edge)
{
    int index = edges.indexOf(edge);
    // удаление дуги из списка
    if (index != -1)
        edges.removeAt(index);
}

// функция обработчик событий контекстного меню
void Vertex::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->exec(event->screenPos());
}


