/****************************************************************************
** Meta object code from reading C++ file 'infowindow.h'
**
** Created: Thu 29. Apr 20:59:13 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../infowindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'infowindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InfoWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      50,   42,   11,   11, 0x0a,
      71,   11,   11,   11, 0x08,
      97,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_InfoWindow[] = {
    "InfoWindow\0\0,\0infoUpdate(QString,QString)\0"
    "newName\0nameChanged(QString)\0"
    "on_canselButton_clicked()\0"
    "on_addVertexButton_clicked()\0"
};

const QMetaObject InfoWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_InfoWindow,
      qt_meta_data_InfoWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &InfoWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *InfoWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *InfoWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InfoWindow))
        return static_cast<void*>(const_cast< InfoWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int InfoWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: infoUpdate((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: nameChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: on_canselButton_clicked(); break;
        case 3: on_addVertexButton_clicked(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void InfoWindow::infoUpdate(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
