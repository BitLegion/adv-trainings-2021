#pragma once 

#include <unistd.h> 
#include <string> 

class SuperstructureInput {
    bool enabled; 

    bool gripper_toggle, roller_forwards, roller_backwards; 

    float arm_position; 

    bool upper_limit, lower_limit; 
};

class SuperstructureOutput {
    bool enabled; 

    bool gripper_open, roller_forwards, roller_backwards; 

    float arm_position; 

    bool upper_limit, lower_limit;
};

class Superstructure {
public: 
    Superstructure(std::string socket_path = "superstructure") : socket_path_{socket_path}, socket_fd_{-1} {};
    ~Superstructure() {
        if (socket_fd_ > 0) {
            close(socket_fd_);
        }
    };

    void run();

    bool iterate();

private: 
    std::string socket_path_; 
    int socket_fd_; 
};
