#include "TText.h"



int main()
{
	char filename[100] = "text.txt\0";
	char test[100] = "test.txt\0";

	TText text;
	text.Load(test);

	text.GoFirst();
	char str[81] = "DownSection";
	text.InsertDownSection(str);

	text.GoNext();
	char str2[81] = "NextLine";
	text.InsertNextLine(str2);

	char str3[81] = "DownLine";
	text.InsertDownLine(str3);

	char str4[81] = "NextSection";





	text.InsertNextSection(str4);

	text.Print();
	//text.Print(test);


}