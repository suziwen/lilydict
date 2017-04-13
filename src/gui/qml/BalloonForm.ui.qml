import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

Rectangle {
    id: rectangle1
    radius: 10
    property alias btn_sound0: btn_sound0
    property alias btn_sound1: btn_sound1
    property alias word_name: word_name
    property alias btn_addword: btn_addword
    property alias pronu_uk: pronu_uk
    property alias pronu_us: pronu_us
    property alias rowLayout_pronu: rowLayout_pronu

    property alias text_shanbay: text_shanbay
    property alias text_youdao: text_youdao
    property alias rectangle_shanbay: rectangle_shanbay
    property alias rectangle_youdao: rectangle_youdao
    RowLayout {
        id: rowLayout_pronu
        x: 8
        y: 10
        height: 21
        Text {
            id: word_name
            text: qsTr("Text")
            style: Text.Normal
            font.bold: true
            color:'#209e85'
            verticalAlignment: Text.AlignBottom
            font.pixelSize: 18
        }
        Text {
            visible: pronu_us.visible
            text: qsTr("UK:")
            font.italic: true
            font.bold: false
            font.pixelSize: 12
        }
        Text {
            id: pronu_uk
            visible: pronu_us.visible
            color: "gray"
            text: qsTr("/ɡʊd/")
            font.pixelSize: 12
        }
        ToolButton {
            id: btn_sound0
            width: 16
            height: 16
            iconSource: "qrc:/img/sound0.ico"
        }
        Text {
            visible: pronu_us.visible
            text: qsTr("US:")
            font.italic: true
            font.bold: true
            font.pixelSize: 12
        }
        Text {
            id: pronu_us
            color: "gray"
            text: qsTr("/ɡʊd/")
            font.bold: true
            font.pixelSize: 12
        }
        ToolButton {
            id: btn_sound1
            width: 16
            height: 16
            iconSource: "qrc:/img/sound1.ico"
        }
        ToolButton {
            id: btn_addword
            tooltip: qsTr("添加进生词库，加入背单词计划")
            iconSource: "qrc:/img/add1.png"
        }

    }
    Rectangle {
        id: rectangle_shanbay
        x: 10
        y: 42
        width: parent.width-20
        //Layout.fillHeight:true
        color: "#f5f5f5"
        radius: 0
        visible: false
        height: text_shanbay.paintedHeight
        border.color: "#e3e3e3"



        Text {
            id: text_shanbay
            width: parent.width - 20
            //height: 77
            text: qsTr("word definition youdao")
            clip: false
            textFormat: Text.RichText
            wrapMode: Text.WrapAnywhere
            font.pixelSize: 15
        }
        Image {
            id: image1
            y: 9
            sourceSize.height: 15
            sourceSize.width: 15
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.rightMargin: 2
            z: 1
            source: "../img/shanbay.ico"
        }
        Label {
            id: label1
            color: "#9e9898"
            text: qsTr("词义来源扇贝网")
            anchors.rightMargin: 18
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            font.pointSize: 9

        }
    }

    Rectangle {
        id: rectangle_youdao
        x: 10
        y: rectangle_shanbay.y+rectangle_shanbay.height+10
        width: parent.width-20
        //Layout.fillHeight:true
        color: "#f5f5f5"
        radius: 3
        visible: false
        height: text_youdao.paintedHeight
        border.color: "#e3e3e3"

        Image {
            id: image2
            y: 9
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            z: 1
            source: "../img/youdao.ico"
        }

        Text {
            id: text_youdao
            width: parent.width - 20
            //height: 77
            text: qsTr("word definition youdao")
            clip: false
            textFormat: Text.RichText
            wrapMode: Text.WrapAnywhere
            font.pixelSize: 15
        }

        Label {
            id: label2
            color: "#9e9898"
            text: qsTr("词义来源有道词典")
            anchors.rightMargin: 18
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            font.pointSize: 9
        }
    }
}
