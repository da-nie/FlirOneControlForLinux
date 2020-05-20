/****************************************************************************
** Meta object code from reading C++ file 'cmainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../FlirOneControl/cmainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cmainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CMainWindow_t {
    QByteArrayData data[12];
    char stringdata0[331];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CMainWindow_t qt_meta_stringdata_CMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 11), // "CMainWindow"
QT_MOC_LITERAL(1, 12, 34), // "on_pushButton_ApplyPalette_cl..."
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 31), // "on_pushButton_SaveVideo_clicked"
QT_MOC_LITERAL(4, 80, 36), // "on_pushButton_SaveImageCross_..."
QT_MOC_LITERAL(5, 117, 38), // "on_pushButton_SaveImageNoScal..."
QT_MOC_LITERAL(6, 156, 29), // "on_pushButton_SaveRAW_clicked"
QT_MOC_LITERAL(7, 186, 31), // "on_pushButton_ShowVideo_clicked"
QT_MOC_LITERAL(8, 218, 34), // "on_pushButton_SaveAllFrame_cl..."
QT_MOC_LITERAL(9, 253, 31), // "on_pushButton_SaveFrame_clicked"
QT_MOC_LITERAL(10, 285, 40), // "on_comboBox_Language_currentI..."
QT_MOC_LITERAL(11, 326, 4) // "arg1"

    },
    "CMainWindow\0on_pushButton_ApplyPalette_clicked\0"
    "\0on_pushButton_SaveVideo_clicked\0"
    "on_pushButton_SaveImageCross_clicked\0"
    "on_pushButton_SaveImageNoScale_clicked\0"
    "on_pushButton_SaveRAW_clicked\0"
    "on_pushButton_ShowVideo_clicked\0"
    "on_pushButton_SaveAllFrame_clicked\0"
    "on_pushButton_SaveFrame_clicked\0"
    "on_comboBox_Language_currentIndexChanged\0"
    "arg1"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CMainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    1,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,

       0        // eod
};

void CMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CMainWindow *_t = static_cast<CMainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_ApplyPalette_clicked(); break;
        case 1: _t->on_pushButton_SaveVideo_clicked(); break;
        case 2: _t->on_pushButton_SaveImageCross_clicked(); break;
        case 3: _t->on_pushButton_SaveImageNoScale_clicked(); break;
        case 4: _t->on_pushButton_SaveRAW_clicked(); break;
        case 5: _t->on_pushButton_ShowVideo_clicked(); break;
        case 6: _t->on_pushButton_SaveAllFrame_clicked(); break;
        case 7: _t->on_pushButton_SaveFrame_clicked(); break;
        case 8: _t->on_comboBox_Language_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject CMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CMainWindow.data,
      qt_meta_data_CMainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CMainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int CMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
