#include "BA_header.h"


int main(void){
	acctDet *account;
	account = (acctDet*)calloc(sizeof(acctDet), PLIMIT);

	account[0].balance_history[0] = 50000;
	strcpy(account[0].branch[0], "basak");
	strcpy(account[0].date[0], __DATE__);
	char acctId[CHARLIMIT];
	int i=0;// IDENTIFIES THE TYPE OF SAVINGS

	do {
		system("cls");
		printf("\n\tNo account yet? Type REGISTER to create an account.");
		printf("\n\n\tAccount ID: ");
		gets_s(acctId);
		toupper(acctId[CHARLIMIT]);
	} while (strcmp(acctId, "REGISTER") != 0);
	
	
	acctHistory(account, 0);

	getch();
	return 0;
}
	i = accountTypeReg(i);

//int main(void){
//	acctDet account[PLIMIT];
//
//
//	int flag = TRUE;
//	char acctId[CHARLIMIT];
//	char *actReply;
//	actReply = (char*)calloc(sizeof(char), CHARLIMIT);
//
//	int key=0; //left and right key function selection for account type
//	do{
//		system("cls");
//		printf("\n\tNo account yet? Type REGISTER to create an account.");
//		printf("\n\n\tAccount ID: ");
//		gets_s(acctId);
//		toupper(acctId[CHARLIMIT]);
//	}while (strcmp(acctId, "REGISTER") != 0);
//	
//	printf("\n\t==========	Welcome!	==========");
//	printf("\n\n\tSelect the following types:\n");
//	strcpy(actReply,"[TIME]");
//	
//	do {
//		switch (key) {
//		case LTARROW:
//			printf("\033[0;33m");
//			printf("%s", "test");
//			printf("\033[0m");
//			printf("    [TIME]");
//			printf("    [TRUST]");
//			printf("    [CANCEL]");
//			break;
//		case RTARROW:
//
//			break;
//		}
//	}while(flag == TRUE);
//
//getch();
//return 0;
//}