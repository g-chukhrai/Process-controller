#include <QtGui>
#include "graphscene.h"
#include "edge.h"
#include "mainwindow.h"
#include "infowindow.h"

// конструктор графической сцены
GraphScene::GraphScene(QMenu *itemMenu, QObject *parent) : QGraphicsScene(parent)
{
    myItemMenu = itemMenu;
    // установка состояния перемещения объектов
    myMode = MoveMode;
    // установка счетчика вершин в единицу
    vertexCount = 1;
    line = 0;
    isModified = false;
    // установка значения переменной хранящей вес последней вершины
    lastValue = 1;
    // выделение памяти для окна параметров
    infoW = new InfoWindow(this);
    connect(infoW,SIGNAL(infoUpdate(QString,QString)),this,SLOT(infoUpdate(QString,QString)));
    // установка родителя сцены
    thisParent = parent;
}

// функция - обработчик события нажатия кнопки мыши
void GraphScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    // если была нажата не левая кнопка мыши
    if (mouseEvent->button() != Qt::LeftButton)
    {
        // если была нажата средняя кнопка мыши
        if (mouseEvent->button() == Qt::MidButton)
            // вызов функции изменения режима сцены
            emit setMoveMode();
        return;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);

    // если сцена находится в состоянии добавления дуг
    if(myMode == GraphScene::AddArc)
    {
        // выделить память для линии
        line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),mouseEvent->scenePos()));
        // установить карандаш отрисовки линии
        line->setPen(QPen(Qt::black, 1,Qt::DashLine));
        // добавить линию на сцену
        addItem(line);
    }
    // если сцена находится в режиме перемещения объектов и выделенных объектов нет
    else if (myMode == GraphScene::MoveMode && selectedItems().isEmpty())
    {        
        // установить режим сцены в состояние выделения объектов
        setMode(GraphScene::SelectMode);
        selectP = mouseEvent->scenePos();
        // выделить память для прямоугольника
        selectRect = new QGraphicsRectItem(QRectF(selectP,mouseEvent->scenePos()));
        // добавить прямоугольник на сцену
        addItem(selectRect);
    }
    moveBug = false;
}

// обработчик события перемещения мыши
void GraphScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (moveBug)
        return;
    // если сцена находится в состоянии перемещения объектов
    if (myMode == GraphScene::MoveMode && !selectedItems().isEmpty())
    {
        // вычислить координаты изменения позиции мыши
        int dx = mouseEvent->scenePos().x()-mouseEvent->lastScenePos().x();
        int dy = mouseEvent->scenePos().y()-mouseEvent->lastScenePos().y();
        // если объекты будут перемешены за пределы сцены  - запретить
        if (itemsBoundingRect().left()+dx < sceneRect().left() || itemsBoundingRect().right()+dx > sceneRect().right() ||
            itemsBoundingRect().y()+dy < sceneRect().top() || itemsBoundingRect().bottom()+dy > sceneRect().bottom())
            return;
        // для каждого выделенного объекта
        foreach(QGraphicsItem* selItem,selectedItems()){
            if (selItem->type() == Vertex::Type )
            {
                Vertex *item = qgraphicsitem_cast<Vertex *>(selItem);
                // переместить объект на определенные координаты
                item->moveBy(dx,dy);
            }
        }
    }

    // иначе если сцена в режиме добавления дуги
    else if (myMode == GraphScene::AddArc && line != 0)
    {
        // продлить рисуемую линию
        QLineF newLine(QPointF(line->line().p1().x(),line->line().p1().y()),
                       QPointF(mouseEvent->scenePos().x(),mouseEvent->scenePos().y()));
        line->setLine(newLine);
    }
    // иначе если сцена в режиме выделения
    else if (myMode == GraphScene::SelectMode)
    {
        // удалить старый прямогуольник со сцены
        removeItem(selectRect);
        // создать новый
        selectRect = new QGraphicsRectItem(QRectF(selectP,mouseEvent->scenePos()));
        selectRect->setZValue(300);
        // установить полупрозрачный цвет
        selectRect->setBrush(QColor(177, 235, 230, 100));
        // для каждого объекта сцены
        foreach(QGraphicsItem* item,items())
            // если объект пересекается с прямоугольником - выделить объект
            if (item->collidesWithItem(selectRect))
                item->setSelected(true);
        // иначе - сбросить выдление
        else
            item->setSelected(false);
        // добавить прямоугольник на сцену
        addItem(selectRect);
    }
    // обновить сцену
    update();
}

// функция обработчик события отпускания кнопки мыши
void GraphScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    moveBug = true;
    // если сцена в режиме добавления дуги
    if (myMode == GraphScene::AddArc && line!=0)
    {        
        // получить список объектов под конечными точками линии
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        
        // если списки не пусты
        if (!startItems.isEmpty() && !endItems.isEmpty())
        {
            // если первый и второй объект типа вершина
            if (startItems.first()->type() == Vertex::Type && endItems.first()->type() == Vertex::Type)
            {
                // произвести преобразование объектов
                Vertex *startItem = qgraphicsitem_cast<Vertex *>(startItems.first());
                Vertex *endItem = qgraphicsitem_cast<Vertex *>(endItems.first());
                
                // произвести проверки графа на циклы
                if (checkCycle(endItem, startItem))
                {
                    QWidget* w = qobject_cast<QWidget*>(parent());
                    QMessageBox::warning(w,"Ошибка","Создание циклов невозможно.");
                }
                // если циклов нет и начальная вершина не совпадает с конечной
                else if(startItem!=endItem)
                {
                    // создать новую дугу
                    Edge *edge = new Edge(startItem,endItem);
                    edge->setZValue(-100.0);
                    // добавить дугу на сцену
                    addItem(edge);
                    // обновить позицию дуги
                    edge->updatePosition();
                    isModified = true;
                }
            }
        }
        // удалить линию со сцены
        removeItem(line);
    }
    // если сцена в режиме выделения
    else if (myMode == GraphScene::SelectMode)
    {
        // удалить прямоугольник выделения
        removeItem(selectRect);
        // установить режим сцены в режим перемещения
        setMode(GraphScene::MoveMode);
    }
    // для всех объектов дуг на сцене обновить позиции
    foreach(QGraphicsItem* selItem,items())
    {
        if(selItem->type() == Edge::Type)
        {
            Edge *item = qgraphicsitem_cast<Edge *>(selItem);
            item->updatePosition();
        }
    }
    // снять выделение объектов
    selectedItems().clear();
    // обновить сцену
    update();
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

// функция обработчик события двойного клика мыши
void GraphScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    line = 0;
    // если двойной клик был совершен по вершине
    if (!selectedItems().isEmpty())
    {
        // показать окно выбора параметров
        infoW->move(mouseEvent->screenPos().x()-100,mouseEvent->screenPos().y()-200);
        infoExec();        
    }
    // иначе
    else
    {
        QString lastText = QString::number(lastValue);
        QString name = "process"+QString::number(vertexCount++);
        
        bool isCopy = false;
        do
        {
            foreach(Vertex* v, allVertexes)
            {
                if (v->getName() == name)
                {
                    isCopy = true;
                    vertexCount++;
                    name = "process"+QString::number(vertexCount++);
                    break;
                }
                else
                {
                    isCopy = false;
                }
            }
        }
        while (isCopy);

        // вывести окно выбора параметров вершины
        infoW->setName(name);
        infoW->setValue(lastText);
        infoW->move(mouseEvent->screenPos().x()-100,mouseEvent->screenPos().y()-200);
        infoW->exec();

        // если имя и вес задан
        if (vName != " " && vValue != "")
        {
            lastValue = vValue.toInt();
            // создать новую вершину
            Vertex *vertex = new Vertex(myItemMenu);
            vertex->setPos(mouseEvent->scenePos());
            vertex->setZValue(200);
            // установить вершине параметры
            vertex->setName(vName);
            vertex->setValue(vValue);
            vName = vValue = "";
            // добавить вершину на сцену
            addItem(vertex);
            // добавить вершину к списку всех вершин сцены
            allVertexes.append(vertex);
            isModified = true;
        }
    }
}

// функция вызова окна параметров
void GraphScene::infoExec()
{
    if (!selectedItems().isEmpty())
    {
        if(selectedItems().first()->type() == Vertex::Type)
        {
            Vertex *vertex = qgraphicsitem_cast<Vertex *>(selectedItems().first());
            infoW->setName(vertex->getName());
            infoW->setValue(vertex->getValue());
            infoW->exec();

            if (vName != " " && vValue != "")
            {
                lastValue = vValue.toInt();
                vertex->setName(vName);
                vertex->setValue(vValue);
                vName = vValue = "";
                isModified = true;
            }
        }
    }
}

// функция обновления информации вершины
void GraphScene::infoUpdate(QString name,QString value)
{
    vName = name;
    vValue = value;
}

// функция проверки графа на циклы
bool GraphScene::checkCycle(Vertex *startV, Vertex *endV)
{
    // для каждого ребра конечной вершины
    foreach(Edge* edge, endV->edges)
    {
        if (edge->endItem() == endV)
        {
            // найти все входящие пути в данную вершину
            QList<QStringList> result = getInputPath(endV);
            // просмотр всех входящих путей
            for (int i = 0 ; i < result.count() ; i++)
            {
                for (int j = 0 ; j < result[i].count() ; j++)
                {
                    // если результат путь начальную вершину цикл найден
                    if (result[i][j] == startV->getName())
                        return true;
                }
            }
        }
    }
    return false;
}

// функция возвращающая все входящие пути в вершину
QList<QStringList> GraphScene::getInputPath(Vertex* vertex)
{
    QList<QStringList> returnList;

    // для каждого ребра из списка ребер текущей вершины
    foreach(Edge* edge, vertex->edges)
    {
        QStringList list;
        if (edge->endItem() == vertex)
        {
            // рекурсивное получение входящих дуг в начальную вершину
            QList<QStringList>  appList = getInputPath(edge->startItem());
            // если дуги не найдены
            if (appList.isEmpty())
            {
                // добавление в список вершины
                list << edge->startItem()->getName();
                appList << list;
            }
            // иначе
            else
            {
                // добавление к списку найденного списка
                for (int i = 0 ; i < appList.count() ; i++)
                {
                    appList[i].push_front(edge->startItem()->getName());
                }
            }
            // прибавление к возвращаемому списку дополнительного списка
            returnList += appList;
        }
    }
    // возвращение результата
    return returnList;
}

// функция сохранения граф в файл
bool GraphScene::save(QFile *file)
{
    // создание писателя в файл
    QXmlStreamWriter xmlWriter(file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeComment("Filesave Controller");
    xmlWriter.writeStartElement("doc");
    // для каждой вершины из списка вершин
    foreach(Vertex* item, allVertexes)
    {
        // запись типа объекта
        xmlWriter.writeStartElement("Item");
        xmlWriter.writeAttribute("Type",QString::number(item->type()));
        // запись координат объекта
        xmlWriter.writeEmptyElement("ItemPos");
        xmlWriter.writeAttribute("x",QString::number(item->pos().x()));
        xmlWriter.writeAttribute("y",QString::number(item->pos().y()));
        xmlWriter.writeAttribute("z",QString::number(item->zValue()));
        // запись имени и веса объекта
        xmlWriter.writeEmptyElement("ItemName");
        xmlWriter.writeAttribute("name",item->getName());
        xmlWriter.writeAttribute("value",item->getValue());
        xmlWriter.writeEndElement();
    }
    // для каждой дуги запись основных параметров в файл
    foreach(QGraphicsItem* selItem, items())
    {
        if (selItem->type() == Edge::Type)
        {
            Edge *item = qgraphicsitem_cast<Edge *>(selItem);

            xmlWriter.writeStartElement("Item");
            xmlWriter.writeAttribute("Type",QString::number(item->type()));
            xmlWriter.writeEmptyElement("ItemPos");
            xmlWriter.writeAttribute("x",QString::number(item->pos().x()));
            xmlWriter.writeAttribute("y",QString::number(item->pos().y()));
            xmlWriter.writeAttribute("z",QString::number(item->zValue()));
            xmlWriter.writeEmptyElement("ItemName");
            xmlWriter.writeAttribute("start_name",item->startItem()->getName());
            xmlWriter.writeAttribute("end_name",item->endItem()->getName());
            xmlWriter.writeEndElement();
        }
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    return true;
}

// функция загрузки графа из файла
bool GraphScene::load(QFile *file)
{
    // создание считывателя данных
    QXmlStreamReader xmlReader(file);
    int ItemType = 0;
    QPointF mPos;
    qreal z;
    Vertex *insertedItem = 0,*startItm, *endItm;
    Edge  * insertedArrow = 0;

    // пока не щакончится файл
    while(!xmlReader.atEnd()){
        xmlReader.readNext();
        if(xmlReader.isStartDocument()) continue;
        if(xmlReader.isStartElement()){
            if(xmlReader.name()=="doc") continue;
            if(!ItemType and (xmlReader.name()=="Item")){
                bool ok;
                // считывание типа объекта
                ItemType = xmlReader.attributes().value("Type").toString().toInt(&ok);
                if(!ok)
                {
                    xmlReader.raiseError(tr("Item: type number conversion failed"));
                }
                continue;
            }
            // считывание координат объекта
            if(ItemType and (xmlReader.name()=="ItemPos")){
                bool ok,okay;
                okay=true;
                mPos.setX(xmlReader.attributes().value("x").toString().toDouble(&ok));
                okay&=ok;
                mPos.setY(xmlReader.attributes().value("y").toString().toDouble(&ok));
                okay&=ok;
                z=xmlReader.attributes().value("z").toString().toDouble(&ok);
                okay&=ok;
                if(!okay)
                {
                    xmlReader.raiseError(tr("Pos: number conversion failed"));
                }
                continue;
            }
            if(ItemType and (xmlReader.name()=="ItemName")){
                // в зависимости от типа объекта
                switch (ItemType) {
                case QGraphicsItem::UserType+69:
                    {
                        // создание вершины
                        insertedItem = new Vertex(myItemMenu);
                        insertedItem->setPos(mPos);
                        insertedItem->setZValue(z);

                        QString name  = xmlReader.attributes().value("name").toString();
                        QString value = xmlReader.attributes().value("value").toString();
                        insertedItem->setName(name);
                        insertedItem->setValue(value);
                        insertedItem->update();
                        // добавление на сцену
                        addItem(insertedItem);
                        allVertexes.append(insertedItem);

                        break;
                    }
                case QGraphicsItem::UserType+4:
                    {
                        // считывание имени начальной и конечной вершины
                        QString start = xmlReader.attributes().value("start_name").toString();
                        QString end = xmlReader.attributes().value("end_name").toString();

                        bool isStFound =false,isEndFound = false;
                        // проходя все вершины
                        foreach(QGraphicsItem* selItem, items())
                        {
                            if(selItem->type() == Vertex::Type)
                            {
                                Vertex *item = qgraphicsitem_cast<Vertex *>(selItem);
                                // находим начальную вершину
                                if (item->getName() == start)
                                {
                                    startItm = item;
                                    isStFound = true;
                                }
                                // и конечную вершину
                                if(item->getName() == end)
                                {
                                    endItm = item;
                                    isEndFound = true;
                                }
                            }
                        }
                        // если найдена начальная и конечная вершина
                        if (isStFound && isEndFound)
                        {
                            // создаем новую дугу
                            insertedArrow = new Edge(startItm, endItm);
                            insertedArrow->setZValue(z);
                            // добавляем дугу на сцену и обновляем позицию
                            addItem(insertedArrow);
                            insertedArrow->updatePosition();
                        }
                        else
                        {
                            QMessageBox::warning(0,"Ошибка загрузки","Ребро графа не может быть добавлено.");
                            return false;
                        }
                        break;
                    }
                default:
                    break;
                }
                continue;
            }
            continue;
        }
        if(xmlReader.isEndElement()){
            if(ItemType and (xmlReader.name()=="Item")){
                ItemType = 0;
                insertedItem = 0;
                insertedArrow = 0;
            }
        }
    }

    insertedItem = 0;
    insertedArrow = 0;
    setMode(MoveMode);
    update();
    return true;
}


