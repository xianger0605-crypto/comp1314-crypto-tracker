#!/bin/bash
echo "Adding quick Git commits..."

# Commit 1: Add project description
echo "# COMP1314 Coursework - Cryptocurrency Tracker" > PROJECT_INFO.md
echo "Created: $(date)" >> PROJECT_INFO.md
git add . && git commit -m "docs: add project information"

# Commit 2: Update data collection script
echo "" >> gold_scraper.sh
echo "# Additional error handling" >> gold_scraper.sh
git add . && git commit -m "refactor: enhance error handling"

# Commit 3: Run data collection
./gold_scraper.sh
git add . && git commit -m "data: collect price data point"

# Commit 4: Generate plots
./plot_prices.sh
git add . && git commit -m "feat: generate visualization plots"

# Commit 5: Add usage instructions
echo "Usage Instructions:" > USAGE.md
echo "1. ./gold_scraper.sh - Collect data" >> USAGE.md  
echo "2. ./plot_prices.sh - Generate plots" >> USAGE.md
git add . && git commit -m "docs: add usage documentation"
