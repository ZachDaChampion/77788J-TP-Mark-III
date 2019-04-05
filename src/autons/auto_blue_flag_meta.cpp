#include "autons.hpp"
#include "subsystem_controllers/controllers.hpp"

chassis_controller::PidConstants constants_turn_precise = {
  .kp = 5000,
  .ki = 15,
  .kd = -69,
  .max_accel = 250,
  .min_voltage = 1000
};

void autons::auto_blue_flag_meta(bool park) {

  units::Time start_time = pros::millis() * units::MS;

  // get ball from under cap
  intake_controller::set_mode(intake_controller::succ);
  chassis_controller::move_dist_pid(32 * units::INCHES);
  pros::delay(350);
  chassis_controller::rotate_pid(0.0 * units::DEGREES, constants_turn_precise);
  pros::delay(250);

  // back out
  chassis_controller::move_dist_pid(-38);

  // turn (hella precise)
  chassis_controller::rotate_pid(-40.35 * units::DEGREES, constants_turn_precise);
  pros::delay(1000);

  // move up some
  chassis_controller::PidConstants constants_2 = {
    .kp = 950,
    .ki = 10,
    .kd = -250000,
    .max_accel = 250,
    .min_voltage = 1000
  };
  chassis_controller::move_dist_pid(9.69 * units::INCHES);

  // wait for correct time and fire
  while (pros::millis() * units::MS - start_time < 7500) pros::delay(10);
  catapult_controller::fire();

  

}