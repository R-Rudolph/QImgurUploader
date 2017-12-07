QT          += network
INCLUDEPATH += $$PWD/include/qimguruploader

DEFINES += QIMGURUPLOADER_LIBRARY

SOURCES += \
    $$PWD/src/qimguruploader/qimguruploader.cpp \
    $$PWD/src/qimguruploader/qimgurreply.cpp

HEADERS  += \
    $$PWD/include/qimguruploader/qimguruploader.h \
    $$PWD/include/qimguruploader/qimgurreply.h \
    $$PWD/include/qimguruploader/QImgurReply \
    $$PWD/include/qimguruploader/QImgurUploader
