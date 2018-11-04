#-------------------------------------------------
#
# Project created by QtCreator 2018-10-29T09:58:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MagicstompFrenzy
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    midiportmodel.cpp \
    patchlistmodel.cpp \
    midiinthread.cpp \
    midievent.cpp \
    midisender.cpp \
    progresswidget.cpp \
    arraydataeditwidget.cpp \
    patchcommoneditorwidget.cpp \
    patcheditorwidget.cpp \
    midiapplication.cpp \
    effecteditwidgets/ampmultiwidget.cpp \
    effecteditwidgets/effecteditbasewidget.cpp \
    effecteditwidgets/noisegatewidget.cpp \
    effecteditwidgets/ampwidget.cpp \
    effecteditwidgets/compressorwidget.cpp \
    effecteditwidgets/ampmultimodulationwidget.cpp \
    effecteditwidgets/ampmultidelaywidget.cpp \
    effecteditwidgets/ampmultireverbwidget.cpp \
    effecteditwidgets/delaybandwidget.cpp \
    effecteditwidgets/multibanddelaywidget.cpp \
    patchcopydialog.cpp \
    patchlistcombomodel.cpp

HEADERS  += mainwindow.h \
    midiportmodel.h \
    patchlistmodel.h \
    midiinthread.h \
    midievent.h \
    midisender.h \
    progresswidget.h \
    arraydataeditwidget.h \
    patchcommoneditorwidget.h \
    patcheditorwidget.h \
    midiapplication.h \
    magicstomp.h \
    effecteditwidgets/ampmultiwidget.h \
    effecteditwidgets/effecteditbasewidget.h \
    magicstomptext.h \
    effecteditwidgets/noisegatewidget.h \
    effecteditwidgets/ampwidget.h \
    effecteditwidgets/compressorwidget.h \
    effecteditwidgets/ampmultimodulationwidget.h \
    effecteditwidgets/ampmultidelaywidget.h \
    effecteditwidgets/ampmultireverbwidget.h \
    effecteditwidgets/delaybandwidget.h \
    effecteditwidgets/multibanddelaywidget.h \
    patchcopydialog.h \
    patchlistcombomodel.h

linux {
LIBS += -lasound
}

macx {

LIBS += -framework CoreAudio -framework AudioToolbox -framework AudioUnit -framework CoreFoundation -framework CoreMIDI

#ICON = rvplayer3.icns
}

copydata.commands = $(COPY_DIR) $$PWD/effects.ini $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
