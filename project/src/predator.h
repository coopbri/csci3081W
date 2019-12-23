/**
 * @file predator.h
 *
 * @copyright Brian Cooper
 */

#ifndef SRC_PREDATOR_H_
#define SRC_PREDATOR_H_

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
class PredatorDecorator;

/**
 * @brief Entity class to represent a Predator
 *
 * Predators are fundamentally based on Braitenberg vehicles. Predators always
 * ignore food (None behavior), cower from light (Coward behavior), and are
 * aggressive towards Braitenberg vehicles. They have no behavior (None
 * behavior) towards other predators.
 *
 * If a predator catches a Braitenberg vehicle, the BV will "die" (let's call
 * it sleep) and leave a ghost in the location it was at. Ghosts are lighter
 * in color and have no collision box.
 */
class Predator : public ArenaMobileEntity {
 public:
  /**
   * @brief Default constructor.
   */
  Predator();

  /**
   * Deleting the copy assignment and copy constructor. required now with
   *  inclusion of references to sensors and motion_handler/behavior
   */
  Predator(const Predator & rhs) = delete;

  /**
   * @brief Under certain circumstances, the compiler requires that the copy
   * constructor is not defined. This `deletes` the default copy constructor.
   */
  Predator operator=(const Predator & rhs) = delete;

  /**
   * @brief Update the Predator's position and velocity after the
   * specified duration has passed.
   *
   * @param dt The # of timesteps that have elapsed since the last update.
   */
  void TimestepUpdate(unsigned int dt) override;

  /**
  * @brief Update the Predator's wheel velocity based on behavior.
  */
  void Update() override;

  /**
   * @brief Change the movement state of the predator.
   */
  void HandleCollision(EntityType ent_type,
                       ArenaEntity * object = NULL) override;

  /**
  * @brief Detect nearby entities.
  */
  void SenseEntity(const ArenaEntity& entity);

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
   * @brief Get the light behavior of the predator.
   */
  Behavior get_light_behavior() { return light_behavior_; }

  /**
   * @brief Set the light behavior of the predator.
   */
  void set_light_behavior(Behavior behavior) { light_behavior_ = behavior; }

  /**
   * @brief Get the food behavior of the predator.
   */
  Behavior get_food_behavior() { return food_behavior_; }

  /**
   * @brief Set the food behavior of the predator.
   */
  void set_food_behavior(Behavior behavior) { food_behavior_ = behavior; }

  /**
   * @brief Get the bv behavior of the predator.
   */
  Behavior get_robot_behavior() { return robot_behavior_; }

  /**
   * @brief Set the bv behavior of the predator.
   */
  void set_robot_behavior(Behavior behavior) { robot_behavior_ = behavior; }

  /**
  * @brief Eat robot on contact. This resets the food timer back to zero, and
  * also restocks the disguise vector.
  */
  void ConsumeRobot();

  /**
  * @brief This is called when a predator starves. The predator turns into a
  * ghost: it can no longer move, changes color, and loses its collision
  * properties (other entities can pass right through it).
  */
  void Fade();

  /**
  * @brief Get the name of the predator.
  */
  std::string get_name() const override;

  /**
  * @brief Get the light sensors of the predator.
  */
  std::vector<Pose> get_light_sensors_const() const;

  /**
  * @brief Get the light sensors of the predator.
  */
  std::vector<Pose> get_light_sensors();

  /**
  * @brief Update the predator's light sensors.
  */
  void UpdateLightSensors();

  /**
  * @brief Load a configuration for the predator based on JSON configuration
  * file parameters.
  */
  void LoadFromObject(json_object* entity_config) override;

  /**
  * @brief Get the predator's left sensor reading.
  */
  double get_sensor_reading_left(const ArenaEntity* entity);

  /**
  * @brief Get the predator's right sensor reading.
  */
  double get_sensor_reading_right(const ArenaEntity* entity);

  /**
  * @brief A count of the predators in the arena.
  */
  static int count;

  /**
   * @brief An indicator of the life/death status of the predator
   */
  bool alive = true;

 private:
  //! The predator's light sensors
  std::vector<Pose> light_sensors_;

  //! The motion behavior of the predator
  MotionBehaviorDifferential * motion_behavior_{nullptr};

  //! The total wheel velocity of the predator
  WheelVelocity wheel_velocity_;

  //! The food contribution to the robot's wheel velocity
  WheelVelocity food_wheel_velocity_;

  //! The light contribution to the predator's wheel velocity
  WheelVelocity light_wheel_velocity_;

  //! The robot contribution to the predator's wheel velocity
  WheelVelocity bv_wheel_velocity_;

  //! Closest light entity to the predator
  const ArenaEntity* closest_light_entity_;

  //! Closest food entity to the predator
  const ArenaEntity* closest_food_entity_;

  //! Closest bv entity to the predator
  const ArenaEntity* closest_bv_entity_;

  //! Decorator class that allows the predator to take on a disguise if hungry
  PredatorDecorator* decorator_{nullptr};

  //! The food entity contribution to the wheel velocity of the predator
  BehaviorInterface* food_behavior_interface_ = new BehaviorInterface();

  //! The light entity contribution to the wheel velocity of the predator
  BehaviorInterface* light_behavior_interface_ = new BehaviorInterface();

  //! The other robot entity contribution to the wheel velocity of the predator
  BehaviorInterface* robot_behavior_interface_ = new BehaviorInterface();

  //! The predator's light behavior
  Behavior light_behavior_;

  //! The predator's food behavior
  Behavior food_behavior_;

  //! The predator's bv behavior
  Behavior robot_behavior_;

  //! The default speed of the predator
  double defaultSpeed_;

  //! A step counter that increments when a predator collides with something
  int collision_step_counter_ = 0;

  //! A disguise timer that is reset each time a predator takes on a new
  //! disguise.
  int disguise_timer_ = 0;

  //! A food timer that tracks the predator's progress towards starvation.
  //! Decremented each time it takes on a new disguise. At 0, the predator
  //! starves.
  int food_countdown_ = 4;
};

NAMESPACE_END(csci3081);

#endif  // SRC_PREDATOR_H_
