#include "BA_header.h"

//Savings Account
void acctHistory(acctDet *aD, int accIndex){
	aD[accIndex].totalBalance = 0;
	printf("\n||DEPOSITED AMOUNT\t||BRANCH\t||DATE\n");

	for(int i = 0; i < PLIMIT; i++){
		if(aD[accIndex].balance_history[i] != NULL){
			printf("\n||%15.2f\t||%10s\t||%5s", aD[accIndex].balance_history[i], aD[accIndex].branch[i], aD[accIndex].date[i]);
			aD[accIndex].totalBalance += aD[accIndex].balance_history[i];
		}
		else
			break;


		printf("\n||Total: %15.2f", aD[accIndex].totalBalance);
	}

	
}
int accountTypeReg(int i){
	char key = LTARROW, time[CHARLIMIT], savings[CHARLIMIT], trust[CHARLIMIT], cancel[CHARLIMIT];

	strcpy(time, "[TIME]");
	strcpy(savings, "[SAVINGS]");
	strcpy(trust, "[TRUST]");
	strcpy(cancel, "[CANCEL]");

	while (key != ENTER) {
		system("cls");
		printf("\n\t==========	 Welcome!	==========");
		printf("\n\t|\tSelect the following types:\t |\n\t|");

		switch (i) {
		case 0: printf("\033[0;33m");
			printf("%s   ", time);
			printf("\033[0m");
			printf("%s   ", savings);
			printf("%s   ", trust);
			printf("%s", cancel);
			break;
		case 1:
			printf("%s   ", time);
			printf("\033[0;33m");
			printf("%s   ", savings);
			printf("\033[0m");
			printf("%s   ", trust);
			printf("%s", cancel);
			break;
		case 2:printf("%s   ", time);
			printf("%s   ", savings);
			printf("\033[0;33m");
			printf("%s   ", trust);
			printf("\033[0m");
			printf("%s", cancel);
			break;
		case 3:printf("%s   ", time);
			printf("%s   ", savings);
			printf("%s   ", trust);
			printf("\033[0;33m");
			printf("%s", cancel);
			printf("\033[0m");
			break;
		}
		printf(" |\n\t==========================================");

		key = _getch();
		switch (key) {
		case LTARROW:
			i--;
			if (i < 0)
				i = 0;
			break;
		case RTARROW:
			i++;
			if (i == 4)
				i = 3;
			break;
		case ENTER:
			break;
		}
	}
	return i;
}