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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the QtDataVisualization API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef DECLARATIVEBARS_P_H
#define DECLARATIVEBARS_P_H

#include "datavisualizationglobal_p.h"
#include "bars3dcontroller_p.h"
#include "declarativebars_p.h"
#include "q3dvalueaxis.h"
#include "q3dcategoryaxis.h"
#include "qbardataproxy.h"

#include <QAbstractItemModel>
#include <QQuickItem>
#include <QObject>
#include <QQuickWindow>

QT_DATAVISUALIZATION_BEGIN_NAMESPACE

class DeclarativeBars : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QBarDataProxy *dataProxy READ dataProxy WRITE setDataProxy)
    Q_PROPERTY(Q3DCategoryAxis *rowAxis READ rowAxis WRITE setRowAxis)
    Q_PROPERTY(Q3DValueAxis *valueAxis READ valueAxis WRITE setValueAxis)
    Q_PROPERTY(Q3DCategoryAxis *columnAxis READ columnAxis WRITE setColumnAxis)
    Q_PROPERTY(QtDataVisualization::QDataVis::SelectionMode selectionMode READ selectionMode WRITE setSelectionMode)
    Q_PROPERTY(QtDataVisualization::QDataVis::LabelTransparency labelTransparency READ labelTransparency WRITE setLabelTransparency)
    Q_PROPERTY(QtDataVisualization::QDataVis::ShadowQuality shadowQuality READ shadowQuality WRITE setShadowQuality)
    Q_PROPERTY(QtDataVisualization::QDataVis::MeshStyle barType READ barType WRITE setBarType)
    Q_PROPERTY(QtDataVisualization::QDataVis::CameraPreset cameraPreset READ cameraPreset WRITE setCameraPreset)
    Q_PROPERTY(QtDataVisualization::QDataVis::ColorTheme theme READ theme WRITE setTheme)
    Q_PROPERTY(qreal barThickness READ barThickness WRITE setBarThickness)
    Q_PROPERTY(QSizeF barSpacing READ barSpacing WRITE setBarSpacing)
    Q_PROPERTY(bool barSpacingRelative READ isBarSpacingRelative WRITE setBarSpacingRelative)
    Q_PROPERTY(bool barSmoothingEnabled READ isBarSmoothingEnabled WRITE setBarSmoothingEnabled)
    Q_PROPERTY(QString meshFileName READ meshFileName WRITE setMeshFileName)
    Q_PROPERTY(QFont font READ font WRITE setFont)
    Q_PROPERTY(bool gridVisible READ isGridVisible WRITE setGridVisible)
    Q_PROPERTY(bool backgroundVisible READ isBackgroundVisible WRITE setBackgroundVisible)
    Q_PROPERTY(QString itemLabelFormat READ itemLabelFormat WRITE setItemLabelFormat)
    Q_PROPERTY(QPointF selectedBarPos READ selectedBarPos WRITE setSelectedBarPos NOTIFY selectedBarPosChanged)
    Q_ENUMS(QtDataVisualization::QDataVis::SelectionMode)
    Q_ENUMS(QtDataVisualization::QDataVis::ShadowQuality)
    Q_ENUMS(QtDataVisualization::QDataVis::LabelTransparency)
    Q_ENUMS(QtDataVisualization::QDataVis::MeshStyle)
    Q_ENUMS(QtDataVisualization::QDataVis::CameraPreset)
    Q_ENUMS(QtDataVisualization::QDataVis::ColorTheme)

public:
    explicit DeclarativeBars(QQuickItem *parent = 0);
    ~DeclarativeBars();

    // Set color if you don't want to use themes. Set uniform to false if you want the (height)
    // color to change from bottom to top
    Q_INVOKABLE void setBarColor(const QColor &baseColor, bool uniform = true);

    // Set camera rotation if you don't want to use the presets (in horizontal (-180...180) and
    // vertical (0...90) (or (-90...90) if there are negative values) angles and distance in
    // percentage (10...500))
    Q_INVOKABLE void setCameraPosition(qreal horizontal, qreal vertical, int distance);

    QBarDataProxy *dataProxy() const;
    void setDataProxy(QBarDataProxy *dataProxy);

    Q3DCategoryAxis *rowAxis() const;
    void setRowAxis(Q3DCategoryAxis *axis);
    Q3DValueAxis *valueAxis() const;
    void setValueAxis(Q3DValueAxis *axis);
    Q3DCategoryAxis *columnAxis() const;
    void setColumnAxis(Q3DCategoryAxis *axis);

    // Set bar thickness.
    void setBarThickness(qreal thicknessRatio);
    qreal barThickness();

    // Set spacing between bars. Y-component sets the spacing of Z-direction.
    // If spacing is relative, 0.0f means side-to-side and 1.0f = one thickness in between.
    void setBarSpacing(QSizeF spacing);
    QSizeF barSpacing();

    // Set bar spacing relative to thickness or absolute
    void setBarSpacingRelative(bool relative);
    bool isBarSpacingRelative();

    // Bar type
    void setBarType(QDataVis::MeshStyle style);
    QDataVis::MeshStyle barType();

    // Bar smoothing
    void setBarSmoothingEnabled(bool enabled);
    bool isBarSmoothingEnabled();

    // override object type with own mesh
    void setMeshFileName(const QString &objFileName);
    QString meshFileName();

    // Select preset camera placement
    void setCameraPreset(QDataVis::CameraPreset preset);
    QDataVis::CameraPreset cameraPreset();

    // Set theme (object colors, shaders, window color, background colors, light intensity and text
    // colors are affected)
    void setTheme(QDataVis::ColorTheme theme);
    QDataVis::ColorTheme theme();

    // Change selection mode; single bar, bar and row, bar and column, or all
    void setSelectionMode(QDataVis::SelectionMode mode);
    QDataVis::SelectionMode selectionMode();

    // Set font
    void setFont(const QFont &font);
    QFont font();

    // Label transparency adjustment
    void setLabelTransparency(QDataVis::LabelTransparency transparency);
    QDataVis::LabelTransparency labelTransparency();

    // Enable or disable background grid
    void setGridVisible(bool visible);
    bool isGridVisible();

    // Enable or disable background mesh
    void setBackgroundVisible(bool visible);
    bool isBackgroundVisible();

    // Adjust shadow quality
    void setShadowQuality(QDataVis::ShadowQuality quality);
    QDataVis::ShadowQuality shadowQuality();

    void setItemLabelFormat(const QString &format);
    QString itemLabelFormat();

    void setSelectedBarPos(const QPointF &position);
    QPointF selectedBarPos() const;

signals:
    // Signals shadow quality changes.
    void shadowQualityChanged(QDataVis::ShadowQuality quality);
    void selectedBarPosChanged(const QPointF &position);

protected:
    Bars3DController *m_shared;

    // Used to detect when shadow quality changes autonomously due to e.g. resizing.
    void handleShadowQualityUpdate(QDataVis::ShadowQuality quality);

    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);

    void mouseDoubleClickEvent(QMouseEvent *event);
    void touchEvent(QTouchEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    QSize m_initialisedSize;
    QDataVis::ColorTheme m_theme;
};

QT_DATAVISUALIZATION_END_NAMESPACE

#endif