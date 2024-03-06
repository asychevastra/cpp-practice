#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

int main(int argc, char *argv[]) {
    bool semaphore_locked(false);
    std::string semaphore_name("/testo_usb_lock_2_4");
    sem_t *semaphore;
    while (!semaphore_locked)
    {
        semaphore = sem_open(semaphore_name.c_str(), O_CREAT | O_EXCL, S_IRWXU | S_IRWXG | S_IRWXO, 1);
        if (semaphore == SEM_FAILED) {
            if (errno == EEXIST) {
                std::cout << "Trying to lock resource. Wait for 100 ms for the next attempt." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            } else {
                std::cout << "SEM_FAILED: semaphore is broken." << std::endl;
            }
        } else {
            std::cout << "Semaphore acquired." << std::endl;
            semaphore_locked = true;
        }
    }

    std::cout << "Sleep for 10 seconds." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));

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
