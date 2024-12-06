import { createPublicClient, http, parseAbi, stringToHex } from "viem"
import { arbitrumSepolia } from "viem/chains"
import "dotenv/config"

const ABI = parseAbi([
  "function hola_mundo() view returns (string)",
  "function calldata_len() view returns (uint256)",
  "function ping_pong(bytes32) view returns (string)",
  "function mi_balance() view returns (address)"
])

const client = createPublicClient({
  chain: arbitrumSepolia,
  transport: http(),
})

// https://sepolia.arbiscan.io/address/0x6a5a8573fe27c42ce960dcb7a19cf957f0e8f837
const CONTRACT_ADDRESS = "0x99ce05f8b7815b3d3f0f430609ef096cd44d81d5";

// hash
async function main() {
  const result = await client.readContract({
    abi: ABI,
    address: CONTRACT_ADDRESS,
    functionName: "mi_balance",
		account: "0xDa85E5A6e3c84037e9771C63Ba5b7fb3c7CEf14c",
    // args: [stringToHex("pong", { size: 32 })],
  })

  console.debug(`Contract: ${result}`)
}

main()

