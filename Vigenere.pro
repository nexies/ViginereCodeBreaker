TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../libs
OBJECTS_DIR = ../obj/Vigenere
MOC_DIR = ../moc/Vigenere

TARGET = Vigenere

SOURCES += \
        source/interface.cpp \
        source/main.cpp \
        source/f_alphabet.cpp \
        source/f_encryptions.cpp \
        source/t_datamap.cpp

HEADERS += \
    source/interface.h \
    source/unicode_ascii.h \
    source/f_alphabet.h \
    source/f_encryptions.h \
    source/t_datamap.h
