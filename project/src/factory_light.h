/**
 * @file factory_light.h
 *
 * @copyright Brian Cooper
 */

#ifndef SRC_FACTORY_LIGHT_H_
#define SRC_FACTORY_LIGHT_H_

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
  * @brief A factory class for generating light objects; derived from the
  * abstract factory class.
  *
  */
class FactoryLight : public Factory {
 public:
   /**
   * @brief FactoryLight's constructor.
   */
  FactoryLight() {}

  /**
  * @brief FactoryLight's destructor.
  */
  ~FactoryLight() {}

  /**
  * @brief Instantiate a light object.
  */
  Light * Create(json_object* config) override;

  /**
   * @brief Under certain circumstances, the compiler requires that the
   * assignment operator is not defined. This `deletes` the default
   * assignment operator.
   */
  FactoryLight(const FactoryLight& f) = delete;

  /**
   * @brief Under certain circumstances, the compiler requires that the copy
   * constructor is not defined. This `deletes` the default copy constructor.
   */
  FactoryLight &operator=(const FactoryLight * other) = delete;
};

NAMESPACE_END(csci3081);

#endif  // SRC_FACTORY_LIGHT_H_
