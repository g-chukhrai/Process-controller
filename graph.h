#ifndef GRAPH_H
#define GRAPH_H
#include <QList>
#include <QStringList>
#include <QProgressBar>
#include "resultwindow.h"

class Graph
{

public:
    Graph(QList<QStringList> m , QStringList names, QStringList values);
    ~Graph();
     QList<QPair<QString,QString> > * startDealing(int countProc);

private:
    QList<QStringList> matrix;
    QStringList vertexNames;
    QStringList valueList;
    int procCount;

private:
    QList<QPair<QString,QString> > findEnters();
    QList<QPair<QString,QString> > dealingProcess(QList<QPair<QString,QString> > procList, int prCount);

};

#endif // GRAPH_H
