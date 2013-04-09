/****************************************************************************
** Meta object code from reading C++ file 'field.h'
**
** Created: Mon Apr 8 09:06:47 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Game/field.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'field.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_field[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x05,
      21,    6,    6,    6, 0x05,
      36,    6,    6,    6, 0x05,
      53,    6,    6,    6, 0x05,

 // slots: signature, parameters, type, tag, flags
      64,    6,    6,    6, 0x0a,
      72,    6,    6,    6, 0x0a,
      86,    6,    6,    6, 0x0a,
     103,    6,    6,    6, 0x0a,
     121,    6,    6,    6, 0x0a,
     138,    6,    6,    6, 0x0a,
     157,    6,    6,    6, 0x0a,
     175,    6,    6,    6, 0x0a,
     185,    6,    6,    6, 0x08,
     196,    6,    6,    6, 0x08,
     213,    6,    6,    6, 0x08,
     224,    6,    6,    6, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_field[] = {
    "field\0\0tankWounded()\0enemyWounded()\0"
    "Window_Restart()\0nextTurn()\0shoot()\0"
    "shoot_Enemy()\0enemyMove_SLOT()\0"
    "startMovingLeft()\0stopMovingLeft()\0"
    "startMovingRight()\0stopMovingRight()\0"
    "restart()\0moveShot()\0moveShot_Enemy()\0"
    "moveLeft()\0moveRight()\0"
};

void field::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        field *_t = static_cast<field *>(_o);
        switch (_id) {
        case 0: _t->tankWounded(); break;
        case 1: _t->enemyWounded(); break;
        case 2: _t->Window_Restart(); break;
        case 3: _t->nextTurn(); break;
        case 4: _t->shoot(); break;
        case 5: _t->shoot_Enemy(); break;
        case 6: _t->enemyMove_SLOT(); break;
        case 7: _t->startMovingLeft(); break;
        case 8: _t->stopMovingLeft(); break;
        case 9: _t->startMovingRight(); break;
        case 10: _t->stopMovingRight(); break;
        case 11: _t->restart(); break;
        case 12: _t->moveShot(); break;
        case 13: _t->moveShot_Enemy(); break;
        case 14: _t->moveLeft(); break;
        case 15: _t->moveRight(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData field::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject field::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_field,
      qt_meta_data_field, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &field::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *field::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *field::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_field))
        return static_cast<void*>(const_cast< field*>(this));
    return QWidget::qt_metacast(_clname);
}

int field::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void field::tankWounded()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void field::enemyWounded()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void field::Window_Restart()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void field::nextTurn()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
