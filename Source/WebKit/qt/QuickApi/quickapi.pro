# -------------------------------------------------------------------
# Target file for the QtWebKitWidgets dynamic library
#
# See 'Tools/qmake/README' for an overview of the build system
# -------------------------------------------------------------------

# Use Qt5's module system
load(qt_build_config)

TEMPLATE = lib
TARGET = qmlwebkit1plugin
TARGET.module_name = QtWebKit1

CONFIG += plugin

QMLDIRFILE = $${_PRO_FILE_PWD_}/qmldir
copy2build.input = QMLDIRFILE
copy2build.output = $${ROOT_BUILD_DIR}/imports/$${TARGET.module_name}/qmldir
!contains(TEMPLATE_PREFIX, vc):copy2build.variable_out = PRE_TARGETDEPS
copy2build.commands = $$QMAKE_COPY ${QMAKE_FILE_IN} ${QMAKE_FILE_OUT}
copy2build.name = COPY ${QMAKE_FILE_IN}
copy2build.CONFIG += no_link
QMAKE_EXTRA_COMPILERS += copy2build

contains(QT_CONFIG, reduce_exports):CONFIG += hide_symbols

WEBKIT_DESTDIR = $${ROOT_BUILD_DIR}/lib

SOURCE_DIR = $${ROOT_WEBKIT_DIR}/Source/WebKit

INCLUDEPATH += \
    $$SOURCE_DIR/qt/Api \
    $$SOURCE_DIR/qt/QuickApi \
    $$SOURCE_DIR/qt/WebCoreSupport \
    $$SOURCE_DIR/qt/WidgetSupport \
    $$ROOT_WEBKIT_DIR/Source/WTF/wtf/qt

enable?(DEVICE_ORIENTATION)|enable?(ORIENTATION_EVENTS) {
    QT += sensors
}

#enable?(GEOLOCATION): QT += location

#use?(QT_MULTIMEDIA): QT *= multimediawidgets

contains(CONFIG, texmap): DEFINES += WTF_USE_TEXTURE_MAPPER=1

use?(PLUGIN_BACKEND_XLIB): PKGCONFIG += x11

QT += network quick

#have?(QTPRINTSUPPORT): QT += printsupport

#use?(TEXTURE_MAPPER_GL)|enable?(WEBGL) {
#    QT *= opengl
#}
QT += webkit

use?(3D_GRAPHICS): WEBKIT += ANGLE

WEBKIT += javascriptcore wtf webcore

DESTDIR = $${ROOT_BUILD_DIR}/imports/$${TARGET.module_name}

# ---------------- Custom developer-build handling -------------------
#
# The assumption for Qt developer builds is that the module file
# will be put into qtbase/mkspecs/modules, and the libraries into
# qtbase/lib, with rpath/install_name set to the Qt lib dir.
#
# For WebKit we don't want that behavior for the libraries, as we want
# them to be self-contained in the WebKit build dir.
#
!production_build: CONFIG += force_independent

BASE_TARGET = $$TARGET

# Allow doing a debug-only build of WebKit (not supported by Qt)
macx:!debug_and_release:debug: TARGET = $$BASE_TARGET

DEFINES += QT_NO_CONTEXTMENU
QT -= widgets

SOURCES += \
    $${SOURCE_DIR}/qt/QuickApi/plugin.cpp \
    $${SOURCE_DIR}/qt/QuickApi/qquickpageclient.cpp \
    $${SOURCE_DIR}/qt/QuickApi/qquickwebview.cpp \
    $${SOURCE_DIR}/qt/QuickApi/qwebframe.cpp \
    $${SOURCE_DIR}/qt/QuickApi/qwebpage.cpp \
    $${SOURCE_DIR}/qt/WidgetSupport/DefaultFullScreenVideoHandler.cpp

HEADERS += \
    $${SOURCE_DIR}/qt/QuickApi/qquickpageclient.h \
    $${SOURCE_DIR}/qt/QuickApi/qquickwebview.h \
    $${SOURCE_DIR}/qt/QuickApi/qwebframe.h \
    $${SOURCE_DIR}/qt/QuickApi/qwebframe_p.h \
    $${SOURCE_DIR}/qt/QuickApi/qwebpage.h \
    $${SOURCE_DIR}/qt/QuickApi/qwebpage_p.h \
    $${SOURCE_DIR}/qt/Api/qwebkitplatformplugin.h \
    $${SOURCE_DIR}/qt/WidgetSupport/DefaultFullScreenVideoHandler.h

INCLUDEPATH += \
    $$PWD/qt/Api \
    $$PWD/qt/WebCoreSupport

enable?(VIDEO) {
    !use?(QTKIT):!use?(GSTREAMER):use?(QT_MULTIMEDIA) {
        HEADERS += $$PWD/WebKit/qt/WidgetSupport/FullScreenVideoWidget.h
        SOURCES += $$PWD/WebKit/qt/WidgetSupport/FullScreenVideoWidget.cpp
    }
}

# The fallback to QT_INSTALL_IMPORTS can be removed once we
# depend on Qt 5 RC1.
importPath = $$[QT_INSTALL_QML]
isEmpty(importPath): importPath = $$[QT_INSTALL_IMPORTS]

target.path = $${importPath}/$${TARGET.module_name}

qmldir.files += $$PWD/qmldir
qmldir.path +=  $${importPath}/$${TARGET.module_name}

INSTALLS += target qmldir
