#include "infowindow.h"
#include "ui_infowindow.h"
#include "graphscene.h"
#include <QtGui/QKeyEvent>
#include <QMessageBox>

// конструктор окна параметров
InfoWindow::InfoWindow(GraphScene *inScene,QWidget *parent) :
        QDialog(parent),
        ui(new Ui::InfoWindow)
{
    ui->setupUi(this);

    scene = inScene;
    connect(ui->lineName,SIGNAL(textChanged(QString)),this,SLOT(nameChanged(QString)));

    this->setWindowTitle("Диспетчер распараллеливания процессов");
    this->setWindowIcon(QIcon(":/images/icon.png"));
}

void InfoWindow::changeEvent(QEvent *e)
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

// функция установки имени процесса
void InfoWindow::setName(QString nm)
{
    // задать виджету с именем соответствуюшую строку
    ui->lineName->setText(nm);
    name = nm;
}

// функция установки веса процесса
void InfoWindow::setValue(QString vl)
{
    // установить виджету соответствующее значение
    ui->lineValue->setValue(vl.toInt());
    value = vl;
    // выделить текст в виджете и сфокусировать
    ui->lineValue->selectAll();
    ui->lineValue->setFocus();
}


// функция обработчик измения строки с именем процесса
void InfoWindow::nameChanged(QString newName)
{
    bool isCopyName = false;
    // для каждой вершины на сцене
    foreach(Vertex *vertex, scene->allVertexes)
    {
        // если имя вершины совпадает с именем новой вершины
        if (vertex->getName() == newName && !scene->selectedItems().contains(vertex))
        {
            // установить значение переменной проверки повтора
            isCopyName = true;
            break;
        }
    }
    // получить шрифт виджета
    QFont font = ui->lineName->font();
    QPalette palette;
    // если имя повторяется сделать шрифт красным иначе черным
    if (isCopyName)
        palette.setColor(QPalette::Text,Qt::red);
    else
        palette.setColor(QPalette::Text,Qt::black);

    // установить палитру на виджет
    ui->lineName->setPalette(palette);
}

// функция обработчик нажатия кнопки применить
void InfoWindow::on_addVertexButton_clicked()
{
    // если одно из полей не заполнено вывести предупреждение
    if (ui->lineName->text() == "" || ui->lineValue->text() =="")
        QMessageBox::warning(this,"Ошибка","Одно из полей не заполнено");
    // иначе если имя процесса не повторяется вызвать функцию обновления данных
    else if (ui->lineName->palette().color(QPalette::Text) != Qt::red)
    {
        emit infoUpdate(ui->lineName->text(),ui->lineValue->text());
        this->close();
    }
    // иначе вывести предупреждающее сообщение
    else
    {
        QMessageBox::warning(this,"Ошибка","Процесс с заданным именем уже существует");
    }
}

// функция обработчик нажатия кнопки отмена
void InfoWindow::on_canselButton_clicked()
{
    this->close();
}

// деструктор окна
InfoWindow::~InfoWindow()
{
    delete ui;
}
