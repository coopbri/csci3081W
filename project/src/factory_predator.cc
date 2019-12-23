/**
 * @file factory_predator.cc
 *
 * @copyright Brian Cooper
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/factory_predator.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
Predator * FactoryPredator::Create(json_object* config) {
  Predator * predator = new Predator;
  predator->LoadFromObject(config);
  return predator;
}

NAMESPACE_END(csci3081);
