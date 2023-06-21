export class SPOLParserResult{
    constructor(){
        this.MethodName = "";
        this.NoWait = false;
        this.Parameters = new Map();
    }
}

export class SPOLParser{
    constructor(){
        this.ControllerName = "Unknown_SPOLParser_VIJS";
        this.FunctionLike = false;
        this.Parameters = new Array();
    }
    newResult(){
        return new SPOLParserResult();
    }
    recordResult(pobj){
        this.Parameters.push(pobj);
    }
    onParseLine(line){ 
        VISystem.printLine("Parser is not implemented yet.");
        return false;
    }
}