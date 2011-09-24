#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H
#include <QGraphicsScene>
#include <QFile>
#include "vertex.h"
#include "edge.h"
#include "infowindow.h"

class GraphScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GraphScene(QMenu *itemMenu, QObject *parent = 0);
    enum Mode { AddVertex, AddArc, MoveMode, SelectMode};

    void setFileName(QString fn)
    { fileName = fn; }
    QString getFileName()
    { return fileName; }

    void setMode(Mode mode)
    { myMode = mode;}
    Mode getMode()
    { return myMode; }
    bool save(QFile *file);
    bool load(QFile *file);

    void setMoveBug(bool bl)
    { moveBug = bl; }
    void setModified(bool bl)
    { isModified = bl; }
    bool getModified()
    { return isModified; }

    void setVertexCount (int count)
    { this->vertexCount = count; }
    int getVertexCount()
    { return this->vertexCount; }

    QList<Vertex*> allVertexes;

public slots:
    void infoUpdate(QString, QString);
    void infoExec();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);

signals:
    void setMoveMode();
private:
    InfoWindow *infoW;
    QString fileName;
    Mode myMode;
    bool moveBug,isModified;
    QGraphicsRectItem *selectRect;
    QPointF selectP;
    QMenu *myItemMenu;
    QGraphicsLineItem *line;
    int vertexCount,lastValue;
    QString vName,vValue;
    bool checkCycle(Vertex* startV,Vertex* endV);
    QList<QStringList> getInputPath(Vertex* vertex);
    QObject *thisParent;
};

#endif
