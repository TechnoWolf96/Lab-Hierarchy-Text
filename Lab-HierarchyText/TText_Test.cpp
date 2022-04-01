#include "TText.h"
#include "Control.h"
#include <conio.h>

#define DOWN 80
#define NEXT 77
#define UP 72
#define ESC 27
#define INSERT 82
#define DELETE 83
#define ENTER 13

TMemory TTextNode::memory;

void TextConsole()
{
	char filename[100];
	bool saved = false;
begin:

	while (true)
	{
		clrscr();
		cout << "Enter filename: ";
		cin >> filename;

		TText text(30);
		text.Load(filename);
		text.GoFirstLine();


		while (true)
		{
			clrscr();
			cout << "Navigation: |v|>|<| ; INSERT - Insert line; ENTER - Update line;" << endl;
			cout << "DELETE - Delete line; S - Save text; M - Show free memory; C - Clean memory; ESC - Close text." << endl;
			text.Print();

			if (saved) cout << "Text saved." << endl;
			saved = false;

			char control = _getch();
			switch (control)
			{
			case DOWN: try { text.GoNextLine(); }
					 catch (...) {} break;
			case UP: try { text.GoBackLine(); }
				   catch (...) {} break;
			case NEXT: try { text.GoDownLine(); }
					 catch (...) {} break;

			case INSERT:
			{
				char str[81];
				cout << "1 - Next line; 2 - Next section; 3 - Down line; 4 - Down section; 5 - Cancel" << endl;
				char a = _getch();
				if (a == '5') break;
				cout << "Enter line: ";
				cin >> str;
				switch (a)
				{
				case '1': text.InsertNextLine(str); break;
				case '2': text.InsertNextSection(str); break;
				case '3': text.InsertDownLine(str); break;
				case '4': text.InsertDownSection(str); break;
				}
				break;
			}


			case ENTER:
				char str[81];
				cout << "Enter new line: ";
				cin >> str;
				text.SetNavCurrent(str);
				break;

			case 's':
				text.Print(filename);
				saved = true;
				break;

			case ESC:
				goto begin;
				break;

			case DELETE:
			{
				cout << "1 - Next line; 2 - Down line; 3 - Cancel" << endl;
				char a = _getch();
				if (a == '3') break;
				switch (a)
				{
				case '1': text.DeleteNextLine(); break;
				case '2': text.DeleteDownLine(); break;
				case '3': break;
				}
				break;
			}

			case 'm':
				cout << "Free memory:" << endl;
				TTextNode::PrintFree();
				cout << "Press any key to continue." << endl;
				_getch();
				break;

			case 'c':
				text.CleanMemory();
				cout << "Memory cleaned. Press any key to continue." << endl;
				_getch();
				break;

			}


		}
	}
}

void TestCopy()
{
	TText a(100);
	char filename[100];
	strcpy(filename, "text.txt");
	a.Load(filename);

	TText* b = a.GetCopy();
	cout << "===== Start text =====\n";
	a.Print();
	cout << "\n===== Copyed text =====\n";
	b->Print();

}




int main()
{
	//TextConsole();
	TestCopy();

}