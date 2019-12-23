/**
 * @file behavior_interface.h
 *
 * @copyright Brian Cooper
 */

#ifndef SRC_BEHAVIOR_INTERFACE_H_
#define SRC_BEHAVIOR_INTERFACE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"
#include "src/wheel_velocity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief An abstract behavior class that serves as an interface for
 * derived behavior classes.
 *
 */
class BehaviorInterface {
 public:
  /**
  * @brief Behavior's constructor.
  */
  BehaviorInterface() {}

  /**
  * @brief Behavior's destructor.
  */
  virtual ~BehaviorInterface() {}

  /**
  * Virtual method for calculating wheel velocity according to behavior.
  *
  * Each derived behavior class implements this.
  */
  virtual WheelVelocity getWheelVelocity(double rsr = 0, double lsr = 0,
    double speed = 0);

  /**
   * @brief Under certain circumstances, the compiler requires that the
   * assignment operator is not defined. This `deletes` the default
   * assignment operator.
   */
  BehaviorInterface(const BehaviorInterface& b) = delete;

  /**
   * @brief Under certain circumstances, the compiler requires that the copy
   * constructor is not defined. This `deletes` the default copy constructor.
   */
  BehaviorInterface &operator=(const BehaviorInterface* other) = delete;
};

NAMESPACE_END(csci3081);

#endif  // SRC_BEHAVIOR_INTERFACE_H_
