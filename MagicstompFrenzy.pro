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

CONFIG += c++14

SOURCES += main.cpp\
    mainwindow.cpp \
    midiportmodel.cpp \
    patchlistmodel.cpp \
    midievent.cpp \
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
    patchlistcombomodel.cpp \
    effecteditwidgets/basspreamp.cpp \
    preferencesdialog.cpp \
    effecteditwidgets/freqspinbox.cpp \
    effecteditwidgets/bassfreqspinbox.cpp \
    effecteditwidgets/expspinbox.cpp \
    effecteditwidgets/hqpitchwidget.cpp \
    effecteditwidgets/dualpitchwidget.cpp \
    effecteditwidgets/acousticmultiwidget.cpp \
    effecteditwidgets/distortionwidget.cpp \
    effecteditwidgets/reverbwidget.cpp \
    effecteditwidgets/reverbtimespinbox.cpp \
    effecteditwidgets/hpfspinbox.cpp \
    effecteditwidgets/lpfspinbox.cpp \
    effecteditwidgets/gatereverbwidget.cpp \
    effecteditwidgets/choruswidget.cpp \
    effecteditwidgets/flangewidget.cpp \
    effecteditwidgets/symphonicwidget.cpp \
    effecteditwidgets/vintageflangewidget.cpp \
    effecteditwidgets/phaserwidget.cpp \
    effecteditwidgets/vintagephaserwidget.cpp \
    effecteditwidgets/monodelaywidget.cpp \
    effecteditwidgets/stereodelaywidget.cpp \
    effecteditwidgets/moddelaywidget.cpp \
    effecteditwidgets/delaylcrwidget.cpp \
    effecteditwidgets/echowidget.cpp \
    effecteditwidgets/tapeechowidget.cpp \
    effecteditwidgets/tremolowidget.cpp \
    effecteditwidgets/autopanwidget.cpp \
    effecteditwidgets/reverbmultiwidget.cpp \
    effecteditwidgets/reverbchoruswidget.cpp \
    effecteditwidgets/reverbflangewidget.cpp \
    effecteditwidgets/reverbpanwidget.cpp \
    effecteditwidgets/delaymultiwidget.cpp \
    effecteditwidgets/delayearlyrefwidget.cpp \
    effecteditwidgets/delayreverbwidget.cpp \
    effecteditwidgets/distortiondelaywidget.cpp \
    effecteditwidgets/multifilterwidget.cpp \
    effecteditwidgets/threebandeqwidget.cpp \
    effecteditwidgets/rotarywidget.cpp \
    effecteditwidgets/ringmodwidget.cpp \
    effecteditwidgets/modfilterwidget.cpp \
    effecteditwidgets/mbanddynawidget.cpp \
    effecteditwidgets/dynafilterwidget.cpp \
    effecteditwidgets/dynaflangewidget.cpp \
    effecteditwidgets/dynaphaserwidget.cpp \
    effecteditwidgets/springreverbwidget.cpp \
    standardmidifile.cpp \
    importbankselectiondialog.cpp \
    knobparametermodel.cpp \
    effecteditwidgets/renardseriesspinbox.cpp \
    effecteditwidgets/compressorreleasecombobox.cpp \
    effecteditwidgets/noisegatedecaycombobox.cpp

HEADERS  += mainwindow.h \
    midiportmodel.h \
    patchlistmodel.h \
    midievent.h \
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
    patchlistcombomodel.h \
    effecteditwidgets/basspreamp.h \
    preferencesdialog.h \
    effecteditwidgets/freqspinbox.h \
    effecteditwidgets/bassfreqspinbox.h \
    effecteditwidgets/expspinbox.h \
    effecteditwidgets/hqpitchwidget.h \
    effecteditwidgets/dualpitchwidget.h \
    effecteditwidgets/acousticmultiwidget.h \
    effecteditwidgets/distortionwidget.h \
    effecteditwidgets/reverbwidget.h \
    effecteditwidgets/reverbtimespinbox.h \
    effecteditwidgets/hpfspinbox.h \
    effecteditwidgets/lpfspinbox.h \
    effecteditwidgets/gatereverbwidget.h \
    effecteditwidgets/choruswidget.h \
    effecteditwidgets/flangewidget.h \
    effecteditwidgets/symphonicwidget.h \
    effecteditwidgets/vintageflangewidget.h \
    effecteditwidgets/phaserwidget.h \
    effecteditwidgets/vintagephaserwidget.h \
    effecteditwidgets/monodelaywidget.h \
    effecteditwidgets/stereodelaywidget.h \
    effecteditwidgets/moddelaywidget.h \
    effecteditwidgets/delaylcrwidget.h \
    effecteditwidgets/echowidget.h \
    effecteditwidgets/tapeechowidget.h \
    effecteditwidgets/tremolowidget.h \
    effecteditwidgets/autopanwidget.h \
    effecteditwidgets/reverbmultiwidget.h \
    effecteditwidgets/reverbchoruswidget.h \
    effecteditwidgets/reverbflangewidget.h \
    effecteditwidgets/reverbpanwidget.h \
    effecteditwidgets/delaymultiwidget.h \
    effecteditwidgets/delayearlyrefwidget.h \
    effecteditwidgets/delayreverbwidget.h \
    effecteditwidgets/distortiondelaywidget.h \
    effecteditwidgets/multifilterwidget.h \
    effecteditwidgets/threebandeqwidget.h \
    effecteditwidgets/rotarywidget.h \
    effecteditwidgets/ringmodwidget.h \
    effecteditwidgets/modfilterwidget.h \
    effecteditwidgets/mbanddynawidget.h \
    effecteditwidgets/dynafilterwidget.h \
    effecteditwidgets/dynaflangewidget.h \
    effecteditwidgets/dynaphaserwidget.h \
    effecteditwidgets/springreverbwidget.h \
    userevents.h \
    standardmidifile.h \
    importbankselectiondialog.h \
    knobparametermodel.h \
    knobparameters.h \
    effecteditwidgets/renardseriesspinbox.h \
    effecteditwidgets/compressorreleasecombobox.h \
    effecteditwidgets/noisegatedecaycombobox.h

linux {

HEADERS += midiinthread.h \
    midisender.h \
    midiportidalsa.h

SOURCES += midiinthread.cpp \
    midisender.cpp \
    midiportidalsa.cpp

LIBS += -lasound
}

macx {

LIBS += -framework CoreAudio -framework AudioToolbox -framework AudioUnit -framework CoreFoundation -framework CoreMIDI

ICON = magicstomp.icns
}

win64 {
HEADERS += inmidiheaderusedevent.h
SOURCES += inmidiheaderusedevent.cpp
LIBS += -lwinmm
}

win32 {
HEADERS += inmidiheaderusedevent.h
SOURCES += inmidiheaderusedevent.cpp
LIBS += -lwinmm
}

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

copydata.commands = $(COPY_DIR) $$PWD/effects.ini $$OUT_PWD && $(COPY_DIR) $$PWD/guitarpresets.ini $$OUT_PWD && $(COPY_DIR) $$PWD/basspresets.ini $$OUT_PWD && $(COPY_DIR) $$PWD/acousticpresets.ini $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

RESOURCES += \
    magicstompfrenzy.qrc
