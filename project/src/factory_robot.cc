/**
 * @file factory_robot.cc
 *
 * @copyright Brian Cooper
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/factory_robot.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
BraitenbergVehicle * FactoryRobot::Create(json_object* config) {
  BraitenbergVehicle * bv = new BraitenbergVehicle;
  bv->LoadFromObject(config);
  return bv;
}

NAMESPACE_END(csci3081);
