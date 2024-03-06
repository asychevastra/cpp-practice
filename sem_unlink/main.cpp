#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

int main(int argc, char *argv[]) {
    std::string semaphore_name("/testo_usb_lock_2_4");

    int sem_unlink_result;
    sem_unlink_result = sem_unlink(semaphore_name.c_str());
    if (sem_unlink_result == 0) {
        std::cout << "Semaphore unlinked successfully." << std::endl;
    } else {
        if (errno == EACCES) {
            std::cout << "Has no rights to unlink." << std::endl;
        } else if (errno == ENAMETOOLONG) {
            std::cout << "Unlink failed: name too long." << std::endl;
        } else if (errno == ENOENT) {
            std::cout << "There is no semaphore to unlink." << std::endl;
        } else {
            std::cout << "Undefined error on semaphore unlink." << std::endl;
        }
    }

    return 0;
}
