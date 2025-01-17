#pragma once

#include "hardware/encoder/Encoder.hpp"
#include "pros/motors.hpp"

namespace lemlib {

enum class BrakeMode { COAST, BRAKE, HOLD, INVALID };

enum class MotorType { V5, EXP, INVALID };

enum class Cartridge { RED = 100, GREEN = 200, BLUE = 600, INVALID };

class Motor : public Encoder {
    public:
        /**
         * @brief Construct a new Motor object
         *
         * @param port the port of the motor
         *
         * @b Example:
         * @code {.cpp}
         * void initialize() {
         *     // construct a new Motor object with port 1
         *     lemlib::Motor motor = pros::Motor(1);
         * }
         * @endcode
         */
        Motor(pros::Motor motor);
        /**
         * @brief move the motor at a percent power from -1.0 to +1.0
         *
         * This function uses the following values of errno when an error state is reached:
         *
         * ENODEV: the port cannot be configured as a motor
         *
         * @param percent the power to move the motor at from -1.0 to +1.0
         * @return 0 on success
         * @return INT_MAX on failure, setting errno
         *
         * @b Example:
         * @code {.cpp}
         * void initialize() {
         *     lemlib::Motor motor = pros::Motor(1);
         *     // move the motor forward at 50% power
         *     motor.move(0.5);
         *     // move the motor backward at 50% power
         *     motor.move(-0.5);
         *     // stop the motor
         *     motor.move(0);
         * }
         * @endcode
         */
        int move(double percent);
        /**
         * @brief move the motor at a given angular velocity
         *
         * This function uses the following values of errno when an error state is reached:
         *
         * ENODEV: the port cannot be configured as a motor
         *
         * @param velocity the target angular velocity to move the motor at
         * @return 0 on success
         * @return INT_MAX on failure, setting errno
         *
         * @b Example:
         * @code {.cpp}
         * void initialize() {
         *     lemlib::Motor motor = pros::Motor(1);
         *     // move the motor forward at 50 degrees per second
         *     motor.moveVelocity(50_degps);
         *     // move the motor backward at 50 degrees per second
         *     motor.moveVelocity(-50_degps);
         *     // stop the motor
         *     motor.moveVelocity(0_degps);
         * }
         * @endcode
         */
        int moveVelocity(AngularVelocity velocity);
        /**
         * @brief brake the motor
         *
         * This function will stop the motor using the set brake mode
         *
         * This function uses the following values of errno when an error state is reached:
         *
         * ENODEV: the port cannot be configured as a motor
         *
         * @return 0 on success
         * @return INT_MAX on failure, setting errno
         *
         * @b Example:
         * @code {.cpp}
         * void initialize() {
         *     lemlib::Motor motor = pros::Motor(1);
         *     // move the motor forward at 50% power
         *     motor.move(0.5);
         *     // brake the motor
         *     motor.brake();
         * }
         * @endcode
         */
        int brake();
        /**
         * @brief set the brake mode of the motor
         *
         * This function uses the following values of errno when an error state is reached:
         *
         * ENODEV: the port cannot be configured as a motor
         *
         * @param mode the brake mode to set the motor to
         * @return 0 on success
         * @return INT_MAX on failure, setting errno
         *
         * @b Example:
         * @code {.cpp}
         * void initialize() {
         *     lemlib::Motor motor = pros::Motor(1);
         *     // set the motor to brake when stopped
         *     motor.setBrakeMode(lemlib::BrakeMode::BRAKE);
         *     // set the motor to coast when stopped
         *     motor.setBrakeMode(lemlib::BrakeMode::COAST);
         *     // set the motor to hold when stopped
         *     motor.setBrakeMode(lemlib::BrakeMode::HOLD);
         * }
         * @endcode
         */
        int setBrakeMode(BrakeMode mode);
        /**
         * @brief get the brake mode of the motor
         *
         * This function uses the following values of errno when an error state is reached:
         *
         * ENODEV: the port cannot be configured as a motor
         *
         * @return BrakeMode enum value of the brake mode
         * @return BrakeMode::INVALID on failure, setting errno
         *
         * @b Example:
         * @code {.cpp}
         * void initialize() {
         *     lemlib::Motor motor = pros::Motor(1);
         *     const lemlib::BrakeMode mode = motor.getBrakeMode();
         *     if (mode == lemlib::BrakeMode::BRAKE) {
         *         std::cout << "Brake mode is set to BRAKE!" << std::endl;
         *     } else if (mode == lemlib::BrakeMode::COAST) {
         *         std::cout << "Brake mode is set to COAST!" << std::endl;
         *     } else if (mode == lemlib::BrakeMode::HOLD) {
         *         std::cout << "Brake mode is set to HOLD!" << std::endl;
         *     } else {
         *         std::cout << "Error getting brake mode!" << std::endl;
         *     }
         * }
         * @endcode
         */
        BrakeMode getBrakeMode() const;
        /**
         * @brief whether the motor is connected
         *
         * @return 0 if its not connected
         * @return 1 if it is connected
         *
         * @b Example:
         * @code {.cpp}
         * void initialize() {
         *     lemlib::Motor motor = pros::Motor(1);
         *     const int result = motor.isConnected();
         *     if (result == 1) {
         *         std::cout << "motor is connected!" << std::endl;
         *     } else if (result == 0) {
         *         std::cout << "motor is not connected!" << std::endl;
         *     } else {
         *         std::cout << "Error checking if motor is connected!" << std::endl;
         *     }
         * }
         * @endcode
         */
        int isConnected() override;
        /**
         * @brief Get the relative angle measured by the motor
         *
         * The relative angle measured by the motor is the angle of the motor relative to the last time the motor
         * was reset. As such, it is unbounded.
         *
         * This function uses the following values of errno when an error state is reached:
         *
         * ENODEV: the port cannot be configured as a motor
         *
         * @return Angle the relative angle measured by the motor
         * @return INFINITY if there is an error, setting errno
         *
         * @b Example:
         * @code {.cpp}
         * void initialize() {
         *     lemlib::Motor motor = pros::Motor(1);
         *     const Angle angle = motor.getAngle();
         *     if (angle == INFINITY) {
         *         std::cout << "Error getting relative angle!" << std::endl;
         *     } else {
         *         std::cout << "Relative angle: " << angle.convert(deg) << std::endl;
         *     }
         * }
         * @endcode
         */
        Angle getAngle() override;
        /**
         * @brief Set the relative angle of the motor
         *
         * This function uses the following values of errno when an error state is reached:
         *
         * ENODEV: the port cannot be configured as a motor
         *
         * This function sets the relative angle of the motor. The relative angle is the number of rotations the
         * motor has measured since the last reset. This function is non-blocking.
         *
         * @param angle the relative angle to set the measured angle to
         * @return 0 on success
         * @return INT_MAX on failure, setting errno
         *
         * @b Example:
         * @code {.cpp}
         * void initialize() {
         *     lemlib::Motor motor = pros::Motor(1);
         *     if (motor.setAngle(0_stDeg) == 0) {
         *         std::cout << "Relative angle set!" << std::endl;
         *         std::cout < "Relative angle: " << to_sDeg(motor.getAngle()) << std::endl; // outputs 0
         *     } else {
         *         std::cout << "Error setting relative angle!" << std::endl;
         *     }
         * }
         * @endcode
         */
        int setAngle(Angle angle) override;
        /**
         * @brief Get the type of the motor
         *
         * There are 2 motors legal for use: The 11W V5 motor and the 5.5W EXP motor
         *
         * This function uses the following values of errno when an error state is reached:
         *
         * ENODEV: the port cannot be configured as a motor
         *
         * @return MotorType the type of the motor
         * @return MotorType::Invalid on failure, setting errno
         *
         * @b Example:
         * @code {.cpp}
         * void initialize() {
         *     lemlib::Motor motor = pros::Motor(1);
         *     switch (motor.getType()) {
         *        case (lemlib::MotorType::V5): {
         *            std::cout << "V5 Motor on port 1" << std::endl;
         *            break;
         *        }
         *        case (lemlib::MotorType::EXP): {
         *            std::cout << "EXP Motor on port 1" << std::endl;
         *            break;
         *        }
         *        default: std::cout << "Error getting type of motor on port 1" << std::endl;
         *     }
         * }
         * @endcode
         */
        MotorType getType();
        /**
         * @brief Get the cartridge installed in the motor
         *
         * This function uses the following values of errno when an error state is reached:
         *
         * ENODEV: the port cannot be configured as a motor
         *
         * @return Cartridge the type of cartridge installed in the motor
         * @return Cartridge::Invalid on failure, setting errno
         *
         * @b Example:
         * @code {.cpp}
         * void initialize() {
         *     lemlib::Motor motor = pros::Motor(1);
         *     switch (motor.getCartridge()) {
         *        case (lemlib::Cartridge::RED): {
         *            std::cout << "Red Cartridge in motor on port 1" << std::endl;
         *            break;
         *        }
         *        case (lemlib::Cartridge::GREEN): {
         *            std::cout << "Green Cartridge in motor on port 1" << std::endl;
         *            break;
         *        }
         *        case (lemlib::Cartridge::BLUE): {
         *            std::cout << "Blue Cartridge in motor on port 1" << std::endl;
         *            break;
         *        }
         *        default: std::cout << "Error getting cartridge of motor on port 1" << std::endl;
         *     }
         * }
         * @endcode
         */
        Cartridge getCartridge() const;
        /**
         * @brief get whether the motor is reversed
         *
         * @return 0 if the motor is not reversed
         * @return 1 if the motor is reversed
         *
         * @b Example:
         * @code {.cpp}
         * void initialize() {
         *     lemlib::Motor motor = pros::Motor(1);
         *     if (motor.isReversed() == 1) {
         *         std::cout << "Motor is reversed!" << std::endl;
         *     } else if (motor.isReversed() == 0) {
         *         std::cout << "Motor is not reversed!" << std::endl;
         *     } else {
         *         std::cout << "Error checking if motor is reversed!" << std::endl;
         *     }
         * }
         * @endcode
         */
        bool isReversed() const;
        /**
         * @brief set whether the motor should be reversed or not
         *
         * This function does not return a value or set errno, as it is impossible for it to fail
         *
         * @param reversed whether the motor should be reversed or not
         * @return 0 on success
         * @return INT_MAX on failure, setting errno
         *
         * @b Example:
         * @code {.cpp}
         * void initialize() {
         *     lemlib::Motor motor = pros::Motor(1);
         *     // reverse the motor
         *     motor.setReversed(true);
         * }
         * @endcode
         */
        void setReversed(bool reversed);
        /**
         * @brief Get the port the motor is connected to
         *
         * Just like in PROS, the port is negative if the motor is reversed
         *
         * @return int the port the motor is connected to
         *
         * @b Example:
         * @code {.cpp}
         * void initialize() {
         *     lemlib::Motor motor = pros::Motor(1);
         *     std::cout << "Motor is connected to port " << motor.getPort() << std::endl;
         * }
         * @endcode
         */
        int getPort() const;
    private:
        /**
         * @brief Get the number of counts the motor recorded in absolute position
         *
         * PROS does not allow you to get the absolute position of a motor in a specific encoder unit without a write
         * op. We want to avoid writing to the motor to avoid race conditions, which means we have to do the unit
         * conversions ourselves
         *
         * @return int number of counts
         */
        int getAbsoluteCounts();
        pros::Motor m_motor;
};
} // namespace lemlib