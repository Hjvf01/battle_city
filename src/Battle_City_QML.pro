TEMPLATE = app

QT += qml quick core gui

CONFIG += c++11

SOURCES += main.cpp \
    controllers/game_handler.cpp \
    builders/builder.cpp \
    game_objects/brick_wall.cpp \
    game_objects/armor_wall.cpp \
    game_objects/enemy_tank.cpp \
    game_objects/user_tank.cpp \
    game_objects/user_base.cpp \
    game_objects/bullet.cpp \
    controllers/board_controller.cpp \
    controllers/user_controller.cpp \
    controllers/enemy_controller.cpp \
    controllers/bullet_controller.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    builders/builder.h \
    controllers/game_handler.h \
    game_objects/brick_wall.h \
    game_objects/armor_wall.h \
    game_objects/enemy_tank.h \
    game_objects/user_tank.h \
    game_objects/base.h \
    game_objects/user_base.h \
    game_objects/bullet.h \
    game_objects/movable.h \
    controllers/controllers.h \
    builders/factories.h

DISTFILES +=
