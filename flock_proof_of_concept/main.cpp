#include <sys/file.h>
#include <unistd.h>
// #include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

int main(int argc, char *argv[]) {
    bool file_locked(false);
    std::string file_name("/tmp/testo_usb_lock_0_1");
    int fd;
    while (!file_locked)
    {
        int lock_result;
        std::cout << "Trying to open file " << file_name << std::endl;
        fd = open(file_name.c_str(), O_RDWR | O_CREAT);
        int chmod_result = chmod(file_name.c_str(), S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH);
        std::cout << "Trying to lock file " << file_name << std::endl;
        lock_result = flock(fd, LOCK_EX | LOCK_NB);

        if (lock_result == 0) {
            std::cout << "File locked." << std::endl;
            file_locked = true;
        } else {
            if (errno == EWOULDBLOCK) {
                close(fd);
                std::cout << "Trying to lock resource. Wait for 100 ms for the next attempt." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                // return false;
            } else {
                close(fd);
                // throw std::runtime_error("Failed to lock file for mutex on usb device.");
            }
        }
    }

    close(fd);

    std::cout << "Sleep for 10 seconds." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));

	int unlock_result;
    fd = open(file_name.c_str(), O_WRONLY | O_CREAT);
	unlock_result = flock(fd, LOCK_UN);
	close(fd);
	if (unlock_result == 0) {
		// Success
		return 0;
	} else {
		if (errno == EBADF) {
			throw std::runtime_error("UsbResourceMutex: fd is not an open file descriptor");
		} else {
			throw std::runtime_error("UsbResourceMutex: undefined error on releasing lock.");
		}
	}

    return 0;
}
