for i in 1 2 3 4 5 6 7 8 9 10
do
bufsize=$i
gcc -D BUFFER_SIZE=$bufsize main.c get_next_line_bonus.c get_next_line_utils_bonus.c
./a.out test2 > sample.txt
diff sample.txt test2
done
echo $bufsize
