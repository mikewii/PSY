QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Icon.cpp \
    Japanese/Check.cpp \
    Japanese/Grammar.cpp \
    Japanese/Japanese.cpp \
    Japanese/Phonetics.cpp \
    Japanese/Word.cpp \
    Journal/Journal.cpp \
    Mainwindow.cpp \
    Settingswindow.cpp \
    Utils.cpp \
    main.cpp

HEADERS += \
    Icon.hpp \
    Japanese/Check.hpp \
    Japanese/Grammar.hpp \
    Japanese/Japanese.hpp \
    Japanese/Kana.hpp \
    Japanese/Phonetics.hpp \
    Japanese/Word.hpp \
    Journal/Emotion.hpp \
    Journal/Journal.hpp \
    Kana.hpp \
    Mainwindow.h \
    Settings.hpp \
    Settingswindow.h \
    Utils.h

FORMS += \
    Mainwindow.ui \
    Settingswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
