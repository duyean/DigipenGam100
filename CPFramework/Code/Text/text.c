#include <stdio.h>
#include "cprocessing.h"
#include "../CMP_Text_Pak.h"

/*
* Takes in filePath of the font and the CP_Color
* Returns: Initialized TextTemplate
* Uses: To keep the font and colour as a template for later use
*/
TextTemplate CreateTextTemplate(char* font, CP_Color color) {
	TextTemplate newTT;
	newTT.font = CP_Font_Load(font);
	newTT.color = color;
	return newTT;
}