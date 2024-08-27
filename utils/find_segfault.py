import subprocess

def run_binary(binary_path, input_data):
    try:
        # Execute the binary with the provided input and capture the output and errors
        process = subprocess.run(binary_path, input=input_data, capture_output=True, text=True)
        return process.returncode, process.stdout, process.stderr
    except Exception as e:
        return None, str(e), None

def find_segfault(binary_path):
    input_length = 1
    while True:
        # Create a string of 'A's with the current length
        input_data = 'A' * input_length
        
        # Run the binary with the input data
        returncode, stdout, stderr = run_binary(binary_path, input_data)
        
        # If returncode is negative, it indicates a crash (e.g., segmentation fault)
        if returncode is not None and returncode < 0:
            print(f"Segmentation fault at input length: {input_length}")
            print(f"Return code: {returncode}, stderr: {stderr}")
            break
        elif returncode is None:
            print(f"Failed to run the binary: {stdout}")
            break
        
        # Increment input length for the next iteration
        input_length += 1

# Remplacez par le chemin du binaire à tester
if __name__ == "__main__":
    from sys import argv, exit
    if len(argv) != 2:
        exit()
    find_segfault(argv[1])
