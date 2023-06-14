import {t10_SPOL} from "__story__/t10_SPOL.js"

export function main(){
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
>>>:"Hello, world!" says the computer.
...
SPOL*/