export class VIESBehavior{
    constructor(){
        this.objectName = "VIESBehavior"
        this.consoleLog("INITED")
    }
    onActive(){}
    onTick(){}
    onSubSide(){}
    consoleLog(msg){
        System.log("["+this.objectName+"]"+msg);
    }
    setObjectName(name){
        this.objectName = name;
    }
    getObjectName(){
        return this.objectName;
    }
}

export class VIESPlugin extends VIESBehavior{
   // static Instance = null;
    constructor(){
        super();
        VIESPlugin.Instance = this;
        this.objectName = "VIESPlugin";
    }
    getInstance(){
        return VIESPlugin.Instance;
    }
    getPluginName(){
        return this.objectName;
    }
    setPluginName(name){
        this.objectName = name;
    }
}

console.log("VIESObject Module loaded");

