/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "src/factory_light.h"

 /******************************************************
* TEST FEATURE SetUp
*******************************************************/
class FactoryLightTest : public ::testing::Test {
  protected:
   virtual void SetUp() {
     factory_light = new csci3081::FactoryLight();
     json = "{\"type\":\"Light\",\"x\":150,\"y\":300\"r\":30}";
     config = new json_value();
     err = parse_json(config, json);
     light = factory_light->Create(&(config->get<json_object>()));
   }
   virtual void TearDown() {
     delete factory_light;
   }

   csci3081::FactoryLight * factory_light;
   csci3081::Light * light;
   picojson::value* config;
   std::string json;
   std::string err;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(FactoryLightTest, Create) {
  EXPECT_EQ(light->get_type(), csci3081::kLight);
  EXPECT_EQ(light->get_pose().x, 150);
  EXPECT_EQ(light->get_pose().y, 300);
  EXPECT_EQ(light->get_radius(), 30);
}
