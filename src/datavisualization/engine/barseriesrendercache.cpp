/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
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

#include "barseriesrendercache_p.h"

QT_BEGIN_NAMESPACE_DATAVISUALIZATION

BarSeriesRenderCache::BarSeriesRenderCache(QAbstract3DSeries *series,
                                           Abstract3DRenderer *renderer)
    : SeriesRenderCache(series, renderer),
      m_visualIndex(-1)
{
}

BarSeriesRenderCache::~BarSeriesRenderCache()
{
}

void BarSeriesRenderCache::cleanup(TextureHelper *texHelper)
{
    m_renderArray.clear();
    m_sliceArray.clear();

    SeriesRenderCache::cleanup(texHelper);
}

QT_END_NAMESPACE_DATAVISUALIZATION
