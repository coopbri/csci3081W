/**
 * @file factory_predator.h
 *
 * @copyright Brian Cooper
 */

#ifndef SRC_FACTORY_PREDATOR_H_
#define SRC_FACTORY_PREDATOR_H_

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
  * @brief A factory class for generating predator objects; derived from the
  * abstract factory class.
  *
  */
class FactoryPredator : public Factory {
 public:
   /**
   * @brief FactoryPredator's constructor.
   */
  FactoryPredator() {}

  /**
  * @brief FactoryPredator's destructor.
  */
  ~FactoryPredator() {}

  /**
  * @brief Instantiate a predator object.
  */
  Predator * Create(json_object* config) override;

  /**
   * @brief Under certain circumstances, the compiler requires that the
   * assignment operator is not defined. This `deletes` the default
   * assignment operator.
   */
  FactoryPredator(const FactoryPredator& f) = delete;

  /**
   * @brief Under certain circumstances, the compiler requires that the copy
   * constructor is not defined. This `deletes` the default copy constructor.
   */
  FactoryPredator &operator=(const FactoryPredator * other) = delete;
};

NAMESPACE_END(csci3081);

#endif  // SRC_FACTORY_PREDATOR_H_
