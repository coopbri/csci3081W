/**
 * @file behavior_aggressive.h
 *
 * @copyright Brian Cooper
 */

#ifndef SRC_BEHAVIOR_AGGRESSIVE_H_
#define SRC_BEHAVIOR_AGGRESSIVE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/behavior_interface.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief A behavior class to implement the aggressive behavior; derived from
  * the abstract behavior class.
  *
  */
class BehaviorAggressive : public BehaviorInterface {
 public:
   /**
   * @brief BehaviorAggressive's constructor.
   */
  BehaviorAggressive() {}

  /**
  * @brief BehaviorAggressive's destructor.
  */
  ~BehaviorAggressive() {}

  /**
  * @brief Calculate the wheel velocity for the aggressive behavior.
  */
  WheelVelocity getWheelVelocity(double rsr, double lsr, double speed) override;

  /**
   * @brief Under certain circumstances, the compiler requires that the
   * assignment operator is not defined. This `deletes` the default
   * assignment operator.
   */
  BehaviorAggressive(const BehaviorAggressive& f) = delete;

  /**
   * @brief Under certain circumstances, the compiler requires that the copy
   * constructor is not defined. This `deletes` the default copy constructor.
   */
  BehaviorAggressive &operator=(const BehaviorAggressive * other) = delete;
};

NAMESPACE_END(csci3081);

#endif  // SRC_BEHAVIOR_AGGRESSIVE_H_
