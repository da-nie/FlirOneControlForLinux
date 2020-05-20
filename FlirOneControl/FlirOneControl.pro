#-------------------------------------------------
#
# Project created by QtCreator 2020-05-18T19:11:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FlirOneControl
TEMPLATE = app
LIBS +=-L/usr/local/lib -lusb-1.0


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    cflironecontrol.cpp \
    cmainwindow.cpp \
    cringbuffer.cpp \
    main.cpp \
    cflironereceiver.cpp \
    cmutex.cpp \
    cthread.cpp \
    system.cpp \
    tga.cpp \
    cflironedriver.cpp \
    craiifileout.cpp \
    craiifilein.cpp \
    clog.cpp \
    cdecorator_iimage.cpp \
    cdecorator_scale.cpp \
    cpicture.cpp \
    iimage.cpp \
    cgraphics.cpp \
    clabel_imagearea.cpp \
    libjpeg/cdjpeg.c \
    libjpeg/jaricom.c \
    libjpeg/jcapimin.c \
    libjpeg/jcapistd.c \
    libjpeg/jcarith.c \
    libjpeg/jccoefct.c \
    libjpeg/jccolor.c \
    libjpeg/jcdctmgr.c \
    libjpeg/jchuff.c \
    libjpeg/jcinit.c \
    libjpeg/jcmainct.c \
    libjpeg/jcmarker.c \
    libjpeg/jcmaster.c \
    libjpeg/jcomapi.c \
    libjpeg/jcparam.c \
    libjpeg/jcprepct.c \
    libjpeg/jcsample.c \
    libjpeg/jctrans.c \
    libjpeg/jdapimin.c \
    libjpeg/jdapistd.c \
    libjpeg/jdarith.c \
    libjpeg/jdatadst.c \
    libjpeg/jdatasrc.c \
    libjpeg/jdcoefct.c \
    libjpeg/jdcolor.c \
    libjpeg/jddctmgr.c \
    libjpeg/jdhuff.c \
    libjpeg/jdinput.c \
    libjpeg/jdmainct.c \
    libjpeg/jdmarker.c \
    libjpeg/jdmaster.c \
    libjpeg/jdmerge.c \
    libjpeg/jdpostct.c \
    libjpeg/jdsample.c \
    libjpeg/jdtrans.c \
    libjpeg/jerror.c \
    libjpeg/jfdctflt.c \
    libjpeg/jfdctfst.c \
    libjpeg/jfdctint.c \
    libjpeg/jidctflt.c \
    libjpeg/jidctfst.c \
    libjpeg/jidctint.c \
    libjpeg/jmemansi.c \
    libjpeg/jmemmgr.c \
    libjpeg/jquant1.c \
    libjpeg/jquant2.c \
    libjpeg/jutils.c \
    libjpeg/rdbmp.c \
    libjpeg/rdcolmap.c \
    libjpeg/rdgif.c \
    libjpeg/rdppm.c \
    libjpeg/rdrle.c \
    libjpeg/rdswitch.c \
    libjpeg/rdtarga.c \
    libjpeg/transupp.c \
    libjpeg/wrbmp.c \
    libjpeg/wrgif.c \
    libjpeg/wrppm.c \
    libjpeg/wrrle.c \
    libjpeg/wrtarga.c \
    clanguage.cpp \
    ilanguage.cpp \
    clanguageenglish.cpp \
    clanguagerussian.cpp

HEADERS += \
    cflironecontrol.h \
    cmainwindow.h \
    cringbuffer.h \
    cflironereceiver.h \
    cmutex.h \
    craiicmutex.h \
    cthread.h \
    system.h \
    tga.h \
    cflironedriver.h \
    craiifileout.h \
    craiifilein.h \
    libusb.h \
    clog.h \
    cdecorator_iimage.h \
    cdecorator_scale.h \
    cpicture.h \
    iimage.h \
    cgraphics.h \
    clabel_imagearea.h \
    libjpeg/cderror.h \
    libjpeg/cdjpeg.h \
    libjpeg/jconfig.h \
    libjpeg/jdct.h \
    libjpeg/jerror.h \
    libjpeg/jinclude.h \
    libjpeg/jmemsys.h \
    libjpeg/jmorecfg.h \
    libjpeg/jpegint.h \
    libjpeg/jpeglib.h \
    libjpeg/jversion.h \
    libjpeg/transupp.h \
    clanguage.h \
    ilanguage.h \
    clanguageenglish.h \
    clanguagerussian.h

FORMS += \
        cmainwindow.ui
