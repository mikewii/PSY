QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CCheck.cpp \
    CGrammar.cpp \
    CJapanese.cpp \
    CJournal.cpp \
    CMainwindow.cpp \
    CPhonetics.cpp \
    CSettingswindow.cpp \
    CUtils.cpp \
    CWord.cpp \
    main.cpp

HEADERS += \
    CCheck.hpp \
    CGrammar.hpp \
    CJapanese.hpp \
    CJournal.hpp \
    CMainwindow.h \
    CPhonetics.hpp \
    CSettingswindow.h \
    CUtils.h \
    CWord.hpp \
    Emotion.hpp \
    Kana.hpp \
    Settings.hpp

FORMS += \
    CMainwindow.ui \
    CSettingswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
