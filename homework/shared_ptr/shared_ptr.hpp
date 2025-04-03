/*
`shared_ptr` is a RAII class:

* Holds a pointer to managed object (template class)
* Holds a pointer to shared control block with 2 counters and a deleter:
  * shared_refs count (as `std::atomic<size_t>`)
  * weak_refs count (as `std::atomic<size_t>`)
  * deleter (function pointer)
* Constructor copies a pointer and allocate the control block
* Destructor decrease shared_refs and:
  * if shared_refs == 0 -> release the managed object
  * if shared_refs == 0 and weak_refs == 0 -> release the control block
* Copying is allowed - it increments shared_refs
* Moving is allowed and it means:
  * Copying original pointers to a new object
  * Setting source pointer to nullptr
* Member functions: `operator*()`, `operator->()`, `get()`, `reset()`, `use_count()`, `operator bool()`
* Should be implemented in `shared_ptr.hpp` file inside `my` namespace
* Tests should be written inside `shared_ptr_tests.cpp` using GoogleTest or Catch2
* You should instantiate `shared_ptr` template class in `shared_ptr_tests.cpp` above your test cases, e.g. `template class my::shared_ptr<int>;` It's needed for code coverage check to work properly.

Do not forget about CI - UT + Valgrind / ASAN. Work in pairs.

[Read the notes on cppreference.com](https://en.cppreference.com/w/cpp/memory/shared_ptr)
*/


