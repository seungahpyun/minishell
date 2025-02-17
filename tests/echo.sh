#!/bin/bash

OUT=output.txt

echo 'testing zero arguments'
(../echo > zero_arguments.txt)
diff zero_arguments.txt error.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
fi
rm ${OUT}

echo 'testing one argument'
(../echo hello > one_argument.txt)
diff one_argument.txt 1.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
fi
rm ${OUT}

echo 'testing two arguments'
(../echo hi again > two_arguments.txt)
diff two_arguments.txt 2.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
fi
rm ${OUT}

echo 'testing string argument'
(../echo "this works" > string_argument.txt)
diff string_argument.txt str.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
fi
rm ${OUT}

echo 'testing -n without an argument'
(../echo -n > just_no_nl.txt)
diff just_no_nl.txt no_nl_error.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
fi
rm ${OUT}

echo 'testing -f(invalid option)'
(../echo -f > inv_opt.txt)
diff inv_opt.txt invalid_opt.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
	echo 'your output: '
	cat inv_opt.txt
	echo 'expected output: '
	cat invalid_opt.txt
fi
rm ${OUT}

echo 'testing -f(invalid option) with an argument'
(../echo -f hello > inv_opt_arg.txt)
diff inv_opt_arg.txt invalid_opt_arg.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
	echo 'your output: '
	cat inv_opt_arg.txt
	echo 'expected output: '
	cat invalid_opt_arg.txt
fi
rm ${OUT}

echo 'testing -ng without an argument'
(../echo -ng > inv_opt_2.txt)
diff inv_opt_2.txt invalid_opt_2.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
	echo 'your output: '
	cat inv_opt_2.txt
	echo 'expected output: '
	cat invalid_opt_2.txt
fi
rm ${OUT}

echo 'testing -nnnnn without an argument'
(../echo -nnnnn > just_no_nl.txt)
diff just_no_nl.txt no_nl_error.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
	echo 'your output: '
	cat just_no_nl.txt
	echo 'expected output: '
	cat no_nl_error.txt
fi
rm ${OUT}

echo 'testing four -n without an argument'
(../echo -n -n -n -n > just_no_nl.txt)
diff just_no_nl.txt no_nl_error.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
	echo 'your output: '
	cat just_no_nl.txt
	echo 'expected output: '
	cat no_nl_error.txt
fi
rm ${OUT}

echo 'testing -n with an argument'
(../echo -n hello > no_newline.txt)
diff no_newline.txt no_nl.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
fi
rm ${OUT}

echo 'testing -n with an argument'
(../echo hello -n > .txt)
diff .txt .txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
fi
rm ${OUT}

echo 'testing -- with an argument'
(../echo -- > one_argument_2.txt)
diff one_argument_2.txt one_arg_2.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
fi
rm ${OUT}
