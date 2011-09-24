#include "matrixwindow.h"
#include "resultwindow.h"
#include "ui_matrixwindow.h"
#include <QDesktopWidget>
#include <QResizeEvent>

// конструктор окна матрицы
MatrixWindow::MatrixWindow(GraphScene* scn, QWidget *parent) : QDialog(parent), ui(new Ui::MatrixWindow)
{
    ui->setupUi(this);
    scene = scn;
    // вызов функции создани€ матриц
    createTables();
    // вызов функции создани€ матрицы предварительного выполнени€
    createTimeTable();
    setWindowTitle("ƒиспетчер распараллеливани€ процессов");
    setWindowIcon(QIcon(":/images/icon.png"));

    // установка окна по центру
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());
}


void MatrixWindow::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

// функци€ создани€ матриц
void MatrixWindow::createTables()
{
    // нахождение размера матрицы
    int tableSize = scene->allVertexes.count();
    // установка размеров матрицы
    ui->matrixTable->setColumnCount(tableSize);
    ui->matrixTable->setRowCount(tableSize);

    ui->valueTable->setColumnCount(tableSize);
    ui->valueTable->setRowCount(1);

    ui->timeTable->setColumnCount(tableSize);
    ui->timeTable->setRowCount(1);

    // заполнение матрицы нул€ми
    for (int i = 0 ; i < tableSize; i++)
        for (int j = 0 ; j < tableSize ; j++)
        {
        QTableWidgetItem *cell = new QTableWidgetItem("0");
        ui->matrixTable->setItem(i,j,cell);
    }

    // заполение списка имен вершин
    foreach(Vertex* vertex, scene->allVertexes)
        tableLabels << vertex->getName();

    // установка подписей к столбац и строкам матриц
    ui->matrixTable->setVerticalHeaderLabels(tableLabels);
    ui->matrixTable->setHorizontalHeaderLabels(tableLabels);
    ui->valueTable->setHorizontalHeaderLabels(tableLabels);
    ui->timeTable->setHorizontalHeaderLabels(tableLabels);

    // проход по всех вершинах
    foreach(Vertex* vertex, scene->allVertexes)
    {
        int from = tableLabels.indexOf(vertex->getName());
        // проход по всем дугам вершины
        foreach(Edge* edge, vertex->edges)
        {
            // если дуга между вершинами найдена
            if (edge->startItem() == vertex)
            {
                // поставить в €чейку единицу
                int to = tableLabels.indexOf(edge->endItem()->getName());
                QTableWidgetItem *cell = new QTableWidgetItem("1");
                ui->matrixTable->setItem(from,to,cell);
            }
        }
        // поставить в €чейку матрицы весов вес вершины
        QTableWidgetItem *cell = new QTableWidgetItem(vertex->getValue());
        ui->valueTable->setItem(0,from,cell);
    }

    // раст€нуть строки столбцы по содержимому
    ui->matrixTable->resizeColumnsToContents();
    ui->valueTable->resizeColumnsToContents();    
}

// фукнци€ создани€ матрицы предварительного выполнени€
void MatrixWindow::createTimeTable()
{
    // дл€ каждой вершины
    foreach(Vertex* vertex, scene->allVertexes)
    {
        int from = tableLabels.indexOf(vertex->getName());
        int maxTime = -1;
        // дл€ каждой дуги вершины
        foreach(Edge* edge, vertex->edges)
        {
            if (edge->endItem() == vertex)
            {
                // находим список вход€щих путей
                QList<QStringList> result = getInputPath(vertex);
                // дл€ всех найденных путей
                for (int i = 0 ; i < result.count() ; i++)
                {
                    int time= vertex->getValue().toInt();

                    // находим врем€ выполнени€ пути
                    for (int j = 0 ; j < result[i].count() ; j++)
                    {
                        foreach(Vertex* v, scene->allVertexes)
                        {
                            if (v->getName() == result[i][j])
                            {
                                time += v->getValue().toInt();
                                break;
                            }
                        }
                    }
                    // находим максимальное врем€ выполнени€
                    if (time > maxTime)
                        maxTime = time;
                }
                break;
            }
        }
        if (maxTime == -1)
            maxTime = vertex->getValue().toInt();
        // устанавливаем в €чейку значение максимального времени выполнени€
        QTableWidgetItem *cell = new QTableWidgetItem(QString::number(maxTime));
        ui->timeTable->setItem(0,from,cell);
    }
    // раст€гивание колонок
    ui->timeTable->resizeColumnsToContents();
}

// функци€ возвращающа€ все вход€щие пути в вершину
QList<QStringList> MatrixWindow::getInputPath(Vertex* vertex)
{
    QList<QStringList> returnList;

    // дл€ каждого ребра из списка ребер текущей вершины
    foreach(Edge* edge, vertex->edges)
    {
        QStringList list;
        if (edge->endItem() == vertex)
        {
            // рекурсивное получение вход€щих дуг в начальную вершину
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

// функци€ вызова окна распределени€
void MatrixWindow::on_manageProcess_clicked()
{
    close();
    // создание окна
    ResultWindow *resultW = new ResultWindow(ui->matrixTable, ui->valueTable, scene);
    // запуск
    resultW->exec();
}

void MatrixWindow::on_backButton_clicked()
{
    close();
}

// функци€ реагирующа€ на изменение размеров окна
void MatrixWindow::resizeEvent(QResizeEvent *e)
{
    // изменение размеров матриц
    ui->matrixTable->resize(e->size().width() * 460 / 520 ,e->size().height() * 280 / 520);
    ui->valueTable->resize(e->size().width() * 460 / 520 ,e->size().height() * 60 / 520);
    ui->timeTable->resize(e->size().width() * 460 / 520 ,e->size().height() * 60 / 520);
    // изменение координат виджетов
    ui->label_2->setGeometry(ui->label_2->geometry().x(),ui->matrixTable->geometry().bottom(),
                             ui->label_2->geometry().width(),ui->label_2->geometry().height());
    ui->valueTable->setGeometry(ui->valueTable->geometry().x(),ui->label_2->geometry().bottom(),
                                ui->valueTable->geometry().width(),ui->valueTable->geometry().height());
    ui->label_3->setGeometry(ui->label_3->geometry().x(),ui->valueTable->geometry().bottom(),
                             ui->label_3->geometry().width(),ui->label_3->geometry().height());
    ui->timeTable->setGeometry(ui->timeTable->geometry().x(),ui->label_3->geometry().bottom(),
                               ui->timeTable->geometry().width(),ui->timeTable->geometry().height());
    ui->backButton->setGeometry(ui->backButton->geometry().x(),ui->timeTable->geometry().bottom()+10,
                                ui->backButton->geometry().width(),ui->backButton->geometry().height());
    ui->manageProcess->setGeometry(ui->timeTable->geometry().right()-180,ui->timeTable->geometry().bottom()+10,
                                   ui->manageProcess->geometry().width(),ui->manageProcess->geometry().height());

}

MatrixWindow::~MatrixWindow()
{
    delete ui;
}

void MatrixWindow::on_valueTable_cellChanged(int i, int j)
{
    int value = ui->valueTable->item(i,j)->text().toInt();
    if
            (value > 0 && value <= 999999);
    else
       ui->valueTable->item(i,j)->setText("1");

    foreach(Vertex *vertex, this->scene->allVertexes)
    {
        if(vertex->getName() == this->tableLabels[j])
            vertex->setValue(ui->valueTable->item(i,j)->text());
    }
    this->createTimeTable();
}
