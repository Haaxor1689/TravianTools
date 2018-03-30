TEMPLATE = app
TARGET = TravianTools

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    Other/TravianAPI.cpp \
    Other/TravianMapView.cpp \
    Views/MainView.cpp

HEADERS += \
    AppConfigs/AppConfigs.hpp \
    AppConfigs/Macros.hpp \
    Other/TravianAPI.hpp \
    Other/TravianMapView.hpp \
    Other/WorkerThread.hpp \
    Other/PixmapSheet.hpp \
    Other/json.hpp \
    Views/MainView.hpp \
    Models/Gameworld.hpp \
    Models/Map.hpp \
    Models/MapCell.hpp \
    Models/Kingdom.hpp \
    Models/Player.hpp \
    Models/ServerData.hpp \
    Models/Village.hpp

RESOURCES += \
    Assets/Assets.qrc
