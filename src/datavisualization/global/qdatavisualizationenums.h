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

#ifndef QDATAVISUALIZATIONENUMS_H
#define QDATAVISUALIZATIONENUMS_H

#include <QtDataVisualization/qdatavisualizationglobal.h>
#include <QObject>

// namespace must be declared without using macros for qdoc
namespace QtDataVisualization {

class QT_DATAVISUALIZATION_EXPORT QDataVis : public QObject
{
    Q_OBJECT
    Q_ENUMS(CameraPreset)
    Q_ENUMS(Theme)
    Q_ENUMS(ShadowQuality)
    Q_ENUMS(LabelStyle)
    Q_FLAGS(SelectionFlag SelectionFlags)
    Q_ENUMS(ColorStyle)

public:
    // TODO: Move to input handler (QTRD-2505)
    enum InputState {
        InputStateNone = 0,
        InputStateOnScene,
        InputStateOnOverview,
        InputStateOnSlice,
        InputStateRotating,
        InputStateOnPinch
    };

    // TODO: Move to camera (QTRD-2505)
    enum CameraPreset {
        CameraPresetNone = -1,
        CameraPresetFrontLow = 0,
        CameraPresetFront,
        CameraPresetFrontHigh,
        CameraPresetLeftLow,
        CameraPresetLeft,
        CameraPresetLeftHigh,
        CameraPresetRightLow,
        CameraPresetRight,
        CameraPresetRightHigh,
        CameraPresetBehindLow,
        CameraPresetBehind,
        CameraPresetBehindHigh,
        CameraPresetIsometricLeft,
        CameraPresetIsometricLeftHigh,
        CameraPresetIsometricRight,
        CameraPresetIsometricRightHigh,
        CameraPresetDirectlyAbove,
        CameraPresetDirectlyAboveCW45,
        CameraPresetDirectlyAboveCCW45,
        CameraPresetFrontBelow,
        CameraPresetLeftBelow,
        CameraPresetRightBelow,
        CameraPresetBehindBelow,
        CameraPresetDirectlyBelow
    };

    // TODO: Move to theme
    enum Theme {
        ThemeQt,
        ThemePrimaryColors,
        ThemeDigia,
        ThemeStoneMoss,
        ThemeArmyBlue,
        ThemeRetro,
        ThemeEbony,
        ThemeIsabelle,
        ThemeUserDefined
    };

    enum SelectionFlag {
        SelectionNone              = 0,
        SelectionItem              = 1,
        SelectionRow               = 2,
        SelectionItemAndRow        = SelectionItem | SelectionRow,
        SelectionColumn            = 4,
        SelectionItemAndColumn     = SelectionItem | SelectionColumn,
        SelectionRowAndColumn      = SelectionRow | SelectionColumn,
        SelectionItemRowAndColumn  = SelectionItem | SelectionRow | SelectionColumn,
        SelectionSlice             = 8,
        SelectionMultiSeries       = 16
    };
    Q_DECLARE_FLAGS(SelectionFlags, SelectionFlag)

    enum ShadowQuality {
        ShadowQualityNone = 0,
        ShadowQualityLow,
        ShadowQualityMedium,
        ShadowQualityHigh,
        ShadowQualitySoftLow,
        ShadowQualitySoftMedium,
        ShadowQualitySoftHigh
    };

    // TODO: to theme
    enum ColorStyle {
        ColorStyleUniform = 0,
        ColorStyleObjectGradient,
        ColorStyleRangeGradient
    };
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QDataVis::SelectionFlags)
}

#endif
