import QtQuick 1.1
//import QtQuick.Window 2.0
//import QtQuick.Controls 1.1

import videoViewer 1.0

Rectangle {
    width: 750
    height: 720

    MouseArea {
        anchors.fill: parent
        onClicked: {
            //Qt.quit();
            //Qt.Dialog("Do you want to quit?");
        }

        Row {
            id: row1
            x: 0
            y: 0
            width: parent.width
            height: parent.height/3
            Grid {
                columns: 3
                spacing: 2
                Rectangle {
                    //color: "red";
                    width: 80; height: 20
                    TextEdit {
                        id: textEdit1
                        width: 80
                        height: 20
                        text: qsTr("Text Edit")
                        font.pixelSize: 12
                    }
                }
                Rectangle { color: "green"; width: 20; height: 50 }
                Rectangle { color: "blue"; width: 50; height: 20 }
                Rectangle { color: "cyan"; width: 50; height: 50 }
                Rectangle { color: "magenta"; width: 10; height: 10 }
            }
//            Rectangle{
//                id: row1_Rect
//                color:"#80111111"
//                anchors.fill: parent

//                Grid {
//                    id: grid1
//                    anchors.fill: parent
//                    columns: 3
//                    spacing: 2


//                    Rectangle{
//                        id: textEdit1_Rect
//                        border.color:"#FF0000"
//                        TextEdit {
//                            id: textEdit1
//                            width: 80
//                            height: 20
//                            text: qsTr("Text Edit")
//                            font.pixelSize: 12
//                        }
//                    }

//                    Rectangle{
//                        id: textEdit2_Rect
//                        Text {
//                            id: text2
//                            width: 80
//                            height: 20
//                            text: qsTr("Enter IP")
//                            font.pixelSize: 12
//                        }
//                    }

//                    Rectangle{
//                        id: textEdit3_Rect

//                        border.color:"#00FF00"
//                        Text {
//                            id: text1
//                            width: 80
//                            height: 20
//                            text: qsTr("Text")
//                            font.pixelSize: 12
//                        }
//                    }
//                }
//            }
        }

        Row {
            id: row2;
            x: 0;
            y: parent.height/3;
            width: parent.width;
            height: 2*parent.height/3;
            Grid {
                id: grid2;
                anchors.fill: parent;
                columns: 2;
                spacing: 2;
//                Rectangle{
//                    id: mainView_Rect
//                    color: "#80F00000"
//                    width: 644; height: 484;
//                    VideoViewer{ objectName: "mainView";}
//                    border.width: 1
//                    border.color: "blue"
//                }

                Rectangle{
                    id: mainView_Rect
                    color: "#80F00000"
                    width: 320; height: 240;
                    VideoViewer{ objectName: "mainView";}
                    border.width: 1
                    border.color: "blue"
                }
                Rectangle{
                    id: mainView1_Rect
                    color: "#800F0000"
                    width: 320; height: 240;
                    VideoViewer{objectName: "mainView1";}
                    border.width: 1
                    border.color: "red"
                }
                Rectangle{
                    id: mainView2_Rect
                    color: "#8000F000"
                    width: 320; height: 240;
                    VideoViewer{objectName: "mainView2";}
                    border.width: 1
                    border.color: "green"
                }
                Rectangle{
                    id: mainView3_Rect
                    color: "#80000F00"
                    width: 320; height: 240;
                    VideoViewer{objectName: "mainView3";}
                    border.width: 1;
                    border.color: "yellow";
                }
            }

        }
    }
}
