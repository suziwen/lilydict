import QtQuick 2.4
import QtQuick.Controls 1.5

Item {
    y: 0
    width: 600
    height: 400
    property alias btn_return: btn_return
    property alias cb_screentext: cb_screentext
    property alias cb_autospeak: cb_autospeak
    property alias cb_showlogo: cb_showlogo
    property alias cb_autohide: cb_autohide
    property alias cb_startloginshanbay: cb_startloginshanbay
    property alias cb_selectedtext: cb_selectedtext
    property alias cb_clipboardtext: cb_clipboardtext
    Rectangle {
        id: rectangle1
        x: 8
        y: 8
        width: parent.width - 2 * x
        height: 90
        color: "#ffffff"
        radius: 0
        border.width: 1
        border.color: "#f0f0f0"

        Label {
            x: 15
            y: 10
            text: qsTr("功能设置：")
            font.bold: true
        }

        CheckBox {
            id: cb_screentext
            x: 28
            y: 37
            text: qsTr("开启屏幕取词")
        }

        CheckBox {
            id: cb_autospeak
            x: 156
            y: 37
            width: 87
            height: 25
            text: qsTr("自动发音")
        }
        CheckBox {
            id: cb_showlogo
            x: 264
            y: 37
            width: 119
            text: qsTr("显示取词图标")
        }
        CheckBox {
            id: cb_autohide
            x: 401
            y: 37
            width: 119
            text: qsTr("登录后自动隐藏主窗口")
        }
    }

    Rectangle {
        id: rectangle2
        x: 8
        y: 114
        width: parent.width - 2 * x
        height: 120
        color: "#ffffff"
        radius: 5
        z: -2
        border.width: 1
        border.color: "#f0f0f0"

        Label {
            id: label1
            x: 15
            y: 10
            text: qsTr("取词方式：")
            font.bold: true
        }

        CheckBox {
            id: cb_selectedtext
            x: 30
            y: 37
            text: qsTr("鼠标选中取词（仅支持linux）")
        }

        CheckBox {
            id: cb_clipboardtext
            x: 30
            y: 68
            width: 100
            text: qsTr("粘贴板取词，选中单词后按“ctrl+c”或者鼠标点右键使用“复制”菜单项")
        }
    }
    Rectangle {
        id: rectangle3
        x: 8
        y: 251
        width: 450
        height: 90
        color: "#ffffff"
        radius: 0
        border.width: 1
        border.color: "#f0f0f0"

        Label {
            x: 15
            y: 10
            text: qsTr("其它设置：")
            font.bold: true


        }

        CheckBox {
            id: cb_startloginshanbay
            x: 30
            y: 37
            width: 119
            text: qsTr("启动时登录扇贝网")
        }
    }

    Button {
        id: btn_return
        x: 495
        y: 290
        text: qsTr("确定")
    }
    Image {
        id: image
        x: 485
        y: 193
        width: 100
        height: 100
        z: -1
        source: "qrc:/img/logo.png"
    }
}
