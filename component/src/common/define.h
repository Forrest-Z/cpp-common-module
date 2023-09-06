#pragma once

#define SAFE_NEW(ptr, classname) \
  try {                          \
    ptr = new classname();       \
  } catch (...) {                \
    ptr = nullptr;               \
  }

#define SAFE_DELETE(ptr) \
  if (ptr != nullptr) {  \
    delete ptr;          \
    ptr = nullptr;       \
  }
