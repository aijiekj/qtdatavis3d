/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Data Visualization module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include <QtDataVisualization/QScatter3DSeries>

using namespace QtDataVisualization;

class DataGenerator  : public QObject
{
    Q_OBJECT
public:
    DataGenerator(QObject *parent = 0);
    virtual ~DataGenerator();

public slots:
    void generateData(QScatter3DSeries *series, uint count);
    void add(QScatter3DSeries *series, uint count);

private:
    QScatter3DSeries m_series;
};

#endif // DATAGENERATOR_H
