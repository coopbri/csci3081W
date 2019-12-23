/**
 * @file factory_robot.h
 *
 * @copyright Brian Cooper
 */

#ifndef SRC_FACTORY_ROBOT_H_
#define SRC_FACTORY_ROBOT_H_

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
  * @brief A factory class for generating robot objects; derived from the
  * abstract factory class.
  *
  */
class FactoryRobot : public Factory {
 public:
   /**
   * @brief FactoryRobot's constructor.
   */
  FactoryRobot() {}

  /**
  * @brief FactoryRobot's destructor.
  */
  ~FactoryRobot() {}

  /**
  * @brief Instantiate a robot object.
  */
  BraitenbergVehicle * Create(json_object* config) override;

  /**
   * @brief Under certain circumstances, the compiler requires that the
   * assignment operator is not defined. This `deletes` the default
   * assignment operator.
   */
  FactoryRobot(const FactoryRobot& f) = delete;

  /**
   * @brief Under certain circumstances, the compiler requires that the copy
   * constructor is not defined. This `deletes` the default copy constructor.
   */
  FactoryRobot &operator=(const FactoryRobot * other) = delete;
};

NAMESPACE_END(csci3081);

#endif  // SRC_FACTORY_ROBOT_H_
