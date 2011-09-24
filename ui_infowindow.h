/********************************************************************************
** Form generated from reading UI file 'infowindow.ui'
**
** Created: Thu 29. Apr 20:58:47 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFOWINDOW_H
#define UI_INFOWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_InfoWindow
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineName;
    QPushButton *addVertexButton;
    QPushButton *canselButton;
    QSpinBox *lineValue;

    void setupUi(QDialog *InfoWindow)
    {
        if (InfoWindow->objectName().isEmpty())
            InfoWindow->setObjectName(QString::fromUtf8("InfoWindow"));
        InfoWindow->resize(181, 229);
        InfoWindow->setStyleSheet(QString::fromUtf8(""));
        label = new QLabel(InfoWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 20, 81, 16));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial Narrow"));
        font.setPointSize(10);
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        label->setFont(font);
        label_2 = new QLabel(InfoWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 80, 111, 21));
        label_2->setFont(font);
        lineName = new QLineEdit(InfoWindow);
        lineName->setObjectName(QString::fromUtf8("lineName"));
        lineName->setGeometry(QRect(40, 40, 113, 20));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial Narrow"));
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        lineName->setFont(font1);
        lineName->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        addVertexButton = new QPushButton(InfoWindow);
        addVertexButton->setObjectName(QString::fromUtf8("addVertexButton"));
        addVertexButton->setGeometry(QRect(40, 150, 111, 31));
        addVertexButton->setFont(font1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        addVertexButton->setIcon(icon);
        addVertexButton->setIconSize(QSize(24, 24));
        canselButton = new QPushButton(InfoWindow);
        canselButton->setObjectName(QString::fromUtf8("canselButton"));
        canselButton->setGeometry(QRect(40, 180, 111, 31));
        canselButton->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        canselButton->setIcon(icon1);
        canselButton->setIconSize(QSize(24, 24));
        lineValue = new QSpinBox(InfoWindow);
        lineValue->setObjectName(QString::fromUtf8("lineValue"));
        lineValue->setGeometry(QRect(40, 110, 111, 21));
        lineValue->setMinimum(1);
        lineValue->setMaximum(999999);
        lineValue->setValue(1);

        retranslateUi(InfoWindow);

        QMetaObject::connectSlotsByName(InfoWindow);
    } // setupUi

    void retranslateUi(QDialog *InfoWindow)
    {
        InfoWindow->setWindowTitle(QApplication::translate("InfoWindow", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("InfoWindow", "\320\230\320\274\321\217 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\260", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("InfoWindow", "\320\222\320\265\321\201 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\260", 0, QApplication::UnicodeUTF8));
        addVertexButton->setText(QApplication::translate("InfoWindow", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        canselButton->setText(QApplication::translate("InfoWindow", "\320\236\321\202\320\274\320\265\320\275\320\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class InfoWindow: public Ui_InfoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFOWINDOW_H
