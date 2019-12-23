/**
 * @file factory.h
 *
 * @copyright Brian Cooper
 */

#ifndef SRC_FACTORY_H_
#define SRC_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"
#include "src/braitenberg_vehicle.h"
#include "src/predator.h"
#include "src/food.h"
#include "src/light.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief An abstract factory class that serves as an interface for
 * derived factory classes.
 *
 */
class Factory {
 public:
  /**
  * @brief Factory's constructor.
  */
  Factory() {}

  /**
  * @brief Factory's destructor.
  */
  virtual ~Factory() {}

  /**
  * Virtual method for creating/instantiating an entity.
  *
  * Each derived factory class implements this.
  */
  virtual ArenaEntity* Create(json_object* config) = 0;

  /**
   * @brief Under certain circumstances, the compiler requires that the
   * assignment operator is not defined. This `deletes` the default
   * assignment operator.
   */
  Factory(const Factory& f) = delete;

  /**
   * @brief Under certain circumstances, the compiler requires that the copy
   * constructor is not defined. This `deletes` the default copy constructor.
   */
  Factory &operator=(const Factory* other) = delete;
};

NAMESPACE_END(csci3081);

#endif  // SRC_FACTORY_H_
