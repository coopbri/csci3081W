/**
 * @file braitenberg_vehicle.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <ctime>
#include "src/braitenberg_vehicle.h"
#include "src/params.h"
#include "src/graphics_arena_viewer.h"
class SensorLightLove;

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

int BraitenbergVehicle::count = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
BraitenbergVehicle::BraitenbergVehicle() :
  light_sensors_(), wheel_velocity_(), food_wheel_velocity_(),
  light_wheel_velocity_(), bv_wheel_velocity_(), wv_values_(6),
  light_behavior_(kNone), food_behavior_(kNone), robot_behavior_(kNone),
  closest_light_entity_(NULL), closest_food_entity_(NULL),
  closest_bv_entity_(NULL), gav_observer_(NULL), defaultSpeed_(5.0) {
  set_type(kBraitenberg);
  motion_behavior_ = new MotionBehaviorDifferential(this);
  light_sensors_.push_back(Pose());
  light_sensors_.push_back(Pose());
  set_color(BRAITENBERG_COLOR);
  set_pose(ROBOT_INIT_POS);

  wheel_velocity_ = WheelVelocity(0, 0);

  // Set ID
  count++;
  set_id(count);
}

void BraitenbergVehicle::TimestepUpdate(__unused unsigned int dt) {
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

void BraitenbergVehicle::HandleCollision(__unused EntityType ent_type,
                                         __unused ArenaEntity * object) {
  if (alive) {
    collision_step_counter_ = 1;
    set_heading(static_cast<int>((get_pose().theta + 180)) % 360);
  }
}

void BraitenbergVehicle::SenseEntity(const ArenaEntity& entity) {
  const ArenaEntity** closest_entity_ = NULL;
  if (entity.get_type() == kLight) {
    closest_entity_ = &closest_light_entity_;
  } else if (entity.get_type() == kFood) {
    closest_entity_ = &closest_food_entity_;
  } else if (entity.get_type() == kBraitenberg) {
    if (entity.get_name() != this->get_name()) {
      closest_entity_ = &closest_bv_entity_;
    }
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

void BraitenbergVehicle::Update() {
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

  // Store the contributing wheel velocities in a vector to be displayed by
  // the graphics arena viewer
  wv_values_[0] = light_wheel_velocity_;
  wv_values_[1] = food_wheel_velocity_;
  wv_values_[2] = bv_wheel_velocity_;

  // Change color of robot depending on active stimuli
  if ((food_behavior_ == kNone && light_behavior_ == kNone)
      || (food_behavior_ != kNone && light_behavior_ != kNone)) {
    set_color(BRAITENBERG_COLOR);  // set maroon
  } else if (food_behavior_ != kNone && light_behavior_ == kNone) {
    set_color({0, 0, 255});  // set blue
  } else {
    set_color({255, 204, 51});  // set gold
  }

  // Calculate the total wheel velocity
  if (numBehaviors) {
    // gravitate towards food if getting hungry
    if (food_timer_ >= 300) {
      // really gravitate towards food if beginning to starve!
      if (food_timer_ >= 400) {
        wheel_velocity_ = WheelVelocity(
          (2*food_wheel_velocity_.left),
          (2*food_wheel_velocity_.right),
          defaultSpeed_);
      } else {
        wheel_velocity_ = WheelVelocity(
          (food_wheel_velocity_.left),
          (food_wheel_velocity_.right),
          defaultSpeed_);
      }
    } else {
      wheel_velocity_ = WheelVelocity(
        (light_wheel_velocity_.left + food_wheel_velocity_.left
          + bv_wheel_velocity_.left)/numBehaviors,
        (light_wheel_velocity_.right + food_wheel_velocity_.right
          + bv_wheel_velocity_.right)/numBehaviors,
        defaultSpeed_);
    }
  } else {
    wheel_velocity_ = WheelVelocity(0, 0);
  }

  // Ghost the robot if it starves
  if (food_timer_ >= 600) {
    this->Fade();
  }
  food_timer_++;

  // Update the GUI with new wheel velocity values
  Notify(wv_values_);
}

void BraitenbergVehicle::set_food_velocity(Behavior behavior) {
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

void BraitenbergVehicle::set_light_velocity(Behavior behavior) {
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

void BraitenbergVehicle::set_bv_velocity(Behavior behavior) {
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

void BraitenbergVehicle::Notify(std::vector<WheelVelocity> wv) {
  // Verify GAV pointer is not null
  if (gav_observer_) {
    gav_observer_->OnUpdate(wv);
  }
}

void BraitenbergVehicle::Subscribe(GraphicsArenaViewer * gav) {
  gav_observer_ = gav;
}

void BraitenbergVehicle::Unsubscribe() {
  gav_observer_ = NULL;
}

void BraitenbergVehicle::ConsumeFood() {
  food_timer_ = 0;
}

void BraitenbergVehicle::Fade() {
  alive = false;
  set_type(kGhost);
  set_is_moving(false);
  set_color({255, 204, 255});  // "ghostly pink"
}

std::string BraitenbergVehicle::get_name() const {
  return "Braitenberg " + std::to_string(get_id());
}

std::vector<Pose> BraitenbergVehicle::get_light_sensors_const() const {
  return light_sensors_;
}

std::vector<Pose> BraitenbergVehicle::get_light_sensors() {
  return light_sensors_;
}

double BraitenbergVehicle::get_sensor_reading_left(const ArenaEntity* entity) {
  if (entity) {
    return 1800.0/std::pow(
      1.08, (entity->get_pose()-light_sensors_[0]).Length());
  }

  return 0.0001;
}

double BraitenbergVehicle::get_sensor_reading_right(const ArenaEntity* entity) {
  if (entity) {
    return 1800.0/std::pow(
      1.08, (entity->get_pose()-light_sensors_[1]).Length());
  }

  return 0.0001;
}

void BraitenbergVehicle::UpdateLightSensors() {
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

void BraitenbergVehicle::LoadFromObject(json_object* entity_config) {
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
