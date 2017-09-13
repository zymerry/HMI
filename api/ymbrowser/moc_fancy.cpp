/****************************************************************************
** Meta object code from reading C++ file 'fancy.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "fancy.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fancy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Fancy[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      39,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,    7,    6,    6, 0x0a,
      36,    6,   28,    6, 0x0a,
      61,   49,   45,    6, 0x0a,
      86,   49,   45,    6, 0x0a,
     119,  115,    6,    6, 0x0a,
     133,    6,   45,    6, 0x0a,
     160,  153,    6,    6, 0x0a,
     187,  183,   45,    6, 0x0a,
     216,  202,   45,    6, 0x0a,
     245,  236,   28,    6, 0x0a,
     264,  183,   45,    6, 0x0a,
     289,  284,   45,    6, 0x0a,
     309,  183,    6,    6, 0x0a,
     325,    6,   45,    6, 0x0a,
     336,    6,   45,    6, 0x0a,
     349,    6,    6,    6, 0x0a,
     361,  183,   45,    6, 0x0a,
     406,  378,   45,    6, 0x0a,
     441,    6,   28,    6, 0x0a,
     459,  455,   45,    6, 0x0a,
     481,  183,    6,    6, 0x0a,
     499,  236,    6,    6, 0x0a,
     525,  236,    6,    6, 0x0a,
     550,    6,   45,    6, 0x0a,
     583,  561,   45,    6, 0x0a,
     608,  603,   45,    6, 0x0a,
     626,    6,   28,    6, 0x0a,
     637,    6,    6,    6, 0x0a,
     649,    6,   45,    6, 0x0a,
     662,    6,   45,    6, 0x0a,
     680,    6,   45,    6, 0x0a,
     706,  695,   45,    6, 0x0a,
     731,  725,   45,    6, 0x0a,
     762,  751,   45,    6, 0x0a,
     787,  783,   45,    6, 0x0a,
     808,    6,    6,    6, 0x0a,
     822,    6,   45,    6, 0x0a,
     834,    6,    6,    6, 0x08,
     849,    6,    6,    6, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Fancy[] = {
    "Fancy\0\0param\0print(QString)\0QString\0"
    "getMsg()\0int\0string,find\0"
    "indexOf(QString,QString)\0"
    "lastIndexOf(QString,QString)\0url\0"
    "load(QString)\0getCurrentPageNum()\0"
    "number\0setCurrentPageNum(int)\0arg\0"
    "gpio_open(int)\0arg,direction\0"
    "gpio_setio(int,int)\0arg,size\0"
    "gpio_read(int,int)\0gpio_set_write(int)\0"
    "data\0gpio_write(QString)\0gpio_close(int)\0"
    "key_open()\0key_select()\0key_close()\0"
    "serial_open(int)\0arg,nSpeed,nBits,Evnt,nStop\0"
    "serial_setopt(int,int,int,int,int)\0"
    "serial_read()\0str\0serial_write(QString)\0"
    "serial_close(int)\0serial_set_write(int,int)\0"
    "serial_set_read(int,int)\0mic_open()\0"
    "samplerate,rec_volume\0mic_setopt(int,int)\0"
    "size\0mic_set_read(int)\0mic_read()\0"
    "mic_close()\0audio_open()\0audio_init_frag()\0"
    "audio_setdef()\0samplerate\0audio_setrate(int)\0"
    "sound\0audio_setsound(int)\0write_size\0"
    "audio_set_write(int)\0buf\0audio_write(QString)\0"
    "audio_close()\0open_file()\0attachObject()\0"
    "onRecvSocket()\0"
};

void Fancy::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Fancy *_t = static_cast<Fancy *>(_o);
        switch (_id) {
        case 0: _t->print((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: { QString _r = _t->getMsg();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: { int _r = _t->indexOf((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->lastIndexOf((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: _t->load((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: { int _r = _t->getCurrentPageNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 6: _t->setCurrentPageNum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: { int _r = _t->gpio_open((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 8: { int _r = _t->gpio_setio((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 9: { QString _r = _t->gpio_read((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 10: { int _r = _t->gpio_set_write((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 11: { int _r = _t->gpio_write((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 12: _t->gpio_close((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: { int _r = _t->key_open();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 14: { int _r = _t->key_select();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 15: _t->key_close(); break;
        case 16: { int _r = _t->serial_open((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 17: { int _r = _t->serial_setopt((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 18: { QString _r = _t->serial_read();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 19: { int _r = _t->serial_write((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 20: _t->serial_close((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->serial_set_write((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 22: _t->serial_set_read((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 23: { int _r = _t->mic_open();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 24: { int _r = _t->mic_setopt((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 25: { int _r = _t->mic_set_read((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 26: { QString _r = _t->mic_read();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 27: _t->mic_close(); break;
        case 28: { int _r = _t->audio_open();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 29: { int _r = _t->audio_init_frag();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 30: { int _r = _t->audio_setdef();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 31: { int _r = _t->audio_setrate((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 32: { int _r = _t->audio_setsound((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 33: { int _r = _t->audio_set_write((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 34: { int _r = _t->audio_write((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 35: _t->audio_close(); break;
        case 36: { int _r = _t->open_file();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 37: _t->attachObject(); break;
        case 38: _t->onRecvSocket(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Fancy::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Fancy::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Fancy,
      qt_meta_data_Fancy, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Fancy::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Fancy::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Fancy::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Fancy))
        return static_cast<void*>(const_cast< Fancy*>(this));
    return QObject::qt_metacast(_clname);
}

int Fancy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 39)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 39;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
