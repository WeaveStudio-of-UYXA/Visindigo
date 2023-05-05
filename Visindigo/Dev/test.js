export function main() {
    //VIGUI.resize(1366, 768);
    VIGUI.enableGUIFrame();
    VIGUI.showFullScreen();
    SPOL.init();
    SPOL.title("VI-T1","Visindigo 测试", "./Resource/Logo.png", "./Resource/BG.png");
    SPOL.cover(true);
    SPOL.backdrop("./Resource/光落.png");
    SPOL.speak("天雨", "。。。");
    SPOL.speak("天雨", "秋风起，鸿雁南飞");
    SPOL.speak("天雨", "白羽落，望长空青邃，不知古人何日归");
    SPOL.speak(""," ");
    SPOL.cover(false);
    VISystem.wait(500);
    SPOL.backdrop();
    VISystem.wait(500);
    VISystem.exit();
}




