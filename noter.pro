QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    sources/controller.cpp \
    sources/malware_capturing_cpu.cpp \
    sources/malware_capturing_ram.cpp \
    sources/malware_file_renamer.cpp \
    sources/malware_http_spammer.cpp \
    sources/model.cpp \
    sources/note.cpp \
    sources/main.cpp

HEADERS += \
    headers/controller.h \
    \\
    headers/malware_capturing_cpu.h \
    headers/malware_capturing_ram.h \
    headers/malware_file_renamer.h \
    headers/malware_http_spammer.h \
    headers/model.h \
    headers/note.h

FORMS += \
    forms/mainwindow.ui

INCLUDEPATH += \
    sources/ \
    headers/ \
    forms/


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
