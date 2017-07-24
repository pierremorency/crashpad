// Copyright 2017 The Crashpad Authors. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef CRASHPAD_UTIL_LINUX_PROC_STAT_READER_H_
#define CRASHPAD_UTIL_LINUX_PROC_STAT_READER_H_

#include <sys/time.h>
#include <sys/types.h>

#include <string>

#include "base/macros.h"
#include "util/misc/initialization_state_dcheck.h"

namespace crashpad {

//! \brief Reads the /proc/[pid]/stat file for a thread.
class ProcStatReader {
 public:
  ProcStatReader();
  ~ProcStatReader();

  //! \brief Initializes the reader.
  //!
  //! This method must be successfully called before calling any other.
  //!
  //! \param[in] tid The thread ID to read the stat file for.
  bool Initialize(pid_t tid);

  //! \brief Determines the target thread’s start time.
  //!
  //! \param[out] start_time The time that the thread started.
  //!
  //! \return `true` on success, with \a start_time set. Otherwise, `false` with
  //!     a message logged.
  bool StartTime(timeval* start_time) const;

 private:
  bool ReadFile(std::string* contents) const;

  pid_t tid_;
  InitializationStateDcheck initialized_;

  DISALLOW_COPY_AND_ASSIGN(ProcStatReader);
};

}  // namespace crashpad

#endif  // CRASHPAD_UTIL_LINUX_PROC_STAT_READER_H_
