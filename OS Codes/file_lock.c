#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open the file in read-write mode
    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        perror("Failed to open file");
        return 1;
    }

    // Initialize the lock structure
    struct flock lock = {0};
    lock.l_type = F_WRLCK;     // Write lock
    lock.l_whence = SEEK_END;  // Relative to end of file
    lock.l_start = -100;       // Start 100 bytes from the end
    lock.l_len = 100;          // Lock the last 100 bytes

    printf("Press Enter to set lock...\n");
    getchar();

    // Attempt to set a write lock
    printf("Trying to acquire lock...\n");
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        fcntl(fd, F_GETLK, &lock); // Check who holds the lock
        printf("File is locked by process (PID): %d\n", lock.l_pid);
        close(fd);
        return 1;
    }

    printf("Lock acquired.\n");

    // Read the last 50 bytes of the file
    char buffer[101] = {0}; // Buffer with null-termination
    if (lseek(fd, -50, SEEK_END) == -1 || read(fd, buffer, 50) == -1) {
        perror("Failed to read from file");
        close(fd);
        return 1;
    }

    printf("Data read from file:\n%s\n", buffer);

    printf("Press Enter to release lock...\n");
    getchar();

    // Release the lock
    lock.l_type = F_UNLCK; // Unlock
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("Failed to release lock");
        close(fd);
        return 1;
    }

    printf("Lock released.\n");
    close(fd);
    return 0;
}
