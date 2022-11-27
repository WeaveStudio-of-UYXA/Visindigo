//此文档为VIJS版本的YSP实现方式。
class YSPTitlePage{
    constructor(){
        this.BG = VIGUI.newVIPicture();
        this.BlackBG = VIGUI.newVIPicture();
        this.Logo = VIGUI.newVIPicture();
        this.Title = VIGUI.newVIText();
        this.SubTitle = VIGUI.newVIText();

        this.BG.setGeometry(0, 0, 1, 1);
        this.BlackBG.fillColor(0, 0, 0);
        this.BlackBG.setGeometry(0, 0, 1, 1);
        this.BlackBG.setOpacity(0, 0, 1);
        this.Logo.setGeometry(0.367, 0.222, 0.472, 0.472);
        this.Title.setGeometry(0, 0.4, 1, 0.085);
        this.Title.setAlignment("M");
        this.Title.setStyleSheet("VITextLabel{color:#FFFFFF;font-family:'Microsoft YaHei';font-size:AUTO_98_PR;}");
        this.SubTitle.setGeometry(0, 0.5, 1, 0.055);
        this.SubTitle.setAlignment("M");
        this.SubTitle.setStyleSheet("VITextLabel{color:#FFFFFF;font-family:'Microsoft YaHei';font-size:AUTO_98_PR;}");
    }
    raise(){
        this.BG.raise();
        this.BlackBG.raise();
        this.Logo.raise();
        this.Title.raise();
        this.SubTitle.raise();
    }
    show(){
        this.BG.show();
        this.BlackBG.show();
        this.Logo.show();
    }
    setBG(path){
        this.BG.setPicture(path);
    }
    setTitle(text){
        this.Title.setText(text);
    }
    setSubTitle(text){
        this.SubTitle.setText(text);
    }
    setLogo(path){
        this.Logo.setPicture(path);
    }
}
class YSPStoryPage{
    constructor(){
        this.BG1 = VIGUI.newVIPicture();
        this.BG2 = VIGUI.newVIPicture();
        this.Chara1 = VIGUI.newVIPicture();
        this.Chara2 = VIGUI.newVIPicture();
        this.Chara3 = VIGUI.newVIPicture();
        this.Cover = VIGUI.newVIPicture();
        this.NameLabel = VIGUI.newVIText();
        this.TextLabel = VIGUI.newVIText();
        this.FreeLabel = VIGUI.newVIText();
    }
}

class SPOL9{
    constructor(){
        this.Title = new YSPTitlePage();
    }
}

export var SPOL = new SPOL9();