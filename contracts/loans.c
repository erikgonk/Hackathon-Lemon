#include "../include/stylus_sdk.h"
#include "../stylus-sdk-c/include/storage.h"
#include "actions.h"

// Function to check if the user is eligible for a loan
ArbResult request_loan(uint8_t *input, size_t len)  {
	// Validate input length and extract necessary information
	if (len != 32)
		return _return_short_string(Failure, "Invalid address length");

	uint8_t *address = input;
	LoanPetition petition;

	// Retrieve the petition address
	ArbResult result = retrieve(address, &petition, sizeof(LoanPetition));
	if (result.status != Success)
		return _return_short_string(Failure, "Petition not found");

	// Validate the petition status
	if (petition.status == 0)
		return _return_short_string(Failure, "Petition is still pending");

	// Update the petition status
	petition.status = 2; // Status 2 = Loan granted

	// Store the updated petition
	store(petition.petitioner, &petition, sizeof(LoanPetition));

	return _return_short_string(Success, "Loan requested aproved");
}
