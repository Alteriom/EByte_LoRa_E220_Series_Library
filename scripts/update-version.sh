#!/bin/bash

# Update version script for Alteriom EByte LoRa E220 Library
# Usage: ./scripts/update-version.sh <new_version>

if [ $# -eq 0 ]; then
    echo "Usage: $0 <new_version>"
    echo "Example: $0 1.0.1"
    exit 1
fi

NEW_VERSION=$1

echo "Updating version to $NEW_VERSION..."

# Update library.properties
sed -i "s/version=.*/version=$NEW_VERSION/" library.properties

# Update library.json
sed -i "s/\"version\": \".*\"/\"version\": \"$NEW_VERSION\"/" library.json

# Update package.json
sed -i "s/\"version\": \".*\"/\"version\": \"$NEW_VERSION\"/" package.json

# Update LoRa_E220.h
sed -i "s/VERSION: .*/VERSION: $NEW_VERSION/" LoRa_E220.h

echo "Version updated to $NEW_VERSION in all files:"
echo "- library.properties"
echo "- library.json" 
echo "- package.json"
echo "- LoRa_E220.h"

echo ""
echo "Next steps:"
echo "1. Update CHANGELOG.md with new version details"
echo "2. Commit changes: git add . && git commit -m 'Bump version to v$NEW_VERSION'"
echo "3. Create tag: git tag -a v$NEW_VERSION -m 'Release v$NEW_VERSION'"
echo "4. Push: git push origin main --tags"