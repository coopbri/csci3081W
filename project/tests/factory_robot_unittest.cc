/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "src/factory_robot.h"
#include "src/lib/picojson.h"

 /******************************************************
* TEST FEATURE SetUp
*******************************************************/
class FactoryRobotTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    factory_robot = new csci3081::FactoryRobot();
    json = "{\"type\":\"Braitenberg\",\"x\":270,\"y\":270,\"r\":15\"theta\":0,\"light_behavior\":\"None\",\"food_behavior\":\"None\",\"robot_behavior\":\"None\"}";
    config = new json_value();
    err = parse_json(config, json);
    bv = factory_robot->Create(&(config->get<json_object>()));
  }
  virtual void TearDown() {
    delete factory_robot;
  }

  csci3081::FactoryRobot * factory_robot;
  csci3081::BraitenbergVehicle * bv;
  picojson::value* config;
  std::string json;
  std::string err;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(FactoryRobotTest, Create) {
  EXPECT_EQ(bv->get_type(), csci3081::kBraitenberg);
  EXPECT_EQ(bv->get_pose().x, 270);
  EXPECT_EQ(bv->get_pose().y, 270);
  EXPECT_EQ(bv->get_pose().theta, 0);
  EXPECT_EQ(bv->get_radius(), 15);
  EXPECT_EQ(bv->get_light_behavior(), 0);
  EXPECT_EQ(bv->get_food_behavior(), 0);
}
