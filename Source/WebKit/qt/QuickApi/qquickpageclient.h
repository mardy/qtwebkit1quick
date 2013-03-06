/*
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifndef QQUICKPAGECLIENT_H
#define QQUICKPAGECLIENT_H

#include "FrameView.h"
#include "GraphicsContext.h"
#include "IntRect.h"
#include "QWebPageClient.h"
#include "TextureMapperLayerClientQt.h"
#include "TiledBackingStore.h"
#include "qquickwebview.h"
#include "qwebframe.h"
#include "qwebframe_p.h"
#include "qwebpage.h"
#include "qwebpage_p.h"
#include <Settings.h>
#include <qmetaobject.h>
#include <qtimer.h>

QT_BEGIN_NAMESPACE
class QStyle;
QT_END_NAMESPACE

namespace WebCore {

class PageClientQQuick : public QWebPageClient {
public:
    PageClientQQuick(QQuickWebView* newView, QWebPage* newPage)
        : view(newView)
        , page(newPage)
    {
        Q_ASSERT(view);
    }
    virtual ~PageClientQQuick();

    virtual void scroll(int dx, int dy, const QRect&);
    virtual void update(const QRect& dirtyRect);
    virtual void repaintViewport();
    virtual void setInputMethodEnabled(bool);
    virtual bool inputMethodEnabled() const;
    virtual void setInputMethodHints(Qt::InputMethodHints);

#ifndef QT_NO_CURSOR
    virtual QCursor cursor() const;
    virtual void updateCursor(const QCursor&);
#endif

    virtual QPalette palette() const;
    virtual int screenNumber() const;
    virtual QObject* ownerWidget() const;
    virtual QRect geometryRelativeToOwnerWidget() const;

    virtual QObject* pluginParent() const;

    virtual QStyle* style() const;

    virtual bool viewResizesToContentsEnabled() const { return false; }

    virtual QRectF windowRect() const;

    virtual void setWidgetVisible(Widget*, bool visible);

    QQuickWebView* view;
    QWebPage* page;
};

}
#endif // QQUICKPAGECLIENT_H
