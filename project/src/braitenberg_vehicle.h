/**
 * @file braitenberg_vehicle.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_BRAITENBERG_VEHICLE_H_
#define SRC_BRAITENBERG_VEHICLE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <ctime>
#include <string>
#include <vector>
#include "src/common.h"
#include "src/arena_mobile_entity.h"
#include "src/motion_behavior_differential.h"
#include "src/wheel_velocity.h"
#include "src/behavior_explore.h"
#include "src/behavior_aggressive.h"
#include "src/behavior_love.h"
#include "src/behavior_coward.h"
#include "src/behavior_enum.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class GraphicsArenaViewer;
/**
 * @brief Entity class to represent a Braitenberg Vehicle
 *
 * A braitenberg vehicle is a simple machine that is used to show how simple
 * concepts (in this case wiring) can give way to complex looking behavior. In
 * this simulation, Braitenberg vehicles contain sensors, which can be hooked
 * up in four different ways, and thus they can exhibit four different behaviors
 */
class BraitenbergVehicle : public ArenaMobileEntity {
 public:
  /**
   * @brief Default constructor.
   */
  BraitenbergVehicle();

  /**
   * Deleting the copy assignment and copy constructor. required now with
   *  inclusion of references to sensors and motion_handler/behavior
   */
  BraitenbergVehicle(const BraitenbergVehicle & rhs) = delete;

  /**
   * @brief Under certain circumstances, the compiler requires that the copy
   * constructor is not defined. This `deletes` the default copy constructor.
   */
  BraitenbergVehicle operator=(const BraitenbergVehicle & rhs) = delete;

  /**
   * @brief Update the BraitenbergVehicle's position and velocity after the
   * specified duration has passed.
   *
   * @param dt The # of timesteps that have elapsed since the last update.
   */
  void TimestepUpdate(unsigned int dt) override;

  /**
  * @brief Update the BraitenbergVehicle's wheel velocity based on behavior.
  */
  void Update() override;

  /**
   * @brief Change the movement state of the BraitenbergVehicle.
   */
  void HandleCollision(EntityType ent_type,
                       ArenaEntity * object = NULL) override;

  /**
   * @brief Detect nearby entities.
   */
  void SenseEntity(const ArenaEntity& entity);

  /**
  * @brief This is called when a predator collides with a robot. The robot
  * turns into a ghost: it can no longer move, changes color, and loses its
  * collision properties (other entities can pass right through it).
  */
  void Fade();

  /**
   * @brief Get the name of the robot.
   */
  std::string get_name() const override;

  /**
   * @brief Get the light sensors of the robot.
   */
  std::vector<Pose> get_light_sensors_const() const;

  /**
   * @brief Get the light sensors of the robot.
   */
  std::vector<Pose> get_light_sensors();

  /**
   * @brief Update the robot's light sensors.
   */
  void UpdateLightSensors();

  /**
   * @brief Load a configuration for the robot based on JSON configuration
   * file parameters.
   */
  void LoadFromObject(json_object* entity_config) override;

  /**
   * @brief Get the light behavior of the robot.
   */
  Behavior get_light_behavior() { return light_behavior_; }

  /**
   * @brief Set the light behavior of the robot.
   */
  void set_light_behavior(Behavior behavior) { light_behavior_ = behavior; }

  /**
   * @brief Get the food behavior of the robot.
   */
  Behavior get_food_behavior() { return food_behavior_; }

  /**
   * @brief Set the food behavior of the robot.
   */
  void set_food_behavior(Behavior behavior) { food_behavior_ = behavior; }

  /**
   * @brief Get the bv behavior of the robot.
   */
  Behavior get_robot_behavior() { return robot_behavior_; }

  /**
   * @brief Set the bv behavior of the robot.
   */
  void set_robot_behavior(Behavior behavior) { robot_behavior_ = behavior; }

  /**
   * @brief Set the food velocity contribution of the robot.
   */
  void set_food_velocity(Behavior behavior);

  /**
   * @brief Set the light velocity contribution of the robot.
   */
  void set_light_velocity(Behavior behavior);

  /**
   * @brief Set the other robot velocity contribution of the robot.
   */
  void set_bv_velocity(Behavior behavior);

  /**
  * @brief Eat food on contact. This resets the food timer back to zero.
  */
  void ConsumeFood();

  /**
  * @brief Send statistical updates to subscribers
  */
  void Notify(std::vector<WheelVelocity> wv);

  /**
  * @brief Attach robot to subscriber
  */
  void Subscribe(GraphicsArenaViewer * gav);

  /**
  * @brief Detatch robot from subscriber
  */
  void Unsubscribe();

  /**
   * @brief Get the robot's left sensor reading.
   */
  double get_sensor_reading_left(const ArenaEntity* entity);

  /**
   * @brief Get the robot's right sensor reading.
   */
  double get_sensor_reading_right(const ArenaEntity* entity);

  /**
   * @brief A count of the robots in the arena.
   */
  static int count;

  /**
   * @brief An indicator of the life/death status of the robot
   */
  bool alive = true;

 private:
  //! The robot's light sensors
  std::vector<Pose> light_sensors_;

  //! The motion behavior of the robot
  MotionBehaviorDifferential * motion_behavior_{nullptr};

  //! The total wheel velocity of the robot
  WheelVelocity wheel_velocity_;

  //! The food contribution to the robot's wheel velocity
  WheelVelocity food_wheel_velocity_;

  //! The light contribution to the robot's wheel velocity
  WheelVelocity light_wheel_velocity_;

  //! The other robot contribution to the robot's wheel velocity
  WheelVelocity bv_wheel_velocity_;

  //! Vector containing contributing values of wheel velocity
  std::vector<WheelVelocity> wv_values_;

  //! The food entity contribution to the wheel velocity of the robot
  BehaviorInterface* food_behavior_interface_ = new BehaviorInterface();

  //! The light entity contribution to the wheel velocity of the robot
  BehaviorInterface* light_behavior_interface_ = new BehaviorInterface();

  //! The other robot entity contribution to the wheel velocity of the robot
  BehaviorInterface* robot_behavior_interface_ = new BehaviorInterface();

  //! The robot's light behavior
  Behavior light_behavior_;

  //! The robot's food behavior
  Behavior food_behavior_;

  //! The robot's bv behavior
  Behavior robot_behavior_;

  //! Closest light entity to the robot
  const ArenaEntity* closest_light_entity_;

  //! Closest food entity to the robot
  const ArenaEntity* closest_food_entity_;

  //! Closest bv entity to the robot
  const ArenaEntity* closest_bv_entity_;

  //! The graphics arena viewer, which attaches to robots as an observer
  GraphicsArenaViewer* gav_observer_;

  //! The default speed of the robot
  double defaultSpeed_;

  //! A step counter that increments when a robot collides with something
  int collision_step_counter_ = 0;

  //! A food timer that tracks the robot's progress towards starvation
  int food_timer_ = 0;
};

NAMESPACE_END(csci3081);

#endif  // SRC_BRAITENBERG_VEHICLE_H_
