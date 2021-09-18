import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQml 2.12

import NestedWindow.com 1.0

Window {
    x:0
    objectName: "mainWindow"
    id:window
    width: 1024
    height: 768
    visible: true
    title: qsTr("Hello World")
    Button{
        property int count: 0
        objectName: "btn"
        onClicked: {
        }
    }
    NestedWindow{
        id:nestedWindow
        otherWinClassName: "Main HighGUI class"
        otherWinTitleName:"w"
        x:window.x+100
        y:window.y+100
        width: window.width/2
        heigth: window.height /2
        qtWindowTitle: window.title
    }


}
