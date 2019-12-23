/**
 * @file predator_decorator.cc
 *
 * @copyright Brian Cooper
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/predator_decorator.h"

/*******************************************************************************
* Namespaces
******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
* Constructors/Destructor
******************************************************************************/
PredatorDecorator::PredatorDecorator() :
  light_(), food_(), robot_(), disguises_(), behaviors_() {
    disguises_.push_back(&light_);
    disguises_.push_back(&food_);
    disguises_.push_back(&robot_);

    behaviors_.push_back(kNone);
    behaviors_.push_back(kAggressive);
    behaviors_.push_back(kCoward);
    behaviors_.push_back(kExplore);
    behaviors_.push_back(kLove);
  }

void PredatorDecorator::Disguise(Predator * predator) {
  if (!disguises_.empty()) {
    // random index generation for the potential disguises
    std::random_device rand_device_;
    std::mt19937 rand_engine_{rand_device_()};
    std::uniform_int_distribution<int> dist_(0, disguises_.size() - 1);
    ArenaEntity* rand_disguise_ = disguises_[dist_(rand_engine_)];

    // change features according to which disguise was selected
    if (rand_disguise_ == &light_) {
      predator->set_color(LIGHT_COLOR);  // white
      predator->set_is_moving(false);

      predator->set_food_behavior(kNone);
      predator->set_light_behavior(kCoward);

      // remove light disguise from potential disguises
      disguises_.erase(std::remove(disguises_.begin(), disguises_.end(),
        &light_), disguises_.end());
    }
    if (rand_disguise_ == &food_) {
      predator->set_color(FOOD_COLOR);  // green
      predator->set_is_moving(false);

      predator->set_food_behavior(kNone);
      predator->set_light_behavior(kCoward);

      // remove food disguise from potential disguises
      disguises_.erase(std::remove(disguises_.begin(), disguises_.end(),
        &food_), disguises_.end());
    }
    if (rand_disguise_ == &robot_) {
      predator->set_color(BRAITENBERG_COLOR);  // red
      predator->set_is_moving(true);

      // select random food and light behaviors for the robot disguise
      std::uniform_int_distribution<int> behavior_dist_(0,
        behaviors_.size() - 1);
      Behavior rand_behavior = behaviors_[behavior_dist_(rand_engine_)];
      predator->set_food_behavior(rand_behavior);
      predator->set_light_behavior(rand_behavior);

      // remove robot disguise from potential disguises
      disguises_.erase(std::remove(disguises_.begin(), disguises_.end(),
        &robot_), disguises_.end());
    }
  }
}

void PredatorDecorator::Restock() {
  disguises_.clear();
  disguises_.push_back(&light_);
  disguises_.push_back(&food_);
  disguises_.push_back(&robot_);
}

NAMESPACE_END(csci3081);
