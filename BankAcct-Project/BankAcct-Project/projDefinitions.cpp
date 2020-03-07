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