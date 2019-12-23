/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "src/factory_food.h"

 /******************************************************
* TEST FEATURE SetUp
*******************************************************/
class FactoryFoodTest : public ::testing::Test {
  protected:
   virtual void SetUp() {
     factory_food = new csci3081::FactoryFood();
     json = "{\"type\":\"Food\",\"x\":200,\"y\":200\"r\":20,\"theta\":0.0}";
     config = new json_value();
     err = parse_json(config, json);
     food = factory_food->Create(&(config->get<json_object>()));
   }
   virtual void TearDown() {
     delete factory_food;
   }

   csci3081::FactoryFood * factory_food;
   csci3081::Food * food;
   picojson::value* config;
   std::string json;
   std::string err;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
 TEST_F(FactoryFoodTest, Create) {
   EXPECT_EQ(food->get_type(), csci3081::kFood);
   EXPECT_EQ(food->get_pose().x, 200);
   EXPECT_EQ(food->get_pose().y, 200);
   EXPECT_EQ(food->get_pose().theta, 0.0);
   EXPECT_EQ(food->get_radius(), 20);
 }
