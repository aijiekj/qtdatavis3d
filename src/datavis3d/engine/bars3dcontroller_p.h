/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtDataVis3D module.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

//
//  W A R N I N G
//  -------------
//
// This file is not part of the QtDataVis3D API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef Q3DBARSCONTROLLER_p_H
#define Q3DBARSCONTROLLER_p_H

#include <QtCore/QSize>
#include <QtCore/QObject>
#include <QWindow>

#include "abstract3dcontroller_p.h"
#include "datavis3dglobal_p.h"
#include "qdataset_p.h"

//#define DISPLAY_RENDER_SPEED

class QFont;
class QPoint;
class QSizeF;

QT_DATAVIS3D_BEGIN_NAMESPACE

class Bars3dRenderer;
class QDataItem;
class QDataRow;
class QDataSet;
class LabelItem;

class QT_DATAVIS3D_EXPORT Bars3dController : public Abstract3DController
{
    Q_OBJECT

public:
    enum SelectionType {
        SelectionNone = 0,
        SelectionBar,
        SelectionRow,
        SelectionColumn
    };

private:
    bool m_isInitialized;

    // Data
    QDataSet *m_dataSet;
    int m_rowCount;
    int m_columnCount;

    // Interaction
    MouseState m_mouseState;
    QPoint m_mousePos;
    SelectionMode m_selectionMode;
    bool m_isSlicingActivated;

    bool m_isBarSpecRelative;
    QSizeF m_barThickness;
    QSizeF m_barSpacing;

    // Look'n'Feel
    QString m_objFile;
    QFont m_font;
    bool m_isGridEnabled;
    bool m_isBackgroundEnabled;
    GLint m_tickCount;
    GLfloat m_tickStep;
    GLfloat m_tickMinimum;

    Bars3dRenderer *m_renderer;

public:
    explicit Bars3dController(QRect rect);
    ~Bars3dController();

    void initializeOpenGL();
    void render(const GLuint defaultFboHandle = 0);

    int columnCount();
    int rowCount();

    MouseState mouseState();
    QPoint mousePosition();

    bool isSlicingActive();
    void setSlicingActive(bool isSlicing);

    QMatrix4x4 calculateViewMatrix(int zoom, int viewPortWidth, int viewPortHeight, bool showUnder = false);

    // Add a row of data. Each new row is added to the front of the sample space, moving previous
    // rows back (if sample space is more than one row deep)
    void addDataRow(const QVector<GLfloat> &dataRow);
    // ownership of dataItems is transferred
    void addDataRow(const QVector<QDataItem*> &dataRow);
    // ownership of dataRow is transferred
    void addDataRow(QDataRow *dataRow);

    // Add complete data set at a time, as a vector of data rows
    void addDataSet(const QVector< QVector<GLfloat> > &data);

    // ownership of dataItems is transferred
    void addDataSet(const QVector< QVector<QDataItem*> > &data);
    // ownership of dataSet is transferred
    void addDataSet(QDataSet* dataSet);

    QPair<GLfloat, GLfloat> limits();

    // bar thickness, spacing between bars, and is spacing relative to thickness or absolute
    // y -component sets the thickness/spacing of z -direction
    // With relative 0.0f means side-to-side, 1.0f = one thickness in between
    void setBarSpecs(QSizeF thickness = QSizeF(1.0f, 1.0f),
                     QSizeF spacing = QSizeF(1.0f, 1.0f),
                     bool relative = true);
    QSizeF barThickness();
    QSizeF barSpacing();
    bool isBarSpecRelative();

    // bar type; bars (=cubes), pyramids, cones, cylinders, etc.
    void setBarType(BarStyle style, bool smooth = false);
    QString objFile();

    // override bar type with own mesh
    void setMeshFileName(const QString &objFileName);

    // how many samples per row and column, and names for axes
    void setupSampleSpace(int samplesRow, int samplesColumn);

    // Set tick count and step. Note; tickCount * step should be the maximum possible value of data
    // set. Minimum is the absolute minimum possible value a bar can have. This is especially
    // important to set if values can be negative.
    void setTickCount(GLint tickCount, GLfloat step, GLfloat minimum = 0.0f);

    // TODO: light placement API

    // Change selection mode; single bar, bar and row, bar and column, or all
    void setSelectionMode(SelectionMode mode);
    SelectionMode selectionMode();

    // Font size adjustment
    void setFontSize(float fontsize);
    float fontSize();

    // Set font
    void setFont(const QFont &font);
    QFont font();

    // Enable or disable background grid
    void setGridEnabled(bool enable);
    bool gridEnabled();

    // Enable or disable background mesh
    void setBackgroundEnabled(bool enable);
    bool backgroundEnabled();

#if defined(Q_OS_ANDROID)
    void mouseDoubleClickEvent(QMouseEvent *event);
    void touchEvent(QTouchEvent *event);
#endif
    void mousePressEvent(QMouseEvent *event, const QPoint &mousePos);
    void mouseReleaseEvent(QMouseEvent *event, const QPoint &mousePos);
    void mouseMoveEvent(QMouseEvent *event, const QPoint &mousePos);
    void wheelEvent(QWheelEvent *event);

    // TODO: abstract renderer should have accessor for Drawer instead
    virtual Drawer *drawer();

signals:
    void selectionModeChanged(SelectionMode mode);
    void slicingActiveChanged(bool isSlicing);
    void dataSetChanged(QDataSetPrivate *dataSet);
    void limitsChanged(QPair<GLfloat, GLfloat> limits);
    void sampleSpaceChanged(int samplesRow, int samplesColumn);
    void barSpecsChanged(QSizeF thickness, QSizeF spacing, bool relative);
    void objFileChanged(QString fileName);
    void fontChanged(QFont font);
    void gridEnabledChanged(bool enable);
    void backgroundEnabledChanged(bool enable);
    void tickCountChanged(GLint tickCount, GLfloat step, GLfloat minimum);

private:
    void handleLimitChange();

    Q_DISABLE_COPY(Bars3dController)

    friend class DeclarativeBars;
    friend class DeclarativeBarsRenderer;
};


QT_DATAVIS3D_END_NAMESPACE

#endif