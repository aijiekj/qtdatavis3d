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

import QtQuick 2.0
import HelperWidgets 2.0
import QtQuick.Layouts 1.0

Column {
    anchors.left: parent.left
    anchors.right: parent.right

    Section {
        anchors.left: parent.left
        anchors.right: parent.right
        caption: qsTr("Scatter3D")

        SectionLayout {
            Label {
                text: qsTr("renderingMode")
                tooltip: qsTr("Rendering Mode")
                Layout.fillWidth: true
            }
            SecondColumnLayout {
                ComboBox {
                    backendValue: backendValues.renderingMode
                    model: ["RenderIndirect", "RenderDirectToBackground",
                        "RenderDirectToBackground_NoClear"]
                    Layout.fillWidth: true
                    scope: "AbstractGraph3D"
                }
            }
            Label {
                text: qsTr("msaaSamples")
                tooltip: qsTr("MSAA Sample Count")
                Layout.fillWidth: true
            }
            SpinBox {
                suffix: " x MSAA"
                backendValue: backendValues.msaaSamples
                minimumValue: 0
                maximumValue: 16
                Layout.fillWidth: true
            }
            Label {
                text: qsTr("shadowQuality")
                tooltip: qsTr("Shadow Quality")
                Layout.fillWidth: true
            }
            SecondColumnLayout {
                ComboBox {
                    backendValue: backendValues.shadowQuality
                    model: ["ShadowQualityNone", "ShadowQualityLow", "ShadowQualityMedium",
                        "ShadowQualityHigh", "ShadowQualitySoftLow", "ShadowQualitySoftMedium",
                        "ShadowQualitySoftHigh"]
                    Layout.fillWidth: true
                    scope: "AbstractGraph3D"
                }
            }
            Label {
                text: qsTr("selectionMode")
                tooltip: qsTr("Selection Mode")
                Layout.fillWidth: true
            }
            SecondColumnLayout {
                ComboBox {
                    backendValue: backendValues.selectionMode
                    model: ["SelectionNone", "SelectionItem"]
                    Layout.fillWidth: true
                    scope: "AbstractGraph3D"
                }
            }
            Label {
                text: qsTr("measureFps")
                tooltip: qsTr("Measure Frames Per Second")
                Layout.fillWidth: true
            }
            SecondColumnLayout {
                CheckBox {
                    backendValue: backendValues.measureFps
                    Layout.fillWidth: true
                }
            }
            Label {
                text: qsTr("orthoProjection")
                tooltip: qsTr("Use Orthographic Projection")
                Layout.fillWidth: true
            }
            SecondColumnLayout {
                CheckBox {
                    backendValue: backendValues.orthoProjection
                    Layout.fillWidth: true
                }
            }
            Label {
                text: qsTr("aspectRatio")
                tooltip: qsTr("Horizontal to Vertical Aspect Ratio")
                Layout.fillWidth: true
            }
            SecondColumnLayout {
                SpinBox {
                    backendValue: backendValues.aspectRatio
                    minimumValue: 0.1
                    maximumValue: 10.0
                    stepSize: 0.1
                    decimals: 1
                    Layout.fillWidth: true
                }
            }
            Label {
                text: qsTr("optimizationHints")
                tooltip: qsTr("Optimization Hints")
                Layout.fillWidth: true
            }
            SecondColumnLayout {
                ComboBox {
                    backendValue: backendValues.optimizationHints
                    model: ["OptimizationDefault", "OptimizationStatic"]
                    Layout.fillWidth: true
                    scope: "AbstractGraph3D"
                }
            }
            Label {
                text: qsTr("polar")
                tooltip: qsTr("Use Polar Coordinates")
                Layout.fillWidth: true
            }
            SecondColumnLayout {
                CheckBox {
                    id: polarCheckbox
                    backendValue: backendValues.polar
                    Layout.fillWidth: true
                }
            }
            Label {
                text: qsTr("radialLabelOffset")
                tooltip: qsTr("Radial Label Offset")
                Layout.fillWidth: true
                visible: polarCheckbox.checked
            }
            SecondColumnLayout {
                visible: polarCheckbox.checked
                SpinBox {
                    backendValue: backendValues.radialLabelOffset
                    minimumValue: 0.0
                    maximumValue: 1.0
                    stepSize: 0.01
                    decimals: 2
                    Layout.fillWidth: true
                }
            }
            Label {
                text: qsTr("horizontalAspectRatio")
                tooltip: qsTr("Horizontal Aspect Ratio")
                Layout.fillWidth: true
            }
            SecondColumnLayout {
                SpinBox {
                    backendValue: backendValues.horizontalAspectRatio
                    minimumValue: 0.0
                    maximumValue: 100.0
                    stepSize: 0.01
                    decimals: 2
                    Layout.fillWidth: true
                }
            }
            Label {
                text: qsTr("margin")
                tooltip: qsTr("Graph Margin")
                Layout.fillWidth: true
            }
            SecondColumnLayout {
                SpinBox {
                    backendValue: backendValues.margin
                    minimumValue: -1.0
                    maximumValue: 100.0
                    stepSize: 0.1
                    decimals: 1
                    Layout.fillWidth: true
                }
            }
        }
    }
}
