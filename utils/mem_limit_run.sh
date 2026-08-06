#!/usr/bin/bash

# Verify we have at least a limit and a command
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <limit> <command> [arguments...]"
    echo "Example: $0 2G ./program --verbose"
    exit 1
fi

# Grab the first argument as the memory limit
MEMORY_LIMIT="$1"

# Shift the arguments array down by 1 (removes the limit, keeps the command + flags)
shift

# Execute the command with systemd-run
# MemoryMax takes the variable dynamically
# MemorySwapMax=0 ensures an instant crash without swapping
systemd-run --user --scope -p MemoryMax="$MEMORY_LIMIT" -p MemorySwapMax=0 "$@"
