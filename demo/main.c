#include "fs.h"

void read_line_cb(const char* line, unsigned long ln) {
    printf("%lu\t%s\n", ln, line);
}

int main(int argc, char const* argv[])
{
    // const char* line = fs.read_line("./a.txt", 2);
    // printf("%s\n", line);
    // fs.delete(line);

    // const char* file_data = fs.read_all("./a.txt");
    // printf("%s", file_data);
    // fs.delete(file_data);
    
    // int res = fs.read_line_by_line("./a.txt", read_line_cb);

    // fs.trunc("a1.txt");

    // fs.remove("a1.txt");
    fs.write("a.txt", "hello world!");
    // fs.append("b.txt", "this is a test file.");
    fs.copy("a.txt", "b.txt");
    return 0;
}
