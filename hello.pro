QT += widgets sql core gui charts

DEFINES += _WIN32_WINNT=0x0A00
TEMPLATE = app
LIBS += -lws2_32
# Enable C++17
CONFIG   += c++17

# Input
SOURCES += main.cpp
# Add UI files
FORMS += mainwindow.ui addrecordwindow.ui optionswindow.ui

# Add PostgreSQL include directory
INCLUDEPATH += "C:/Program Files/PostgreSQL/include"

# Add PostgreSQL library directory and link libpq
LIBS += -L"C:/Program Files/PostgreSQL/lib" -lpq