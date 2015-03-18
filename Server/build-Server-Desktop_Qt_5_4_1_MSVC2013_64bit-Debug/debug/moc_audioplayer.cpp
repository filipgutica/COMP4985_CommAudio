/****************************************************************************
** Meta object code from reading C++ file 'audioplayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Server/audioplayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'audioplayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AudioPlayer_t {
    QByteArrayData data[11];
    char stringdata[189];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AudioPlayer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AudioPlayer_t qt_meta_stringdata_AudioPlayer = {
    {
QT_MOC_LITERAL(0, 0, 11), // "AudioPlayer"
QT_MOC_LITERAL(1, 12, 18), // "on_btnPlay_clicked"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 19), // "on_btnPause_clicked"
QT_MOC_LITERAL(4, 52, 29), // "on_sliderProgress_sliderMoved"
QT_MOC_LITERAL(5, 82, 8), // "position"
QT_MOC_LITERAL(6, 91, 27), // "on_sliderVolume_sliderMoved"
QT_MOC_LITERAL(7, 119, 18), // "on_positionChanged"
QT_MOC_LITERAL(8, 138, 18), // "on_durationChanged"
QT_MOC_LITERAL(9, 157, 20), // "on_btnResume_clicked"
QT_MOC_LITERAL(10, 178, 10) // "readBuffer"

    },
    "AudioPlayer\0on_btnPlay_clicked\0\0"
    "on_btnPause_clicked\0on_sliderProgress_sliderMoved\0"
    "position\0on_sliderVolume_sliderMoved\0"
    "on_positionChanged\0on_durationChanged\0"
    "on_btnResume_clicked\0readBuffer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AudioPlayer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    1,   56,    2, 0x08 /* Private */,
       6,    1,   59,    2, 0x08 /* Private */,
       7,    1,   62,    2, 0x08 /* Private */,
       8,    1,   65,    2, 0x08 /* Private */,
       9,    0,   68,    2, 0x08 /* Private */,
      10,    0,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::LongLong,    5,
    QMetaType::Void, QMetaType::LongLong,    5,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AudioPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AudioPlayer *_t = static_cast<AudioPlayer *>(_o);
        switch (_id) {
        case 0: _t->on_btnPlay_clicked(); break;
        case 1: _t->on_btnPause_clicked(); break;
        case 2: _t->on_sliderProgress_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_sliderVolume_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_positionChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 5: _t->on_durationChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 6: _t->on_btnResume_clicked(); break;
        case 7: _t->readBuffer(); break;
        default: ;
        }
    }
}

const QMetaObject AudioPlayer::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AudioPlayer.data,
      qt_meta_data_AudioPlayer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AudioPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AudioPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AudioPlayer.stringdata))
        return static_cast<void*>(const_cast< AudioPlayer*>(this));
    return QDialog::qt_metacast(_clname);
}

int AudioPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
