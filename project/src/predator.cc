/**
 * @file predator.cc
 *
 * @copyright Brian Cooper
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <ctime>
#include "src/predator.h"
#include "src/params.h"
#include "src/graphics_arena_viewer.h"
#include "src/predator_decorator.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

int Predator::count = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Predator::Predator() :
  light_sensors_(), wheel_velocity_(), food_wheel_velocity_(),
  light_wheel_velocity_(), bv_wheel_velocity_(), closest_light_entity_(NULL),
  closest_food_entity_(), closest_bv_entity_(NULL), light_behavior_(kCoward),
  food_behavior_(kNone), robot_behavior_(kAggressive), defaultSpeed_(5.0) {
    set_type(kPredator);
    motion_behavior_ = new MotionBehaviorDifferential(this);
    light_sensors_.push_back(Pose());
    light_sensors_.push_back(Pose());
    set_color({102, 0, 102});  // Dark purple
    set_pose(ROBOT_INIT_POS);

    wheel_velocity_ = WheelVelocity(0, 0);

    // Set ID
    count++;
    set_id(count);
  }

void Predator::TimestepUpdate(__unused unsigned int dt) {
  if (is_moving()) {
    motion_behavior_->UpdatePose(dt, wheel_velocity_);
  }
  UpdateLightSensors();

  if (collision_step_counter_ == 20) {
    set_heading(static_cast<int>((get_pose().theta + 45)) % 360);
    // reset collision step counter
    collision_step_counter_ = 0;
  }

  if (collision_step_counter_ != 0) {
    collision_step_counter_++;
  }
}

void Predator::HandleCollision(__unused EntityType ent_type,
                               __unused ArenaEntity * object) {
  if (alive) {
    collision_step_counter_ = 1;
    set_heading(static_cast<int>((get_pose().theta + 180)) % 360);
  }
}

void Predator::SenseEntity(const ArenaEntity& entity) {
  const ArenaEntity** closest_entity_ = NULL;
  if (entity.get_type() == kLight) {
    closest_entity_ = &closest_light_entity_;
  } else if (entity.get_type() == kBraitenberg) {
    closest_entity_ = &closest_bv_entity_;
  }

  if (!closest_entity_) {
    return;
  }

  if (!*closest_entity_) {
    *closest_entity_ = &entity;
  }

  double distance = (this->get_pose()-entity.get_pose()).Length();
  double closest_distance =
  (this->get_pose()-(*closest_entity_)->get_pose()).Length();
  if (distance < closest_distance) {
    *closest_entity_ = &entity;
    closest_distance = distance;
  }
  if (closest_distance > 100.0) {
    *closest_entity_ = NULL;
  }
}

void Predator::Update() {
  int numBehaviors = 3;

  this->set_food_velocity(this->get_food_behavior());
  this->set_light_velocity(this->get_light_behavior());
  this->set_bv_velocity(this->get_robot_behavior());

  // Check if any of the behaviors are set to none
  if (this->get_food_behavior() == kNone) {
    numBehaviors--;
  }
  if (this->get_light_behavior() == kNone) {
    numBehaviors--;
  }
  if (this->get_robot_behavior() == kNone) {
    numBehaviors--;
  }

  food_wheel_velocity_ = WheelVelocity(0, 0);

  food_wheel_velocity_ = food_behavior_interface_->getWheelVelocity(
    get_sensor_reading_right(closest_food_entity_),
     get_sensor_reading_left(closest_food_entity_),
      defaultSpeed_);

  light_wheel_velocity_ = WheelVelocity(0, 0);

  light_wheel_velocity_ = light_behavior_interface_->getWheelVelocity(
    get_sensor_reading_right(closest_light_entity_),
     get_sensor_reading_left(closest_light_entity_),
      defaultSpeed_);

  bv_wheel_velocity_ = WheelVelocity(0, 0);

  bv_wheel_velocity_ = robot_behavior_interface_->getWheelVelocity(
    get_sensor_reading_right(closest_bv_entity_),
     get_sensor_reading_left(closest_bv_entity_),
      defaultSpeed_);

  // Calculate the total wheel velocity
  if (numBehaviors) {
    wheel_velocity_ = WheelVelocity(
      (light_wheel_velocity_.left + bv_wheel_velocity_.left)/numBehaviors,
      (light_wheel_velocity_.right + bv_wheel_velocity_.right)/numBehaviors,
      defaultSpeed_);
  } else {
    wheel_velocity_ = WheelVelocity(
      (light_wheel_velocity_.left + food_wheel_velocity_.left
        + bv_wheel_velocity_.left)/numBehaviors,
      (light_wheel_velocity_.right + food_wheel_velocity_.right
        + bv_wheel_velocity_.right)/numBehaviors,
      defaultSpeed_);
  }

  if (alive) {
    if (disguise_timer_ >= 150) {
      // Decrement the starvation progress counter
      food_countdown_--;

      // Ghost the predator if it starves
      if (food_countdown_ <= 0) {
        // delete this->decorator_;
        this->Fade();
      }

      // instantiate a decorator if one hasn't been yet
      if (decorator_ == nullptr) {
        decorator_ = new PredatorDecorator();
      }

      // begin the disguise selection
      decorator_->Disguise(this);

      // Reset disguise timer back to zero
      disguise_timer_ = 0;
    }
  }
  disguise_timer_++;
}

void Predator::set_food_velocity(Behavior behavior) {
  switch (behavior) {
    case kExplore:
      food_behavior_interface_ = new BehaviorExplore();
      break;
    case kAggressive:
      food_behavior_interface_ = new BehaviorAggressive();
      break;
    case kLove:
      food_behavior_interface_ = new BehaviorLove();
      break;
    case kCoward:
      food_behavior_interface_ = new BehaviorCoward();
      break;
    case kNone:
    default:
      break;
  }
}

void Predator::set_light_velocity(Behavior behavior) {
  switch (behavior) {
    case kExplore:
      light_behavior_interface_ = new BehaviorExplore();
      break;
    case kAggressive:
      light_behavior_interface_ = new BehaviorAggressive();
      break;
    case kLove:
      light_behavior_interface_ = new BehaviorLove();
      break;
    case kCoward:
      light_behavior_interface_ = new BehaviorCoward();
      break;
    case kNone:
    default:
      break;
  }
}

void Predator::set_bv_velocity(Behavior behavior) {
  switch (behavior) {
    case kExplore:
      robot_behavior_interface_ = new BehaviorExplore();
      break;
    case kAggressive:
      robot_behavior_interface_ = new BehaviorAggressive();
      break;
    case kLove:
      robot_behavior_interface_ = new BehaviorLove();
      break;
    case kCoward:
      robot_behavior_interface_ = new BehaviorCoward();
      break;
    case kNone:
    default:
      break;
  }
}

void Predator::ConsumeRobot() {
  set_color({102, 0, 102});  // Dark purple
  disguise_timer_ = 0;

  // reset possible disguises if a decorator class has been instantiated
  if (decorator_ != nullptr) {
    decorator_->Restock();
  }

  // reset behaviors in case they were changed
  this->set_light_behavior(kCoward);
  this->set_food_behavior(kNone);
}

void Predator::Fade() {
  alive = false;
  set_type(kGhost);
  set_is_moving(false);
  set_color({255, 204, 255});  // "ghostly pink"
}

std::string Predator::get_name() const {
  return "Predator " + std::to_string(get_id());
}

std::vector<Pose> Predator::get_light_sensors_const() const {
  return light_sensors_;
}

std::vector<Pose> Predator::get_light_sensors() {
  return light_sensors_;
}

double Predator::get_sensor_reading_left(const ArenaEntity* entity) {
  if (entity) {
    return 1800.0/std::pow(
      1.08, (entity->get_pose()-light_sensors_[0]).Length());
  }

  return 0.0001;
}

double Predator::get_sensor_reading_right(const ArenaEntity* entity) {
  if (entity) {
    return 1800.0/std::pow(
      1.08, (entity->get_pose()-light_sensors_[1]).Length());
  }

  return 0.0001;
}

void Predator::UpdateLightSensors() {
  for (unsigned int f = 0; f < light_sensors_.size(); f++) {
    Pose& pos = light_sensors_[f];
    if (f == 0) {
      pos.x = get_pose().x + get_radius() * cos(deg2rad(get_pose().theta - 40));
      pos.y = get_pose().y + get_radius() * sin(deg2rad(get_pose().theta - 40));
    } else {
      pos.x = get_pose().x + get_radius() * cos(deg2rad(get_pose().theta + 40));
      pos.y = get_pose().y + get_radius() * sin(deg2rad(get_pose().theta + 40));
    }
  }
}

void Predator::LoadFromObject(json_object* entity_config) {
  ArenaEntity::LoadFromObject(entity_config);

  if ((*entity_config).find("light_behavior") != (*entity_config).end()) {
    light_behavior_ = get_behavior_type(
      (*entity_config)["light_behavior"].get<std::string>());
  }
  if ((*entity_config).find("food_behavior") != (*entity_config).end()) {
    food_behavior_ = get_behavior_type(
      (*entity_config)["food_behavior"].get<std::string>());
  }
  if ((*entity_config).find("robot_behavior") != (*entity_config).end()) {
    robot_behavior_ = get_behavior_type(
      (*entity_config)["robot_behavior"].get<std::string>());
  }

  UpdateLightSensors();
}

NAMESPACE_END(csci3081);
