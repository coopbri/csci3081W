/**
 * @file behavior_interface.cc
 *
 * @copyright Brian Cooper
 */

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
WheelVelocity BehaviorInterface::getWheelVelocity(double rsr, double lsr,
  double speed) {
    WheelVelocity wv = WheelVelocity(lsr, rsr, speed);
    return wv;
}

NAMESPACE_END(csci3081);
