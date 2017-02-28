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
    property alias text_def: text_def
    property alias btn_addword: btn_addword
    property alias pronu_uk: pronu_uk
    property alias pronu_us: pronu_us
    property alias rowLayout_pronu: rowLayout_pronu
    RowLayout {
        id: rowLayout_pronu
        x: 8
        y: 21
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
    Text {
        id: text_def
        x: 8
        y: 48
        width: parent.width -15
        //height: 77
        text: qsTr("word definition")
        anchors.rightMargin: -8
        anchors.bottomMargin: -48
        anchors.leftMargin: 8
        anchors.topMargin: 48
        textFormat: Text.RichText
        wrapMode: Text.WrapAnywhere
        font.pixelSize: 15
    }
}
