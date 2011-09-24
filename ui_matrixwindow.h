/********************************************************************************
** Form generated from reading UI file 'matrixwindow.ui'
**
** Created: Thu 29. Apr 20:58:47 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATRIXWINDOW_H
#define UI_MATRIXWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_MatrixWindow
{
public:
    QTableWidget *matrixTable;
    QTableWidget *valueTable;
    QPushButton *manageProcess;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QTableWidget *timeTable;
    QPushButton *backButton;

    void setupUi(QDialog *MatrixWindow)
    {
        if (MatrixWindow->objectName().isEmpty())
            MatrixWindow->setObjectName(QString::fromUtf8("MatrixWindow"));
        MatrixWindow->resize(520, 520);
        MatrixWindow->setMinimumSize(QSize(520, 520));
        MatrixWindow->setStyleSheet(QString::fromUtf8("border-color: rgb(221, 162, 255);"));
        matrixTable = new QTableWidget(MatrixWindow);
        matrixTable->setObjectName(QString::fromUtf8("matrixTable"));
        matrixTable->setGeometry(QRect(30, 30, 460, 280));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(matrixTable->sizePolicy().hasHeightForWidth());
        matrixTable->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial Narrow"));
        font.setPointSize(10);
        font.setBold(false);
        font.setWeight(50);
        matrixTable->setFont(font);
        matrixTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        matrixTable->horizontalHeader()->setDefaultSectionSize(30);
        matrixTable->horizontalHeader()->setMinimumSectionSize(20);
        matrixTable->verticalHeader()->setDefaultSectionSize(20);
        matrixTable->verticalHeader()->setMinimumSectionSize(20);
        valueTable = new QTableWidget(MatrixWindow);
        valueTable->setObjectName(QString::fromUtf8("valueTable"));
        valueTable->setGeometry(QRect(30, 330, 460, 60));
        valueTable->setFont(font);
        valueTable->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        valueTable->horizontalHeader()->setDefaultSectionSize(30);
        valueTable->horizontalHeader()->setMinimumSectionSize(20);
        valueTable->verticalHeader()->setVisible(false);
        valueTable->verticalHeader()->setDefaultSectionSize(20);
        valueTable->verticalHeader()->setMinimumSectionSize(20);
        manageProcess = new QPushButton(MatrixWindow);
        manageProcess->setObjectName(QString::fromUtf8("manageProcess"));
        manageProcess->setGeometry(QRect(310, 480, 180, 30));
        manageProcess->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        manageProcess->setIcon(icon);
        manageProcess->setIconSize(QSize(24, 24));
        label = new QLabel(MatrixWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 10, 121, 21));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial Narrow"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);
        label_2 = new QLabel(MatrixWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 310, 100, 20));
        label_2->setFont(font1);
        label_3 = new QLabel(MatrixWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 390, 200, 20));
        label_3->setFont(font1);
        timeTable = new QTableWidget(MatrixWindow);
        timeTable->setObjectName(QString::fromUtf8("timeTable"));
        timeTable->setGeometry(QRect(30, 410, 460, 60));
        timeTable->setFont(font);
        timeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        timeTable->horizontalHeader()->setDefaultSectionSize(30);
        timeTable->horizontalHeader()->setMinimumSectionSize(20);
        timeTable->verticalHeader()->setVisible(false);
        timeTable->verticalHeader()->setDefaultSectionSize(20);
        timeTable->verticalHeader()->setMinimumSectionSize(20);
        backButton = new QPushButton(MatrixWindow);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setGeometry(QRect(30, 480, 180, 30));
        backButton->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/previous.png"), QSize(), QIcon::Normal, QIcon::Off);
        backButton->setIcon(icon1);
        backButton->setIconSize(QSize(24, 24));

        retranslateUi(MatrixWindow);

        QMetaObject::connectSlotsByName(MatrixWindow);
    } // setupUi

    void retranslateUi(QDialog *MatrixWindow)
    {
        MatrixWindow->setWindowTitle(QApplication::translate("MatrixWindow", "Dialog", 0, QApplication::UnicodeUTF8));
        manageProcess->setText(QApplication::translate("MatrixWindow", "\320\240\320\260\321\201\320\277\321\200\320\265\320\264\320\265\320\273\320\270\321\202\321\214 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\321\213", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MatrixWindow", "\320\234\320\260\321\202\321\200\320\270\321\206\320\260 \321\201\320\273\320\265\320\264\320\276\320\262\320\260\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MatrixWindow", "\320\227\320\275\320\260\321\207\320\265\320\275\320\270\321\217 \320\262\320\265\321\201\320\276\320\262", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MatrixWindow", "\320\240\320\260\320\275\320\275\320\270\320\265 \321\201\321\200\320\276\320\272\320\270 \320\262\321\213\320\277\320\276\320\273\320\265\320\275\320\270\321\217 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\276\320\262", 0, QApplication::UnicodeUTF8));
        backButton->setText(QApplication::translate("MatrixWindow", "\320\235\320\260\320\267\320\260\320\264", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MatrixWindow: public Ui_MatrixWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATRIXWINDOW_H
