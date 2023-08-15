#include "clsLoginScreen.h"

int main()

{
	while (true)
	{
		if (!clsLoginScreen::ShowLoginScreen())
			break;
	}

	system("pause > nul");
	return 0;
}

/*
Note: Use the following credentials to log in with full access:

Username: admin
Password: admin
*/