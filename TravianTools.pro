TEMPLATE = app
TARGET = TravianTools

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    Other/TravianAPI.cpp \
    Views/MainView.cpp

HEADERS += \
    AppConfigs/AppConfigs.hpp \
    AppConfigs/Macros.hpp \
    Other/TravianAPI.hpp \
    Views/MainView.hpp \
    Other/WorkerThread.hpp \
    Other/json.hpp \
    Models/Gameworld.hpp \
    Models/Map.hpp \
    Models/MapCell.hpp \
    Models/Kingdom.hpp \
    Models/Player.hpp \
    Models/ServerData.hpp \
    Models/Village.hpp
