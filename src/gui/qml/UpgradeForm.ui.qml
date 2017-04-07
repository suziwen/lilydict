import QtQuick 2.6
import QtQuick.Controls 1.5

Item {
    width: 500
    height: 200
    property alias labelMsg: labelMsg;
    property alias btn_return: btn_return;
    Label {
        id: labelMsg
        width: parent.width - 2*x
        x: 42
        y: 34
        text: qsTr("百合词典新版本发布提示")
        wrapMode: Text.WordWrap
        textFormat: Text.RichText
    }

    Button {
        id: btn_return
        x: 403
        y: 153
        text: qsTr("确定")
    }
}
