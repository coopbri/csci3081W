/**
 * @file arena_viewer.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_VIEWER_H_
#define SRC_ARENA_VIEWER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/arena.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class to view the arena model
 */
class ArenaViewer {
 public:
  virtual ~ArenaViewer() {}
  virtual bool RunViewer() = 0;
  virtual void SetArena(Arena* arena) = 0;
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_VIEWER_H_
