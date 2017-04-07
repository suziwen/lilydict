import QtQuick 2.6
import QtQuick.Window 2.2
import QtMultimedia 5.6
Window {
    id: window
    width: upgradeForm.width
    height: upgradeForm.height
    visible: false
    title: "百合词典新版本发布提示"
    flags: Qt.Dialog
    UpgradeForm {
        id: upgradeForm
        //labelMsg.text: cfg.getLicenceInfo()
        labelMsg.onLinkActivated: Qt.openUrlExternally(link)
        btn_return.onClicked: {
            window.close();
        }
    }
    function showMsg(msg,url){
        upgradeForm.labelMsg.text = msg + "<a href='"+url+"'>"+url+"</a>";
        visible = true;
    }
    onClosing:{
        //console.log("main windows is closing");
        visible = false;
        close.accepted = false;
    }
}
