TEMPLATE = app
CONFIG += console 
CONFIG += object_with_source
CONFIG -= qt

TRUNK_DIR = ../../..
BIN_DIR = TRUNK_DIR/bin
SRC_DIR = TRUNK_DIR/src

TARGET = BIN_DIR/Brotato

SOURCES += \ 
    ../../../src/PotatoEngine/_potatoEngine_main.cpp \
    ../../../src/PotatoEngine/PotatoPlant.cpp \
    ../../../src/PotatoEngine/Stem.cpp \
    ../../../src/PotatoEngine/Potato.cpp \
    ../../../src/PotatoEngine/Cell.cpp \
    ../../../src/PotatoEngine/RenderCell.cpp \
    ../../../src/PotatoEngine/GeometryCell.cpp \
    ../../../src/PotatoEngine/RectangleGeometry.cpp \
    ../../../src/PotatoEngine/LineGeometry.cpp \
    ../../../src/PotatoEngine/InputListener.cpp \
    ../../../src/PotatoEngine/Debug/Renderer.cpp \
    ../../../src/PotatoEngine/Debug/Logger.cpp \
    ../../../src/PotatoEngine/Core/Transform.cpp \
    ../../../src/PotatoEngine/Core/Math.cpp \
    ../../../src/PotatoEngine/Debug/assert.cpp \
    ../../../src/PotatoEngine/PotatoDNA.cpp

HEADERS +=  \
    ../../../src/PotatoEngine/PotatoPlant.hpp \
    ../../../src/PotatoEngine/Stem.hpp \
    ../../../src/PotatoEngine/Potato.hpp \
    ../../../src/PotatoEngine/Cell.hpp \
    ../../../src/PotatoEngine/RenderCell.hpp \
    ../../../src/PotatoEngine/GeometryCell.hpp \
    ../../../src/PotatoEngine/RectangleGeometry.hpp \
    ../../../src/PotatoEngine/LineGeometry.hpp \
    ../../../src/PotatoEngine/InputListener.hpp \
    ../../../src/PotatoEngine/Debug/Renderer.hpp \
    ../../../src/PotatoEngine/Debug/Logger.hpp \
    ../../../src/PotatoEngine/Core/AARect.hpp \
    ../../../src/PotatoEngine/Core/Rect.hpp \
    ../../../src/PotatoEngine/Core/ClassHelpers.hpp \
    ../../../src/PotatoEngine/Core/ClassHelpers.hpp \
    ../../../src/PotatoEngine/Core/LibsHelpers.hpp \
    ../../../src/PotatoEngine/Core/Transform.hpp \
    ../../../src/PotatoEngine/Core/Vector2.hpp \
    ../../../src/PotatoEngine/Core/Math.hpp \
    ../../../src/PotatoEngine/Core/Pool.hpp \
    ../../../src/PotatoEngine/Core/Tools.hpp \
    ../../../src/PotatoEngine/Core/NonInstantiable.hpp \
    ../../../src/PotatoEngine/Core/NonCopyable.hpp \
    ../../../src/PotatoEngine/Core/Stainable.hpp \
    ../../../src/PotatoEngine/Core/Singleton.hpp \
    ../../../src/PotatoEngine/Core/CompilFlags.hpp \
    ../../../src/PotatoEngine/Debug/assert.hpp \
    ../../../src/PotatoEngine/PotatoDNA.hpp

OTHER_FILES += \
    ../../../src/TODO
