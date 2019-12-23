/**
 * @file behavior_coward.h
 *
 * @copyright Brian Cooper
 */

#ifndef SRC_BEHAVIOR_COWARD_H_
#define SRC_BEHAVIOR_COWARD_H_

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
  * @brief A behavior class to implement the coward behavior; derived from the
  * abstract behavior class.
  *
  */
class BehaviorCoward : public BehaviorInterface {
 public:
   /**
   * @brief BehaviorCoward's constructor.
   */
  BehaviorCoward() {}

  /**
  * @brief BehaviorCoward's destructor.
  */
  ~BehaviorCoward() {}

  /**
  * @brief Calculate the wheel velocity for the coward behavior.
  */
  WheelVelocity getWheelVelocity(double rsr, double lsr, double speed) override;

  /**
   * @brief Under certain circumstances, the compiler requires that the
   * assignment operator is not defined. This `deletes` the default
   * assignment operator.
   */
  BehaviorCoward(const BehaviorCoward& f) = delete;

  /**
   * @brief Under certain circumstances, the compiler requires that the copy
   * constructor is not defined. This `deletes` the default copy constructor.
   */
  BehaviorCoward &operator=(const BehaviorCoward * other) = delete;
};

NAMESPACE_END(csci3081);

#endif  // SRC_BEHAVIOR_COWARD_H_
