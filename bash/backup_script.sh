#!/bin/bash

# Check if the number of arguments passed is less than 1
if [ $# -lt 2 ]; then
    echo "Usage: $0 <source_path> <destination_path> [-c|--compression <compression_level>]"
    exit 1
fi

# This flag specifies whether the compression level has been entered or not. 
flg=0
# Check if the first positional argument is a directory
if [ -d "$1" ]; then
    # Check if the second argument is a directory
    if [ -d "$2" ]; then
        # Check if the third argument is -c
        if [ "$3" == "-c" ] || [ "$3" == "--compression" ];  then
            # Check if the compression level is provided
            if [ -z "$4" ]; then
                echo "Error: Compression level is missing."
                exit 1
            fi
            
            # Check if the compression level is an integer between 1 and 9
            if ! [[ "$4" =~ ^[1-9]$|^1[0-9]$|^20$ ]]; then
                echo "Error: Compression level must be an integer between 1 and 9."
                exit 1
            fi
            flg=1
        fi
    else
        # Create destination directory if it doesn't exist
        mkdir -p "$2"
    fi
else
    echo "The argument $1 is not a directory or does not exist."
fi

# Get current date
current_date=$(date +"%Y-%m-%d")

# Generate backup filename
backup_filename="${current_date}_$(basename "$1").zip"
backup_filepath="$2/$backup_filename"

num_dic=$(find "$1" -type d | wc -l)
num_file=$(find "$1" -type f | wc -l)

# Store pwd and change directory to source folder
pwd=$(pwd)
cd $(realpath $1)
cd ..
# Extract the last part of the path from $1
directory_name=$(basename "$1")

# Record start time
START_TIME=$(date -u '+%H:%M:%S UTC')

# Execute backup
if [ $flg -eq 0 ]; then
    eval "zip -r $backup_filepath $directory_name"
else
    eval "zip -r -$4 $backup_filepath $directory_name"
fi

# Record end time
END_TIME=$(date -u '+%H:%M:%S UTC')

# Change dirctory to last directory 
cd $pwd

# Calculate duration
START_SECONDS=$(date -u -d "$START_TIME" '+%s')
END_SECONDS=$(date -u -d "$END_TIME" '+%s')
DURATION_SECONDS=$((END_SECONDS - START_SECONDS))
DURATION_MINUTES=$((DURATION_SECONDS / 60))
DURATION_SECONDS=$((DURATION_SECONDS % 60))

# Generate log
log_file="$2/backup_log.txt"
echo "$log_file"
echo "Backup Log Report" > "$log_file"
echo -e "\nDate: $(date '+%Y-%m-%d')" >> "$log_file"
echo "Time: $START_TIME" >> "$log_file"
echo -e "\nMachine Information:" >> "$log_file"
echo "$(uname -a)" >> "$log_file"
echo -e "\nBackup Details:" >> "$log_file"
echo "Source Path: $(realpath "$1")" >> "$log_file"
echo "Destination Path: $(realpath $backup_filepath)" >> "$log_file"
if [ $flg -eq 0 ]; then
    echo "Compression Level: 1" >> "$log_file"
else
    echo "Compression Level: $4" >> "$log_file"
fi
echo "Files Backed Up: $num_file" >> "$log_file"
echo "Directories Backed Up: $num_dic" >> "$log_file"
echo -e "\nBackup Summary:" >> "$log_file"
echo "Start Time: $START_TIME" >> "$log_file"
echo "End Time: $END_TIME" >> "$log_file"
echo "Total Duration: ${DURATION_MINUTES} minutes ${DURATION_SECONDS} seconds" >> "$log_file"

# Exit with success
exit 0
