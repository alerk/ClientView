import QtQuick 1.1
//import QtQuick.Window 2.0
//import QtQuick.Controls 1.1

import videoViewer 1.0

Rectangle {
    width: 750
    height: 520

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }

        Row {
            id: row1
            x: 0
            y: 0
            width: parent.width
            height: parent.height/3
            Rectangle{
                id: row1_Rect
                color:"#80FF33EE"
                Grid {
                    id: grid1
                    rows: 3
                    columns: 3
                    anchors.fill: parent


                    Rectangle{
                        id: textEdit1_Rect
                        border.color:"#FF0000"
                        TextEdit {
                            id: textEdit1
                            width: 80
                            height: 20
                            text: qsTr("Text Edit")
                            font.pixelSize: 12
                        }
                    }

                    Rectangle{
                        id: textEdit2_Rect
                        border.color:"#0000FF"
                        Text {
                            id: text2
                            text: qsTr("Enter IP")
                            font.pixelSize: 12
                        }
                    }

                    Rectangle{
                        id: textEdit3_Rect
                        border.color:"#00FF00"
                        Text {
                            id: text1
                            text: qsTr("Text")
                            font.pixelSize: 12
                        }
                    }
                }
            }
        }

        Row {
            id: row2
            x: 0
            y: parent.height/3
            width: parent.width
            height: 2*parent.height/3
            Rectangle{
                id: row2_Rect
                color: "#90EE55AA"

                Grid {
                    id: grid2
                    columns: 2
                    rows: 2
                    Rectangle{
                        id: mainView_Rect
                        VideoViewer{
                            objectName: "mainView"
                            anchors.fill: parent
                        }
                        border.width: 1
                        border.color: "blue"
                    }
                    Rectangle{
                        id: mainView1_Rect
                        VideoViewer{
                            objectName: "mainView1"
                            //anchors.fill: parent
                        }
                        border.width: 1
                        border.color: "blue"
                    }
                    Rectangle{
                        id: mainView2_Rect
                        VideoViewer{
                            objectName: "mainView2"
                            //anchors.fill: parent
                        }
                        border.width: 1
                        border.color: "blue"
                    }
                    Rectangle{
                        id: mainView3_Rect
                        VideoViewer{
                            objectName: "mainView3"
                            //anchors.fill: parent
                        }
                        border.width: 1
                        border.color: "blue"
                    }
                }
            }
        }
    }
}
