/****************************************************************************
** Meta object code from reading C++ file 'matrixwindow.h'
**
** Created: Thu 29. Apr 20:59:10 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../matrixwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'matrixwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MatrixWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      25,   14,   13,   13, 0x08,
      60,   13,   13,   13, 0x08,
      84,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MatrixWindow[] = {
    "MatrixWindow\0\0row,column\0"
    "on_valueTable_cellChanged(int,int)\0"
    "on_backButton_clicked()\0"
    "on_manageProcess_clicked()\0"
};

const QMetaObject MatrixWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MatrixWindow,
      qt_meta_data_MatrixWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MatrixWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MatrixWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MatrixWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MatrixWindow))
        return static_cast<void*>(const_cast< MatrixWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int MatrixWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_valueTable_cellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: on_backButton_clicked(); break;
        case 2: on_manageProcess_clicked(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
