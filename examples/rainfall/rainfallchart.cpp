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

#include "rainfallchart.h"
#include <QtDataVisualization/q3dcategoryaxis.h>
#include <QtDataVisualization/q3dvalueaxis.h>
#include <QGuiApplication>
#include <QFont>
#include <QDebug>
#include <QTextStream>
#include <QFile>

using namespace QtDataVisualization;

RainfallChart::RainfallChart(Q3DBars *rainfall)
    : m_chart(rainfall)
{
    // In data file the months are in numeric format, so create custom list
    for (int i = 1; i <= 12; i++)
        m_numericMonths << QString::number(i);

    m_columnCount = m_numericMonths.size();

    m_proxy = new VariantBarDataProxy;
    m_chart->setActiveDataProxy(m_proxy);

    updateYearsList(2000, 2012);

    // Set up bar specifications; make the bars as wide as they are deep,
    // and add a small space between the bars
    m_chart->setBarThickness(1.0);
    m_chart->setBarSpacing(QSizeF(0.2, 0.2));

    // Set axis labels and titles
    QStringList months;
    months << "January" << "February" << "March" << "April" << "May" << "June" << "July" << "August" << "September" << "October" << "November" << "December";
    m_chart->rowAxis()->setTitle("Year");
    m_chart->columnAxis()->setTitle("Month");
    m_chart->valueAxis()->setTitle("rainfall");
    m_chart->valueAxis()->setLabelFormat("%d mm");
    m_chart->rowAxis()->setCategoryLabels(m_years);
    m_chart->columnAxis()->setCategoryLabels(months);

    // Set bar type to cylinder
    m_chart->setBarType(QDataVis::MeshStyleCylinders, false);

    // Set shadows to medium
    m_chart->setShadowQuality(QDataVis::ShadowQualityMedium);

    // Set font
    m_chart->setFont(QFont("Century Gothic", 30));

    // Set selection mode to bar and column
    m_chart->setSelectionMode(QDataVis::SelectionModeSliceColumn);

    // Set theme
    m_chart->setTheme(QDataVis::ThemeArmyBlue);

    // Set preset camera position
    m_chart->setCameraPreset(QDataVis::CameraPresetIsometricRightHigh);

    // Disable grid
    m_chart->setGridVisible(false);

    // Set window title
    m_chart->setTitle(QStringLiteral("Monthly rainfall in Northern Finland"));
}

RainfallChart::~RainfallChart()
{
    delete m_mapping;
    delete m_dataSet;
    delete m_chart;
}

void RainfallChart::start()
{
    addDataSet();
}

void RainfallChart::updateYearsList(int start, int end)
{
    m_years.clear();
    for (int i = start; i <= end; i++)
        m_years << QString::number(i);

    m_rowCount = m_years.size();
}

void RainfallChart::addDataSet()
{
    m_dataSet =  new VariantDataSet;
    VariantDataItemList *itemList = new VariantDataItemList;
    QTextStream stream;
    QFile dataFile(":/data/raindata.txt");
    if (dataFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        stream.setDevice(&dataFile);
        while (!stream.atEnd()) {
            QString line = stream.readLine();
            if (line.startsWith("#"))
                continue;
            QStringList strList = line.split(",", QString::SkipEmptyParts);
            if (strList.size() < 3) {
                qWarning() << "Invalid row read from data:" << line;
                continue;
            }
            VariantDataItem *newItem = new VariantDataItem;
            for (int i = 0; i < 2; i++)
                newItem->append(strList.at(i).trimmed());
            newItem->append(strList.at(2).trimmed().toDouble());
            itemList->append(newItem);
        }
    } else {
        qWarning() << "Unable to open data file:" << dataFile.fileName();
    }

    m_dataSet->addItems(itemList);

    m_proxy->setDataSet(m_dataSet);

    m_mapping =  new VariantBarDataMapping(0, 1, 2, m_years, m_numericMonths);
    m_proxy->setMapping(m_mapping);
}
