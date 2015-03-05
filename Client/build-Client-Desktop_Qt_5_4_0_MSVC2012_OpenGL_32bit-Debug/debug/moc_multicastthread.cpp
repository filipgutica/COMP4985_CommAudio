/****************************************************************************
** Meta object code from reading C++ file 'multicastthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Client/multicastthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'multicastthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MulticastThread_t {
    QByteArrayData data[7];
    char stringdata[98];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MulticastThread_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MulticastThread_t qt_meta_stringdata_MulticastThread = {
    {
QT_MOC_LITERAL(0, 0, 15), // "MulticastThread"
QT_MOC_LITERAL(1, 16, 22), // "bufferFillCountChanged"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 6), // "bCount"
QT_MOC_LITERAL(4, 47, 20), // "producerCountChanged"
QT_MOC_LITERAL(5, 68, 5), // "count"
QT_MOC_LITERAL(6, 74, 23) // "processPendingDatagrams"

    },
    "MulticastThread\0bufferFillCountChanged\0"
    "\0bCount\0producerCountChanged\0count\0"
    "processPendingDatagrams"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MulticastThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void MulticastThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MulticastThread *_t = static_cast<MulticastThread *>(_o);
        switch (_id) {
        case 0: _t->bufferFillCountChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->producerCountChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->processPendingDatagrams(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MulticastThread::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MulticastThread::bufferFillCountChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (MulticastThread::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MulticastThread::producerCountChanged)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject MulticastThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_MulticastThread.data,
      qt_meta_data_MulticastThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MulticastThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MulticastThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MulticastThread.stringdata))
        return static_cast<void*>(const_cast< MulticastThread*>(this));
    return QThread::qt_metacast(_clname);
}

int MulticastThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void MulticastThread::bufferFillCountChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MulticastThread::producerCountChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
