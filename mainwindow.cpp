#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QLabel>
#include <QList>
#include <QFileDialog>
#include "mainwindow.h"
#include "matrixwindow.h"
#include "graphscene.h"
#include "edge.h"
#include "graph.h"
#include <math.h>

//Конструктор главного окна
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // вызов функции создания меню
    createMenus();
    // создание графической сцены
    scene = new GraphScene(itemMenu);
    // задание сцене размера
    scene->setSceneRect(QRectF(0, 0, 2000, 2000));
    connect(scene, SIGNAL(setMoveMode()),this, SLOT(setMoveMode()));
    // привязка сцены к виджету
    ui->graphicsView->setScene(scene);

    connect(ui->saveAction,SIGNAL(triggered()),this,SLOT(save()));
    connect(ui->saveAction,SIGNAL(triggered()),this,SLOT(saveAs()));
    ui->saveAsAction->setShortcut(tr("Ctrl+Shift+s"));
    connect(ui->loadAction,SIGNAL(triggered()),this,SLOT(load()));
    connect(ui->newAction,SIGNAL(triggered()),this,SLOT(newFile()));
    connect(ui->exitAction,SIGNAL(triggered()),this,SLOT(exit()));
    connect(ui->aboutAction,SIGNAL(triggered()),this,SLOT(about()));
    ui->exitAction->setShortcut(tr("Alt+F4"));

    // установка заголовка окна
    programmTitle = "Диспетчер поярусного распределения";
    // вызов функции создания нового файла
    newFile();

    // установка размера главного окна
    //setFixedSize(800,600);
    // установка главного окна по центру экрана
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());
}

// функция обработки событий программы
void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

// функция создания меню программы
void MainWindow::createMenus()
{
    // создание кнопки удаления элемента
    deleteAction = new QAction(QIcon(":/images/delete.png"),"Удалить элемент", this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setToolTip("Удалить элемент со сцены");
    connect(deleteAction, SIGNAL(triggered()),this, SLOT(deleteButton_clicked()));

    // создание кнопки удаления всех элементов
    QAction *deleteAllAction = new QAction(QIcon(":/images/deleteAll.png"),"Удалить все элементы", this);
    deleteAllAction->setShortcut(tr("Ctrl+Shift+Delete"));
    deleteAllAction->setToolTip("Удалить все элементы");
    connect(deleteAllAction, SIGNAL(triggered()),this, SLOT(deleteAll()));

    // создание кнопки вызова окна параметров вершины
    QAction *infoAct = new QAction(QIcon(":/images/info.png"),"Изменить информацию", this);
    infoAct->setShortcut(tr("Ctrl+i"));
    connect(infoAct, SIGNAL(triggered()),this, SLOT(infoExec()));

    // создание контекстного меню вершины
    itemMenu = new QMenu("Меню вершины");
    // добавление в контекстное меню кнопок удалить и изменить информацию
    itemMenu->addAction(deleteAction);
    itemMenu->addAction(infoAct);

    // создание кнопки просмотра матрицы
    viewMatrixAction = new QAction(QIcon(":/images/next.png"),"Просмотреть матрицу", this);
    viewMatrixAction->setShortcut(tr("Ctrl+m"));
    viewMatrixAction->setToolTip("Удалить элемент со сцены");
    connect(viewMatrixAction, SIGNAL(triggered()),this, SLOT(viewMatrix_clicked()));

    // создание кнопки изменяющей состояние сцены
    addArcAction = new QAction(QIcon(":/images/arc.png"),"Добавить дугу", this);
    addArcAction->setShortcut(tr("Ctrl+e"));
    addArcAction->setCheckable(true);
    addArcAction->setToolTip("Удалить элемент со сцены");
    connect(addArcAction, SIGNAL(triggered()),this, SLOT(addArc_clicked()));

    // добавление в тулбар кнопок добавления, удаления, просмотра
    ui->mainToolBar->addAction(addArcAction);
    ui->mainToolBar->addAction(deleteAction);
    ui->mainToolBar->addAction(deleteAllAction);
    ui->mainToolBar->addAction(viewMatrixAction);
    // установка шрифта тулбара
    ui->mainToolBar->setFont(QFont("Arial Narrow", 10));  
}

// функция обрабочик нажатия кнопки создания нового файла
void MainWindow::newFile()
{
    // очиста сцены
    scene->clear();
    // очистка списка всех вершин
    scene->allVertexes.clear();
    scene->setVertexCount(1);
    setCurrentFileName("");
}

// функия сохранения текущего графа
bool MainWindow::save()
{
    // если у сцены отсутствует имя
    if (scene->getFileName().isEmpty())
    {
        // вызвать функцию сохранить как
        return saveAs();
    }
    // открытие файла с указанныым именем
    QFile file(scene->getFileName());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        QMessageBox::warning(this,"Ошибка сохранения графа",file.errorString());
    else
    {
        // очистка файла
        file.remove(scene->getFileName());
        // вызов функции сохранения
        scene->save(&file);
        scene->setModified(false);
        return true;
    }
    return false;
}

// функция сохранения файла с новым именем
bool MainWindow::saveAs()
{
    // получение имени файла из файлового диалога
    QString fileName = QFileDialog::getSaveFileName(this,"Сохранить как...",".ctrl","Файл диспетчера (*.ctrl)");
    if (fileName.isEmpty())
        return false;

    // открытие файла
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(this,"Ошибка сохранения файла",file.errorString());
    }
    else
    {
        // вызов функции сохранения файла
        if(scene->save(&file))
        {
            // вызов функции установки имени файла
            setCurrentFileName(fileName);
            scene->setModified(false);
            return true;
        }
        // закрытие файла
        file.close();
    }
    return false;
}

// функция загрузки графа из файла
bool MainWindow::load()
{
    // получение имени открываемого файла
    QString fileName =  QFileDialog::getOpenFileName(this,"Открыть файл",".ctrl","Файл диспетчера (*.ctrl)");
    QFile file(fileName);
    // открытие файла
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"Ошибка загрузки файла",file.errorString());
    }
    else
    {
        // создание нового файла
        newFile();
        // вызов функции загрузки файла
        scene->load(&file);
        // установка имени файла
        setCurrentFileName(fileName);
        // вызов функции центрирования графа
        centerScrollBar();
        return true;
    }
    return false;
}

// функция предлагающая сохранить изменения
bool MainWindow::maybeSave()
{
    // если сцена не была изменена вернуться
    if (scene->getModified() == false)
        return true;
    if (scene->getFileName().startsWith(QLatin1String(":/")))
        return true;

    // создание окна сообщения
    QMessageBox saveBox(this);
    saveBox.setIcon(QMessageBox::Information);
    saveBox.setWindowTitle(programmTitle);
    saveBox.setText("Сохранить изменения?");
    QPushButton *saveButton = saveBox.addButton("Сохранить",QMessageBox::ActionRole);
    QPushButton *saveAsButton = saveBox.addButton("Сохранить как",QMessageBox::ActionRole);
    saveBox.addButton("Не сохранять",QMessageBox::ActionRole);
    QPushButton *abortButton = saveBox.addButton("Отмена",QMessageBox::ActionRole);
    saveBox.exec();

    // обработчик событий нажатий на определенную кнопку
    if (saveBox.clickedButton() == saveButton)
        save();
    if (saveBox.clickedButton() == saveAsButton)
        saveAs();
    else if (saveBox.clickedButton() == abortButton)
        return false;

    return true;
}

// функция установки имени файла
void MainWindow::setCurrentFileName(const QString &fileName)
{
    // установка имени сцене
    scene->setFileName(fileName);
    QString shownName;
    // переменная счетчик количества созданных файлов
    static int sequenceNumber = 1;

    // если у сцены нет имени сделать показываемым именем Безымянный
    if (scene->getFileName().isEmpty())
        shownName = QString("%2 | Безымянный %1.ctrl").arg(sequenceNumber++).arg(programmTitle);
    // иначе сделать именем имя сцены
    else
        shownName = programmTitle + " | " + QFileInfo(scene->getFileName()).fileName();

    // установка имени окна
    setWindowTitle(shownName);
    scene->setModified(false);
}

// функция обработчик нажатия кнопки добавить дугу
void MainWindow::addArc_clicked()
{
    // если кнопка нажата  устанавливаем сцену в режим добавления дуги
    if (addArcAction->isChecked())
        scene->setMode(GraphScene::AddArc);
    // иначе устанавливаем сцену в режим перемещения
    else
        scene->setMode(GraphScene::MoveMode);
}

// функция обработчик нажатия кнопки удалить
void MainWindow::deleteButton_clicked()
{
    // для каждого объекта на сцене
    foreach (QGraphicsItem *item, scene->selectedItems())
    {
        // если тип объекта - вершина
        if (item->type() == Vertex::Type)
        {
            // производим преобразование между объектами
            Vertex *curItem = qgraphicsitem_cast<Vertex *>(item);
            // для каждого ребра из списка ребер текущей вершины
            foreach(Edge* edge, curItem->edges)
            {
                // удаляем ребро из списка ребер конечной вершины
                edge->endItem()->edges.removeOne(edge);
                // удаляем ребро со сцены
                scene->removeItem(edge);
            }
            // удаляем вершину из списка вершин
            scene->allVertexes.removeOne(curItem);
        }
        // если тип объекта - ребро
        if (item->type() == Edge::Type)
        {
            // производим преобразование между объектами
            Edge *edge = qgraphicsitem_cast<Edge *>(item);
            // из списка ребер начальной и конечной вершины удаляем ребро
            edge->startItem()->removeArrow(edge);
            edge->endItem()->removeArrow(edge);
        }
        // удаляем ребро со сцены
        scene->removeItem(item);
    }
    // сцена изменилась
    scene->setModified(true);
    // если список вершин пуст
    if(scene->allVertexes.isEmpty())
    {
        // устанавливаем в 1 счетчик вершин
        scene->setVertexCount(1);
    }
}

// функция удаления всех объектов со сцены
void MainWindow::deleteAll()
{
    // очистка сцены
    scene->clear();
    // установка счетчика вершин в единицу
    scene->setVertexCount(1);
    if (!scene->allVertexes.isEmpty())
    {
        // очистка списка всех вершин
        scene->allVertexes.clear();
    }
    // обновление сцены
    scene->update();
    // измение переменной модификаций сцены
    scene->setModified(false);
}


// функция обработчик нажатия кнопки просмотра матрицы
void MainWindow::viewMatrix_clicked()
{
    // если на сцене нет объектов выдать сообщение
    if (scene->allVertexes.isEmpty())
    {
        QMessageBox::warning(this,"Ошибка","Добавьте процессы");
    }
    // иначе создать и запустить окно отображения матрицы
    else
    {
        MatrixWindow *matrix = new MatrixWindow(scene);
        matrix->exec();
    }
}

// функция центрирования графа
void MainWindow::centerScrollBar()
{
    // получение ширины и высоты виджета
    int w = ui->graphicsView->width(), h = ui->graphicsView->height();
    // получение прямоугольника ограничивающего все объекты
    QRectF  itemsRect = scene->itemsBoundingRect();
    // получение указателей на скролл бары
    QScrollBar *vBar = ui->graphicsView->verticalScrollBar(), *hBar = ui->graphicsView->horizontalScrollBar();
    // обновление положения скролл баров
    vBar->setValue(itemsRect.top() + itemsRect.height()/2 - h/2);
    hBar->setValue(itemsRect.left() + itemsRect.width()/2 - w/2);
}

// функция установки состояния сцены
void MainWindow::setMoveMode()
{
    // если была нажата кнопка добавления дуги
    if (addArcAction->isChecked())
    {
        // отжать кнопку
        addArcAction->setChecked(false);
        // установить состояние сцены в режим перемещения
        scene->setMode(GraphScene::MoveMode);
    }
    else
    {
        // иначе нажать на кнопку
        addArcAction->setChecked(true);
        // изменить состояние сцены
        scene->setMode(GraphScene::AddArc);
    }
}

// функция закрытия главного окна
void MainWindow::exit()
{
    close();
}

// функция вызова окна параметров вершин
void MainWindow::infoExec()
{
    scene->infoExec();
}

// функция вызова окна со справкой
void MainWindow::about()
{
    // создание окна
    QMessageBox msgBox(QMessageBox::Information,QString("О программе..."),
                       QString("\n\nПрограмма предназначена для распараллеливания процессов с помощью поярусного распределения."));
    msgBox.setIconPixmap(QPixmap(":/images/icon.png"));
    msgBox.setFont(QFont("Arial",12));
    // запуск окна
    msgBox.exec();
}


// функция обработчик события закрытия окна
void MainWindow::closeEvent(QCloseEvent *event)
{
    // если операции по сохранению выполнены разрешить событие
    if (maybeSave())
        event->accept();
    // иначе отклонить
    else
        event->ignore();
}

// деструктор окна
MainWindow::~MainWindow()
{
    delete ui;
}
