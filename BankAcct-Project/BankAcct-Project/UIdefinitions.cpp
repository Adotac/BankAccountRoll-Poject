#include "BA_header.h"

<<<<<<< HEAD
=======
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
	
	printf("\r%s\r", "                 ");
	
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
	
	printf("\r%s\r", "                                   ");
	//printf("\r\t\t\t\t\t\t\t\t\t\t\t\t\r");
	}while(key != ENTER);
}

int optBenefits(){
	char key;
	int iCtr = 1;

	do{

		switch(iCtr){
		case 1:
			textHighllght("[SUCCESSOR]");
			printf("\t");
			printf("[SCHOLARSHIP]");
			printf("\t");
			printf("[RETIREMENT PLAN]");
			printf("\t");
			printf("[EXIT]");
			break;
		case 2:
			printf("[SUCCESSOR]");
			printf("\t");
			textHighllght("[SCHOLARSHIP]");
			printf("\t");
			printf("[RETIREMENT PLAN]");
			printf("\t");
			printf("[EXIT]");
			break;
		case 3:
			printf("[SUCCESSOR]");
			printf("\t");
			printf("[SCHOLARSHIP]");
			printf("\t");
			textHighllght("[RETIREMENT PLAN]");
			printf("\t");
			printf("[EXIT]");
			break;
		case 4:
			printf("[SUCCESSOR]");
			printf("\t");
			printf("[SCHOLARSHIP]");
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
	
	printf("\r");
	}while(key != ENTER);
}


>>>>>>> d3997c5... Functions being arranged
