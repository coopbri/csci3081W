/**
 * @file behavior_love.h
 *
 * @copyright Brian Cooper
 */

#ifndef SRC_BEHAVIOR_LOVE_H_
#define SRC_BEHAVIOR_LOVE_H_

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
  * @brief A behavior class to implement the love behavior; derived from the
  * abstract behavior class.
  *
  */
class BehaviorLove : public BehaviorInterface {
 public:
   /**
   * @brief BehaviorLove's constructor.
   */
  BehaviorLove() {}

  /**
  * @brief BehaviorLove's destructor.
  */
  ~BehaviorLove() {}

  /**
  * @brief Calculate the wheel velocity for the love behavior.
  */
  WheelVelocity getWheelVelocity(double rsr, double lsr, double speed) override;

  /**
   * @brief Under certain circumstances, the compiler requires that the
   * assignment operator is not defined. This `deletes` the default
   * assignment operator.
   */
  BehaviorLove(const BehaviorLove& f) = delete;

  /**
   * @brief Under certain circumstances, the compiler requires that the copy
   * constructor is not defined. This `deletes` the default copy constructor.
   */
  BehaviorLove &operator=(const BehaviorLove * other) = delete;
};

NAMESPACE_END(csci3081);

#endif  // SRC_BEHAVIOR_LOVE_H_
