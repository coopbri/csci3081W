/**
 * @file factory_food.h
 *
 * @copyright Brian Cooper
 */

#ifndef SRC_FACTORY_FOOD_H_
#define SRC_FACTORY_FOOD_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/factory.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief A factory class for generating food objects; derived from the
  * abstract factory class.
  *
  */
class FactoryFood : public Factory {
 public:
   /**
   * @brief FactoryFood's constructor.
   */
  FactoryFood() {}

  /**
  * @brief FactoryFood's destructor.
  */
  ~FactoryFood() {}

  /**
  * @brief Instantiate a food object.
  */
  Food * Create(json_object* config) override;

  /**
   * @brief Under certain circumstances, the compiler requires that the
   * assignment operator is not defined. This `deletes` the default
   * assignment operator.
   */
  FactoryFood(const FactoryFood& f) = delete;

  /**
   * @brief Under certain circumstances, the compiler requires that the copy
   * constructor is not defined. This `deletes` the default copy constructor.
   */
  FactoryFood &operator=(const FactoryFood * other) = delete;
};

NAMESPACE_END(csci3081);

#endif  // SRC_FACTORY_FOOD_H_
