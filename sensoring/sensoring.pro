QT += widgets serialport
QT += charts

HEADERS += \
    chart.h \
    chartsettingdlg.h \
    chartview.h \
    mainwindow.h \
    serialdemo.h \
    serialport.h \
    serialsource.h \
    settingsdialog.h \
    console.h \
    statusbar.h

SOURCES += \
    chartsettingdlg.cpp \
    main.cpp \
    chart.cpp \
    chartview.cpp \
    mainwindow.cpp \
    serialdemo.cpp \
    serialport.cpp \
    serialsource.cpp \
    settingsdialog.cpp \
    console.cpp \
    statusbar.cpp

FORMS += \
    chartsettingdlg.ui \
    mainwindow.ui \
    settingsdialog.ui

RESOURCES += \
    sensoring.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
