import QtQuick 2.5
import QtQuick.Window 2.2
Window {
    id:window
    width: 630
    height: 360
    //flags: Q_OS_WIN ? Qt.Dialog:Qt.WindowStaysOnTopHint
    SetupForm {
        btn_return.onClicked: {
            window.close();
        }
        cb_screentext.onCheckedChanged: {
            cfg.setScreentext(cb_screentext.checked);

        }
        cb_autospeak.onCheckedChanged: {
            cfg.setAutospeak(cb_autospeak.checked);
        }
        cb_showlogo.onCheckedChanged: {
            cfg.setShowquerylogo(cb_showlogo.checked);
        }
        cb_autohide.onCheckedChanged: {
            cfg.setAutohide(cb_autohide.checked);
        }
        cb_startloginshanbay.onCheckedChanged: {
            cfg.setStartloginshanbay(cb_startloginshanbay.checked);
        }

        cb_selectedtext.onCheckedChanged: {
            cfg.setSelectedtext(cb_selectedtext.checked);
        }
        cb_clipboardtext.onCheckedChanged: {
            cfg.setClipboardtext(cb_clipboardtext.checked);
        }

        Component.onCompleted: {
            cb_screentext.checked = cfg.isGetscreentext();
            cb_autospeak.checked = cfg.isAutospeak();
            cb_showlogo.checked = cfg.isShowquerylogo();
            cb_selectedtext.checked = cfg.isGetselectedtext();
            cb_clipboardtext.checked = cfg.isGetclipboardtext();
            cb_autohide.checked = cfg.isAutohide();
            cb_startloginshanbay.checked = cfg.isStartloginshanbay();
        }

    }
    Component.onCompleted: {
        setX(Screen.width / 2 - width / 2);
        setY(Screen.height / 2 - height / 2);
    }
    onClosing:{
        //console.log("main windows is closing");
        visible = false;
        close.accepted = false;
    }
}
