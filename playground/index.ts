// Import necessary modules and functions from the 'viem' library and 'dotenv' for environment variable management
import { createPublicClient, http, parseAbi, stringToHex } from "viem"; // viem is used for interacting with Ethereum-like blockchains
import { arbitrumSepolia } from "viem/chains"; // Configuration for the Arbitrum Sepolia testnet
import "dotenv/config"; // Loads environment variables from a .env file

// Define the ABI (Application Binary Interface) for the smart contract
const ABI = parseAbi([
  "function hola_mundo() view returns (string)", // A function that returns a string (likely "Hello, World!" or similar)
  "function calldata_len() view returns (uint256)", // A function that returns the length of calldata (uint256)
  "function ping_pong(bytes32) view returns (string)", // A function that accepts a bytes32 input and returns a string
  "function mi_balance() view returns (address)", // A function that returns an address (likely related to account balance or ownership)
]);

// Create a public client for connecting to the blockchain
const client = createPublicClient({
  chain: arbitrumSepolia, // Specify the Arbitrum Sepolia testnet
  transport: http(), // Use HTTP as the transport method for blockchain communication
});

// Define the smart contract's address on the Arbitrum Sepolia testnet
// You can view this contract on the Arbiscan explorer: https://sepolia.arbiscan.io/address/0x6a5a8573fe27c42ce960dcb7a19cf957f0e8f837
const CONTRACT_ADDRESS = "0x99ce05f8b7815b3d3f0f430609ef096cd44d81d5";

// Main function to interact with the smart contract
async function main() {
  // Call the `mi_balance` function on the smart contract
  const result = await client.readContract({
    abi: ABI, // Pass the contract ABI to define callable functions
    address: CONTRACT_ADDRESS, // The smart contract's address
    functionName: "mi_balance", // Specify the function to call
    account: "0xDa85E5A6e3c84037e9771C63Ba5b7fb3c7CEf14c", // Pass the account address for implicit context (not used here directly)
    // args: [stringToHex("pong", { size: 32 })], // Example of passing arguments (commented out as `mi_balance` doesn't require args)
  });

  // Log the result of the function call to the console
  console.debug(`Contract: ${result}`);
}

// Call the main function to execute the script
main();