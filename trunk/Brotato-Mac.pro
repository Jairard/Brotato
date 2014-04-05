TEMPLATE = app
CONFIG += console
CONFIG -= qt

TARGET = ../../bin/test
INCLUDEPATH += 

SOURCES += \ 
    src/Math.cpp \
    src/main.cpp \
    src/Physics/World.cpp \
    src/Physics/Rectangle.cpp \
    src/Physics/Entity.cpp \
    src/Graphics/SegmentShape.cpp \
    src/Graphics/RectangleShape.cpp \
    src/Graphics/Shape.cpp \
    src/Graphics/PointShape.cpp \
    src/GameObjects/GameObject.cpp \
    src/Graphics/SFMLEntity.cpp \
    src/Graphics/Entity.cpp \
    src/Windows/FixedFramerateWindow.cpp \
    src/GameObjects/DecorBox.cpp \
    src/GameObjects/Box.cpp \
    src/Graphics/_ThickPointShape.cpp \
    src/Graphics/DebugRenderer.cpp

HEADERS += \ 
    src/Vector2.hpp \
    src/Singleton.hpp \
    src/Math.hpp \
    src/Physics/World.hpp \
    src/Physics/Rectangle.hpp \
    src/Physics/Entity.hpp \
    src/Graphics/SegmentShape.hpp \
    src/Graphics.hpp \
    src/Graphics/RectangleShape.hpp \
    src/Graphics/Shape.hpp \
    src/Graphics/PointShape.hpp \
    src/GameObjects/GameObject.hpp \
    src/Graphics/SFMLEntity.hpp \
    src/Graphics/Entity.hpp \
    src/Windows/FixedFramerateWindow.hpp \
    src/GameObjects/DecorBox.hpp \
    src/GameObjects/Box.hpp \
    src/Physics.hpp \
    src/GameObjects.hpp \
    src/Graphics/_ThickPointShape.hpp \
    src/Graphics/DebugRenderer.hpp
