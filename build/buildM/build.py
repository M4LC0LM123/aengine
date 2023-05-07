import os

# Replace "/path/to/directory" with the path of the directory you want to open
directory_path = "/Documents/github/horrorGame/cpp/build/buildM"

# Replace "command_to_run" with the command you want to run in the Terminal
command = "cd Documents/github/horrorGame/cpp/build/buildM & ls"

# Open Terminal and navigate to the specified directory
os.system(f"open -a Terminal {directory_path}")

# Run the command in the Terminal window
os.system(f"osascript -e 'tell application \"Terminal\" to do script \"{command}\"'")
