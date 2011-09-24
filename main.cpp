#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QTextCodec>

// главная функция программы
int main(int argc, char *argv[])
{
    // создание приложения
    QApplication a(argc, argv);
    // подключение ресурсов
    Q_INIT_RESOURCE(resource);
    // установка текстового кодека для кириллицы
    QTextCodec *codec = QTextCodec::codecForName("CP1251");
    QTextCodec::setCodecForCStrings(codec);
    // создание главного окна
    MainWindow w;
    // отображение главного окна
    w.show();
    return a.exec();
}
