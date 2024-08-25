#!/usr/bin/python3

import subprocess

# Make sure the autograder is in the same directory as hw2.c
FILE_NAME = "part4"

def compile_program():
    compile_result = subprocess.run(["gcc", "-fsanitize=address", "-Wall", FILE_NAME+".c", "-o", FILE_NAME], capture_output=True, text=True)
    if compile_result.returncode != 0:
        print("Compilation failed:", compile_result.stderr)
        return False
    return True

def run_test(test_number, test_input, expected_output):
    process = subprocess.Popen(["./"+FILE_NAME, str(test_input)], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    stdout, stderr = process.communicate()

    print(f"Test Case {test_number}: Input = {test_input}", end=" ")

    if stdout.strip() == expected_output.strip() or stderr.strip() == expected_output.strip():
        print("✓ Passed")
        return True
    else:
        print("✗ Failed")
        print(f"   Expected: {expected_output}")
        print(f"   Got: {stdout.strip() if stdout != '' else stderr.strip()}")
        return False

def main():
    if not compile_program():
        return

    test_cases = [
        (1, 292827483647, "0"),
        (2, -1, "0"),
        (3, 0, "-1"),
        (5, 700, "2"),
		(6, 1923048, "3"),
		(7, -937234822, "1"),
        (8, 96, "5"),
        (9, 3072, "10"),
        (10, 25853952, "15"),
        (11, 11075584, "16"),
        (12, 3221225472, "30"),
        (13, -2147483648 , "31"),
        (14, -2146435072, "20"),
        # Add more test cases as needed
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
