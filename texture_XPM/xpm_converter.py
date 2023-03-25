import os

INPUT_FILENAME = "test"
OUTPUT_FILENAME = "output"
LINE_LENGTH = 32
NUM_LINES = 32
NEW_LINE_LENGTH = 64
NEW_NUM_LINES = 64

if not os.path.isfile(INPUT_FILENAME):
	print("Error: input file {} not found".format(INPUT_FILENAME))
	exit(1)

with open(INPUT_FILENAME, "r") as input_file, open(OUTPUT_FILENAME, "w") as output_file:
	for line in input_file:
		# Remove newline character at end of line
		line = line.rstrip()

		# Extend the line to NEW_LINE_LENGTH by repeating each character not if if the char is a double quote or a comma
		new_line = ""
		for char in line:
			if char == '"' or char == ',':
				new_line += char
			else:
				new_line += char * 2

		# Write the extended line to the output file twice to create 64 lines
		for i in range(2):
			output_file.write(new_line + "\n")

	# Copy the contents of the input file to the output file for the remaining lines
	for line in input_file:
		output_file.write(line)
