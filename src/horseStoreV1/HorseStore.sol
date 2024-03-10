// SPDX-License-Identifier: GPL-3.0-only

pragma solidity ^0.8.20;

contract HorseStore {
    uint256 numberOfHorses;

    function updateHorseNumber(uint256 newNumberOfHorces) external {
        numberOfHorses = newNumberOfHorces;
    }

    function readNumberOfHorses() external view returns (uint256) {
        return numberOfHorses;
    }
}
