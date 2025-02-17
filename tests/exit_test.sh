#!/bin/bash

OUT=output.txt

echo 'testing zero arguments'
(../exit)
echo $? > zero_arguments.txt
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

echo 'testing one argument'
(../exit 4)
echo $? > one_argument.txt
diff one_argument.txt one.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
	echo 'your output: '
	cat one_argument.txt
	echo 'expected output: '
	cat one.txt
fi
rm ${OUT}

echo 'testing one argument'
(../exit " 4")
echo $? > one_argument.txt
diff one_argument.txt one.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
	echo 'your output: '
	cat one_argument.txt
	echo 'expected output: '
	cat one.txt
fi
rm ${OUT}

echo 'testing one argument'
(../exit "4 ")
echo $? > one_argument.txt
diff one_argument.txt one.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
	echo 'your output: '
	cat one_argument.txt
	echo 'expected output: '
	cat one.txt
fi
rm ${OUT}

echo 'testing two arguments'
(../exit 4 4 2> two_arguments.txt)
diff two_arguments.txt two_error.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
	echo 'your output: '
	cat two_arguments.txt
	echo 'expected output: '
	cat two_error.txt
fi
rm ${OUT}

echo 'testing non-numeric argument'
(../exit hei 2> non_numeric.txt)
diff non_numeric.txt non_num.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
	echo 'your output: '
	cat non_numeric.txt
	echo 'expected output: '
	cat non_num.txt
fi
rm ${OUT}
