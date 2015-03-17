/****************************************************************************
** Meta object code from reading C++ file 'audioplayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Client/audioplayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'audioplayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AudioPlayer_t {
    QByteArrayData data[18];
    char stringdata[276];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AudioPlayer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AudioPlayer_t qt_meta_stringdata_AudioPlayer = {
    {
QT_MOC_LITERAL(0, 0, 11), // "AudioPlayer"
QT_MOC_LITERAL(1, 12, 10), // "audioReady"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 1), // "d"
QT_MOC_LITERAL(4, 26, 18), // "on_btnPlay_clicked"
QT_MOC_LITERAL(5, 45, 19), // "on_btnPause_clicked"
QT_MOC_LITERAL(6, 65, 29), // "on_sliderProgress_sliderMoved"
QT_MOC_LITERAL(7, 95, 8), // "position"
QT_MOC_LITERAL(8, 104, 27), // "on_sliderVolume_sliderMoved"
QT_MOC_LITERAL(9, 132, 18), // "on_positionChanged"
QT_MOC_LITERAL(10, 151, 18), // "on_durationChanged"
QT_MOC_LITERAL(11, 170, 20), // "on_btnResume_clicked"
QT_MOC_LITERAL(12, 191, 23), // "processPendingDatagrams"
QT_MOC_LITERAL(13, 215, 8), // "playData"
QT_MOC_LITERAL(14, 224, 17), // "audioStateChanged"
QT_MOC_LITERAL(15, 242, 13), // "QAudio::State"
QT_MOC_LITERAL(16, 256, 5), // "state"
QT_MOC_LITERAL(17, 262, 13) // "writeMoreData"

    },
    "AudioPlayer\0audioReady\0\0d\0on_btnPlay_clicked\0"
    "on_btnPause_clicked\0on_sliderProgress_sliderMoved\0"
    "position\0on_sliderVolume_sliderMoved\0"
    "on_positionChanged\0on_durationChanged\0"
    "on_btnResume_clicked\0processPendingDatagrams\0"
    "playData\0audioStateChanged\0QAudio::State\0"
    "state\0writeMoreData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AudioPlayer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   77,    2, 0x08 /* Private */,
       5,    0,   78,    2, 0x08 /* Private */,
       6,    1,   79,    2, 0x08 /* Private */,
       8,    1,   82,    2, 0x08 /* Private */,
       9,    1,   85,    2, 0x08 /* Private */,
      10,    1,   88,    2, 0x08 /* Private */,
      11,    0,   91,    2, 0x08 /* Private */,
      12,    0,   92,    2, 0x08 /* Private */,
      13,    1,   93,    2, 0x08 /* Private */,
      14,    1,   96,    2, 0x08 /* Private */,
      17,    0,   99,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::LongLong,    7,
    QMetaType::Void, QMetaType::LongLong,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void,

       0        // eod
};

void AudioPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AudioPlayer *_t = static_cast<AudioPlayer *>(_o);
        switch (_id) {
        case 0: _t->audioReady((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->on_btnPlay_clicked(); break;
        case 2: _t->on_btnPause_clicked(); break;
        case 3: _t->on_sliderProgress_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_sliderVolume_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_positionChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 6: _t->on_durationChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 7: _t->on_btnResume_clicked(); break;
        case 8: _t->processPendingDatagrams(); break;
        case 9: _t->playData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 10: _t->audioStateChanged((*reinterpret_cast< QAudio::State(*)>(_a[1]))); break;
        case 11: _t->writeMoreData(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAudio::State >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AudioPlayer::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AudioPlayer::audioReady)) {
                *result = 0;
            }
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
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void AudioPlayer::audioReady(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
