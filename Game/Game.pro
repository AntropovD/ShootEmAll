QT    += phonon

HEADERS += \
    window.h \
    field.h

SOURCES += \
    main.cpp \
    window.cpp \
    field.cpp

RESOURCES += \
    resources.qrc
	
RC_FILE = myicon.rc 

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog

