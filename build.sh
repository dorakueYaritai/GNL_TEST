bufsize=$1
gcc -D BUFFER_SIZE=$bufsize main.c get_next_line_bonus.c get_next_line_utils_bonus.c -fsanitize=address
echo $bufsize

for str in test1 test2 test3 test4 test5 test6 test7 test8
do
cat $str
done