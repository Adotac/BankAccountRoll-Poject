#include "BA_header.h"

//UI Functions
void textHighllght(char s[]){
	
	printf("\033[0;33m");
	printf("%s   ", s);
	printf("\033[0m");
}

int optYesNo(){
	char key;
	int iCtr = 1;

	do{

		switch(iCtr){
		case 1:
			textHighllght("[YES]");
			printf("\t");
			printf("[NO]");
			
			break;
		case 2:
			printf("[YES]");
			printf("\t");
			textHighllght("[NO]");
			break;
		
		
		}

		key = getch();
		switch(key){
		case LTARROW:
			iCtr--;
			if(iCtr < 1)
				iCtr = 1;
			break;
		case RTARROW:
			iCtr++;
			if(iCtr > 2)
				iCtr = 2;
			break;
		case ENTER:
			return iCtr;
			break;
		}
	
	printf("\r%s\r", "                                             ");
	
	}while(key != ENTER);
}

int optTrust(){
	char key;
	int iCtr = 1;

	do{
		
		switch(iCtr){
		case 1:
			textHighllght("[ADD LEDGER]");
			printf("\t");
			printf("[DELETE LEDGER]");
			printf("\t");
			printf("[LINK ACCOUNT]");
			printf("\t");
			printf("[EXIT]");
			break;
		case 2:
			printf("[ADD LEDGER]");
			printf("\t");
			textHighllght("[DELETE LEDGER]");
			printf("\t");
			printf("[LINK ACCOUNT]");
			printf("\t");
			printf("[EXIT]");
			break;
		case 3:
			printf("[ADD LEDGER]");
			printf("\t");
			printf("[DELETE LEDGER]");
			printf("\t");
			textHighllght("[LINK ACCOUNT]");
			printf("\t");
			printf("[EXIT]");
			break;
		case 4:
			printf("[ADD LEDGER]");
			printf("\t");
			printf("[DELETE LEDGER]");
			printf("\t");
			printf("[LINK ACCOUNT]");
			printf("\t");
			textHighllght("[EXIT]");
			break;
		
		}

		key = getch();
		switch(key){
		case LTARROW:
			iCtr--;
			if(iCtr < 1)
				iCtr = 1;
			break;
		case RTARROW:
			iCtr++;
			if(iCtr > 4)
				iCtr = 4;
			break;
		case ENTER:
			return iCtr;
			break;
		}
	
	printf("\r                                                                 \r");
	
	}while(key != ENTER);

}

int optLedger(){
	char key;
	int iCtr = 1;

	do{
		
		switch(iCtr){
		case 1:
			textHighllght("[ASSETS]");
			printf("\t");
			printf("[LIABILITIES]");
			
			break;
		case 2:
			printf("[ASSETS]");
			printf("\t");
			textHighllght("[LIABILITIES]");
			break;
		
		
		}

		key = getch();
		switch(key){
		case LTARROW:
			iCtr--;
			if(iCtr < 1)
				iCtr = 1;
			break;
		case RTARROW:
			iCtr++;
			if(iCtr > 2)
				iCtr = 2;
			break;
		case ENTER:
			return iCtr;
			break;
		}
	
	printf("\r%s\r", "                                                             ");
	}while(key != ENTER);
}

int optBenefits(){
	char key;
	int iCtr = 1;
	printf("\n");
	do{

		switch(iCtr){
		case 1:
			
			textHighllght("[SUCCESSOR]");
			printf("\t");
			printf("[CHARITY]");
			printf("\t");
			printf("[RETIREMENT PLAN]");
			printf("\t");
			printf("[EXIT]");
			break;
		case 2:
		
			printf("[SUCCESSOR]");
			printf("\t");
			textHighllght("[CHARITY]");
			printf("\t");
			printf("[RETIREMENT PLAN]");
			printf("\t");
			printf("[EXIT]");
			break;
		case 3:
			
			printf("[SUCCESSOR]");
			printf("\t");
			printf("[CHARITY]");
			printf("\t");
			textHighllght("[RETIREMENT PLAN]");
			printf("\t");
			printf("[EXIT]");
			break;
		case 4:
			
			printf("[SUCCESSOR]");
			printf("\t");
			printf("[CHARITY]");
			printf("\t");
			printf("[RETIREMENT PLAN]");
			printf("\t");
			textHighllght("[EXIT]");
			break;
		
		}

		key = getch();
		switch(key){
		case LTARROW:
			iCtr--;
			if(iCtr < 1)
				iCtr = 1;
			break;
		case RTARROW:
			iCtr++;
			if(iCtr > 4)
				iCtr = 4;
			break;
		case ENTER:
			return iCtr;
			break;
		}
	
	printf("\r                                                                              \r");
	}while(key != ENTER);
}

int optTime(acctDet *aD, Time *tiD){
	char key = UPARROW;
	int choice=1, flag = TRUE;

	do {
			fflush(stdin);
			system("cls");
			printf ("Welcome %s, \n", tiD->acctID);
			printf("\n%s %s %s", aD->First, aD->Middle, aD->Last);
			
			printf("\n\t===========================  Time Deposit  ===========================\n");
			
			switch (choice) {
			case 1:
				printf("\n");printf("\t\t\t\t");
				textHighllght("[Check Money]");
				printf("\n");printf("\t\t\t\t");
				printf("CALCULATE INTEREST");
				printf("\n");printf("\t\t\t\t");
				printf("BORROW MONEY");
				printf("\n");printf("\t\t\t\t");
				printf("BACK");
				break;
			case 2:
				printf("\n");printf("\t\t\t\t");
				printf("Check Money");
				printf("\n");printf("\t\t\t\t");
				textHighllght("[CALCULATE INTEREST]");
				printf("\n");printf("\t\t\t\t");
				printf("BORROW MONEY");
				printf("\n");printf("\t\t\t\t");
				printf("BACK");
				break;
			case 3:
				printf("\n");printf("\t\t\t\t");
				printf("Check Money");
				printf("\n");printf("\t\t\t\t");
				printf("CALCULATE INTEREST");
				printf("\n");printf("\t\t\t\t");
				textHighllght("[BORROW MONEY]");
				printf("\n");printf("\t\t\t\t");
				printf("BACK");
				break;
			case 4:
				printf("\n");printf("\t\t\t\t");
				printf("Check Money");
				printf("\n");printf("\t\t\t\t");
				printf("CALCULATE INTEREST");
				printf("\n");printf("\t\t\t\t");
				printf("BORROW MONEY");
				printf("\n");printf("\t\t\t\t");
				textHighllght("[BACK]");
				break;
			}
			key = getch();
			switch (key) {
			case UPARROW:
				choice--;
				if (choice < 1)
					choice = 4;
				break;
			case DWARROW:
				choice++;
				if (choice > 4)
					choice = 1;
				break;
			}
			
		} while (key != ENTER);

	return choice;
}

int LoginScreen(){

	
	char key;
	int iCtr = 1;

	do{
		fflush(stdin);
		system("cls");
		printf("\n\n\n\t\t");
		printf("==================[ WELCOME TO E-BANK ]===================");
		printf("\n");printf("\t\t\t\t");

		switch(iCtr){
		case 1:
			printf("\n");printf("\t\t\t\t");
			textHighllght("[LOGIN]");
			printf("\n");printf("\t\t\t\t");
			printf("REGISTER");
			printf("\n");printf("\t\t\t\t");
			printf("EXIT");
			
			break;
		case 2:
			printf("\n");printf("\t\t\t\t");
			printf("LOGIN");
			printf("\n");printf("\t\t\t\t");
			textHighllght("[REGISTER]");
			printf("\n");printf("\t\t\t\t");
			printf("EXIT");
			break;
		case 3:
			printf("\n");printf("\t\t\t\t");
			printf("LOGIN");
			printf("\n");printf("\t\t\t\t");
			printf("REGISTER");
			printf("\n");printf("\t\t\t\t");
			textHighllght("[EXIT]");
			break;
		
		
		}

		key = getch();
		switch(key){
		case UPARROW:
			iCtr--;
			if(iCtr < 1)
				iCtr = 3;
			break;
		case DWARROW:
			iCtr++;
			if(iCtr > 3)
				iCtr = 1;
			break;
		case ENTER:
			system("cls");
			return iCtr;
			break;
		}
	
	}while(key != ENTER);
}

int optAdmin(){
	char key;
	int iCtr = 1;

	do{
		printf("\n\n\t\t\t\t\t");
		printf("------ADMIN PANEL------");

		switch(iCtr){
		case 1:
			printf("\n");printf("\t\t\t\t");
			textHighllght("[DISPLAY ALL ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			printf("[DISPLAY ALL SAVINGS ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			printf("[DISPLAY ALL TIME ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			printf("[DISPLAY ALL TRUST ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			printf("[DELETE AN ACCOUNT]");
			printf("\n");printf("\t\t\t\t");
			printf("[SEARCH AN ACCOUNT]");
			printf("\n");printf("\t\t\t\t");
			printf("[LOGOUT]");
			break;
		case 2:
			printf("\n");printf("\t\t\t\t");
			printf("[DISPLAY ALL ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			textHighllght("[DISPLAY ALL SAVINGS ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			printf("[DISPLAY ALL TIME ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			printf("[DISPLAY ALL TRUST ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			printf("[DELETE AN ACCOUNT]");
			printf("\n");printf("\t\t\t\t");
			printf("[SEARCH AN ACCOUNT]");
			printf("\n");printf("\t\t\t\t");
			printf("[LOGOUT]");
			break;
		case 3:
			printf("\n");printf("\t\t\t\t");
			printf("[DISPLAY ALL ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			printf("[DISPLAY ALL SAVINGS ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			textHighllght("[DISPLAY ALL TIME ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			printf("[DISPLAY ALL TRUST ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			printf("[DELETE AN ACCOUNT]");
			printf("\n");printf("\t\t\t\t");
			printf("[SEARCH AN ACCOUNT]");
			printf("\n");printf("\t\t\t\t");
			printf("[LOGOUT]");
			break;
		case 4:
			printf("\n");printf("\t\t\t\t");
			printf("[DISPLAY ALL ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			printf("[DISPLAY ALL SAVINGS ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			printf("[DISPLAY ALL TIME ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			textHighllght("[DISPLAY ALL TRUST ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			printf("[DELETE AN ACCOUNT]");
			printf("\n");printf("\t\t\t\t");
			printf("[SEARCH AN ACCOUNT]");
			printf("\n");printf("\t\t\t\t");
			printf("[LOGOUT]");
			break;
		case 5:
			printf("\n");printf("\t\t\t\t");
			printf("[DISPLAY ALL ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			printf("[DISPLAY ALL SAVINGS ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			printf("[DISPLAY ALL TIME ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			printf("[DISPLAY ALL TRUST ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			textHighllght("[DELETE AN ACCOUNT]");
			printf("\n");printf("\t\t\t\t");
			printf("[SEARCH AN ACCOUNT]");
			printf("\n");printf("\t\t\t\t");
			printf("[LOGOUT]");
			break;
		case 6:
			printf("\n");printf("\t\t\t\t");
			printf("[DISPLAY ALL ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			printf("[DISPLAY ALL SAVINGS ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			printf("[DISPLAY ALL TIME ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			printf("[DISPLAY ALL TRUST ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			printf("[DELETE AN ACCOUNT]");
			printf("\n");printf("\t\t\t\t");
			textHighllght("[SEARCH AN ACCOUNT]");
			printf("\n");printf("\t\t\t\t");
			printf("[LOGOUT]");
			break;
		case 7:
			printf("\n");printf("\t\t\t\t");
			printf("[DISPLAY ALL ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			printf("[DISPLAY ALL SAVINGS ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			printf("[DISPLAY ALL TIME ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			printf("[DISPLAY ALL TRUST ACCOUNTS]");
			printf("\n");printf("\t\t\t\t");
			printf("[DELETE AN ACCOUNT]");
			printf("\n");printf("\t\t\t\t");
			printf("[SEARCH AN ACCOUNT]");
			printf("\n");printf("\t\t\t\t");
			textHighllght("[LOGOUT]");
			break;
		}

		key = getch();
		switch(key){
		case UPARROW:
			iCtr--;
			if(iCtr < 1)
				iCtr = 7;
			break;
		case DWARROW:
			iCtr++;
			if(iCtr > 7)
				iCtr = 1;
			break;
		case ENTER:
			return iCtr;
			break;
		}
	
		system("cls");
	}while(key != ENTER);
}


int SavingMoneyOpts(){
	char key;
	int iCtr = 1;

	do{

		switch(iCtr){
		case 1:
			textHighllght("[DEPOSIT]");
			printf("\t");
			printf("[WITHDRAW]");
			printf("\t");
			printf("[MONEY TRANSFER]");
			printf("\t");
			printf("[EXIT]");
			break;
		case 2:
			printf("[DEPOSIT]");
			printf("\t");
			textHighllght("[WITHDRAW]");
			printf("\t");
			printf("[MONEY TRANSFER]");
			printf("\t");
			printf("[EXIT]");
			break;
		case 3:
			printf("[DEPOSIT]");
			printf("\t");
			printf("[WITHDRAW]");
			printf("\t");
			textHighllght("[MONEY TRANSFER]");
			printf("\t");
			printf("[EXIT]");
			break;
		case 4:
			printf("[DEPOSIT]");
			printf("\t");
			printf("[WITHDRAW]");
			printf("\t");
			printf("[MONEY TRANSFER]");
			printf("\t");
			textHighllght("[EXIT]");
			break;
		
		}

		key = getch();
		switch(key){
		case LTARROW:
			iCtr--;
			if(iCtr < 1)
				iCtr = 1;
			break;
		case RTARROW:
			iCtr++;
			if(iCtr > 4)
				iCtr = 4;
			break;
		case ENTER:
			return iCtr;
			break;
		}
	
	printf("\r");
	}while(key != ENTER);

}

int accountTypeReg(){
	int i = 0;
	char key = LTARROW;

	while (key != ENTER) {
		system("cls");
		printf("\n\t===============	 Welcome!	================");
		printf("\n\t|\t   Select the following types:		|\n\t|");

		switch (i) {
		case 0: 
			textHighllght("    [TIME]");
			printf("%s   ", "[SAVINGS]");
			printf("%s   ", "[TRUST]");
			printf("%s", "[CANCEL]");
			break;
		case 1:
			printf("    %s   ", "[TIME]");
			textHighllght("[SAVINGS]");
			printf("%s   ", "[TRUST]");
			printf("%s", "[CANCEL]");
			break;
		case 2:
			printf("    %s   ", "[TIME]");
			printf("%s   ", "[SAVINGS]");
			textHighllght("[TRUST]");
			printf("%s", "[CANCEL]");
			break;
		case 3:
			printf("    %s   ", "[TIME]");
			printf("%s   ", "[SAVINGS]");
			printf("%s   ", "[TRUST]");
			textHighllght("[CANCEL]");
			break;
		}
		printf("\t|\n\t================================================");

		key = getch();
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

const char *typeIdentifier(accType aT){
	
	switch(aT){
	case SAVINGS:
		return "SAVINGS";
		break;
	case TRUST:
		return "TRUST";
		break;
	case TIME:
		return "TIME";
		break;
	default:
		return "ERROR";
		break;
	
	}
	
	
}

const char *trustIdentifier(Tbenefits tB){
	
	switch(tB){
	case SUCCESSOR:
		return "SUCCESSOR";
		break;
	case CHARITY:
		return "CHARITY";
		break;
	case RETIREMENT:
		return "RETIREMENT";
		break;
	default:
		return "ERROR";
		break;
	
	}
	
	
}

