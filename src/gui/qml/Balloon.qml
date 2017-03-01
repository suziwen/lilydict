import QtQuick 2.6
import QtQuick.Window 2.2
import QtMultimedia 5.6
Window {
    id: window
    visible: false
    width: 360
    height: 180
    flags: Qt.WindowStaysOnTopHint|Qt.SplashScreen
    objectName: "balloon"
    property Dict dict: Dict{}
    signal signalBtnaddwordClick(string type,string id)
    //slot
    function addWordRet(retstr){
       dict.addWordRet(retstr);
    }
    function showWord(){
        window.requestActivate();
        mainForm.text_def.text = dict.shanbayWordinfo+dict.youdaoWordinfo;// + dict.def_en_info ;
        window.width = Math.max(mainForm.rowLayout_pronu.width + 160,360);
        window.height = Math.max(mainForm.text_def.height + 100,90);
    }

    function showYoudaoWord(wordinfo){
        //console.log(wordinfo);
        dict.setYoudaoWordinfo(wordinfo);
        showWord();
    }

    function showShanbayWord(wordstr){
        //console.log("wordstr:"+wordstr);
        dict.setShanbayWordinfo(wordstr);
        showWord();
    }
    Audio {
            id: playSound0
        }
    Audio {
            id: playSound1
        }
    BalloonForm {
        id: mainForm
        anchors.fill: parent
        btn_addword.onClicked: dict.addWord();
        btn_sound0.onClicked: {
            playSound0.play();
        }
        btn_sound1.onClicked: {
            playSound1.play();
        }

    }
    onActiveChanged: {
        console.log("window onActiveChanged"+ active);
        visible = active;
    }
    WinInfo{
        id: winInfo
        visible: false
    }

}

