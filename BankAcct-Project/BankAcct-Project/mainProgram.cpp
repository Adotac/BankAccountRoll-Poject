#include "BA_header.h"


int main(void){

	char acctId[CHARLIMIT];
	const char* actReply[ACCTSELT];
	int key=0; //left and right key function selection for account type
	do {
		system("cls");
		printf("\n\tNo account yet? Type REGISTER to create an account.");
		printf("\n\n\tAccount ID: ");
		gets_s(acctId);
		toupper(acctId[CHARLIMIT]);
	} while (strcmp(acctId, "REGISTER") != 0);
	
	printf("\n\t==========	Welcome!	==========");
	printf("\n\n\tSelect the following types:\n");
	strcpy(actReply[0],"[TIME]");
	do {
		switch (key) {
		case LTARROW:
			printf("\033[0;33m");
			printf("%s",);
			printf("\033[0m");
			printf("    [TIME]");
			printf("    [TRUST]");
			printf("    [CANCEL]");
			break;
		case RTARROW:

			break;
		}
	}

_getch();
return 0;
}