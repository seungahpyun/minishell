#!/bin/bash

OUT=output.txt

echo 'testing zero arguments'
(../pwd > zero_arguments.txt)
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

echo 'testing -L option'
(../pwd -L > L_option.txt)
diff L_option.txt L.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
	echo 'your output: '
	cat L_option.txt
	echo 'expected output: '
	cat L.txt
fi
rm ${OUT}

echo 'testing -P option'
(../pwd -P > P_option.txt)
diff P_option.txt P.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
	echo 'your output: '
	cat P_option.txt
	echo 'expected output: '
	cat P.txt
fi
rm ${OUT}
