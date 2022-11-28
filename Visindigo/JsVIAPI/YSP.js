//此文档为VIJS版本的YSP实现方式。
class YSPTitlePage{
    constructor(){
        this.BG = VIGUI.newVIPicture();
        this.BlackBG = VIGUI.newVIPicture();
        this.Logo = VIGUI.newVIPicture();
        this.Head = VIGUI.newVIText();
        this.Title = VIGUI.newVIText();
        this.SubTitle = VIGUI.newVIText();

        this.BG.setGeometry(0, 0, 1, 1);
        this.BlackBG.fillColor(0, 0, 0);
        this.BlackBG.setGeometry(0, 0, 1, 1);
        this.BlackBG.setOpacity(0);
        this.Logo.move(0.35, 0.222);
        this.Logo.resizeWidthAndRatio(0.3, 1);
        this.Logo.setAlignment("M");
        this.Head.setGeometry(0, 0.33, 1, 0.06);
        this.Head.setAlignment("M");
        this.Head.setStyleSheet("VITextLabel{color:#FFFFFF;font-family:'Microsoft YaHei';font-size:AUTO_60_PR;}");
        this.Head.setText("Visindigo SPOL"); 
        this.Title.setGeometry(0, 0.4, 1, 0.137);
        this.Title.setAlignment("M");
        this.Title.setStyleSheet("VITextLabel{color:#FFFFFF;font-family:'Microsoft YaHei';font-size:AUTO_60_PR;}");
        this.SubTitle.setGeometry(0, 0.5, 1, 0.09);
        this.SubTitle.setAlignment("M");
        this.SubTitle.setStyleSheet("VITextLabel{color:#FFFFFF;font-family:'Microsoft YaHei';font-size:AUTO_60_PR;}");
    }
    raise(){
        this.BG.raise();
        this.BlackBG.raise();
        this.Head.raise();
        this.Logo.raise();
        this.Title.raise();
        this.SubTitle.raise();
    }
    show(){
        this.Head.show();
        this.Title.show();
        this.SubTitle.show();
        this.BG.show();
        this.BlackBG.show();
        this.Logo.show();
        
    }
    hide(){
        this.BG.hide();
        this.BlackBG.hide();
        this.Logo.hide();
        this.Head.hide();
        this.Title.hide();
        this.SubTitle.hide();
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
    doAnimation(){
        this.show();
        VISystem.wait(5000);
        this.BlackBG.setOpacityAni(0, 1, 1000, true);
        this.BlackBG.setOpacity(1);
        this.Logo.setOpacityAni(1, 0, 1000);
        this.Title.setOpacityAni(1, 0, 1000);
        this.SubTitle.setOpacityAni(1, 0, 1000);
        VISystem.wait(1000);
        this.hide();
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
export default class SPOL9{
    constructor(){
        this.Title = new YSPTitlePage();
        this.Story = new YSPStoryPage();
    }
    title(title, subtitle, logo, bg){
        this.Title.setBG(bg);
        this.Title.setTitle(title);
        this.Title.setSubTitle(subtitle);
        this.Title.setLogo(logo);
        this.Title.doAnimation();
    }
}

export var SPOL = new SPOL9();
