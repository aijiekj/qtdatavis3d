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

#include "datavisualizationglobal_p.h"
#include "qabstract3dseries.h"
#include <QString>

#ifndef QABSTRACT3DSERIES_P_H
#define QABSTRACT3DSERIES_P_H

QT_DATAVISUALIZATION_BEGIN_NAMESPACE

class QAbstractDataProxy;
class Abstract3DController;

struct QAbstract3DSeriesChangeBitField {
    bool itemLabelFormatChanged        : 1;
    bool meshChanged                   : 1;
    bool meshSmoothChanged             : 1;
    bool userDefinedMeshChanged        : 1;

    QAbstract3DSeriesChangeBitField()
        : itemLabelFormatChanged(true),
          meshChanged(true),
          meshSmoothChanged(true),
          userDefinedMeshChanged(true)
    {
    }
};

class QAbstract3DSeriesPrivate : public QObject
{
    Q_OBJECT
public:
    QAbstract3DSeriesPrivate(QAbstract3DSeries *q, QAbstract3DSeries::SeriesType type);
    virtual ~QAbstract3DSeriesPrivate();

    QAbstractDataProxy *dataProxy() const;
    virtual void setDataProxy(QAbstractDataProxy *proxy);
    virtual void setController(Abstract3DController *controller);
    virtual void connectControllerAndProxy(Abstract3DController *newController) = 0;

    void setItemLabelFormat(const QString &format);
    void setVisible(bool visible);
    void setMesh(QAbstract3DSeries::Mesh mesh);
    void setMeshSmooth(bool enable);
    void setUserDefinedMesh(const QString &meshFile);

    QAbstract3DSeriesChangeBitField m_changeTracker;
    QAbstract3DSeries *q_ptr;
    QAbstract3DSeries::SeriesType m_type;
    QString m_itemLabelFormat;
    QAbstractDataProxy *m_dataProxy;
    bool m_visible;
    Abstract3DController *m_controller;
    QAbstract3DSeries::Mesh m_mesh;
    bool m_meshSmooth;
    QString m_userDefinedMesh;
};

QT_DATAVISUALIZATION_END_NAMESPACE

#endif // QAbstract3DSeries_P_H
