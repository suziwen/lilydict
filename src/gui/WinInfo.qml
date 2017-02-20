import QtQuick 2.0

Text {
    color: "#0a3ea2"
    text: qsTr("windows prompt information")
    anchors.left: parent.left
    anchors.leftMargin: 10
    anchors.bottomMargin: 10
    anchors.bottom: parent.bottom
    style: Text.Normal
    font.bold: true
    font.pointSize: 11
    function showinfo(msg){
        text = msg;
        visible = true;
    }
    function hide(){
        visible = false;
    }
}
