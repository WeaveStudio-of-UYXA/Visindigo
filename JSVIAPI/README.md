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