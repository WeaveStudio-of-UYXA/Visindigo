export function main() {
    VIGUI.resize(1366, 768);
    //VIGUI.showFullScreen();
    VISystem.print("这片大地上从来都有敢于直面天灾的勇士，他们不会因为天灾而退缩，而是会用自己的力量去拯救这片大地。");
    var t = VIGUI.newVIText();
    t.setText("这片大地上从来都有敢于直面天灾的勇士，他们不会因为天灾而退缩，而是会用自己的力量去拯救这片大地。");
    t.setText("我的足迹遍布大地，但却也不是整个泰拉");
    t.setText("你好，世界。");
    VISystem.print("Hello world");
    VISystem.wait(5000);
    VISystem.exit();
}