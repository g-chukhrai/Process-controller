/****************************************************************************
** Meta object code from reading C++ file 'resultwindow.h'
**
** Created: Thu 29. Apr 21:34:51 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../resultwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'resultwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ResultWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      37,   13,   13,   13, 0x08,
      61,   13,   13,   13, 0x08,
      85,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ResultWindow[] = {
    "ResultWindow\0\0on_saveExcel_clicked()\0"
    "on_makeScreen_clicked()\0on_backButton_clicked()\0"
    "on_startDeal_clicked()\0"
};

const QMetaObject ResultWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ResultWindow,
      qt_meta_data_ResultWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ResultWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ResultWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ResultWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ResultWindow))
        return static_cast<void*>(const_cast< ResultWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int ResultWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_saveExcel_clicked(); break;
        case 1: on_makeScreen_clicked(); break;
        case 2: on_backButton_clicked(); break;
        case 3: on_startDeal_clicked(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
