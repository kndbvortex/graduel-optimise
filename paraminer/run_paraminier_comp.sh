#!/bin/bash

# Define your dataset and filename
filename=$(cat filename.txt)
filename_without_ext=$(cat filename.txt  | cut -d '/' -f 4-4 | grep '[A-Za-z0-9_]*' | cut -d '.' -f 1-1)

if [ "$1" ]; then
    filename=$1
    filename_without_ext=$(cat filename.txt  | cut -d '/' -f 6-6 | grep '[A-Za-z0-9_]*' | cut -d '.' -f 1-1)
fi


# Create output directories if not exist
mkdir -p results

# Function to match the results from the output text
function match_result() {
    local text="$1"
    local result_dict_time="$2"
    local result_dict_patterns="$3"
    local result_dict_candidates="$4"

    time=$(echo "$text" | grep -oP '^\d+ms' | grep -oP '\d+')
    patterns=$(echo "$text" |  grep -oP "\d+ patterns" | grep -oP "\d+")

    echo "$time,$patterns" >> "$result_dict_time"
}

# Initialize files to store results
grite_results_file="results/paraminer_${filename_without_ext%.*}.csv"
test_results_file="results/test_paraminer_${filename_without_ext%.*}.csv"

echo "time,patterns" > "$grite_results_file"
echo "time,patterns" > "$test_results_file"

# Define percents for iterations
percents=(0.3 0.5 0.7 0.8)

# Loop over percents and run the Python scripts
for percent in "${percents[@]}"; do

    # Run the Python scripts
    echo  "Grite seuil=${percent}"
    $(paraminer-1.0-all_type_of_files/src/paraminer_graduals "$filename"  "$percent" -t 10  > para.txt) &

    echo  "Test seuil=${percent}"
    $(paraminer-1.0/src/paraminer_graduals "$filename"  "$percent"  > modif_para.txt -t 10) &

    wait
    # Parse the outputs and append results
    grite_output=$(cat para.txt)
    test_output=$(cat modif_para.txt)
    echo "Initial : ${grite_output}"
    echo "Test : ${test_output}"
    match_result "$grite_output" "$grite_results_file"
    match_result "$test_output" "$test_results_file"
done

# Convert CSV to Excel using xlsx2csv or other utility (this is optional)
# You can install xlsx2csv and convert CSV to Excel if needed
# xlsx2csv "$grite_results_file" "results/Grite_${filename%.*}.xlsx"
# xlsx2csv "$test_results_file" "results/test_${filename%.*}.xlsx"

echo "Results saved to $grite_results_file and $test_results_file"
