import { main2 } from "./main.js";
export function main() {
    main2();
    VISystem.print("这片大地上从来都有敢于直面天灾的勇士，他们不会因为天灾而退缩，而是会用自己的力量去拯救这片大地。");
    VIGUI.setWindowTitle("Test");
    VISystem.sleep(5000);
    VIGUI.showFullScreen();
}