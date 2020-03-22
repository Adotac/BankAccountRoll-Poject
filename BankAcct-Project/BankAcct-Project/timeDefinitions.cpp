#include "BA_header.h"


void depositMoney(Time *tiD)
{
	system("cls");
	float money;
	printf ("\n\t\tDepositing Section\n");
	printf ("Current Money : %.2f\n", tiD->totalBalance);
	printf ("\n\tAmount of money to deposit: ");
	scanf ("%f", &money);
	tiD->totalBalance = tiD->totalBalance + money;
	printf ("\n\n\tSuccess!");
	getch();

}


void withrawMoney(Time *tiD)
{
	system("cls");
	float money,interest;
	float withrawM;
	int days;

	dateExtractor('D', tiD->date, &days);

	if (days >= 360)
	{
		printf("\n\t======================================================================\n");
		printf("\t|\t You've already reached the expected date to withraw.        |\n");
		printf("\t|                                                                    |\n");
		printf("\t| You can now get the deposited money with an interest of 3 percent. |\n");
		printf("\t======================================================================\n");
		
		printf("\n\t=========================  Withdraw Section  =========================\n");
		printf ("Current Money : %.2f\n", tiD->totalBalance);
		printf ("\n\tAmount of money to withraw: ");
		scanf ("%f", &money);

		
		
		tiD->totalBalance += tiD->interestBalance;

		tiD->totalBalance = tiD->totalBalance - money; 
		printf ("\n\tTotal money : %.2f \n", tiD->totalBalance);
		printf ("\tWithdrawed Money : %.2f \n", money);
	}
	else if (days < 360)
	{
		printf("\n\t======================================================================\n");
		printf("\t|\t    You've not reached the expected date to withraw.         |\n");
		printf("\t|                                                                    |\n");
		printf("\t|\t\t You are not allowed to withraw yet.                 |\n");
		printf("\t======================================================================\n");
	}
	getch();
}


void calculateTimeDeposit()
{
	system("cls");
	float money, interest, total;
	printf("\n\t========================  Input the Following  =======================\n");
	printf ("\tInput amount of money: ");
	scanf ("%f", &money);
	interest = 12 * (money*INTEREST*TAX);
	total = money + interest;
	printf ("\tMoney : %.2f\n", money);
	printf ("\tInterest : %f\n", INTEREST);
	printf ("\tTax : %.2f\n", TAX);
	printf ("\n\tTotal(1 year) : %.2f", total);
	getch();
}


void checkMoney(char userId[], Savings* svD, acctDet *aD, Time *tiD, FILE *acdb, FILE *svdb , FILE *tidb)
{

	int choice=1;
	char key = UPARROW;

	do {//main loop
		system("cls");
		if (tiD->totalBalance < tiD->interestBalance)
		{
			printf("\n\t=============================  Notice:  =============================\n\t|\t   Your current money is below the expected deposit.        |\n"
				"\t|    You can only withdraw once every month with an interest of 3%%. |\n\t=====================================================================");
		}
	
		//show money
		printf ("Current Money : %.2f\n", tiD->totalBalance);
		
		fflush(stdin);
		printf("\n");printf("\t\t\t\t");
		printf("Menu:");
	
		switch (choice) {
		case 1:
			printf("\n");printf("\t\t\t\t");
			textHighllght("[Deposit Money]");
			printf("\n");printf("\t\t\t\t");
			printf("Withdraw Money");
			printf("\n");printf("\t\t\t\t");
			printf("Back");
			break;
		case 2:
			printf("\n");printf("\t\t\t\t");
			printf("Deposit Money");
			printf("\n");printf("\t\t\t\t");
			textHighllght("[Withdraw Money]");
			printf("\n");printf("\t\t\t\t");
			printf("Back");
			break;
		case 3:
			printf("\n");printf("\t\t\t\t");
			printf("Deposit Money");
			printf("\n");printf("\t\t\t\t");
			printf("Withdraw Money");
			printf("\n");printf("\t\t\t\t");
			textHighllght("[Back]");
			break;
		}
		key = getch();
		switch (key) {
		case UPARROW:
			choice--;
			if (choice < 1)
				choice = 3;
			break;
		case DWARROW:
			choice++;
			if (choice > 3)
				choice = 1;
			break;
		}
		
	} while (key != ENTER);


	switch (choice)
	{
	case 1: depositMoney(tiD);
		break;
	case 2: withrawMoney(tiD);
		break;
	case 3: return; 
		break;
	}
}


void TimeDeposit(char userId[], Savings* svD, acctDet *aD, Time *tiD, FILE *acdb, FILE *svdb , FILE *tidb)
{
	if(FindIdFileSetter(userId, "FA,FI", acdb, aD, tidb, tiD) != TRUE){
		printf("\n\n\nError! Corrupted Account");
		getch();
		return;
	}

	tiD->interestBalance = 12 * (tiD->totalBalance * INTEREST * TAX);
	do{

		switch (optTime(aD, tiD)){

		case 1: 
			checkMoney(userId, svD, aD, tiD, acdb, svdb, tidb);
			break;
		case 2: 
			calculateTimeDeposit();
			break;
		case 3:
			//BORROW FUNCTION
			MoneyTransfer(tiD->acctID, svD, aD, tiD, acdb, svdb, tidb);
			break;
		case 4: 
			
			return;

		}
	
		system("cls");
	}while(TRUE);
}

int createTime(){
	float initial = 0;
	system("cls");
	printf("\nOne last step!");
	printf("\nEnter an initial amount(not less than %d): ", MIN_INITIAL);
	scanf(" %f", &initial);

	while(initial < MIN_INITIAL){
		system("cls");
		printf("Initial is not enough!");
		printf("\nEnter an initial amount(not less than %d): ", MIN_INITIAL);
		scanf(" %f", &initial);

		if(initial < 0){
			return NA;
		}
	}

	return initial;


}