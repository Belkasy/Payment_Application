/**
 * @name            terminal.c
 * @def             part of pyment system project - FWD
 * @version         v1.0
 * @authors         Abdelrahman Belkasy
 * @date            19 August 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "../STD_LIB.h"
#include "..\Card\card.h"
#include "terminal.h"

/*
----------------------------------------------------------------------------------------------------
!-                                      Fuctions Implementation
----------------------------------------------------------------------------------------------------
*/
/**
 * @brief Function to scan the Card Holder Name
 * @param ST_terminalData_t *
 * @return EN_terminalError_t (Terminal Error State)
*/
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    /* Get Current Systen Clock */
    SYSTEMTIME CurrentTime;
    GetLocalTime(&CurrentTime);

    /* Formating the date and store in the trimData */
    sprintf(termData->transactionDate, "%.2d/%.2d/%.4d",CurrentTime.wDay,
                                                        CurrentTime.wMonth, 
                                                        CurrentTime.wYear   ) ;

    /* Date data anf formating validation */
    if(     (strlen(termData->transactionDate)   != (TRANSACTION_DATE_MAX_SIZE)   ) ||
            (      (termData->transactionDate)   ==  NULL                         ) ||
            (      (termData->transactionDate[2]) !=  '/'                         ) ||
            (      (termData->transactionDate[5]) !=  '/'                         )     )
    {
        return WRONG_DATE;
    }
    else
    {
        return TERMINAL_OK;
    } 
}/* getTransactionDate */

/**
 * @brief Function to Chek if the Card Expired
 * @param ST_cardData_t
 * @param ST_terminalData_t *
 * @return EN_terminalError_t (Terminal Error State)
*/
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
    /* Get expire Mounth and Year in integers for comparason */
    uint8_t expireMounth    = ((cardData.cardExpirationDate[0]-'0') *10) + (cardData.cardExpirationDate[1]-'0');
    uint8_t expireYear      = ((cardData.cardExpirationDate[3]-'0') *10) + (cardData.cardExpirationDate[4]-'0');
    
    /* Get current Mounth and Year in integers for comparason */
    uint8_t currentMounth   = ((termData.transactionDate[3]-'0') *10) + (termData.transactionDate[4]-'0');
    uint8_t currentYear     = ((termData.transactionDate[8]-'0') *10) + (termData.transactionDate[9]-'0');

    if (currentYear > expireYear)
    {
        return EXPIRED_CARD;
    }
    else if (currentYear == expireYear)
        {
            if (currentMounth > expireMounth)
            {
                return EXPIRED_CARD;
            }
        }
    return TERMINAL_OK;

}/* isCardExpired */

/**
 * @brief Function to scan the Transaction Amount
 * @param ST_terminalData_t *
 * @return EN_terminalError_t (Terminal Error State)
*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
        /* Get data from the console by user*/
    printf ("Please Enter Transaction Amount: ");
    scanf("%f",&termData->transAmount);

    /* name data validation */
    if (termData->transAmount <= 0)
    {
        termData->transAmount = 0;
        return INVALID_AMOUNT;
    }
    else
    {
        return TERMINAL_OK;
    } 
}/* getTransactionAmount */

/**
 * @brief Function to Set the Max Transaction Amount
 * @param ST_terminalData_t *
 * @return EN_terminalError_t (Terminal Error State)
*/
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
    printf ("Please Enter Max Transaction Amount: ");
    scanf("%f",&termData->maxTransAmount);
    
    /* name data validation */
    if (termData->maxTransAmount <= 0)
    {
        termData->maxTransAmount = 0;
        return INVALID_MAX_AMOUNT;
    }
    else
    {
        return TERMINAL_OK;
    } 
}/* setMaxAmount */

/**
 * @brief Function to Chek if the transaction amount Exeed the max amount
 * @param ST_terminalData_t *
 * @return EN_terminalError_t (Terminal Error State)
*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    if (termData->transAmount > termData->maxTransAmount)
    {
        return EXCEED_MAX_AMOUNT;
    }
    else
    {
        return TERMINAL_OK;
    }
}/* isBelowMaxAmount */

/*
----------------------------------------------------------------------------------------------------
!-                                          Test Fuctions
----------------------------------------------------------------------------------------------------
*/
static void test_getTransactionDate(void)
{
    /*Create a new card struct*/
    ST_terminalData_t *termData;
    /* Alloocating Memory for the card */
    termData = (ST_terminalData_t *) malloc(sizeof(ST_terminalData_t));

    /* declare the function  */
    int error = getTransactionDate(termData);

    /* Check the function Arguments */
    printf("DATE: %s\n", termData->transactionDate);
    /* Check the length of the string */
    printf("Name String Length: %d\n", strlen(termData->transactionDate));

    /* Check if there error or not */
    if (error == TERMINAL_OK)                    {printf("ERROR TYPE: TERMINAL_OK");}
    else if (error == WRONG_DATE)       {printf("ERROR TYPE: WRONG_DATE");}
    else                                {printf("TESTING ERROR FAILD");}
}/* test_getTransactionDate */

static void test_isCardExpired(void)
{
    /*Create a new card struct*/
    ST_terminalData_t *termData;
    /* Alloocating Memory for the card */
    termData = (ST_terminalData_t *) malloc(sizeof(ST_terminalData_t));

    /*Create a new card struct*/
    ST_cardData_t *cardData;
    /* Alloocating Memory for the card */
    cardData = (ST_cardData_t *) malloc (sizeof (ST_cardData_t));

    /* declare the function  */
    getCardExpiryDate(cardData);
    getTransactionDate(termData);

    /* declare the function  */
    int error = isCardExpired(*cardData, *termData);

    /* Check the function Arguments */
    printf("EXPIRE DATE: %s\n", cardData->cardExpirationDate);
    printf("CURRENT DATE: %s\n", termData->transactionDate);
    

    /* Check if there error or not */
    if (error == TERMINAL_OK)           {printf("ERROR TYPE: TERMINAL_OK");}
    else if (error == EXPIRED_CARD)     {printf("ERROR TYPE: EXPIRED_CARD");}
    else                                {printf("TESTING ERROR FAILD");}
}/* test_getTransactionDate */

static void test_getTransactionAmount(void)
{
    /*Create a new card struct*/
    ST_terminalData_t *termData;
    /* Alloocating Memory for the card */
    termData = (ST_terminalData_t *) malloc(sizeof(ST_terminalData_t));

    /* declare the function  */
    int error = getTransactionAmount(termData);

    /* Check the function Arguments */
    printf("TRANSACTION AMOUNT: %.2f\n", termData->transAmount);

    /* Check if there error or not */
    if (error == TERMINAL_OK)                    {printf("ERROR TYPE: TERMINAL_OK");}
    else if (error == INVALID_AMOUNT)   {printf("ERROR TYPE: INVALID_AMOUNT");}
    else                                {printf("TESTING ERROR FAILD");}
}/* test_getTransactionDate */

static void test_setMaxAmount(void)
{
    /*Create a new card struct*/
    ST_terminalData_t *termData;
    /* Alloocating Memory for the card */
    termData = (ST_terminalData_t *) malloc(sizeof(ST_terminalData_t));

    /* declare the function  */
    int error = setMaxAmount(termData);

    /* Check the function Arguments */
    printf("MAX TRANSACTION AMOUNT: %.2f\n", termData->maxTransAmount);

    /* Check if there error or not */
    if (error == TERMINAL_OK)                         {printf("ERROR TYPE: TERMINAL_OK");}
    else if (error ==  INVALID_MAX_AMOUNT)   {printf("ERROR TYPE: INVALID_MAX_AMOUNT");}
    else                                     {printf("TESTING ERROR FAILD");}
}/* test_getTransactionDate */

static void test_isBelowMaxAmount(void)
{
    /*Create a new card struct*/
    ST_terminalData_t *termData;
    /* Alloocating Memory for the card */
    termData = (ST_terminalData_t *) malloc(sizeof(ST_terminalData_t));

    /* declare the function  */
    getTransactionAmount(termData);
    setMaxAmount(termData);
    int error = isBelowMaxAmount(termData);

    /* Check the function Arguments */
    printf("TRANSACTION AMOUNT: %f\n", termData->transAmount);
    printf("TRANSACTION MAX AMOUNT: %f\n", termData->transAmount);

    /* Check if there error or not */
    if (error == TERMINAL_OK)                        {printf("ERROR TYPE: TERMINAL_OK");}
    else if (error == EXCEED_MAX_AMOUNT)    {printf("ERROR TYPE: EXCEED_MAX_AMOUNT");}
    else                                    {printf("TESTING ERROR FAILD");}
}/* test_getTransactionDate */
/*
int main()
{
    test_isBelowMaxAmount();
    return 0;
}
*/