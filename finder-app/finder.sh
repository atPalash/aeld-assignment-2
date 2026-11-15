
#!/bin/bash

path="$1"
text="$2"

if [ -z "$path" ] || [ -z "$text" ]; then
    echo "Usage: $0 <directory> <search_string>"
    exit 1
fi

if [ ! -d "$path" ]; then
    echo "Error: $path is not a directory."
    exit 1
fi

# Count all regular files recursively
num_files=$(find "$path" -type f | wc -l)

# Count matching lines recursively
num_matching_lines=$(grep -r -F -o "$text" "$path" | wc -l)

echo "The number of files are $num_files and the number of matching lines are $num_matching_lines"
