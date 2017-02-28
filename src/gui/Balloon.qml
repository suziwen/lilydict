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
    property var voc    
    signal signalBtnaddwordClick(string type,string id)
    //slot
    function addWordRet(retstr){
        console.log(" add word ret"+retstr);
        var json=JSON.parse(retstr);
        if(json.status_code !== 0 ){
            var infostr = qsTr("添加新词失败：") + json.msg;
            mainForm.word_name.text = infostr;
            winInfo.showinfo(infostr);
            return;
        }
        updateBtnaddword(json.data.id);
        winInfo.showinfo(voc.content+qsTr("  已加入扇贝网生词本,列入背单词计划。"));
    }
    function showWord(wordstr){
        window.requestActivate();        console.log("wordstr:"+wordstr);
        var json = JSON.parse(wordstr);
        if(json.status_code !== 0 ){
            mainForm.word_name.text = json.msg;
            mainForm.btn_addword.visible = false;
            mainForm.pronu_us.visible = false;
            mainForm.btn_sound0.visible = mainForm.btn_sound1.visible = false;
            mainForm.text_def.visible = false;
            return;
        }
        winInfo.hide();
        mainForm.text_def.visible = true;
        mainForm.btn_addword.visible = true;
        mainForm.pronu_us.visible = true;
        mainForm.btn_sound0.visible = mainForm.btn_sound1.visible = true;
        voc = json.data;
        updateBtnaddword(voc.learning_id);
        mainForm.word_name.text = voc.content;
        mainForm.pronu_uk.text = "/"+voc.pronunciations.uk+"/";
        mainForm.pronu_us.text = "/"+voc.pronunciations.us+"/";
        if(voc.has_audio){
            mainForm.btn_sound0.visible = mainForm.btn_sound1.visible = true;
            playSound0.source = voc.uk_audio;
            playSound1.source = voc.us_audio;
            if(cfg.isAutospeak()) playSound1.play();
        }else{
            mainForm.btn_sound0.visible = mainForm.btn_sound1.visible = false;
        }
        mainForm.text_def.text =voc.definition;
        window.width = Math.max(mainForm.rowLayout_pronu.width + 20,360);
        window.height = Math.max(mainForm.text_def.height + 100,90);
    }
    function updateBtnaddword(learning_id){
        if(learning_id&&learning_id!==0){
            mainForm.btn_addword.iconSource = "qrc:/img/add0.png";
            mainForm.btn_addword.tooltip = qsTr("忘记了，重新加入背单词计划");

        }else{
            mainForm.btn_addword.iconSource = "qrc:/img/add1.png";
            mainForm.btn_addword.tooltip = qsTr("添加进生词库，加入背单词计划");
        }
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
        btn_addword.onClicked: {            
            if(!cfg.isLoginshanbay()){
                winInfo.showinfo("登录扇贝网后，才能使用加入生词本功能。")
                return;
            }
            if(voc.learning_id&&voc.learning_id!==0){
                signalBtnaddwordClick("relearn",voc.learning_id);
            }else{
                signalBtnaddwordClick("add",voc.object_id);
            }
        }
        btn_sound0.onClicked: {
            //console.log(mainForm.height+"  "+view.contentHeight)
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

