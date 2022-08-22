
/**
 * @name            app.c
 * @def             part of pyment system project - FWD
 * @version         v1.0
 * @authors         Abdelrahman Belkasy
 * @date            21 August 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../STD_LIB.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"
#include "app.h"

extern float CurrentBalance;
/*
----------------------------------------------------------------------------------------------------
!-                                      Fuctions Implementation
----------------------------------------------------------------------------------------------------
*/
void appStart(void)
{
    ST_cardData_t cardData;
    ST_terminalData_t terminalData;
    /** @defgroup Card Ops */
    if (getCardHolderName(&cardData) == WRONG_NAME)     {printf("Wrong card name\n"); return;}
    if (getCardPAN(&cardData) == WRONG_PAN)             {printf("Wrong card PAN\n"); return;}
    if (getCardExpiryDate(&cardData) == WRONG_EXP_DATE) {printf("Wrong card Expiry Date\n"); return;}


    /** @defgroup terminal Ops */
    if (getTransactionDate(&terminalData) == WRONG_DATE)       {printf("Wrong terminal date\n"); return;}
    if (isCardExpired(cardData, terminalData) == EXPIRED_CARD) {printf("Declined\nCard Expired...\n"); return;}
    if (setMaxAmount(&terminalData) == INVALID_MAX_AMOUNT)     {printf("Invalid Max Amount... \n"); return;}

    /** @defgroup Sever Ops */
    ST_transaction_t transactionData;
    uint8_t option;

    do{
        printf("\nTo Make a Transaction Enter 1\n");
        printf("To Found a Transaction Enter 2\n");
        printf("To exit Enter 0\n");
        printf("Your Choice: ");
        scanf(" %d", &option);
        printf("\n");

    
    if (option == 0) {break;}
    else if (option == 1) 
    {
        EN_transStat_t transactionState;
        if (getTransactionAmount(&terminalData) == INVALID_AMOUNT) {printf("Invalid Amount... \n"); return;}
        if (isBelowMaxAmount(&terminalData) == EXCEED_MAX_AMOUNT)  {printf("Declined\nAmount Exceeding Limit...\n"); return;}
        //isValidAccount(&cardData);
        transactionData.cardHolderData = cardData;
        transactionData.terminalData   = terminalData;
        
        transactionState = recieveTransactionData(&transactionData);
        printf("Data: %s\n",terminalData.transactionDate);
        if      (transactionState == APPROVED)                   {printf("Aproved Transaction\n"); return;}
        else if (transactionState == DECLINED_STOLEN_CARD)       {printf("Declined\nInvalid Card\n"); return;}
        else if (transactionState == DECLINED_INSUFFECIENT_FUND) {printf("Declined\nInsuffecient Funds\n"); return;}
        else if (transactionState == INTERNAL_SERVER_ERROR)      {printf("Srver ERROR\n"); return;}
    }
    else if (option == 1) 
    {
        uint8_t SequanceNum = 0;
        printf("Enter Transaction Sequance Number: ");
        scanf("%d", &SequanceNum);
        getTransaction(SequanceNum, &transactionData);
    }
    else {printf("Wrong Option");}
    } while(1);

}/* appStart */

