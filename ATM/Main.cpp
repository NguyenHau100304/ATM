#include "Process.h"
using namespace std;

int main()
{
	loginAdminMenu();
	_getch();
    return 0;
}

/* Nhap password
	char c;
	string s = "";
	while (c = _getch()) {

		if (c == '\r')
			goto Exit;
		if (c == '\b') {
			cout << "\b \b";
			s.erase(s.length() - 1);
		}
		else {
			cout << '*';
			s = s + c;
		}

	}
	Exit:
	cout << '\n' << s;
	*/