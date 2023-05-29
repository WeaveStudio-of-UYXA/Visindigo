import t10_SPOL from Story.t10_SPOL

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
>>>:
...
SPOL*/