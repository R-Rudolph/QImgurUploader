TEMPLATE = app
QT += widgets

TARGET = QImgurUploader-Sample

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    samplewidget.cpp

HEADERS += \ 
    samplewidget.h

include(../QImgurUploader.pri)

