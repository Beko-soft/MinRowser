QT += core gui widgets webenginewidgets

CONFIG += c++17

TARGET = Browser
TEMPLATE = app

SOURCES += \
    browser.cpp

# Daha düşük ikili boyut ve derleme süresi için gereksiz Qt özellikleri devre dışı
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

# Release derlemede optimizasyon
CONFIG(release, debug|release) {
    DEFINES += QT_NO_DEBUG_OUTPUT
}
