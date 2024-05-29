# Opus plugin for Stakewise vaults and Eigenlayer contracts

This repository contains code for the Opus plugin for stakewise and Eigenlayer
contracts.

## Implemented functions

### Stakewise

- burnOsToken(uint128 osTokenShares)
- claimExitedTokens(uint256 positionTicket, uint256 timestamp, uint256 exitQueueIndex)
- deposit(address receiver, address referer)
- enterExitQueue(uint256 shares, address receiver)
- liquidateOsToken(uint256 osTokenShares, address owner, address receiver)
- mintOsToken(address receiver, uint256 osTokenShares, address referrer)
- redeem(uint256 shares, address receiver)
- redeemOsToken(uint256 osTokenShares, address owner, address receiver)

### Eigenlayer
- function delegateTo(address _operator, IDelegationManager.SignatureWithExpiry memory _approverSignatureAndExpiry, bytes32 _approverSalt)

## Testing

For testing, we use the [Zemu](https://github.com/Zondax/zemu) for simulating a Ledger device,
to run the tests make sure your node version is `>21.7` and run:

```bash
npm install
npm run test
```

These will run all tests matching `tests/src/<*.test.js>`