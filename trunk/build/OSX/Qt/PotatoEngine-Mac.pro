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
    ../../../src/PotatoEngine/Debug/assert.cpp \
    ../../../src/PotatoEngine/Core/Transform.cpp \
    ../../../src/PotatoEngine/Core/Math.cpp \
    ../../../src/PotatoEngine/DNACollector.cpp \
    ../../../src/PotatoEngine/BaseOrganism.cpp \
    ../../../src/PotatoEngine/BaseDNA.cpp \
    ../../../src/PotatoEngine/DNACollectorChecker.cpp \
    ../../../src/PotatoEngine/DNACollectorTimestamp.cpp \
    ../../../src/PotatoEngine/Debug/Demangler.cpp \
    ../../../src/PotatoEngine/Debug/Callstack/AbstractCallstack.cpp \
    ../../../src/PotatoEngine/Debug/Callstack/EmptyCallstack.cpp \
    ../../../src/PotatoEngine/Debug/Callstack/BacktraceCallstack.cpp \
    ../../../src/PotatoEngine/Debug/Callstack/BackwardCPPCallstack.cpp \
    ../../../src/PotatoEngine/Debug/Callstack/StackWalkerCallstack.cpp \
    ../../../src/PotatoEngine/Debug/Callstack/StackWalker.cpp \
    ../../../src/PotatoEngine/Debug/SignalHandler.cpp \
    ../../../src/PotatoEngine/Debug/PosixSignalHandler.cpp \
    ../../../src/PotatoEngine/Debug/WindowsSignalHandler.cpp \
    ../../../src/PotatoEngine/Core/BuildConfig.cpp

HEADERS +=  \
    ../../../src/PotatoEngine/stdafx.h \
    ../../../src/PotatoEngine/targetver.h \
    ../../../src/PotatoEngine/PotatoPlant.hpp \
    ../../../src/PotatoEngine/Stem.hpp \
    ../../../src/PotatoEngine/Potato.hpp \
    ../../../src/PotatoEngine/Cell.hpp \
    ../../../src/PotatoEngine/RenderCell.hpp \
    ../../../src/PotatoEngine/GeometryCell.hpp \
    ../../../src/PotatoEngine/RectangleGeometry.hpp \
    ../../../src/PotatoEngine/LineGeometry.hpp \
    ../../../src/PotatoEngine/InputListener.hpp \ \
    ../../../src/PotatoEngine/Debug/Renderer.hpp \
    ../../../src/PotatoEngine/Debug/Logger.hpp \
    ../../../src/PotatoEngine/Debug/assert.hpp \
    ../../../src/PotatoEngine/Core/compil.hpp \
    ../../../src/PotatoEngine/Core/Vector2.hpp \
    ../../../src/PotatoEngine/Core/Transform.hpp \
    ../../../src/PotatoEngine/Core/Tools.hpp \
    ../../../src/PotatoEngine/Core/Stainable.hpp \
    ../../../src/PotatoEngine/Core/Singleton.hpp \
    ../../../src/PotatoEngine/Core/Rect.hpp \
    ../../../src/PotatoEngine/Core/Pool.hpp \
    ../../../src/PotatoEngine/Core/NonInstantiable.hpp \
    ../../../src/PotatoEngine/Core/NonCopyable.hpp \
    ../../../src/PotatoEngine/Core/Math.hpp \
    ../../../src/PotatoEngine/Core/LibsHelpers.hpp \
    ../../../src/PotatoEngine/Core/ClassHelpers.hpp \
    ../../../src/PotatoEngine/Core/AARect.hpp \
    ../../../src/PotatoEngine/Core/types.hpp \
    ../../../src/PotatoEngine/DNACollector.hpp \
    ../../../src/PotatoEngine/BaseOrganism.hpp \
    ../../../src/PotatoEngine/DNA.hpp \
    ../../../src/PotatoEngine/BaseDNA.hpp \
    ../../../src/PotatoEngine/DNACollectorChecker.hpp \
    ../../../src/PotatoEngine/DNACollectorTimestamp.hpp \
    ../../../src/PotatoEngine/Debug/Demangler.hpp \
    ../../../src/PotatoEngine/Debug/Callstack.hpp \
    ../../../src/PotatoEngine/Debug/Callstack/AbstractCallstack.hpp \
    ../../../src/PotatoEngine/Debug/Callstack/EmptyCallstack.hpp \
    ../../../src/PotatoEngine/Debug/Callstack/BacktraceCallstack.hpp \
    ../../../src/PotatoEngine/Debug/Callstack/BackwardCPPCallstack.hpp \
    ../../../src/PotatoEngine/Debug/Callstack/StackWalkerCallstack.hpp \
    ../../../src/PotatoEngine/Debug/Callstack/StackWalker.h \
    ../../../src/PotatoEngine/Debug/Callstack/backward.hpp \
    ../../../src/PotatoEngine/Debug/SignalHandler.hpp \
    ../../../src/PotatoEngine/Debug/PosixSignalHandler.hpp \
    ../../../src/PotatoEngine/Debug/WindowsSignalHandler.hpp \
    ../../../src/PotatoEngine/Core/BuildConfig.hpp

OTHER_FILES += \
    ../../../src/TODO \
    ../../../build/makefile \
    ../../../../.gitignore
