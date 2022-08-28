bufsize=$1
gcc -D BUFFER_SIZE=$bufsize main.c get_next_line_bonus.c get_next_line_utils_bonus.c -fsanitize=address
echo $bufsize
