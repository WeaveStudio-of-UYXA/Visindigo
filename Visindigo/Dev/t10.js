import {t10_SPOL} from "__story__/t10_SPOL.js"
import * as SPDFJS from "SPDFJS.js"
class TestParserBGP extends SPDFJS.SPOLParser{
	constructor(){
		super();
		setControllerName("背景");
	}
	onParseLine(line){
		var args = line.split(" ");
		for(var i = 0;i<args.length;i++){
			if(args[i]!=""){
				var pobj = this.newResult();
				pobj.MethodName = "YSPJS.10X.BGP";
				pobj.Parameters["背景"] = args[i];
				pobj.NoWait = false;
				this.recordResult(pobj);
			}
		}
		return true;
	}
}
export function main(){
	SPOL.installParser(new TestParserBGP());
	SPOL.loadStory(t10_SPOL.PartA);
	if(sth){
		SPOL.loadStory("./scene1/p1.spol");
	}else{
		SPOL.speak("???","...");
	}
}

/*SPOL
/SPOL0.10.0
-->PartA
背景 走廊
>>>:"Hello, world!" says the computer.
>>>:"Just a test."(0.4, 2)
...
SPOL*/