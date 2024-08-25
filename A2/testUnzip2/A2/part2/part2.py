import subprocess

# Make sure the autograder is in the same directory as hw1.c
FILE_NAME = "part2"

def compile_program():
	compile_result = subprocess.run(["gcc", "-fsanitize=address", FILE_NAME+".c", "-o", FILE_NAME], capture_output=True, text=True)
	if compile_result.returncode != 0:
		print("Compilation failed:", compile_result.stderr)
		return False
	return True

def run_test(test_number, test_input, expected_output):
    process = subprocess.Popen(["./"+FILE_NAME, *(test_input.split(' '))], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    stdout, stderr = process.communicate()

    print(f"Test Case {test_number}: Input = {test_input}, stderr: {stderr.strip()}, Output: {expected_output.strip()}", end=" ")

    if stdout.strip() == expected_output.strip() or stderr.strip() == expected_output.strip():
        print("✓ Passed")
        return True
    else:
        print("✗ Failed")
        print(f"   Expected Output: {expected_output.strip()}")
        print(f"   Actual Output: {stdout.strip() if stdout != '' else stderr.strip()}")
        return False

def main():
	if not compile_program():
		return

	test_cases = [
        (1, "0000000000000000", "This value is denormalized"),
        (2, "0000010000000000", "This value is normalized"),
        (3, "0111110000000000", "This value is a special case"),
        (4, "11010101", "must be 16 bits"),
        (5, "gentoo", "invalid format"),
	(6, "10000011111111111", "must be 16 bits"),
	(7, "1111101111111111", "This value is normalized"),
	(8, "1111111000000000", "This value is a special case"),
	(9, "1000000000000000", "This value is denormalized")
		# Add more test cases as needed
		# NOTE: There is only 1 check for validation...Consider testing other validation that you have implemented
	]

	all_passed = True
	for test_number, test_input, expected_output in test_cases:
		if not run_test(test_number, test_input, expected_output):
			all_passed = False

	if all_passed:
		print("All tests passed successfully!")
	else:
		print("Some tests failed.")

if __name__ == "__main__":
	main()
