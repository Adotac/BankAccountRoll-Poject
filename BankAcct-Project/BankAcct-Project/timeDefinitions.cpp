#include "BA_header.h"

void checkMoney(float *principalMoney)
{
	system("cls");
	int choice=1;
	char key = UPARROW;
	if (*principalMoney < DEPOSIT)
	{
		printf("\n\t=============================  Notice:  =============================\n\t|\t   Your current money is below the expected deposit.        |\n"
			"\t|    You can only withdraw once every month with an interest of 3%%. |\n\t=====================================================================");
	}
	showMoney(principalMoney);

	do {//main loop
		fflush(stdin);
		system("cls");
		printf("\n\t\t\t\t\tMenu: \n\n");
		key = getch();
		switch (choice) {
		case 1:

			printf("\n\t\t\t\t\tMenu: \n\n");
			textHighllght("\t\t\t\t   [Deposit Money]\n");
			printf("\n\t\t\t\t   Withdraw Money\n");
			"\n\t\t\t\t\tBack");
			break;
		case 2:printf("\n\t\t\t\t\tMenu: \n\n");
			printf("\t\t\t\t   Deposit Money\n");
			textHighllght("\n\t\t\t\t   [Withdraw Money]\n");
			"\n\t\t\t\t\tBack");
			break;
		case 3:
			printf("\n\t\t\t\t\tMenu: \n\n");
			printf("\t\t\t\t   Deposit Money\n");
			printf("\n\t\t\t\t   Withdraw Money\n");
			printf("\n\t\t\t\t\t[Back]");
			break;
		}
		switch (key) {
		case UPARROW:
			choice--;
			if (choice < 1)
				choice = 1;
			break;
		case DNARROW:
			choice++;
			if (choice > 3)
				choice = 3;
			break;
		}
	} while (key != ENTER);
	switch (choice)
	{
	case 1: depositMoney(principalMoney);
			break;
	case 2: withrawMoney(principalMoney);
			break;
	case 3: break;
	default:
		break;
	}
}

void depositMoney(float *principalMoney)
{
	system("cls");
	float money;
	printf ("\n\t\tDepositing Section\n");
	showMoney(principalMoney);
	printf ("\n\tAmount of money to deposit: ");
	scanf ("%f", &money);
	*principalMoney = *principalMoney + money;
	printf ("\n\n\tSuccess!");
	getch();
	checkMoney(principalMoney);
}

void withrawMoney(float *principalMoney)
{
	system("cls");
	float money,total,interest, totalMoney;
	float withrawM;
	int days;
	printf("\n\t=========================  Withdraw Section  =========================\n");
	showMoney(principalMoney);
	printf ("\n\tAmount of money to withraw: ");
	scanf ("%f", &money);
	printf ("\tNumber of days since deposit: ");
	scanf ("%d", &days);
	if (days >= 360)
	{
		printf("\n\t======================================================================\n");
		printf("\t|\t You've already reached the expected date to withraw.        |\n");
		printf("\t|                                                                    |\n");
		printf("\t| You can now get the deposited money with an interest of 3 percent. |\n");
		printf("\t======================================================================\n");
		total = *principalMoney + (*principalMoney*INTEREST*TAX);
		*principalMoney = total;
		*principalMoney = *principalMoney - money; 
		printf ("\n\tTotal money : %.2f \n", *principalMoney);
		printf ("\tMoney withraw : %.2f \n", money);
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
	checkMoney(principalMoney);
}

void showMoney(float *principalMoney)
{
	printf ("Current Money : %.2f\n", *principalMoney);
}

void calculateTimeDeposit()
{
	system("cls");
	float money, total;
	printf("\n\t========================  Input the Following  =======================\n");
	printf ("\tInput amount of money: ");
	scanf ("%f", &money);
	total = money + (money*INTEREST*TAX);
	printf ("\tMoney : %.2f\n", money);
	printf ("\tInterest : %f\n", INTEREST);
	printf ("\tTax : %.2f\n", TAX);
	printf ("\n\tTotal(1 year) : %.2f", total);
	getch();
}

void TimeDeposit(acctDet *aD, int index)
{
	float *principalMoney;
	principalMoney = &aD[index].totalBalance;
	float newTotalBalance;
	char key = UPARROW;
	int choice=1, flag = TRUE;
	do{
	system ("cls");
	printf ("Welcome %s, \n", aD[index].acctID);
	printf("\n%s %s %s", aD[index].inf.pname.First, aD[index].inf.pname.Middle, aD[index].inf.pname.Last);
	do {//main loop
		fflush(stdin);
		system("cls");
		printf("\n\t===========================  Time Deposit  ===========================\n");
		key = getch();
		switch (choice) {
		case 1:

			printf("\n\t\t\t\t\tMenu: \n\n");
			textHighllght("\t\t\t\t   [Check Money]\n");
			printf("\n\t\t\t\t   Withdraw Money\n");
			"\n\t\t\t\t\tBack");
			break;
		case 2:printf("\n\t\t\t\t\tMenu: \n\n");
			printf("\t\t\t\t   Check Money\n");
			textHighllght("\n\t\t\t\t   [Calculate Time Deposit]\n");
			"\n\t\t\t\t\tBack");
			break;
		case 3:
			printf("\n\t\t\t\t\tMenu: \n\n");
			printf("\t\t\t\t   Check Money\n");
			printf("\n\t\t\t\t   Calculate Time Deposity\n");
			printf("\n\t\t\t\t\t[Back]");
			break;
		}
		switch (key) {
		case UPARROW:
			choice--;
			if (choice < 1)
				choice = 1;
			break;
		case DNARROW:
			choice++;
			if (choice > 3)
				choice = 3;
			break;
		}
	} while (key != ENTER);
	switch (choice)
	{
	case 1: checkMoney(principalMoney);
			break;
	case 2: calculateTimeDeposit();
			break;
	case 3: system ("cls");
			return;
	default:
		break;
	}
	newTotalBalance = *principalMoney;
	aD[index].totalBalance = newTotalBalance;
	system("cls");
	}while(flag == TRUE);
}