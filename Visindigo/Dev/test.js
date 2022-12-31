export function main() {
    VISystem.print(VISystem.argv())
    VISystem.print(VISystem.getSystemProductName());
    VIGUI.resize(1366, 768);
    VIGUI.enableGUIFrame();
    SPOL.init();
    SPOL.title("VI-T1","Visindigo 测试", "./Resource/Logo.png", "./Resource/BG.png");
    SPOL.cover(true);
    SPOL.backdrop("./Resource/光落.png");
    SPOL.speak("天雨", "。。。");
    SPOL.speak("天雨", "秋风起，鸿雁南飞");
    SPOL.speak("天雨", "白羽落，不知何处归");
    VISystem.wait(500);
    test();
    VISystem.exit();
}
function test(){
    VISystem.print("Hello world");
}

