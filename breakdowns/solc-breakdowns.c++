// 6080604052 348015600e575f80fd5b5060a58061001b5f395ff3fe6080604052348015600e575f80fd5b50600436106030575f3560e01c8063cdfead2e146034578063e026c017146045575b5f80fd5b6043603f3660046059565b5f55565b005b5f5460405190815260200160405180910390f35b5f602082840312156068575f80fd5b503591905056fea2646970667358fe1220383afe66001b4fa9cd29c5fefefefe8038fefefefefe159cfe14fefefefe841164736f6c63430008170033

// 3 sections:
// 1. Contract creation code
// 2. Runtime code
// 3. Metadata

// 1. Contract creation code
PUSH1 0x80              // [0x80]
PUSH1 0x40              // [0x40, 0x80]
MSTORE                  // []               // Memory 0x40 -> 0x80

// If someone sent value with this call - revert!
// Otherwise, jump, to continue execution
CALLVALUE               // [msg.value]
DUP1                    // [msg.value, msg.value]
ISZERO                  // [msg.value == 0, msg.value]
PUSH1 0x0e              // [0x0e, msg.value == 0, msg.value]
JUMPI                   // [msg.value]
PUSH0                   // [0x00, msg.value]
DUP1                    // [0x00, 0x00, msg.value]
REVERT                  // [msg.value]

// Jumpdest if msg.value == 0
JUMPDEST                // [msg.value]
POP                     // []
PUSH1 0xa5              // [0xa5]
DUP1                    // [0xa5, 0xa5]
PUSH2 0x001b            // [0x001b, 0xa5, 0xa5]
PUSH0                   // [0x00, 0x001b, 0xa5, 0xa5]
CODECOPY                // [0xa5]                       // Memory [runtime code]
PUSH0                   // [0x00, 0xa5]
RETURN                  // []
INVALID                 // []

// 2. Runtime code
// Entry point for all calls
// free memory pointer
PUSH1 0x80
PUSH1 0x40
MSTORE

// Checking for msg.value and if given - reverting
CALLVALUE               // [msg.value]
DUP1                    // [msg.value, msg.value]
ISZERO                  // [msg.value == 0, msg.value]
PUSH1 0x0e              // [0x0e, msg.value == 0, msg.value]
JUMPI                   // [msg.value]
// if msg.value == 0 jump to jumpdest
PUSH0                   // [0x00, msg.value]
DUP1                    // [0x00, 0x00, msg.value]
REVERT                  // [msg.value]

// This is checking if there is enough calldata for a function selector
JUMPDEST                // [msg.value]
POP                     // []
PUSH1 0x04              // [0x04]
CALLDATASIZE            // [calldatasize, 0x04]
LT                      // [calldatasize < 0x04]
PUSH1 0x30              // [0x30, calldatasize < 0x04]
JUMPI                   // []
// if calldatasize < 0x04 jump to jumpdest at 0x30 (calldata_jump)

// Function dispatching in solidity
PUSH0                   // [0x00]
CALLDATALOAD            // [32 bytes of calldata]
PUSH1 0xe0              // [0xe0, 32 bytes of calldata]
SHR                     // [calldata[0:4]] // func_selector

// function dispatching for setNumberOfHorses
DUP1                    // [func_selector, func_selector]
PUSH4 0xcdfead2e        // [0xcdfead2e, func_selector, func_selector]
EQ                      // [func_selector == 0xcdfead2e, func_selector]
PUSH1 0x34              // [0x34, func_selector == 0xcdfead2e, func_selector]
JUMPI                   // [func_selector]
// if func_selector == 0xcdfead2e -> set_number_of_horses

// function dispatching for readNumberOfHorses
DUP1                    // [func_selector, func_selector]
PUSH4 0xe026c017        // [0xe026c017, func_selector, func_selector]
EQ                      // [func_selector == 0xe026c017, func_selector]
PUSH1 0x45              // [0x45, func_selector == 0xe026c017, func_selector]
JUMPI                   // [func_selector]
// if func_selector == 0xe026c017 -> read_number_of_horses

// calldata_jump dest
JUMPDEST                // []
PUSH0                   // [0x00]
DUP1                    // [0x00, 0x00]
REVERT                  // []

// updateHorseNumber jump dest 1
// Setup jumping program counters in the stack
JUMPDEST                // [func_selector]
PUSH1 0x43              // [0x43, func_selector]
PUSH1 0x3f              // [0x3f, 0x43, func_selector]
CALLDATASIZE            // [calldatasize, 0x3f, 0x43, func_selector]
PUSH1 0x04              // [0x04, calldatasize, 0x3f, 0x43, func_selector]
PUSH1 0x59              // [0x59, 0x04, calldatasize, 0x3f, 0x43, func_selector]
JUMP                    // [0x04, calldatasize, 0x3f, 0x43, func_selector]

// Jump dest 4
JUMPDEST                // [calldata (of numberToUpdate), 0x43, func_selector]
PUSH0                   // [0x00, calldata (of numberToUpdate), 0x43, func_selector]
SSTORE                  // [0x43, func_selector]
JUMP                    // [func_selector]
// Jump to jump dest 5

// Jump dest 5
JUMPDEST                // [func_selector]
STOP                    // [func_selector]

// readNumberOfHorses jump dest 1
JUMPDEST                // [func_selector]
PUSH0                   // [0x00, func_selector]
SLOAD                   // [number_of_horses, func_selector]
PUSH1 0x40              // [0x40, number_of_horses, func_selector]
MLOAD                   // [0x80, number_of_horses, func_selector]           // Memory [0x40: 0x80] (free memory pointer)
SWAP1                   // [number_of_horses, 0x80, func_selector]
DUP2                    // [0x80, number_of_horses, 0x80, func_selector]
MSTORE                  // [0x80, func_selector]                            // Memory 0x80: number_of_horses
PUSH1 0x20              // [0x20, 0x80, func_selector]
ADD                     // [0xa0, func_selector]
PUSH1 0x40              // [0x40, 0xa0, func_selector]
MLOAD                   // [0x80, 0xa0, func_selector]
DUP1                    // [0x80, 0x80, 0xa0, func_selector]
SWAP2                   // [0xa0, 0x80, 0x80, func_selector]
SUB                     // [0xa0 - 0x80, 0x80, func_selector]
SWAP1                   // [0x80, 0xa0 - 0x80, func_selector]
// Return a value of size 32 bytes, that`s lacated at position 0x80 in memory
RETURN                  // [func_selector]

// updateHorseNumber jump dest 2
// Check to see if there is a value to update horse number to
JUMPDEST                // [0x04, calldatasize, 0x3f, 0x43, func_selector]
PUSH0                   // [0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
PUSH1 0x20              // [0x20, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
DUP3                    // [0x04, 0x20, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
DUP5                    // [calldatasize, 0x04, 0x20, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
SUB                     // [calldatasize - 0x04, 0x20, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
// is there more data then just the funciton selector?
SLT                     // [calldatasize - 0x04 < 0x20, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
ISZERO                  // [more_calldata, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
PUSH1 0x68              // [0x68, more_calldata, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
JUMPI                   // [0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
// Jump to dest 3 if there is more calldata then func_selector + 0x20

// revert is there isn`t enough calldata
PUSH0                   // [0x00, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
DUP1                    // [0x00, 0x00, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
REVERT                  // [0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]

// updateHorseNumber jump dest 3
// Grab calldata for updating horse number
JUMPDEST                // [0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
POP                     // [0x04, calldatasize, 0x3f, 0x43, func_selector]
CALLDATALOAD            // [calldata (of numberToUpdate), calldatasize, 0x3f, 0x43, func_selector]
SWAP2                   // [0x3f, calldatasize, calldata (of numberToUpdate), 0x43, func_selector]
SWAP1                   // [calldatasize, 0x3f, calldata (of numberToUpdate), 0x3f, 0x43, func_selector]
POP                     // [0x3f, calldata (of numberToUpdate), 0x3f, 0x43, func_selector]
JUMP                    // [calldata (of numberToUpdate), 0x3f, 0x43, func_selector]
// jump to dest 4

// 3. Metadata
INVALID
LOG2
PUSH5 0x6970667358
INVALID
SLT
SHA3
CODESIZE
GASPRICE
INVALID
PUSH7 0x001b4fa9cd29c5
INVALID
INVALID
INVALID
INVALID
DUP1
CODESIZE
INVALID
INVALID
INVALID
INVALID
INVALID
ISZERO
SWAP13
INVALID
EQ
INVALID
INVALID
INVALID
INVALID
DUP5
GT
PUSH5 0x736f6c6343
STOP
ADDMOD
OR
STOP
CALLER