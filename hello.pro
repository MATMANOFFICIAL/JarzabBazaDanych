QT       += widgets sql core gui


TEMPLATE = app

# Enable C++17
CONFIG   += c++17

# Input
SOURCES += main.cpp
# Add UI files
FORMS += mainwindow.ui addrecordwindow.ui

# Add PostgreSQL include directory
INCLUDEPATH += "C:/Program Files/PostgreSQL/include"

# Add PostgreSQL library directory and link libpq
LIBS += -L"C:/Program Files/PostgreSQL/lib" -lpq