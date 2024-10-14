
# Define your dataset and filename
filename=$(cat config.py | grep '^filename = ".*"' | cut -d '/' -f 6-6 | grep '[A-Za-z0-9_]*')

# Create output directories if not exist
mkdir -p results

# Function to match the results from the output text
function match_result() {
    local text="$1"
    local result_dict_time="$2"
    local result_dict_patterns="$3"
    local result_dict_candidates="$4"

    time=$(echo "$text" | grep -oP '\d+\.\d+ seconds' | grep -oP '\d+\.\d+')
    patterns=$(echo "$text" | grep -oP '\d+ Motifs Fréquent' | grep -oP '\d+')
    candidates=$(echo "$text" | grep -oP '\d+ nombre de candidats' | grep -oP '\d+')

    echo "$time,$patterns,$candidates" >> "$result_dict_time"
}

# Initialize files to store results
grite_results_file="results/Grite_${filename%.*}.csv"
test_results_file="results/test_${filename%.*}.csv"

echo "time,patterns,candidates" > "$grite_results_file"
echo "time,patterns,candidates" > "$test_results_file"

# Define percents for iterations
percents=(0.3 0.5 0.7 0.8)

# Loop over percents and run the Python scripts
for percent in "${percents[@]}"; do

    # Run the Python scripts
    echo  "Grite seuil=${percent}"
    $(python3 grite_from_scratch.py "$percent"  > grite_out_2.txt) &

    echo  "Test seuil=${percent}"
    $(python3 grite_column_pruning.py "$percent" > test_out_2.txt) &

    wait
    # Parse the outputs and append results
    grite_output=$(cat grite_out_2.txt)
    test_output=$(cat test_out_2.txt)
    echo "Grite : ${grite_output}"
    echo "Test : ${test_output}"
    match_result "$grite_output" "$grite_results_file"
    match_result "$test_output" "$test_results_file"
done

# Convert CSV to Excel using xlsx2csv or other utility (this is optional)
# You can install xlsx2csv and convert CSV to Excel if needed
# xlsx2csv "$grite_results_file" "results/Grite_${filename%.*}.xlsx"
# xlsx2csv "$test_results_file" "results/test_${filename%.*}.xlsx"

echo "Results saved to $grite_results_file and $test_results_file"