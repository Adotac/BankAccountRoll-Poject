#include "BA_header.h"

void checkMoney(float *principalMoney)
{
	system("cls");
	int choice;
	if (*principalMoney < DEPOSIT)
	{
		printf ("\nNotice:  \nYour current money is below the expected deposit.\n"
				"You can only withdraw once every month with an interest of 3%%.\n");
	}
	showMoney(principalMoney);
	printf ("\nMenu: \n"
			"1.Deposit Money\n"
			"2.Withraw Money\n"
			"3.Back\n"
			"Choice: ");
	scanf ("%d", &choice);
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
	printf ("Depositing Section\n");
	showMoney(principalMoney);
	printf ("Amount of money to deposit: ");
	scanf ("%f", &money);
	*principalMoney = *principalMoney + money;
	printf ("Success!");
	getch();
	checkMoney(principalMoney);
}

void withrawMoney(float *principalMoney)
{
	system("cls");
	float money,total,interest, totalMoney;
	float withrawM;
	int days;
	printf ("Withraw Section\n");
	showMoney(principalMoney);
	printf ("Amount of money to withraw: ");
	scanf ("%f", &money);
	printf ("Number of days since deposit: ");
	scanf ("%d", &days);
	if (days >= 360)
	{
		printf ("You've already reached the expected date to withraw.\n"
				"You can now get the deposited money with an interest of 3 percent.\n");
		total = *principalMoney + (*principalMoney*INTEREST*TAX);
		*principalMoney = total;
		*principalMoney = *principalMoney - money; 
		printf ("Total money : %.2f \n", *principalMoney);
		printf ("Money withraw : %.2f \n", money);
	}
	else if (days < 360)
	{
		printf ("You've not reached the expected date to withraw.\n"
				"You are not allowed to withraw yet.\n");
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
	printf ("Input amount of money: ");
	scanf ("%f", &money);
	total = money + (money*INTEREST*TAX);
	printf ("Money : %.2f\n", money);
	printf ("Interest : %f\n", INTEREST);
	printf ("Tax : %.2f\n", TAX);
	printf ("Total(1 year);: %.2f", total);
	getch();
}

void TimeDeposit(acctDet *aD, int index)
{
	float *principalMoney;
	principalMoney = &aD[index].totalBalance;
	float newTotalBalance;
	int choice, flag = TRUE;
	do{
	system ("cls");
	printf ("Welcome %s, \n", aD[index].acctID);
	printf("\n%s %s %s", aD[index].inf.pname.First, aD[index].inf.pname.Middle, aD[index].inf.pname.Last);
	printf ("\nTime Deposit\n"
			"1. Check money\n"
			"2. Calculate Time Deposit\n"
			"3. Back\n"
			"Choice: ");
	scanf ("%d", &choice);
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