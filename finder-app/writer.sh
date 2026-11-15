#!/bin/bash

path=$1
text=$2

if [ -z "$path" ] || [ -z "$text" ]; then
    echo "Usage: $0 <file_path> <text_to_search>"
    exit 1
fi

# Create parent directories if they don't exist
mkdir -p "$(dirname "$path")"
cat > "$path" << EOF
$text
EOF