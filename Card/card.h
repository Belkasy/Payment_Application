/**
 * @name            card.c
 * @def             part of pyment system project
 * @version         v1.0
 * @authors         Abdelrahman Belkasy
 * @date            16 August 2022
*/
#ifndef _CARD_H
#define _CARD_H
/*
----------------------------------------------------------------------------------------------------
!-                                          SET PARAMETERS
----------------------------------------------------------------------------------------------------
*/

#define NAME_MAX_SIZE   24
#define NAME_MIN_SIZE   20

#define DATE_SIZE   5

#define PAN_MAX_SIZE    19
#define PAN_MIN_SIZE    16


/*
----------------------------------------------------------------------------------------------------
!-                                         Typedefs
----------------------------------------------------------------------------------------------------
*/

#pragma pack(1)
typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
    CARD_OK, 
    WRONG_NAME, 
    WRONG_EXP_DATE, 
    WRONG_PAN
}EN_cardError_t;
/*
----------------------------------------------------------------------------------------------------
!-                                      Fuctions Prototypes
----------------------------------------------------------------------------------------------------
*/
EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);

#endif /* _CARD_H */