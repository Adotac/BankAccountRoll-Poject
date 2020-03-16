#include "BA_header.h"


int main(void){

	char acctId[CHARLIMIT];
	int i=0;// IDENTIFIES THE TYPE OF SAVINGS

	do {
		system("cls");
		printf("\n\tNo account yet? Type REGISTER to create an account.");
		printf("\n\n\tAccount ID: ");
		gets_s(acctId);
		toupper(acctId[CHARLIMIT]);
	} while (strcmp(acctId, "REGISTER") != 0);
	

	i = accountTypeReg(i);

_getch();
return 0;
}