/**
 * @name            server.c
 * @def             part of pyment system project - FWD
 * @version         v1.0
 * @authors         Abdelrahman Belkasy
 * @date            20 August 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../STD_LIB.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "server.h"

/*
----------------------------------------------------------------------------------------------------
!-                                      Global DataBase Arrayes
----------------------------------------------------------------------------------------------------
*/
/**                                              @def float balance       @def [20]string PAN*/
ST_accountsDB_t globalDB[ACCOUNTS_MAX_SIZE] = {  
                                                {   100.5       ,       "4847 3529 8926 3094"    },     /* user 1 */
                                                {   200.111     ,       "3379 5135 6110 8795"    },     /* user 2 */
                                                {   500.21      ,       "4904 8398 2248 5959"    },     /* user 3 */
                                                {   10.100      ,       "2769 1483 0405 9987"    },     /* user 4 */
                                                {   1000        ,       "1234 5675 9876 5432"    },     /* user 5 */
                                                {   1002.6      ,       "9131 4617 8375 9183"    },     /* user 6 */
                                                {   5000.3      ,       "0490 9912 9683 4267"    }      /* user 7 */ 
                                              };


ST_transaction_t globalTransactionsDB[TRANSACTIONS_MAX_SIZE] = { 
                                                                { 0 , 0 , 0 , 0 }       /* Intialize with zeros */
                                                               };

float CurrentBalance = 0.0;
/*
----------------------------------------------------------------------------------------------------
!-                                      Fuctions Implementation
----------------------------------------------------------------------------------------------------
*/
/**
 * @brief Function to Recive the Tansaction Data and return if APROVED!
 * @param ST_terminalData_t *
 * @return EN_transStat_t (transaction Error State)
*/
EN_transStat_t  recieveTransactionData(ST_transaction_t *transData)
{
                                                                                  transData->transState = APPROVED;       /* Defult */
    if      (isValidAccount (&transData->cardHolderData ) == ACCOUNT_NOT_FOUND)  {transData->transState = DECLINED_STOLEN_CARD;}
    else if (isAmountAvailable (&transData->terminalData) == LOW_BALANCE)        {transData->transState = DECLINED_INSUFFECIENT_FUND;}
    else if (saveTransaction (transData) == SAVING_FAILED)                       {transData->transState = INTERNAL_SERVER_ERROR;}
    else if (APPROVED == transData->transState)
    {
        for (int i = 0; i <= TRANSACTIONS_MAX_SIZE; i++)
        {

            if (strcmp(transData->cardHolderData.primaryAccountNumber, globalDB[i].primaryAccountNumber) == 0)
            {
                printf("Your Old Balance is: %f\n", globalDB[i].balance);
                globalDB[i].balance -= transData->terminalData.transAmount;

                printf("Your New Balance is: %f\n", globalDB[i].balance);
                break;
            }
        }

    }

    return transData->transState;


}/* recieveTransactionData */

/**
 * @brief Function to Check if the Account Valid
 * @param ST_cardData_t *
 * @return EN_serverError_t (Server Error State)
*/
EN_serverError_t isValidAccount(ST_cardData_t *cardData)
{
    for(int i = 0; i <= ACCOUNTS_MAX_SIZE; i++)
    {
        if (strcmp(cardData->primaryAccountNumber, globalDB[i].primaryAccountNumber) == 0)
        {
            CurrentBalance =  globalDB[i].balance;
            return SERVER_OK;
        }
    }
    return ACCOUNT_NOT_FOUND;
}/* isValidAccount */

/**
 * @brief Function to Check if the Amount Available
 * @param ST_terminalData_t *
 * @return EN_serverError_t (Server Error State)
*/
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{

    if ( (termData->transAmount) <= (CurrentBalance) )
    {
        return SERVER_OK;
    }

    return  LOW_BALANCE;

}/* isAmountAvailable */

/**
 * @brief Function to Save the Transaction To Data Base
 * @param ST_transaction_t *
 * @return EN_serverError_t (Server Error State)
*/
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{   
    static uint16_t TransactionIndex_DB = 0;
    static uint32_t seqNum = 0; 
    if (TransactionIndex_DB <= TRANSACTIONS_MAX_SIZE)
    {
        transData->transactionSequenceNumber = seqNum;
        globalTransactionsDB[TransactionIndex_DB].cardHolderData            = transData->cardHolderData;
        globalTransactionsDB[TransactionIndex_DB].terminalData              = transData->terminalData;
        globalTransactionsDB[TransactionIndex_DB].transState                = transData->transState;
        globalTransactionsDB[TransactionIndex_DB].transactionSequenceNumber = transData->transactionSequenceNumber;

        printf("Transaction sequence number: %d\n",  globalTransactionsDB[TransactionIndex_DB].transactionSequenceNumber);

        TransactionIndex_DB +=1;
        seqNum += 1;
        return SERVER_OK;
    }
    return SAVING_FAILED;
}/* saveTransaction */

/**
 * @brief Function to Get the Transaction Data From Data Base
 * @param ST_transaction_t *
 * @param uint32_t transactionSequenceNumber
 * @return EN_serverError_t (Server Error State)
*/
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData)
{
    for (int i = 0; i < TRANSACTIONS_MAX_SIZE; i++)
    {
        if (globalTransactionsDB[i].transactionSequenceNumber == transactionSequenceNumber)
        {
            transData->cardHolderData               = globalTransactionsDB[i].cardHolderData;   
            transData->terminalData                 = globalTransactionsDB[i].terminalData;              
            transData->transState                   = globalTransactionsDB[i].transState;                
            transData->transactionSequenceNumber    = globalTransactionsDB[i].transactionSequenceNumber; 
            
            printf("Transaction Found: %d\n", transactionSequenceNumber);
            return SERVER_OK;

        }
    }
    
    printf("Transaction NOT Found: %d\n", transactionSequenceNumber);
    
    return TRANSACTION_NOT_FOUND;
}

/*
----------------------------------------------------------------------------------------------------
!-                                          Test Fuctions
----------------------------------------------------------------------------------------------------
*/
static void test_recieveTransactionData (void)
{
    /*Create a new card struct*/
    ST_transaction_t *transData;
    /* Alloocating Memory for the card */
    transData = (ST_transaction_t *) malloc(sizeof(ST_transaction_t));

    getCardPAN(&transData->cardHolderData);
    getTransactionAmount(&transData->terminalData);

    /* declare the function  */
    int error = recieveTransactionData(transData);

    /* Check the function Arguments */
    printf("PAN: %s\n", transData->cardHolderData.primaryAccountNumber);

    /* Check if there error or not */
    if (error == APPROVED)                              {printf("ERROR TYPE: APPROVED");}
    else if (error == DECLINED_INSUFFECIENT_FUND)       {printf("ERROR TYPE: DECLINED_INSUFFECIENT_FUND");}
    else if (error == DECLINED_STOLEN_CARD)             {printf("ERROR TYPE: DECLINED_STOLEN_CARD");}
    else if (error == INTERNAL_SERVER_ERROR)            {printf("ERROR TYPE: INTERNAL_SERVER_ERROR");}
    else                                                {printf("TESTING ERROR FAILD");}
}/* test_recieveTransactionData */

static void test_isValidAccount (void)
{
    /*Create a new card struct*/
    ST_transaction_t *transData;
    /* Alloocating Memory for the card */
    transData = (ST_transaction_t *) malloc(sizeof(ST_transaction_t));

    getCardPAN(&transData->cardHolderData);

    /* declare the function  */
    int error = isValidAccount(&transData->cardHolderData);

    printf("PAN: %s\n", transData->cardHolderData.primaryAccountNumber);

    /* Check if there error or not */
    if (error == SERVER_OK)                              {printf("ERROR TYPE: SERVER_OK");}
    else if (error == ACCOUNT_NOT_FOUND)             {printf("ERROR TYPE: ACCOUNT_NOT_FOUND");}
    else                                                {printf("TESTING ERROR FAILD");}
}/* test_isValidAccount */

static void test_isAmountAvailable (void)
{
    /*Create a new card struct*/
    ST_terminalData_t *termData;
    /* Alloocating Memory for the card */
    termData = (ST_terminalData_t *) malloc(sizeof(ST_terminalData_t));

    getTransactionAmount(termData);
    
    /* declare the function  */
    int error = isAmountAvailable(termData);

    printf("CURRENT: %f\n", CurrentBalance);
    printf("NEEDED: %f\n", termData->transAmount);

    /* Check if there error or not */
    if (error == SERVER_OK)                             {printf("ERROR TYPE: SERVER_OK");}
    else if (error == LOW_BALANCE)                      {printf("ERROR TYPE: LOW_BALANCE");}
    else                                                {printf("TESTING ERROR FAILD");}
}/* test_isAmountAvailable */

static void test_saveTransaction (void)
{
     /*Create a new card struct*/
    ST_transaction_t *transData;
    /* Alloocating Memory for the card */
    transData = (ST_transaction_t *) malloc(sizeof(ST_transaction_t));

    getCardPAN(&transData->cardHolderData);
    transData->transState = APPROVED;

    /* declare the function  */
    int error = saveTransaction(transData);

    printf("PAN CARD DATA : %s\n", transData->cardHolderData.primaryAccountNumber);

    printf("PAN CARD DATA IN DB : %s\n", globalTransactionsDB[0].cardHolderData.primaryAccountNumber);

    printf("State: %d\n", globalTransactionsDB[0].transState);


    /* Check if there error or not */
    if (error == SERVER_OK)                             {printf("ERROR TYPE: SERVER_OK");}
    else if (error == ACCOUNT_NOT_FOUND)                {printf("ERROR TYPE: ACCOUNT_NOT_FOUND");}
    else                                                {printf("TESTING ERROR FAILD");}
}/* test_isAmountAvailable */

//static void test_getTransaction (void);

/*
int main(void)
{
    test_saveTransaction();
    return 0;
}
*/