TARGET = LilyDict
TEMPLATE = app

QT += widgets qml multimedia
CONFIG += c++14
#CONFIG += static
RESOURCES += src/gui/qml/qml.qrc icons.qrc
RC_FILE = app.rc

CONFIG(debug, debug|release) {
    DEFINES += DEBUG
}else{
    DEFINES += NDEBUG
}
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

INCLUDEPATH += src
SOURCES += \
    src/main.cpp \
    src/dict/shanbaydict.cpp \
    src/dict/youdaodict.cpp \
    src/app/application.cpp \
    src/gui/Gui.cpp \
    src/app/config.cpp \
    src/gui/dictlogo.cpp \
    src/dict/dict.cpp
HEADERS  += \
    src/dict/shanbaydict.h \
    src/dict/youdaodict.h \
    src/app/application.h \
    src/gui/Gui.h \
    src/app/config.h \
    src/gui/dictlogo.h \
    src/dict/dict.h

win32{

}
macx{
    ICON = logo.icns
}
#DEFINES += QT_NO_WARNING_OUTPUT\
#           QT_NO_DEBUG_OUTPUT





































