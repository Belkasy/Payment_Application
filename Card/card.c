/**
 * @name            card.c
 * @def             part of pyment system project
 * @version         v1.0
 * @authors         Abdelrahman Belkasy
 * @date            16 August 2022
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../STD_LIB.h"
#include "card.h"
/*
----------------------------------------------------------------------------------------------------
!-                                      Fuctions Implementation
----------------------------------------------------------------------------------------------------
**/
/** @defgroup card.c Card Implementation*/

/**
 * @brief Function to scan the Card Holder Name
 * @param ST_cardData_t
 * @return EN_carderror_t (Card Error State)
*/
EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    /* Get data from the console by user*/
    printf ("Please Enter Card's Holder Name: ");
    gets(cardData->cardHolderName);

    /* name data validation */
    if (strlen(cardData->cardHolderName) > (NAME_MAX_SIZE) || 
        strlen(cardData->cardHolderName) < (NAME_MIN_SIZE) ||
              (cardData->cardHolderName) ==     NULL       )
    {
        return WRONG_NAME;
    }
    else
    {
        return CARD_OK;
    } 
}/* getCardHolderName */

/**
 * @brief Function to scan the Card's Expiry Date "MM/YY"
 * @param ST_cardData_t
 * @return EN_carderror_t (Card Error State)
*/
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    /* Get data from the console by user*/
    printf ("Please Enter Card's Expiry Date \"MM/YY\": ");
    gets(cardData->cardExpirationDate);

    /* Date data anf formating validation */
    if(     (strlen(cardData->cardExpirationDate) != (DATE_SIZE)  ) || 
            (      (cardData->cardExpirationDate) ==     NULL     ) ||
            (      (cardData->cardExpirationDate[2]) !=  '/'      )    )
    {
        return WRONG_EXP_DATE;
    }
    else
    {
        return CARD_OK;
    } 
} /* getCardExpiryDate */

/**
 * @brief Function to scan the Card's Primary Account Numbere
 * @param ST_cardData_t
 * @return EN_carderror_t (Card Error State)
*/
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    /* Get data from the console by user*/
    printf ("Please Enter Card's Primary Account Number : ");
    gets(cardData->primaryAccountNumber);

    /* PAN validation */
    if(     (strlen(cardData->primaryAccountNumber) > (PAN_MAX_SIZE)  ) || 
            (strlen(cardData->primaryAccountNumber) < (PAN_MIN_SIZE)  ) || 
            (      (cardData->primaryAccountNumber) ==     NULL       )   )
    {
        return WRONG_PAN;
    }
    else
    {
        return CARD_OK;
    } 
} /* getCardPAN */

/*
----------------------------------------------------------------------------------------------------
!-                                          Test Fuctions
----------------------------------------------------------------------------------------------------
*/
static void test_getCardHolerName(void)
{
    /*Create a new card struct*/
    ST_cardData_t *cardData;
    /* Alloocating Memory for the card */
    cardData = (ST_cardData_t *) malloc (sizeof (ST_cardData_t));

    /* declare the function  */
    int error = getCardHolderName(cardData);

    /* Check the function Print */
    printf("NAME: %s\n", cardData->cardHolderName);
    /* Check the length of the string */
    printf("Name String Length: %d\n", strlen(cardData->cardHolderName));

    /* Check if there error or not */
    if (error == CARD_OK)                    {printf("ERROR TYPE: CARD_OK");}
    else if (error == WRONG_NAME)       {printf("ERROR TYPE: WRONG_NAME");}
    else                                {printf("TESTING ERROR FAILD");}
}/* test_getCardExpiryDate */

static void test_getCardExpiryDate(void)
{
    /*Create a new card struct*/
    ST_cardData_t *cardData;
    /* Alloocating Memory for the card */
    cardData = (ST_cardData_t *) malloc (sizeof (ST_cardData_t));

    /* declare the function  */
    int error = getCardExpiryDate(cardData);

    /* Check the function Print */
    printf("DATE: %s\n", cardData->cardExpirationDate);
    /* Check the length of the string */
    printf("DATE String Length: %d\n", strlen(cardData->cardExpirationDate));

    /* Check if there error or not */
    if (error == CARD_OK)                    {printf("ERROR TYPE: CARD_OK");}
    else if (error == WRONG_EXP_DATE)   {printf("ERROR TYPE: WRONG_EXP_DATE");}
    else                                {printf("TESTING ERROR FAILD");}
}/* test_getCardExpiryDate */

static void test_getCardPAN(void)
{
    /*Create a new card struct*/
    ST_cardData_t *cardData;
    /* Alloocating Memory for the card */
    cardData = (ST_cardData_t *) malloc (sizeof (ST_cardData_t));

    /* declare the function  */
    int error = getCardPAN(cardData);

    /* Check the function Print */
    printf("PAN: %s\n", cardData->primaryAccountNumber);
    /* Check the length of the string */
    printf("PAN String Length: %d\n", strlen(cardData->primaryAccountNumber));

    /* Check if there error or not */
    if (error == CARD_OK)                    {printf("ERROR TYPE: CARD_OK");}
    else if (error == WRONG_PAN)        {printf("ERROR TYPE: WRONG_PAN");}
    else                                {printf("TESTING ERROR FAILD");}
}/* test_getCardExpiryDate */

/*
int main()
{
    test_getCardPAN();

    return 0;
}
*/