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

import QtQuick 2.1
import QtDataVisualization 1.0
import "."

Item {
    id: mainView
    width: 1280
    height: 720
    visible: true

    Data {
        id: graphData
    }

    Item {
        id: dataView
        anchors.bottom: parent.bottom
        width: parent.width
        height: parent.height - shadowToggle.height

        //! [0]
        Scatter3D {
            //! [0]
            id: scatterGraph
            width: dataView.width
            height: dataView.height
            theme: Theme3D { type: AbstractGraph3D.ThemeDigia }
            shadowQuality: AbstractGraph3D.ShadowQualitySoftMedium
            scene.activeCamera.yRotation: 30.0
            //! [1]
            inputHandler: null
            //! [1]

            Scatter3DSeries {
                id: scatterSeries
                itemLabelFormat: "X:@xLabel Y:@yLabel Z:@zLabel"
                mesh: Abstract3DSeries.MeshCube

                ItemModelScatterDataProxy {
                    itemModel: graphData.model
                    xPosRole: "xPos"
                    yPosRole: "yPos"
                    zPosRole: "zPos"
                }
            }
        }

        //! [2]
        MouseArea {
            id: inputArea
            anchors.fill: parent
            hoverEnabled: true
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            property int mouseX: -1
            property int mouseY: -1
            //! [2]

            //! [3]
            onPositionChanged: {
                mouseX = mouse.x;
                mouseY = mouse.y;
            }
            //! [3]

            //! [5]
            onWheel: {
                // Adjust zoom level based on what zoom range we're in.
                var zoomLevel = scatterGraph.scene.activeCamera.zoomLevel;
                if (zoomLevel > 100)
                    zoomLevel += wheel.angleDelta.y / 12.0;
                else if (zoomLevel > 50)
                    zoomLevel += wheel.angleDelta.y / 60.0;
                else
                    zoomLevel += wheel.angleDelta.y / 120.0;
                if (zoomLevel > 500)
                    zoomLevel = 500;
                else if (zoomLevel < 10)
                    zoomLevel = 10;

                scatterGraph.scene.activeCamera.zoomLevel = zoomLevel;
            }
            //! [5]
        }

        //! [4]
        Timer {
            id: reselectTimer
            interval: 10
            running: true
            repeat: true
            onTriggered: {
                scatterGraph.scene.selectionQueryPosition = Qt.point(inputArea.mouseX, inputArea.mouseY);
            }
        }
        //! [4]
    }

    //! [6]
    NumberAnimation {
        id: cameraAnimationX
        loops: Animation.Infinite
        running: true
        target: scatterGraph.scene.activeCamera
        property:"xRotation"
        from: 0.0
        to: 360.0
        duration: 20000
    }
    //! [6]


    //! [7]
    SequentialAnimation {
        id: cameraAnimationY
        loops: Animation.Infinite
        running: true

        NumberAnimation {
            target: scatterGraph.scene.activeCamera
            property:"yRotation"
            from: 5.0
            to: 45.0
            duration: 9000
            easing.type: Easing.InOutSine
        }

        NumberAnimation {
            target: scatterGraph.scene.activeCamera
            property:"yRotation"
            from: 45.0
            to: 5.0
            duration: 9000
            easing.type: Easing.InOutSine
        }
    }
    //! [7]

    NewButton {
        id: shadowToggle
        width: parent.width / 3 // We're adding 3 buttons and want to divide them equally
        text: "Hide Shadows"
        anchors.left: parent.left

        onClicked: {
            if (scatterGraph.shadowQuality === AbstractGraph3D.ShadowQualityNone) {
                scatterGraph.shadowQuality = AbstractGraph3D.ShadowQualitySoftMedium;
                text = "Hide Shadows";
            } else {
                scatterGraph.shadowQuality = AbstractGraph3D.ShadowQualityNone;
                text = "Show Shadows";
            }
        }
    }

    NewButton {
        id: cameraToggle
        width: parent.width / 3
        text: "Animate Camera"
        anchors.left: shadowToggle.right

        onClicked: {
            cameraAnimationX.paused = !cameraAnimationX.paused;
            cameraAnimationY.paused = cameraAnimationX.paused;
            if (cameraAnimationX.paused) {
                text = "Animate Camera";
            } else {
                text = "Pause Camera";
            }
        }
    }

    NewButton {
        id: exitButton
        width: parent.width / 3
        text: "Quit"
        anchors.left: cameraToggle.right
        onClicked: Qt.quit(0);
    }
}
