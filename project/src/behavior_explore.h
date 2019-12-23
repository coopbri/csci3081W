/**
 * @file behavior_explore.h
 *
 * @copyright Brian Cooper
 */

#ifndef SRC_BEHAVIOR_EXPLORE_H_
#define SRC_BEHAVIOR_EXPLORE_H_

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
  * @brief A behavior class to implement the explore behavior; derived from the
  * abstract behavior class.
  *
  */
class BehaviorExplore : public BehaviorInterface {
 public:
   /**
   * @brief BehaviorExplore's constructor.
   */
  BehaviorExplore() {}

  /**
  * @brief BehaviorExplore's destructor.
  */
  ~BehaviorExplore() {}

  /**
  * @brief Calculate the wheel velocity for the explore behavior.
  */
  WheelVelocity getWheelVelocity(double rsr, double lsr, double speed) override;

  /**
   * @brief Under certain circumstances, the compiler requires that the
   * assignment operator is not defined. This `deletes` the default
   * assignment operator.
   */
  BehaviorExplore(const BehaviorExplore& f) = delete;

  /**
   * @brief Under certain circumstances, the compiler requires that the copy
   * constructor is not defined. This `deletes` the default copy constructor.
   */
  BehaviorExplore &operator=(const BehaviorExplore * other) = delete;
};

NAMESPACE_END(csci3081);

#endif  // SRC_BEHAVIOR_EXPLORE_H_
