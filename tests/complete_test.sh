#!/bin/bash

# Compile minishell
make -C ../..

# Define colors
GREEN="\e[32m"
RED="\e[31m"
RESET="\e[0m"

STAT=0
TEST_FILES=(
	"bonus_tests.txt"
	"builtin_tests.txt"
	"extras_tests.txt"
	"pipes_tests.txt"
	# "redirects_tests.txt"
	"syntax_tests.txt"
	"wildcards_tests.txt"
)

chmod 000 ./test_files/invalid_permission
mkdir -p ./outfiles

for TEST_FILE in "${TEST_FILES[@]}"; do
	echo -e "\nRunning tests from: ${TEST_FILE}"

	while read -r TEST_CMD; do
		echo -e "Command: $TEST_CMD"

		# Run minishell and capture output
		OUT=$(echo -e "$TEST_CMD" | ../minishell | grep -v '^msh$ ' | grep -v '^exit$')
		BASH_OUT=$(echo -e "$TEST_CMD" | bash)

		# Check standard output
		if [ "$OUT" == "$BASH_OUT" ]; then
			echo -e "${GREEN}✅ Output matches${RESET}"
		else
			echo -e "${RED}❌ Output differs${RESET}"
			STAT=1
		fi

		# Run minishell and capture errors
		ERR=$(echo -e "$TEST_CMD" | ../minishell 2>&1 >/dev/null)
		BASH_ERR=$(echo -e "$TEST_CMD" | bash 2>&1 >/dev/null)

		# Check error output
		if [ "$ERR" == "$BASH_ERR" ]; then
			echo -e "${GREEN}✅ Error output matches${RESET}"
		else
			echo -e "${RED}❌ Error output differs${RESET}"
			STAT=1
		fi

		echo "--------------------------------"
	done < "$TEST_FILE"
done

# Cleanup
make fclean -C ../../..
chmod 644 ./test_files/invalid_permission
rm -rf ./outfiles

exit $STAT
