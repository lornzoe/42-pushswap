#!/bin/bash

# Configuration: Update these paths if necessary
PUSH_SWAP="./push_swap"
CHECKER_OS="./checker_linux" # The official 42 checker
CHECKER_BONUS="./checker"    # Your bonus executable

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

# Function to run a single test
test_stack() {
    ARG="$@"
    
    # Get the instructions from your push_swap
    INSTRUCTIONS=$($PUSH_SWAP $ARG)
    
    # Get results from both checkers
    RES_OS=$(echo "$INSTRUCTIONS" | $CHECKER_OS $ARG 2>&1)
    RES_BONUS=$(echo "$INSTRUCTIONS" | $CHECKER_BONUS $ARG 2>&1)
    
    if [ "$RES_OS" == "$RES_BONUS" ]; then
        echo -e "${GREEN}[PASS]${NC} Stack: [$ARG]"
    else
        echo -e "${RED}[FAIL]${NC} Stack: [$ARG]"
        echo -e "  Expected: $RES_OS"
        echo -e "  Got     : $RES_BONUS"
    fi
}

echo "--- Starting push_swap Checker Comparison ---"

# 1. Test basic sorted stack
test_stack "1 2 3"

# 2. Test simple unsorted stack
test_stack "3 1 2"

# 3. Test Error handling (Duplicate)
test_stack "1 2 2"

# 4. Test Error handling (Non-numeric)
test_stack "1 2 cat"

# 5. Test Random Stacks (shuf requires coreutils)
for i in {1..5}
do
    RANDOM_STACK=$(shuf -i 1-100 -n 10 | tr '\n' ' ')
    test_stack $RANDOM_STACK
done