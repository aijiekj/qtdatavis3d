/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the QtDataVisualization module.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

#include "declarativescatter_p.h"
#include "declarativescatterrenderer_p.h"
#include "qitemmodelscatterdataproxy.h"

QT_DATAVISUALIZATION_BEGIN_NAMESPACE

const QString smoothString(QStringLiteral("Smooth"));

DeclarativeScatter::DeclarativeScatter(QQuickItem *parent)
    : QQuickItem(parent),
      m_shared(0),
      m_initialisedSize(0, 0),
      m_theme(QDataVis::ThemeDefault)
{
    setFlags(QQuickItem::ItemHasContents);
    setAcceptedMouseButtons(Qt::AllButtons);

    // TODO: These seem to have no effect; find a way to activate anti-aliasing
    setAntialiasing(true);
    setSmooth(true);

    // Create the shared component on the main GUI thread.
    m_shared = new Scatter3DController(boundingRect().toRect());
    QObject::connect(m_shared, &Abstract3DController::shadowQualityChanged, this,
                     &DeclarativeScatter::handleShadowQualityUpdate);

    m_shared->setActiveDataProxy(new QItemModelScatterDataProxy);
}

DeclarativeScatter::~DeclarativeScatter()
{
    delete m_shared;
}

void DeclarativeScatter::handleShadowQualityUpdate(QDataVis::ShadowQuality quality)
{
    emit shadowQualityChanged(quality);
}

QSGNode *DeclarativeScatter::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    // If old node exists and has right size, reuse it.
    if (oldNode && m_initialisedSize == boundingRect().size().toSize()) {
        // Update bounding rectangle (that has same size as before).
        static_cast<DeclarativeScatterRenderer *>( oldNode )->setRect(boundingRect());
        return oldNode;
    }

    // Create a new render node when size changes or if there is no node yet
    m_initialisedSize = boundingRect().size().toSize();

    // Delete old node
    if (oldNode)
        delete oldNode;

    // Create a new one and set it's bounding rectangle
    DeclarativeScatterRenderer *node = new DeclarativeScatterRenderer(window(), m_shared);
    node->setRect(boundingRect());
    m_shared->setBoundingRect(boundingRect().toRect());
    return node;
}

void DeclarativeScatter::setCameraPosition(qreal horizontal, qreal vertical, int distance)
{
    m_shared->setCameraPosition(GLfloat(horizontal), GLfloat(vertical), GLint(distance));
}

void DeclarativeScatter::setObjectColor(const QColor &baseColor, bool uniform)
{
    m_shared->setObjectColor(baseColor, uniform);
}

QScatterDataProxy *DeclarativeScatter::dataProxy() const
{
    return static_cast<QScatterDataProxy *>(m_shared->activeDataProxy());
}

void DeclarativeScatter::setDataProxy(QScatterDataProxy *dataProxy)
{
    m_shared->setActiveDataProxy(dataProxy);
}

Q3DValueAxis *DeclarativeScatter::axisX() const
{
    return static_cast<Q3DValueAxis *>(m_shared->axisX());
}

void DeclarativeScatter::setAxisX(Q3DValueAxis *axis)
{
    m_shared->setAxisX(axis);
}

Q3DValueAxis *DeclarativeScatter::axisY() const
{
    return static_cast<Q3DValueAxis *>(m_shared->axisY());
}

void DeclarativeScatter::setAxisY(Q3DValueAxis *axis)
{
    m_shared->setAxisY(axis);
}

Q3DValueAxis *DeclarativeScatter::axisZ() const
{
    return static_cast<Q3DValueAxis *>(m_shared->axisZ());
}

void DeclarativeScatter::setAxisZ(Q3DValueAxis *axis)
{
    m_shared->setAxisZ(axis);
}

void DeclarativeScatter::setObjectType(QDataVis::MeshStyle style)
{
    QString objFile = m_shared->meshFileName();
    bool smooth = objFile.endsWith(smoothString);
    m_shared->setObjectType(style, smooth);
}

QDataVis::MeshStyle DeclarativeScatter::objectType()
{
    QString objFile = m_shared->meshFileName();
    if (objFile.contains("/sphere"))
        return QDataVis::Spheres;
    else
        return QDataVis::Dots;
}

void DeclarativeScatter::setObjectSmoothingEnabled(bool enabled)
{
    QString objFile = m_shared->meshFileName();
    if (objFile.endsWith(smoothString)) {
        if (enabled)
            return; // Already smooth; do nothing
        else // Rip Smooth off the end
            objFile.resize(objFile.indexOf(smoothString));
    } else {
        if (!enabled) // Already flat; do nothing
            return;
        else // Append Smooth to the end
            objFile.append(smoothString);
    }
    m_shared->setMeshFileName(objFile);
}

bool DeclarativeScatter::isObjectSmoothingEnabled()
{
    QString objFile = m_shared->meshFileName();
    return objFile.endsWith(smoothString);
}

void DeclarativeScatter::setMeshFileName(const QString &objFileName)
{
    m_shared->setMeshFileName(objFileName);
}

QString DeclarativeScatter::meshFileName()
{
    return m_shared->meshFileName();
}

void DeclarativeScatter::setCameraPreset(QDataVis::CameraPreset preset)
{
    m_shared->setCameraPreset(preset);
}

QDataVis::CameraPreset DeclarativeScatter::cameraPreset()
{
    return m_shared->cameraPreset();
}

void DeclarativeScatter::setTheme(QDataVis::ColorTheme theme)
{
    // TODO: Implement correctly once "user-modifiable themes" (QTRD-2120) is implemented
    // We need to save this locally, as there are no getters for it in controller
    m_theme = theme;
    m_shared->setColorTheme(theme);

    // TODO: Investigate why the beforeSynchronizing() signal requires update and is not sent automatically when this value changes,
    // but is sent wen e.g. enable/disable background changes.
    update();
}

QDataVis::ColorTheme DeclarativeScatter::theme()
{
    return m_theme;
}

void DeclarativeScatter::setFont(const QFont &font)
{
    m_shared->setFont(font);
}

QFont DeclarativeScatter::font()
{
    return m_shared->font();
}

void DeclarativeScatter::setLabelTransparency(QDataVis::LabelTransparency transparency)
{
    m_shared->setLabelTransparency(transparency);
}

QDataVis::LabelTransparency DeclarativeScatter::labelTransparency()
{
    return m_shared->labelTransparency();
}

void DeclarativeScatter::setGridVisible(bool visible)
{
    m_shared->setGridEnabled(visible);
}

bool DeclarativeScatter::isGridVisible()
{
    return m_shared->gridEnabled();
}

void DeclarativeScatter::setBackgroundVisible(bool visible)
{
    m_shared->setBackgroundEnabled(visible);
}

bool DeclarativeScatter::isBackgroundVisible()
{
    return m_shared->backgroundEnabled();
}

void DeclarativeScatter::setSelectionMode(QDataVis::SelectionMode mode)
{
    m_shared->setSelectionMode(mode);
}

QDataVis::SelectionMode DeclarativeScatter::selectionMode()
{
    return m_shared->selectionMode();
}

void DeclarativeScatter::setShadowQuality(QDataVis::ShadowQuality quality)
{
    m_shared->setShadowQuality(quality);
}

QDataVis::ShadowQuality DeclarativeScatter::shadowQuality()
{
    return m_shared->shadowQuality();
}

void DeclarativeScatter::setItemLabelFormat(const QString &format)
{
    m_shared->activeDataProxy()->setItemLabelFormat(format);
}

QString DeclarativeScatter::itemLabelFormat()
{
    return m_shared->activeDataProxy()->itemLabelFormat();
}

void DeclarativeScatter::mouseDoubleClickEvent(QMouseEvent *event)
{
#if defined(Q_OS_ANDROID)
    m_shared->mouseDoubleClickEvent(event);
#else
    Q_UNUSED(event)
#endif
}

void DeclarativeScatter::touchEvent(QTouchEvent *event)
{
#if defined(Q_OS_ANDROID)
    m_shared->touchEvent(event);
    update();
#else
    Q_UNUSED(event)
#endif
}

void DeclarativeScatter::mousePressEvent(QMouseEvent *event)
{
    QPoint mousePos = event->pos();
    //mousePos.setY(height() - mousePos.y());
    m_shared->mousePressEvent(event, mousePos);
}

void DeclarativeScatter::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint mousePos = event->pos();
    //mousePos.setY(height() - mousePos.y());
    m_shared->mouseReleaseEvent(event, mousePos);
}

void DeclarativeScatter::mouseMoveEvent(QMouseEvent *event)
{
    QPoint mousePos = event->pos();
    //mousePos.setY(height() - mousePos.y());
    m_shared->mouseMoveEvent(event, mousePos);
}

void DeclarativeScatter::wheelEvent(QWheelEvent *event)
{
    m_shared->wheelEvent(event);
}

QT_DATAVISUALIZATION_END_NAMESPACE