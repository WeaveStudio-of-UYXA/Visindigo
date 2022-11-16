QT       += core gui widgets qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
# 下面这些内容拒绝手动维护：您应该打开Visindigo的Visual Studio项目，右键Visindigo项目，在菜单的Qt项目里选择导出pri
# 按文本打开该pri文件并复制到下面。
SOURCES += \
    main.cpp \
    VIUI/MRW/MRWGlobal.cpp \
    Visindigo/VICore/VIGuiAnimation.cpp \
    VIJSAPI/VIJSGlobal.cpp \

HEADERS += \
    Global.h \
    VIUI/MRW/GUI2D/VI2DGUI.h \
    VIUI/MRW/MRWGlobal.h \
    VIUI/MRW/VIGUI2D.h \
    VIUI/MRW/VisindigoRuntime.h \
    VIUI/VIPlayerWidget.h \
    Visindigo/VICore/VIAnimation.h \
    Visindigo/VICore/VIGuiAnimation.h \
    VIJSAPI/JsVIGUI2D.h \
    VIJSAPI/JsVISystem.h \
    VIJSAPI/JsVIYSP.h \
    VIJSAPI/VIJSGlobal.h \
    VIJSAPI/VIJSHost.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
