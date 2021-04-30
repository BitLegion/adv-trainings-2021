#include <stdexcept> 
#include <unistd.h> 

struct DrivetrainInput {
    float joystick_x, joystick_y;
}; 

struct DrivetrainOutput {
    float left_voltage, right_voltage;
};

class Drivetrain {
public: 
    Drivetrain(std::string socket_path) : socket_path_{socket_path}, socket_fd_{-1} {};
    ~Drivetrain() {
        if (socket_fd_ != -1) {
            close(socket_fd_);
        }
    }

    bool block_and_connect(): 

    void run(); 
    
    bool iterate();

private: 
    std::string socket_path_; 
    int socket_fd_; 
};