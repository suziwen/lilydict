import QtQuick 2.6
import QtQuick.Window 2.2
import QtMultimedia 5.6
Window {
    id: window
    visible: false
    width: 700
    height: 390
    title: cfg.getVersion()
    //flags: Q_OS_WIN ? Qt.Dialog:Qt.WindowStaysOnTopHint
    //flags: Qt.Dialog
    property var voc
    property string def_en_info: ""
    property string shanbayWordinfo: ""
    property string youdaoWordinfo: ""
    property string shanbaylogo: "<img src='https://static.baydn.com/static/img/shanbay_favicon.png' height='16'/>"
    property string youdaologo: "<img src='http://dict.youdao.com/favicon.ico' />"
    signal signalBtnqueryClick(string word)
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
        winInfo.showinfo(voc.content+"  已经加入扇贝网生词本，列入背单词计划。");
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
    /////////////////////////////
    function showWord(){
        mainForm.text_def.text = shanbayWordinfo+youdaoWordinfo + def_en_info ;
    }

    function showYoudaoWord(wordinfo){
        console.log(wordinfo);
        if(wordinfo===""){
            youdaoWordinfo="";
        }else{
             youdaoWordinfo="<table style='background-Color:White' cellSpacing=1>"+
             "<tr>"+
             "<td valign='middle' style='color:grey'>"+youdaologo+"有道</td><td>"+wordinfo+"</td"+
             "</tr>"+
             "</table>";
        }
        showWord();

    }

    function showShanbayWord(wordstr){
        //console.log("wordstr:"+wordstr);
        var json = JSON.parse(wordstr);
        if(json.status_code !== 0 ){
            mainForm.word_name.text = "扇贝"+json.msg;
            mainForm.btn_addword.visible = false;
            mainForm.pronu_us.visible = false;
            mainForm.btn_sound0.visible = mainForm.btn_sound1.visible = false;
            mainForm.text_def.text = shanbayWordinfo = def_en_info = "";
            return;
        }
        mainForm.textWord.text = "";
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
        def_en_info = "<table style='background-Color:mintcream' cellSpacing=1>";
        for(var pos in voc.en_definitions){
            //console.log(pos);
            def_en_info += "<tr><td align='right'>"+pos +"</td><td><ol>";
            var defs=voc.en_definitions[pos];
            for(var i=0;i<defs.length;i++){
                def_en_info += "<li>" + defs[i] +"</li>";
            }
            //def_en_info = def_en_info.substring(0,def_en_info.length-4);
            def_en_info+="</ol></td></tr>"
            //console.log(def_en_info);
        }
        def_en_info+="</table>"

        shanbayWordinfo ="<table style='background-Color:SeaShell' cellSpacing=1>"+
                     "<tr>"+
                     "<td valign='middle' style='color:grey'>"+shanbaylogo+"扇贝</td><td><ul><li>"+voc.definition+"</li></ul></td"+
                     "</tr>"+
                     "</table>";
        showWord();
        //console.log("wordinfo.definition:"+voc.definition);
    }
    ///////////////////////////////
    Audio {
            id: playSound0
        }
    Audio {
            id: playSound1
        }

    Flickable {
        id: view
        anchors.fill: parent
        contentWidth: mainForm.width
        contentHeight: mainForm.height

        MainForm {
            id: mainForm
            width:  window.width //text_def.width + 20
            height: text_def.height + 100
            btn_query.onClicked: {
                winInfo.hide();
                signalBtnqueryClick(textWord.text);
            }
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
            Keys.onPressed: {
                //console.log(event.key + "enterrrrrrrrrrrrrrrrrrrrrrrrrrrr"+Qt.Key_Enter +" "+Qt.Key_Return)
                if(event.key === Qt.Key_Enter || event.key === Qt.Key_Return){
                    if(textWord.focus) {
                        signalBtnqueryClick(textWord.text);
                        return;
                    }
                }
            }
            Component.onCompleted: {
                textWord.forceActiveFocus();
            }
        }

        // Only show the scrollbars when the view is moving.
        states: State {
            name: "ShowBars"
            when: view.movingVertically || view.movingHorizontally
            PropertyChanges { target: verticalScrollBar; opacity: 1 }
            PropertyChanges { target: horizontalScrollBar; opacity: 1 }
        }

        transitions: Transition {
            NumberAnimation { properties: "opacity"; duration: 400 }
        }
    }

    // Attach scrollbars to the right and bottom edges of the view.
    ScrollBar {
        id: verticalScrollBar
        width: 12; height: view.height-12
        anchors.right: view.right
        opacity: 0
        orientation: Qt.Vertical
        position: view.visibleArea.yPosition
        pageSize: view.visibleArea.heightRatio
    }

    ScrollBar {
        id: horizontalScrollBar
        width: view.width-12; height: 12
        anchors.bottom: view.bottom
        opacity: 0
        orientation: Qt.Horizontal
        position: view.visibleArea.xPosition
        pageSize: view.visibleArea.widthRatio
    }
    WinInfo{
        id: winInfo
        visible: false
    }
    Component.onCompleted: {
        setX(Screen.width / 2 - width / 2);
        setY(Screen.height / 2 - height / 2);
        mainForm.word_name.text = "";
        mainForm.text_def.text = "";
        mainForm.btn_addword.visible = false;
        mainForm.pronu_us.visible = false;
        mainForm.btn_sound0.visible = mainForm.btn_sound1.visible = false;
        //console.log("main window"+configs.value("getscreentext"));
    }
    onClosing:{
        //console.log("main windows is closing");
        visible = false;
        close.accepted = false;
    }
}
