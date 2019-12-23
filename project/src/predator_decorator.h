/**
 * @file predator_decorator.h
 *
 * @copyright Brian Cooper
 */

#ifndef SRC_PREDATOR_DECORATOR_H_
#define SRC_PREDATOR_DECORATOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include "src/predator.h"
#include "src/light.h"
#include "src/food.h"
#include "src/braitenberg_vehicle.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Decorates a predator based on its progress towards starvation
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
class PredatorDecorator : public Predator {
 public:
  /**
  * @brief Default constructor.
  */
  PredatorDecorator();

  /**
   * Deleting the copy assignment and copy constructor. required now with
   *  inclusion of references to sensors and motion_handler/behavior
   */
  PredatorDecorator(const PredatorDecorator & rhs) = delete;

  /**
   * @brief Under certain circumstances, the compiler requires that the copy
   * constructor is not defined. This `deletes` the default copy constructor.
   */
  PredatorDecorator operator=(const PredatorDecorator & rhs) = delete;

  /**
   * @brief Disguise the predator as another entity. Activated when a predator
   * gets hungry, and changes at various hunger thresholds.
   */
  void Disguise(Predator * predator);

  /**
   * @brief Restock the disguise vector. This is called after a predator
   * has eaten.
   */
  void Restock();

 private:
  //! A light object for the predator to utilize
  Light light_;

  //! A food object for the predator to utilize
  Food food_;

  //! A robot object for the predator to utilize
  BraitenbergVehicle robot_;

  //! A vector of the possible predator disguises
  std::vector<ArenaEntity*> disguises_;

  //! A vector of the possible predator behaviors, accessed when a robot
  //! disguise is activated
  std::vector<Behavior> behaviors_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_PREDATOR_DECORATOR_H_
