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
import QtDataVisualization 1.2

Bars3D {
    width: 300
    height: 300
    Bar3DSeries {
        ItemModelBarDataProxy {
            itemModel: ListModel {
                ListElement{ row: "row 1"; column: "column 1"; value: "1"; }
                ListElement{ row: "row 1"; column: "column 2"; value: "2"; }
                ListElement{ row: "row 1"; column: "column 3"; value: "3"; }
            }

            rowRole: "row"
            columnRole: "column"
            valueRole: "value"
        }
    }
}
