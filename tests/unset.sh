#!/bin/bash

OUT=output.txt

echo 'testing zero arguments'
(../unset > zero_arguments.txt)
diff zero_arguments.txt no_args.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
	echo 'your output: '
	cat zero_arguments.txt
	echo 'expected output: '
	cat no_args.txt
fi
rm ${OUT}

echo 'testing one argument that is not a variable'
(../unset HAI > zero_arguments.txt)
diff zero_arguments.txt no_args.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
	echo 'your output: '
	cat zero_arguments.txt
	echo 'expected output: '
	cat no_args.txt
fi
rm ${OUT}
