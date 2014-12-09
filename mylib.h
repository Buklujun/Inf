char* read_to_string (int fd_from, char* message);
void write_string_to (char* message, int fd_to);
void write_int_to (int* message, int fd_to, int size);
void read_to_int (int fd_from, int* message, int size);