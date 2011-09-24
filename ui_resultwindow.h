/********************************************************************************
** Form generated from reading UI file 'resultwindow.ui'
**
** Created: Thu 29. Apr 20:58:47 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTWINDOW_H
#define UI_RESULTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_ResultWindow
{
public:
    QLabel *label;
    QPushButton *startDeal;
    QTableWidget *resultTable;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QPushButton *backButton;
    QGraphicsView *graphicsView;
    QSpinBox *spinBox;
    QPushButton *makeScreen;
    QPushButton *saveExcel;

    void setupUi(QDialog *ResultWindow)
    {
        if (ResultWindow->objectName().isEmpty())
            ResultWindow->setObjectName(QString::fromUtf8("ResultWindow"));
        ResultWindow->resize(660, 665);
        ResultWindow->setMinimumSize(QSize(660, 130));
        ResultWindow->setMaximumSize(QSize(1200, 665));
        label = new QLabel(ResultWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(180, 30, 161, 21));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial Narrow"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        startDeal = new QPushButton(ResultWindow);
        startDeal->setObjectName(QString::fromUtf8("startDeal"));
        startDeal->setGeometry(QRect(270, 90, 161, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial Narrow"));
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setWeight(50);
        startDeal->setFont(font1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        startDeal->setIcon(icon);
        startDeal->setIconSize(QSize(24, 24));
        resultTable = new QTableWidget(ResultWindow);
        if (resultTable->columnCount() < 3)
            resultTable->setColumnCount(3);
        if (resultTable->rowCount() < 2)
            resultTable->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        resultTable->setItem(0, 0, __qtablewidgetitem);
        resultTable->setObjectName(QString::fromUtf8("resultTable"));
        resultTable->setGeometry(QRect(20, 130, 620, 170));
        resultTable->setFont(font1);
        resultTable->setRowCount(2);
        resultTable->setColumnCount(3);
        label_2 = new QLabel(ResultWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(180, 60, 111, 16));
        label_2->setFont(font);
        lineEdit_2 = new QLineEdit(ResultWindow);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(320, 60, 51, 20));
        lineEdit_2->setFont(font);
        backButton = new QPushButton(ResultWindow);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setGeometry(QRect(130, 90, 141, 31));
        backButton->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/previous.png"), QSize(), QIcon::Normal, QIcon::Off);
        backButton->setIcon(icon1);
        backButton->setIconSize(QSize(24, 24));
        graphicsView = new QGraphicsView(ResultWindow);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(20, 320, 620, 320));
        graphicsView->setFont(font1);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        spinBox = new QSpinBox(ResultWindow);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(330, 30, 42, 22));
        spinBox->setFont(font);
        spinBox->setMinimum(2);
        spinBox->setValue(2);
        makeScreen = new QPushButton(ResultWindow);
        makeScreen->setObjectName(QString::fromUtf8("makeScreen"));
        makeScreen->setGeometry(QRect(430, 60, 141, 31));
        makeScreen->setFont(font1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/screen.png"), QSize(), QIcon::Normal, QIcon::Off);
        makeScreen->setIcon(icon2);
        makeScreen->setIconSize(QSize(24, 24));
        saveExcel = new QPushButton(ResultWindow);
        saveExcel->setObjectName(QString::fromUtf8("saveExcel"));
        saveExcel->setGeometry(QRect(430, 90, 141, 31));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial Narrow"));
        font2.setPointSize(10);
        saveExcel->setFont(font2);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/excel.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveExcel->setIcon(icon3);
        saveExcel->setIconSize(QSize(24, 24));

        retranslateUi(ResultWindow);

        QMetaObject::connectSlotsByName(ResultWindow);
    } // setupUi

    void retranslateUi(QDialog *ResultWindow)
    {
        ResultWindow->setWindowTitle(QApplication::translate("ResultWindow", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ResultWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\276\321\200\320\276\320\262", 0, QApplication::UnicodeUTF8));
        startDeal->setText(QApplication::translate("ResultWindow", "\320\240\320\260\321\201\320\277\321\200\320\265\320\264\320\265\320\273\320\270\321\202\321\214 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\321\213", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = resultTable->isSortingEnabled();
        resultTable->setSortingEnabled(false);
        resultTable->setSortingEnabled(__sortingEnabled);

        label_2->setText(QApplication::translate("ResultWindow", "\320\222\321\200\320\265\320\274\321\217 \320\262\321\213\320\277\320\276\320\273\320\275\320\265\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        backButton->setText(QApplication::translate("ResultWindow", "\320\235\320\260\320\267\320\260\320\264", 0, QApplication::UnicodeUTF8));
        makeScreen->setText(QApplication::translate("ResultWindow", "\320\241\320\264\320\265\320\273\320\260\321\202\321\214 \321\201\320\272\321\200\320\270\320\275\321\210\320\276\321\202", 0, QApplication::UnicodeUTF8));
        saveExcel->setText(QApplication::translate("ResultWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\262 Excel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ResultWindow: public Ui_ResultWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTWINDOW_H
