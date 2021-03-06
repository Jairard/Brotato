TEMPLATE = app
CONFIG += console 
CONFIG += object_with_source
CONFIG -= qt

TRUNK_DIR = ../../..
BIN_DIR = TRUNK_DIR/bin
SRC_DIR = TRUNK_DIR/src

TARGET = BIN_DIR/Brotato

SOURCES += \ 
    ../../../src/Core/Math.cpp \
    ../../../src/Core/Logger.cpp \
    ../../../src/main.cpp \
    ../../../src/Physics/Entity.cpp \
    ../../../src/Physics/World.cpp \
    ../../../src/Physics/Rectangle.cpp \
    ../../../src/Physics/Edge.cpp \
    ../../../src/Graphics/Renderer.cpp \
    ../../../src/Graphics/SegmentShape.cpp \
    ../../../src/Graphics/RectangleShape.cpp \
    ../../../src/Graphics/Shape.cpp \
    ../../../src/Graphics/SFMLEntity.cpp \
    ../../../src/Graphics/Entity.cpp \
    ../../../src/Graphics/PointShape.cpp \
    ../../../src/Graphics/_ThickPointShape.cpp \
    ../../../src/Graphics/DebugRenderer.cpp \
    ../../../src/GameObjects/GameObject.cpp \
    ../../../src/GameObjects/DecorBox.cpp \
    ../../../src/GameObjects/Box.cpp \
    ../../../src/GameObjects/Segment.cpp \
    ../../../src/Windows/Window.cpp \
    ../../../src/Windows/InputListener.cpp \
    ../../../src/Windows/Game.cpp

HEADERS +=  \
    ../../../src/Physics/World.hpp \
    ../../../src/Physics/Entity.hpp \
    ../../../src/Physics/Rectangle.hpp \ 
    ../../../src/Physics/Edge.hpp \
    ../../../src/Graphics/SegmentShape.hpp \
    ../../../src/Graphics.hpp \
    ../../../src/Graphics/Renderer.hpp \
    ../../../src/Graphics/RectangleShape.hpp \
    ../../../src/Graphics/Shape.hpp \
    ../../../src/Graphics/PointShape.hpp \
    ../../../src/Graphics/SFMLEntity.hpp \
    ../../../src/Graphics/Entity.hpp \
    ../../../src/Graphics/_ThickPointShape.hpp \
    ../../../src/Graphics/DebugRenderer.hpp \
    ../../../src/GameObjects/DecorBox.hpp \
    ../../../src/GameObjects/GameObject.hpp \
    ../../../src/GameObjects/Box.hpp \
    ../../../src/GameObjects/Segment.hpp \
    ../../../src/Physics.hpp \
    ../../../src/GameObjects.hpp \
    ../../../src/Core.hpp \
    ../../../src/Core/Logger.hpp \
    ../../../src/Core/NonInstantiable.hpp \ 
    ../../../src/Core/Vector2.hpp \
    ../../../src/Core/Singleton.hpp \
    ../../../src/Core/Tools.hpp \
    ../../../src/Core/Math.hpp \
    ../../../src/Window.hpp \
    ../../../src/Windows/Window.hpp \
    ../../../src/Windows/InputListener.hpp \
    ../../../src/Windows/Game.hpp
