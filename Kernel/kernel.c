volatile char* video_memory_popinter = (char*)0xb8000;

void putc(char c) {
    *video_memory_popinter = c;
    video_memory_popinter += 2;
}

void puts(char* s) {
    
    int i = 0;
    while (1) {

        char current_char = s[i];

        if (current_char == '\0') {
            break;
        }

        putc(current_char);
        i += 1;
    }
}

void main() {
    char* username = "Vuckoo0";
    puts(username);
}