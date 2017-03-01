import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

Rectangle {
    id: rectangle1
    property alias textWord: textWord
    property alias btn_query: btn_query
    property alias btn_sound0: btn_sound0
    property alias btn_sound1: btn_sound1
    property alias word_name: word_name
    property alias text_def: text_def
    property alias btn_addword: btn_addword
    property alias pronu_uk: pronu_uk
    property alias pronu_us: pronu_us
    //anchors.fill: parent
    //color: "#ffffff"
    TextField {
        id: textWord
        x: 8
        y: 17
        width: 360
        height: 32
        text: ""
        opacity: 0.9
        font.pointSize: 15
        placeholderText: qsTr("Input English Word")
        style: TextFieldStyle {
            textColor: "black"
            background: Rectangle {
                radius: 5
                border.color: "#0099CC"
                border.width: 1
            }
        }
    }
    Button {
        id: btn_query
        x: 380
        y: 20
        width: 55
        height: 27
        text: qsTr("查询")
    }

    RowLayout {
        id: rowLayout_pronu
        x: 8
        y: 57
        width: 180
        height: 21

        Text {
            id: word_name
            text: qsTr("Text")
            font.family: "Arial"
            style: Text.Normal
            font.bold: true
            color:'#209e85'
            verticalAlignment: Text.AlignBottom
            font.pixelSize: 21
        }
        Text {
            visible: pronu_us.visible
            text: qsTr("UK:")
            font.italic: false
            font.bold: false
            font.pixelSize: 15
        }
        Text {
            id: pronu_uk
            visible: pronu_us.visible
            color: "gray"
            text: qsTr("/ɡʊd/")
            font.family: "Courier"
            font.pixelSize: 15
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
            font.italic: false
            font.bold: false
            font.pixelSize: 15
        }
        Text {
            id: pronu_us
            color: "gray"
            text: qsTr("/ɡʊd/")
            font.family: "Courier"
            font.pixelSize: 15
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
        x: 10
        y: 95
        width: parent.width - 20
        //height: 77
        text: qsTr("word definition")
        clip: false
        textFormat: Text.RichText
        wrapMode: Text.WrapAnywhere
        font.pixelSize: 15
    }
}
