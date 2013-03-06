/*
    Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"

#include "qglobal.h"

#include "qquickwebview.h"
#include "qwebpage.h"

#include <QtQml/qqml.h>
#include <QtQml/qqmlengine.h>
#include <QtQml/qqmlextensionplugin.h>

QT_BEGIN_NAMESPACE

class WebKitQmlPlugin : public QQmlExtensionPlugin {
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface" FILE "plugin.json")
    Q_OBJECT
public:
    virtual void initializeEngine(QQmlEngine* engine, const char* uri)
    {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("QtWebKit1"));
    }

    virtual void registerTypes(const char* uri)
    {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("QtWebKit1"));

        qmlRegisterType<QQuickWebView>(uri, 1, 0, "WebView");
        qmlRegisterUncreatableType<QWebPage>(uri, 1, 0, "WebPage", QObject::tr("Cannot create separate instance of WebPage, use WebView"));
    }
};

QT_END_NAMESPACE

#include "plugin.moc"
