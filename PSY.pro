QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


USE_SVG = 1
!qtHaveModule(svg): USE_SVG = 0

greaterThan(USE_SVG, 0) {
    DEFINES += USE_SVG
    QT += svg
}


CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Icon.cpp \
    Iconwindow.cpp \
    Japanese/Check.cpp \
    Japanese/Grammar.cpp \
    Japanese/Japanese.cpp \
    Japanese/Phonetics.cpp \
    Japanese/Word.cpp \
    Journal/Journal.cpp \
    Mainwindow.cpp \
    Probability.cpp \
    Settingswindow.cpp \
    Utils.cpp \
    main.cpp

HEADERS += \
    Icon.hpp \
    Iconwindow.h \
    Japanese/Check.hpp \
    Japanese/Grammar.hpp \
    Japanese/Japanese.hpp \
    Japanese/Kana.hpp \
    Japanese/Phonetics.hpp \
    Japanese/Word.hpp \
    Journal/Emotion.hpp \
    Journal/Journal.hpp \
    Mainwindow.h \
    Probability.hpp \
    Settings.hpp \
    Settingswindow.h \
    Utils.h

FORMS += \
    Iconwindow.ui \
    Mainwindow.ui \
    Settingswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
