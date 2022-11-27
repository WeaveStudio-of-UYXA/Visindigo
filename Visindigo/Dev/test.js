export function main() {
    VISystem.print("???");
    VIGUI.resize(1366, 768);
    VIGUI.enableGUIFrame();
    YSP.SPOL.title("VI-T1","Visindigo 测试", "./Resource/Logo.png", "./Resource/BG.png");
    //VIGUI.showFullScreen();
    /*VISystem.print(VISystem.getSystemProductName());
    VISystem.print("这片大地上从来都有敢于直面天灾的勇士，他们不会因为天灾而退缩，而是会用自己的力量去拯救这片大地。");
    var p = VIGUI.newVIPicture();
    var t = VIGUI.newVIText();
    p.setGeometry(0.35, 0.15, 0.3, 0.7);
    p.setPicture("./Resource/天雨.png");
    p.show();
    t.setGeometry(0.1, 0.4, 0.8, 0.2);
    t.setStyleSheet("VITextLabel{color:#FFFFFF;font-family:'Microsoft YaHei';font-size:30px;}");
    t.setAlignment("C");
    t.setOpacityAni(0, 1, 2000);
    t.setTextAni("这片大地上从来都有敢于直面天灾的勇士。");
    t.textNonlinerProgress([[0, 0], [0.8, 0], [0.9, 1], [1, 1]]);
    t.continueTextAni("\n他们不会因为天灾而退缩，而是会用自己的力量去拯救这片大地。",150,1500);
    t.setOpacityAni(1, 0, 1000, true);
    t.setOpacityAni(0, 1, 1000);
    t.setTextAni("我的足迹遍布大地，但却也不是整个泰拉");
    t.setOpacityAni(1, 0, 1000, true);
    t.setOpacityAni(0, 1, 1);
    t.setTextAni("你好，世界。");
    VISystem.print("Hello world");
    
    */
    VISystem.wait(500);
    VISystem.exit();
}