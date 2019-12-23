/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "src/factory_robot.h"
#include "src/wheel_velocity.h"
#include "src/factory_light.h"
#include "src/behavior_aggressive.h"
#include "src/lib/picojson.h"

 /******************************************************
* TEST FEATURE SetUp
*******************************************************/
class BehaviorAggressiveTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    factory_robot = new csci3081::FactoryRobot();
    factory_light = new csci3081::FactoryLight();
    aggressive = new csci3081::BehaviorAggressive();

    json = "{\"type\":\"Braitenberg\",\"x\":270,\"y\":270,\"r\":15\"theta\":0,\"light_behavior\":\"None\",\"food_behavior\":\"None\",\"robot_behavior\":\"None\"}";
    config = new json_value();
    err = parse_json(config, json);
    bv = factory_robot->Create(&(config->get<json_object>()));
    light = factory_light->Create(&(config->get<json_object>()));

    wv_ptr = new csci3081::WheelVelocity();
    wv_before = *wv_ptr;
    aggressive->getWheelVelocity(bv->get_sensor_reading_right(light),
       bv->get_sensor_reading_left(light), 5.0);
    wv_after = *wv_ptr;

  }
  virtual void TearDown() {
    delete factory_robot;
    delete aggressive;
  }

  csci3081::FactoryRobot * factory_robot;
  csci3081::FactoryLight * factory_light;
  csci3081::BraitenbergVehicle * bv;
  csci3081::Light * light;
  csci3081::BehaviorAggressive * aggressive;

  csci3081::WheelVelocity* wv_ptr;
  csci3081::WheelVelocity wv_before;
  csci3081::WheelVelocity wv_after;

  picojson::value * config;
  std::string json;
  std::string err;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(BehaviorAggressiveTest, Initial) {
  EXPECT_EQ(wv_before.left, 0.0);
  EXPECT_EQ(wv_before.right, 0.0);
}

TEST_F(BehaviorAggressiveTest, After) {
  EXPECT_LT(wv_after.left, 5.0);
  EXPECT_LT(wv_after.right, 5.0);
}
