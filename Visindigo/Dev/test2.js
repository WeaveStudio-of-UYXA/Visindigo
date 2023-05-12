//请不要在Visindigo.JS中使用console.log()，虽然Visindigo支持
//如果你想在非VIESBehavior派生类中打印日志，请使用System.log()
//如果你想在VIESBehavior派生类中打印日志，请使用this.consoleLog()
console.log("test2.js loaded");

export class main extends VIESBase.VIESPlugin {
    constructor(){
        super();
        this.a = 1;
        console.log("a is "+this.a);
        System.log(System.getSystemName());
        this.consoleLog("T");
    }
    aplus(){
        this.a = this.a+1;
        console.log("a is "+this.a);
        return this.a;
    }
}
