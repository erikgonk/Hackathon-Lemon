#ifndef	ACTIONS_H
#define	ACTIONS_H

// Define petition data structure
typedef struct {
	uint8_t petitioner[32]; // User address
	uint8_t loan_amount[32];	// Loan amount requested
	uint32_t status;		// Status of the petition
} LoanPetition;

// Function prototypes.
ArbResult   post_petition(uint8_t *input, size_t len);
ArbResult   accept_petition(uint8_t *input, size_t len);
ArbResult   request_loan(uint8_t *input, size_t len);
ArbResult   repay_loan(uint8_t *input, size_t len);
ArbResult   calldata_len(uint8_t *input, size_t len);
ArbResult   mi_balance(uint8_t *input, size_t len); // ??? used????
ArbResult	retrieve(uint8_t *address, void *data, size_t size);
ArbResult	store(uint8_t *address, void *data, size_t size);

#endif	// ACTIONS_H
