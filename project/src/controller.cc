/**
 * @file controller.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <nanogui/nanogui.h>
#include <string>
#include <fstream>
#include <streambuf>

#include "src/common.h"
#include "src/controller.h"
#include "src/graphics_arena_viewer.h"
#include "src/light.h"
#include "src/food.h"
#include "src/braitenberg_vehicle.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

Controller::Controller(int argc, char **argv) :
  x_dim_(), y_dim_(), last_dt(0), viewers_(), config_(NULL) {
  if (argc > 1) {
    if (argc != 4) {
      std::cout << "Incorrect Command Line Arguments" << std::endl;
    }

    std::ifstream t(std::string(argv[3]).c_str());
    std::string str((std::istreambuf_iterator<char>(t)),
                   std::istreambuf_iterator<char>());

    x_dim_ = atof(argv[1]);
    y_dim_ = atof(argv[2]);

    std::string config_file = std::string(argv[3]).c_str();
    if (config_file.substr(config_file.find_last_of(".") + 1) == "json") {
      std::string json = str;
      config_ = new json_value();
      std::string err = parse_json(config_, json);

      if (!err.empty()) {
        std::cerr << "Parse error: " << err << std::endl;
        delete config_;
        config_ = NULL;
      } else {
        arena_ = new Arena(&(config_->get<json_object>()), x_dim_, y_dim_);
      }
    } else if (config_file.substr(config_file.find_last_of(".") + 1) == "csv") {
      char* csv = argv[3];
      std::string json = ConvertCsv(csv);
      config_ = new json_value();
      std::string err = parse_json(config_, json);

      if (!err.empty()) {
        std::cerr << "Parse error: " << err << std::endl;
        delete config_;
        config_ = NULL;
      } else {
        arena_ = new Arena(&(config_->get<json_object>()), x_dim_, y_dim_);
      }
    }
  }
  if (!config_) {
    arena_ = new Arena();
  }
}

Controller::~Controller() {
  if (config_) {
    delete config_;
  }
  for (unsigned int f = 0; f < viewers_.size(); f++) {
    delete viewers_[f];
  }
}

ArenaViewer* Controller::CreateViewer(int width, int height) {
  return new GraphicsArenaViewer(width, height, this);
}

void Controller::Run() {
  viewers_.push_back(CreateViewer(arena_->get_x_dim(), arena_->get_y_dim()));
  for (unsigned int f = 0; f < viewers_.size(); f++) {
    viewers_[f]->SetArena(arena_);
  }

  for (unsigned int f = 0; f < viewers_.size(); f++) {
    viewer_ = viewers_[f];
    if (viewer_->RunViewer()) {
      break;
    }
  }
}

void Controller::AdvanceTime(double dt) {
  if ((last_dt + dt) <= .05) {
    last_dt += dt;
    return;
  }
  last_dt = 0;
  arena_->AdvanceTime(dt);
}

void Controller::Reset() {
  Light::count = 0;
  Food::count = 0;
  BraitenbergVehicle::count = 0;
  Predator::count = 0;

  if (arena_) {
    delete (arena_);
  }
  if (config_) {
    arena_ = new Arena(&(config_->get<json_object>()), x_dim_, y_dim_);
  } else {
    arena_ = new Arena();
  }
  viewer_->SetArena(arena_);
}

std::string Controller::add_quotes(std::string word) {
  std::string quoted_string("\"");
  quoted_string += (word + "\"");
  return quoted_string;
}

bool Controller::in_number_set(std::string word) {
  // compare returns 0 when it matches the word
  return !(
    word.compare("x") && word.compare("y")
    && word.compare("r") && word.compare("theta") );
}

std::string Controller::ConvertCsv(char* csv) {
  try {
    std::string token;
    std::vector<std::string> keys;
    std::ifstream fin(csv);
    std::string labels;
    fin >> labels;
    std::istringstream ss(labels);
    while (std::getline(ss, token, ',')) {
      keys.push_back(token);
    }

    std::string entities = "{ \"entities\": [\n";
    std::string entity_json;  // populate below by converting csv row to json
    std::string row;          // temp holder of csv row
    std::vector<std::string> words;   // all words parsed from csv row

    while (fin >> row) {
      std::istringstream row_ss(row);
      words.clear();
      while (std::getline(row_ss, token, ',')) {
        words.push_back(token);
      }
      int keys_index = 0;
      entity_json = "     {";
      for (auto word : words) {
        if (keys_index != 0) { entity_json += ","; }
        entity_json += add_quotes(keys[keys_index]) + ":";
        if (in_number_set(keys[keys_index])) {
          entity_json += word;
        } else {
          entity_json += add_quotes(word);
        }
        ++keys_index;
      }
      entity_json += "}";
      entities += entity_json + ",\n";
    }

    entities = entities.substr(0, entities.length()-2);
    entities += "\n  ]\n}";
    return entities;
  }
  catch (const std::exception& e) {
    std::cout << "Incorrect Format of CSV file" << std::endl;
  }
  return "";
}

NAMESPACE_END(csci3081);
