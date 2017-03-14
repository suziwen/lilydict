import QtQuick 2.0

QtObject {
    property string shanbaylogo: "<div style='color:grey;'><img src='qrc:////img/shanbay.ico' height='11'/>扇贝</div>"
    property string youdaologo: "<div style='background-Color:gray;color:grey;'><img src='qrc:////img/youdao.ico' height='11'>有道</div>"
    property string def_en_info:""
    property string shanbayWordinfo: ""
    property string youdaoWordinfo: ""
    property string youdaocolor: "White"
    property string shanbaycolor: "WhiteSmoke"
    property var voc
    function setYoudaoWordinfo(wordinfo){
        if(wordinfo===""){
            youdaoWordinfo="";
        }else{
             youdaoWordinfo="<table style='background-color:"+youdaocolor+"' cellSpacing=1>"+
             "<tr>"+
             "<td valign='top'>"+youdaologo+"</td><td>"+wordinfo+"</td"+
             "</tr>"+
             "</table>";
        }
    }
    function setShanbayWordinfo(wordstr){//qml能够把调用语境中的变量和函数都带进来，比如mainForm
        var json = JSON.parse(wordstr);
        if(json.status_code !== 0 ){
            mainForm.word_name.text = "扇贝"+json.msg;
            mainForm.btn_addword.visible = false;
            mainForm.pronu_us.visible = false;
            mainForm.btn_sound0.visible = mainForm.btn_sound1.visible = false;
            mainForm.text_def.text = dict.shanbayWordinfo = dict.def_en_info = "";
            return;
        }
        if(mainForm.textWord) mainForm.textWord.text = "";
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
        dict.def_en_info = "<table style='background-Color:mintcream' cellSpacing=1>";
        for(var pos in voc.en_definitions){
            //console.log(pos);
            dict.def_en_info += "<tr><td align='right'>"+pos +"</td><td><ol>";
            var defs=voc.en_definitions[pos];
            for(var i=0;i<defs.length;i++){
                dict.def_en_info += "<li>" + defs[i] +"</li>";
            }
            //def_en_info = def_en_info.substring(0,def_en_info.length-4);
            dict.def_en_info+="</ol></td></tr>"
            //console.log(def_en_info);
        }
        dict.def_en_info+="</table>"

        dict.shanbayWordinfo ="<table style='background-Color:"+dict.shanbaycolor+"' cellSpacing=1>"+
                     "<tr>"+
                     "<td valign='middle'>"+dict.shanbaylogo+"</td><td><ul><li>"+voc.definition+"</li></ul></td"+
                     "</tr>"+
                     "</table>";
    }
    function addWord(){
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
        console.log("update add btn");
        if(learning_id&&learning_id!==0){
            mainForm.btn_addword.iconSource = "qrc:/img/add0.png";
            mainForm.btn_addword.tooltip = qsTr("忘记了，重新加入背单词计划");
        }else{
            mainForm.btn_addword.iconSource = "qrc:/img/add1.png";
            mainForm.btn_addword.tooltip = qsTr("添加进生词库，加入背单词计划");
        }
    }
}
