#include "BA_header.h"


int main(void){
	srand(time(NULL));
	FILE *acdb = fopen("acdb.bin", "rb+");
	FILE *svdb = fopen("svdb.bin", "rb+");
	FILE *tidb = fopen("tidb.bin", "rb+");
	FILE *trdb = fopen("trdb.bin", "rb+");

	acctDet *account = (acctDet*)calloc(1, sizeof(struct AccountDetails));
	SavingsDetails *savAcct = (SavingsDetails*)calloc(1, sizeof(struct SavingsDetails));
	TrustDetails *trustAcct = (TrustDetails*)calloc(1, sizeof(struct TrustDetails));
	TimeDetails *timeAcct = (TimeDetails*)calloc(1, sizeof(struct TimeDetails)); 

	int loginFlag = TRUE, a_index = NULL;
	int pinInput = NULL;
	
	char *inputId;
	inputId = (char*)calloc(sizeof(char), CHARLIMIT);
	
	

	
	do {//main loop
		fflush(stdin);
		readFiles(&account, &timeAcct, &trustAcct, &savAcct, &trdb, &svdb, &tidb, &acdb );
		
		system("cls");
		
		

		switch(LoginScreen()){
		
		case 1:
			printf("\n\n\tAccount ID: ");
			gets(inputId);
			upperSentence(inputId);

			if(strcmp(inputId, "ADMINBK") == 0){
				fflush(stdin);
				printf("\n\tPIN: ");
				scanf(" %d", &pinInput);
				if(pinInput == atoi(ADMPASS)){
					//admin funtions
					adminPanel(account,savAcct, timeAcct, trustAcct, acdb, svdb, tidb, trdb);
					
				}
				else{
					printf("\nACCOUNT ID or PIN doesn't match");
					getch();
					continue;
				}

			}
			else if(IdChecker(inputId, account, acdb) == TRUE){
				fflush(stdin);
				printf("\n\tPIN: ");
				scanf(" %d", &pinInput);
				//ari na ang pin input
				if(pinChecker(inputId, pinInput, account, acdb) == TRUE){
					//ari na sulod tanan after login
					
					switch(account->type){
					case TIME:
						TimeDeposit(inputId, savAcct, account, timeAcct, acdb, svdb, tidb);
						fflush(tidb);
						UpdateFiles(inputId, "FI", tidb, timeAcct);
						break;
					case SAVINGS:
						displaySavings(inputId, savAcct, account, timeAcct, acdb, svdb, tidb);
						fflush(svdb);				
							UpdateFiles(inputId, "FS", svdb, savAcct);
						break;
					case TRUST:
						displayTrust(inputId, account, trustAcct, savAcct, timeAcct, acdb, trdb, svdb, tidb);
						fflush(trdb);
						UpdateFiles(inputId, "FR", trdb, trustAcct);
						break;
					}
				}
				else{
					printf("\nACCOUNT ID or PIN doesn't match");
					getch();
					continue;
				}
			}
			else{ 
				printf("\n:::::Account doesn't exist!!:::::");
				getch();
			}
			break;
		case 2:
			acctGenerator(account, timeAcct, trustAcct, savAcct, trdb, svdb, tidb, acdb);	
			break;
		case 3:
			loginFlag = FALSE;
			break;
		}


		

		
	}while(loginFlag == TRUE);
	
	
	
	

	
	free(inputId);
	free(account);
	free(savAcct);
	free(timeAcct);
	free(trustAcct);

	fclose(acdb);
	fclose(trdb);
	fclose(svdb);
	fclose(tidb);
	return 0;
}
	

