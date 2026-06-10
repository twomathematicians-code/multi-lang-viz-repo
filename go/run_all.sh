#!/bin/bash
set -e
export PATH="/home/z/my-project/tools/go/bin:$PATH"
cd "$(dirname "$0")"
echo "=== Running Go Charts ==="
go run main.go
echo ""
echo "=== Done ==="
