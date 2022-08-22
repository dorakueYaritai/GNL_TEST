bufsize=1
gcc -D BUFFER_SIZE=$bufsize main.c get_next_line.c get_next_line_utils.c
cat "$bufsize"
