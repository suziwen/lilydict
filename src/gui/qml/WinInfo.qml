import QtQuick 2.7

Text {
    id: infotext
    color: "#0a3ea2"
    text: qsTr("windows prompt information")
    anchors.left: parent.left
    anchors.leftMargin: 10
    anchors.bottomMargin: 10
    anchors.bottom: parent.bottom
    style: Text.Normal
    font.bold: true
    font.pointSize: 11
    OpacityAnimator{
        id: animator
        target: infotext
        from: 1.0;
        to: 0.0;
        duration: 6000
    }
    function showinfo(msg){
        text = msg;
        visible = true;
        //opacity = 1.0;
        animator.running=true;
    }
    function hide(){
        visible = false;
    }
}
