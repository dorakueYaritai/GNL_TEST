for i in 1 2 3 5 7 10 100 1000 10000
do
bufsize=$i
gcc -D BUFFER_SIZE=$bufsize main.c get_next_line_bonus.c get_next_line_utils_bonus.c
for str in test1 test2 test3 test4 test5 test6 test7 test8
do
./a.out $str > sample.txt
diff sample.txt $str
done
done
echo $bufsize
