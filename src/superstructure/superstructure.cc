#include <superstructure.hh>

#include <cerrno> 
#include <cstring> 
#include <iostream> 
#include <sys/socket.h> 
#include <sys/un.h> 
#include <thread> 

bool Superstructure::iterate() {
    bool gripper_open_ = false; 
    SuperstructureInput input; 
    int result = read(socket_fd_, &input, sizeof(input)); 
    if (result == -1) {
        std::cerr << "Failed to read on superstructure socket: " << std::strerror(errno) << std::endl;
        return false;
    } else if (result == 0) {
        std::cout << "End of file on read(2)\n";
        return false;
    } else if (result != sizeof(input)) {
        std::cerr << "Didn't recieve the right message size\n";
        return false;
    }

    if (input.gripper_toggle) {
        gripper_open_ = !gripper_open_;
    }

    SuperstructureOutput output; 
    if (input.enabled) {
        output.roller_forwards = input.roller_forwards; 
        output.roller_backwards = input.roller_backwards;
        output.gripper_open = gripper_open_;
        output.arm_voltage = 12.0;
    } else {
        output.roller_forwards = false; 
        output.roller_backwards = false; 
        output.gripper_open = false; 
        output.arm_voltage = 0.;
    }

    result = write(socket_fd_, &output, sizeof(output)); 
    if (result == -1) {
        std::cerr << "Failed to write on superstructure socket: " << std::strerror(errno) << std::endl; 
        return false;
    } else if (result == 0) {
        std::cout << "End of file on write(2)\n";
        return false;
    } else if (result != sizeof(input)) {
        std::cerr << "Didn't write the full message\n";
        return false;
    }

    return true;
}

void Superstructure::run() {
    if (socket_fd_ == -1) {
        std::cerr << "Socket FD -1 on call to run\n";
        return;
    }

    while (true) {
        if (iterate() == false) { return; }
    }
}
