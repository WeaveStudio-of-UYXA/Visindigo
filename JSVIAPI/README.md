# JsVI API

喜大普奔，在PyGP（启动Python程序后本地socket通信）、VIL（内嵌类Python解释器）、PyVI（扩展Python解释器）均开发失败之后，我的评价是还得是Qt老大哥的玩意好使。VIAPI现在基于Qt实现的JavaScript脚本引擎（或者更标准的称呼为ECMAScript脚本引擎）提供为JS脚本，鉴于我们未对这套脚本引擎做任何扩展，似乎没有理由称之为VIScripts，因此仍然按上面那样称呼其为JsVI。


# 用户入口点
用户需要在其启动文件中定义一个**导出函数**`main`，例如：
```JavaScript
export function main(){
    VIGUI.debug("Hello world!");
}
```
一切用户操作从该函数开始，并且从该函数结束。当前Visindigo不会向用户入口点`main`传递任何参数，也不会接受返回值。

理论上来说，debug输出这种东西其实应该以
```JavaScript
Console.print("");
System.debug("");
```
或者类似的形式提供API，现在提供该函数的类是`VIGUI2D`的API类，纯属偷懒，至于以后会不会改——
> "看心情"

# 第一个谜语人程序
在YSP进化为Visindigo之后，实际上有很多内部便捷操作以及不复存在了（因为Visindigo瞄准的是更普适的使用环境而非单纯向YSP那样冲着给用户提供快捷方舟剧情模仿去的），所以如果YSP用户以标准的方式写一个Visindigo谜语人程序，那么画风应该是这样的：
```JavaScript
export function main(){
    TitleLabel = VIGUI2D.buildLabel("TE-1");
    SubTitleLabel = VIGUI2D.buildLabel("VI测试1");
    SplashLabel = VIGUI2D.buildLabel("Visindigo咋这么难写？？？")
    Logo = VIGUI2D.buildImage("./Source/logo1.png")
    Image = VIGUI2D.buildImage("./Source/bg1.png");
    TitleLabel.setGeo(x,y,w,h);
    ... 
    TitleLabel.show();
    ... 
    System.waitSecond(5);
    Image.fadeOut(3);
    TitleLabel.hide();
    ... 
    Doctor = VIGUI2D.buildLabel("Doctor");
    SayWhat = VIGUI2D.buildLabel("好家伙那么多的吗？");
    DoctorImage = VIGUI2D.buildImage("./Source/Doctor.png");
    SayWhat.setTextAnimation(150, 1500);
    Doctor.show();
    DoctorImage.show();
    SayWhat.show();
    SayWhat.doAnimation(true);
    VIGUI2D.clearAll();
}
```
当然，对于YSP用户来说这是不可接受的，所以我们按照原来的SPOL提供了以下函数，下面这段代码和上面的效果一样。
```JavaScript
export function main(){
    VIGUI2D.YSPSplashFrom(["Visindigo咋这么难写？？？"])
    VIGUI2D.YSPTitlePage("TE-1", "VI测试1", "./Source/logo1", "./Source/bg1");
    Doctor = VIGUI2D.YSPChara("Doctor");
    Doctor.setImage("./Source/Doctor.png");
    Doctor.say("好家伙那么多的吗？");
    VIGUI2D.clearAll();
}
```

如果您还没有看出来，它对应的SPOL.9X代码是这样的：
```
title(TE-1,VI测试1,logo1,bg1)
>>>Doctor:好家伙那么多的吗
```

确实比SPOL要多，不过优化完的（指YSP名义函数）API我觉得相对还是比原生操作要容易接受的。第一段代码本质上就是第二段代码的后台实际执行内容。