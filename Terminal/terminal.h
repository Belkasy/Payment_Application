/**
 * @name            terminal.h
 * @def             part of pyment system project - FWD
 * @version         v1.0
 * @authors         Abdelrahman Belkasy
 * @date            19 August 2022
*/
#ifndef _TERMINAL_H
#define _TERMINAL_H

/*
----------------------------------------------------------------------------------------------------
!-                                          SET PARAMETERS
----------------------------------------------------------------------------------------------------
*/
#define TRANSACTION_DATE_MAX_SIZE 10
/*
----------------------------------------------------------------------------------------------------
!-                                        Structurs & Enums
----------------------------------------------------------------------------------------------------
*/

#pragma pack(1)
typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
    TERMINAL_OK, 
    WRONG_DATE, 
    EXPIRED_CARD, 
    INVALID_CARD, 
    INVALID_AMOUNT, 
    EXCEED_MAX_AMOUNT, 
    INVALID_MAX_AMOUNT
}EN_terminalError_t ;

/*
----------------------------------------------------------------------------------------------------
!-                                      Fuctions Prototypes
----------------------------------------------------------------------------------------------------
*/

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData);

//EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData);


#endif /* _TERMINAL_H */