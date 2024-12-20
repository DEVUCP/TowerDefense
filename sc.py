import os
import re
import sys

# Function to convert snake_case to camelCase
def snake_to_camel(name: str) -> str:
    parts = name.split('_')
    return parts[0] + ''.join(word.capitalize() for word in parts[1:])

# Function to process a C++ file and convert snake_case to camelCase
def process_cpp_file(filename: str):
    # Check if the filename is an absolute path
    if not os.path.isabs(filename):
        filename = os.path.join(os.getcwd(), filename)  # Convert to absolute path if relative
    
    print(f"Processing file: {filename}")  # Debugging line to check the path
    
    if not os.path.isfile(filename):
        print(f"Error: The file '{filename}' does not exist.")
        return

    # Read the content of the file
    with open(filename, 'r', encoding='utf-8') as file:
        content = file.read()

    # Regular expression patterns to detect function names and parameters
    def convert_snake_case(match):
        name = match.group(1)
        # Only convert names that are in snake_case and not part of types
        if name.islower() and not name.startswith("std::") and not name[0].isupper():
            return snake_to_camel(name)
        return name

    # Regex pattern for function signatures and variables in snake_case (including parameters)
    function_pattern = r'([a-z_][a-z0-9_]*)\s*(?=\()'  # Detect function/variable names
    parameter_pattern = r'([a-z_][a-z0-9_]*)\s*(?=\s*[,)\[])'  # Detect parameter names
    
    # 1. Split content by lines to handle #include separately
    lines = content.splitlines()
    modified_lines = []

    for line in lines:
        # Skip lines with #include or std::, just append them as-is
        if line.strip().startswith("#include") or "std::" in line:
            modified_lines.append(line)
        else:
            # Convert function names and parameters to camelCase
            line = re.sub(function_pattern, convert_snake_case, line)  # Function names
            line = re.sub(parameter_pattern, convert_snake_case, line)  # Function parameters
            modified_lines.append(line)
    
    # Join the modified lines back into content
    modified_content = "\n".join(modified_lines)
    
    # Extract the directory, filename (without extension), and extension from the original filename
    directory = os.path.dirname(filename)
    filename_without_ext, extension = os.path.splitext(os.path.basename(filename))

    # Construct the new filename as "filename1" with the same extension
    new_filename = os.path.join(directory, filename_without_ext + "1" + extension)

    # Save the modified content to the new file
    with open(new_filename, 'w', encoding='utf-8') as new_file:
        new_file.write(modified_content)
    
    print(f"File processed and saved as {new_filename}")

# Run the function with the filename provided as a command-line argument
if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 script.py filename.cpp")
    else:
        filename = sys.argv[1]
        try:
            process_cpp_file(filename)
        except FileNotFoundError:
            print(f"Error: The file '{filename}' was not found.")
        except Exception as e:
            print(f"An error occurred: {e}")
