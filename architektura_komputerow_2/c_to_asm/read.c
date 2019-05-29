#include <unistd.h>

int main()
{
    char data[4];

    if (read(0, data, 4) < 0)
        write(2, "An error occurred in the read.\n", 31);

    return 0;
}