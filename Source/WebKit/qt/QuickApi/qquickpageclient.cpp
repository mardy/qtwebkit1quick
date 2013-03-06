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

#include "config.h"
#include "qquickpageclient.h"

#include <qguiapplication.h>
#include <qquickwindow.h>

#if USE(ACCELERATED_COMPOSITING)
#include "TextureMapper.h"
#include "texmap/TextureMapperLayer.h"
#endif

QWindow* QWebPageClient::ownerWindow() const
{
    QQuickItem *item = qobject_cast<QQuickItem*>(ownerWidget());
    if (!item)
        return 0;
    return item->window();
}


namespace WebCore {

void PageClientQQuick::scroll(int dx, int dy, const QRect& rectToScroll)
{
    Q_UNUSED(dx);
    Q_UNUSED(dy);
    Q_UNUSED(rectToScroll);
    view->update();
}

void PageClientQQuick::update(const QRect & dirtyRect)
{
    qDebug() << Q_FUNC_INFO << dirtyRect;
    view->repaint(dirtyRect);
}

void PageClientQQuick::repaintViewport()
{
    qDebug() << Q_FUNC_INFO;
    view->repaint();
}

void PageClientQQuick::setInputMethodEnabled(bool enable)
{
    view->setFlag(QQuickItem::ItemAcceptsInputMethod, enable);
}

bool PageClientQQuick::inputMethodEnabled() const
{
    return view->flags() & QQuickItem::ItemAcceptsInputMethod;
}

void PageClientQQuick::setInputMethodHints(Qt::InputMethodHints hints)
{
    view->setInputMethodHints(hints);
}

PageClientQQuick::~PageClientQQuick()
{
}

#ifndef QT_NO_CURSOR
QCursor PageClientQQuick::cursor() const
{
    return view->cursor();
}

void PageClientQQuick::updateCursor(const QCursor& cursor)
{
    view->setCursor(cursor);
}
#endif

QPalette PageClientQQuick::palette() const
{
    return QGuiApplication::palette();
}

int PageClientQQuick::screenNumber() const
{
    return 0;
}

QObject* PageClientQQuick::ownerWidget() const
{
    return view;
}

QRect PageClientQQuick::geometryRelativeToOwnerWidget() const
{
    return QRect(0, 0, view->width(), view->height());
}

QObject* PageClientQQuick::pluginParent() const
{
    return view;
}

QStyle* PageClientQQuick::style() const
{
    return 0;
}

QRectF PageClientQQuick::windowRect() const
{
    return QRectF(view->window()->geometry());
}

void PageClientQQuick::setWidgetVisible(Widget* widget, bool visible)
{
    Q_UNUSED(widget);
    Q_UNUSED(visible);
    return;
}

} // namespace WebCore

