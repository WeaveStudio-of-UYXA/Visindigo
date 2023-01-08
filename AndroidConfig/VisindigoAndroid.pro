QT       += core gui widgets qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
# 下面这些内容拒绝手动维护：您应该打开Visindigo的Visual Studio项目，右键Visindigo项目，在菜单的Qt项目里选择导出pri
# 按文本打开该pri文件并复制到下面。
HEADERS += CommonEdit/CECore/CEMacro.h \
    CommonEdit/CECore/CE_QtMacro.h \
    Global.h \
    init.h \
    VIJSAPI/JsVIBase.h \
    VIJSAPI/macro/VIJSGlobal_m.h \
    VIJSAPI/VIGUI/VIGUILabel/JsVIGUILabel.h \
    VIJSAPI/VIJSGlobal.h \
    Visindigo/VICore/macro/VIGeneralBehavior_m.h \
    Visindigo/VICore/VIMath.h \
    Visindigo/VIObjects/macro/VIGlassConvention.h \
    Visindigo/VIObjects/VIImage.h \
    Visindigo/VIWidgets/VIGUILabel/VIGUILabelBase.h \
    VIUI/MRW/GUI2D/VIGUILabel.h \
    VIUI/PW/VisindigoProject.h \
    VIUI/RW/VisindigoRepos.h \
    VIUI/MRW/MRWGlobal.h \
    VIUI/VIPlayerWidget.h \
    VIJSAPI/JsVIGUI2D.h \
    VIJSAPI/JsVISystem.h \
    CommonEdit/CEFunction/CELanguage.h \
    VIJSAPI/JsVIYSP.h \
    VIJSAPI/HostExceptionUI.h \
    VIJSAPI/JsVIGUI2DBase.h \
    VIJSAPI/JsVIChara.h \
    VIJSAPI/JsVIContainer.h \
    Visindigo/VICore/VIAnimation.h \
    Visindigo/VICore/VIQtExtensionMethod.h \
    Visindigo/VICore/VIGeneralBehavior.h \
    VIUI/MRW/GUI2D/VI2DGUIBase.h \
    VIUI/MRW/Scene3D/VIScene3DBase.h \
    Visindigo/VISystem/VISystemBase.h \
    VIUI/MRW/VIGUI2D.h \
    VIJSAPI/VIJSHost.h \
    Visindigo/VICore/VIGuiAnimation.h \
    VIUI/MRW/VisindigoRuntime.h \
    VIUI/MRW/GUI2D/VI2DGUI.h
SOURCES += CommonEdit/CEFunction/CELanguage.cpp \
    init.cpp \
    main.cpp \
    VIJSAPI/VIJSGlobal.cpp \
    Visindigo/VICore/VIGeneralBehavior.cpp \
    Visindigo/VICore/VIGuiAnimation.cpp \
    Visindigo/VISystem/VISystemBase.cpp \
    VIUI/MRW/MRWGlobal.cpp
RESOURCES += Resource.qrc

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
