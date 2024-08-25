import subprocess

# Make sure the autograder is in the same directory as hw1.c
FILE_NAME = "part1"

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
		(1, "invalid", "./binarytodec {binary string} {1 for signed, 0 for unsigned}"),
		(2, "3", "./binarytodec {binary string} {1 for signed, 0 for unsigned}"),

		(3, "123123 1", "invalid binary string"),
		(4, "111 0", "7"),

		(5, "11111111 1", "-1"),
        (6, "11111111 0", "255"),
		(7, "111111111111111111111111111111111111111111111111111111111111111 1", "-1"),
		(8, "000000000000000000000000000000000000000000000000000000000000001 0", "1"),
		(9, "10 2", "./binarytodec {binary string} {1 for signed, 0 for unsigned}"),
		(10, "12345 0", "invalid binary string")
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
