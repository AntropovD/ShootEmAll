/****************************************************************************
** Meta object code from reading C++ file 'window.h'
**
** Created: Tue Apr 9 18:27:33 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Game/window.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Window[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x0a,
      21,    7,    7,    7, 0x0a,
      34,    7,    7,    7, 0x0a,
      44,    7,    7,    7, 0x0a,
      55,    7,    7,    7, 0x0a,
      66,    7,    7,    7, 0x0a,
      77,    7,    7,    7, 0x0a,
      91,    7,    7,    7, 0x0a,
     112,  106,    7,    7, 0x0a,
     130,  106,    7,    7, 0x0a,
     148,    7,    7,    7, 0x0a,
     165,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Window[] = {
    "Window\0\0infoDialog()\0backToHell()\0"
    "newGame()\0mainMenu()\0nextSong()\0"
    "prevSong()\0tankWounded()\0enemyWounded()\0"
    "value\0angleChanged(int)\0forceChanged(int)\0"
    "Window_Restart()\0nextTurn()\0"
};

void Window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Window *_t = static_cast<Window *>(_o);
        switch (_id) {
        case 0: _t->infoDialog(); break;
        case 1: _t->backToHell(); break;
        case 2: _t->newGame(); break;
        case 3: _t->mainMenu(); break;
        case 4: _t->nextSong(); break;
        case 5: _t->prevSong(); break;
        case 6: _t->tankWounded(); break;
        case 7: _t->enemyWounded(); break;
        case 8: _t->angleChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->forceChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->Window_Restart(); break;
        case 11: _t->nextTurn(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Window::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Window::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Window,
      qt_meta_data_Window, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Window::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Window::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Window))
        return static_cast<void*>(const_cast< Window*>(this));
    return QWidget::qt_metacast(_clname);
}

int Window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
