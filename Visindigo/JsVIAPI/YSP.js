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
        this.BG.releaseMemory();
        this.Logo.releaseMemory();
    }
}
class YSPStoryPage{
    constructor(){
        this.BG1 = VIGUI.newVIPicture();
        this.BG2 = VIGUI.newVIPicture();
        this.BGFLAG = 1;
        this.Chara1 = VIGUI.newVIPicture();
        this.Chara2 = VIGUI.newVIPicture();
        this.Chara3 = VIGUI.newVIPicture();
        this.Cover = VIGUI.newVIPicture();
        this.NameLabel = VIGUI.newVIText();
        this.TextLabel = VIGUI.newVIText();
        this.FreeLabel = VIGUI.newVIText();
    } 
    raise(){
        this.BG1.raise();
        this.BG2.raise();
        this.Chara1.raise();
        this.Chara2.raise();
        this.Chara3.raise();
        this.Cover.raise();
        this.NameLabel.raise();
        this.TextLabel.raise();
        this.FreeLabel.raise();
    }
    show(){
        this.BG1.show();
        this.BG2.show();
        this.BG2.setOpacity(0);
        this.Chara1.show();
        this.Chara2.show();
        this.Chara3.show();
        this.Cover.show();
        this.NameLabel.show();
        this.TextLabel.show();
        this.FreeLabel.show();
    }
    hide(){
        this.BG1.hide();
        this.BG2.hide();
        this.Chara1.hide();
        this.Chara2.hide();
        this.Chara3.hide();
        this.Cover.hide();
        this.NameLabel.hide();
        this.TextLabel.hide();
        this.FreeLabel.hide();
    }
    init(){
        this.raise();
        this.BG1.fillColor(0, 0, 0);
        this.BG2.fillColor(0, 0, 0);
        this.BG1.setGeometry(0, 0, 1, 1);
        this.BG2.setGeometry(0, 0, 1, 1);
        this.TextLabel.setGeometry(0.3,0.87,0.55,0.105);
        this.TextLabel.setStyleSheet("VITextLabel{color:#F5F5F5;font-family:'Microsoft YaHei';font-size:AUTO_30_PR;}");
        this.TextLabel.setAlignment("L");
        this.NameLabel.setGeometry(0.052,0.86685,0.1897,0.07);
        this.NameLabel.setStyleSheet("VITextLabel{color:#AAAAAA;font-family:'Microsoft YaHei';font-size:AUTO_60_PR;}");
        this.NameLabel.setAlignment("R");
        this.Cover.setGeometry(0, 0, 1, 1);
        this.Cover.setPicture("./YSP/image/frame.png");
        this.Cover.setOpacity(0);
        this.show();
    }
    setBG(path, fadeintime = 500){
        if(this.BGFLAG == 1){
            this.BG2.setPicture(path);
            if (fadeintime > 0){
                this.BG2.setOpacityAni(0, 1, fadeintime, true);
            }
            this.BGFLAG = 2;
        }
        else{
            this.BG1.setPicture(path);
            if (fadeintime > 0){
                this.BG2.setOpacityAni(1, 0, fadeintime, true);
            }
            this.BGFLAG = 1;
        }
    }
    setChara(charapathlist){
        if(charapathlist.length == 1){
            this.Chara1.setPicture("");
            this.Chara2.setPicture(charapathlist[0]);
            this.Chara3.setPicture("");
        }
        else if(charapathlist.length == 2){
            this.Chara1.setPicture(charapathlist[0]);
            this.Chara3.setPicture(charapathlist[1]);
            this.Chara2.setPicture("");
        }
    }
    setSpeak(name, text, mspt = 100, msw = 1500){
        this.NameLabel.setText(name);
        this.TextLabel.setTextAni(text, mspt, msw, true);
    }
    setCover(bool){
        if(bool){
            this.Cover.setOpacity(1);
        }
        else{
            this.Cover.setOpacity(0);
        }
    }
}


var Title;
var Story;

export function init(){
    Title = new YSPTitlePage();
    Story = new YSPStoryPage();
}

export function title(title, subtitle, logo, bg){
    Title.setBG(bg);
    Title.setTitle(title);
    Title.setSubTitle(subtitle);
    Title.setLogo(logo);
    Title.doAnimation();
    Story.init();
}

export function backdrop(path, fadeintime = 500){
    Story.setBG(path, fadeintime);
}

export function chara(pathlist){
    Story.setChara(pathlist);
}

export function speak(name, text, mspt = 100, msw = 1500){
    Story.setSpeak(name, text, mspt, msw);
}

export function cover(bool){
    Story.setCover(bool);
}