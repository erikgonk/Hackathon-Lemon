#include "../include/stylus_sdk.h"
#include "../stylus-sdk-c/include/storage.h"
#include "actions.h"

// Function to store loan petition
ArbResult post_petition(uint8_t *input, size_t len) {
    // Validate input length and extract necessary information
    if (len < sizeof(uint8_t) + 32)
        return _return_short_string(Failure, "Invalid petition lenght");

	// Extract the user address (first 32 bytes)
    uint8_t *address = input;
	// Extract the loan amount (next 32 bytes)
    uint8_t *loan_amount = input +32; // Point to the loan amount in input

    // Create the petition structure
    LoanPetition petition;
    memcpy(petition.petitioner, address, 32);						// Copy the address into the petition
    memcpy(&petition.loan_amount, loan_amount, sizeof(uint8_t));	// Copy the loan amount into the petition
	petition.status = 0;											// Initialize the status to 0 (Pending)

    // Save petition to blockchain storage
    store(petition.petitioner, &petition, sizeof(LoanPetition));

    return _return_short_string(Success, "Pettition submited");
}

// Function to accept the petition and transition status
ArbResult accept_petition(uint8_t *input, size_t len) {
    if (len != 32)
        return _return_short_string(Failure, "Invalid address length");
    uint8_t *address = input;
    LoanPetition petition;

    // Retrieve the petition address
	ArbResult result = retrieve(address, &petition, sizeof(LoanPetition));

	if (result.status != Success)
		return _return_short_string(Failure, "Petition not found");

	// Validate the petition status ?????????
	if (petition.status != 0)
		return _return_short_string(Failure, "Petition already accepted");

	// Update the petition status
	petition.status = 1; // Status 1 = Petition accepted

	// Store the updated petition
	store(petition.petitioner, &petition, sizeof(LoanPetition));

	return _return_short_string(Success, "Petition accepted");
}
