QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcategory.cpp \
    addsavenote.cpp \
    category.cpp \
    deletednotes.cpp \
    dynamiccategory.cpp \
    dynamicnote.cpp \
    login.cpp \
    main.cpp \
    notesincategory.cpp \
    popupmenu.cpp \
    register.cpp \
    userpage.cpp

HEADERS += \
    addcategory.h \
    addsavenote.h \
    category.h \
    deletednotes.h \
    dynamiccategory.h \
    dynamicnote.h \
    login.h \
    notesincategory.h \
    popupmenu.h \
    register.h \
    userpage.h

FORMS += \
    addcategory.ui \
    addsavenote.ui \
    category.ui \
    deletednotes.ui \
    login.ui \
    notesincategory.ui \
    register.ui \
    userpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=


HEADERS += \
    addsavenote.h

FORMS += \
    addsavenote.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
