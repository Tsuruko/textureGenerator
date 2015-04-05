/****************************************************************************
** Meta object code from reading C++ file 'window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_window_t {
    QByteArrayData data[9];
    char stringdata[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_window_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_window_t qt_meta_stringdata_window = {
    {
QT_MOC_LITERAL(0, 0, 6), // "window"
QT_MOC_LITERAL(1, 7, 14), // "textureChanged"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 11), // "sizeChanged"
QT_MOC_LITERAL(4, 35, 12), // "colorChanged"
QT_MOC_LITERAL(5, 48, 11), // "savePressed"
QT_MOC_LITERAL(6, 60, 11), // "distChanged"
QT_MOC_LITERAL(7, 72, 11), // "combChanged"
QT_MOC_LITERAL(8, 84, 12) // "resetPressed"

    },
    "window\0textureChanged\0\0sizeChanged\0"
    "colorChanged\0savePressed\0distChanged\0"
    "combChanged\0resetPressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_window[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        window *_t = static_cast<window *>(_o);
        switch (_id) {
        case 0: _t->textureChanged(); break;
        case 1: _t->sizeChanged(); break;
        case 2: _t->colorChanged(); break;
        case 3: _t->savePressed(); break;
        case 4: _t->distChanged(); break;
        case 5: _t->combChanged(); break;
        case 6: _t->resetPressed(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject window::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_window.data,
      qt_meta_data_window,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *window::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_window.stringdata))
        return static_cast<void*>(const_cast< window*>(this));
    return QWidget::qt_metacast(_clname);
}

int window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
