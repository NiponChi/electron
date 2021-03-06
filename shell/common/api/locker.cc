// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE.chromium file.

#include "shell/common/api/locker.h"

#include <memory>

namespace mate {

Locker::Locker(v8::Isolate* isolate) {
  if (IsBrowserProcess())
    locker_ = std::make_unique<v8::Locker>(isolate);
}

Locker::~Locker() = default;

}  // namespace mate
