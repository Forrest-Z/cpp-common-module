#include <fcntl.h>
#include <gtest/gtest.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <condition_variable>
#include <cstdlib>  //std::system
#include <functional>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

using namespace boost::interprocess;

// Define an STL compatible allocator of ints that allocates from the
// managed_shared_memory. This allocator will allow placing containers in the
// segment
typedef allocator<int, managed_shared_memory::segment_manager> ShmemAllocator;

// Alias a vector that uses the previous STL-like allocator so that allocates
// its values from the segment
typedef vector<int, ShmemAllocator> MyVector;

// Main function. For parent process argc == 1, for child process argc == 2
TEST(interproc, f1) {
  int pid = fork();
  printf("pid = %d \n", pid);
  if (pid == 0) {  // Parent process
    // Remove shared memory on construction and destruction
    struct shm_remove {
      shm_remove() { shared_memory_object::remove("MySharedMemory"); }
      ~shm_remove() { shared_memory_object::remove("MySharedMemory"); }
    } remover;

    // Create a new segment with given name and size
    managed_shared_memory segment(create_only, "MySharedMemory", 65536);

    // Initialize shared memory STL-compatible allocator
    const ShmemAllocator alloc_inst(segment.get_segment_manager());

    // Construct a vector named "MyVector" in shared memory with argument
    // alloc_inst
    MyVector *myvector = segment.construct<MyVector>("MyVector")(alloc_inst);
    auto mymtx = segment.construct<interprocess_mutex>("Mymtx")();
    scoped_lock<interprocess_mutex> lock(*mymtx);
    for (int i = 0; i < 10; ++i)  // Insert data in the vector
    {
      myvector->push_back(i);
      usleep(10 * 1000);
      printf("write data ... \n");
    }

    sleep(1);
  } else {  // Child process
    // Open the managed segment
    sleep(1);
    managed_shared_memory segment(open_only, "MySharedMemory");

    // Find the vector using the c-string name
    MyVector *myvector = segment.find<MyVector>("MyVector").first;
    auto mymtx = segment.find<interprocess_mutex>("Mymtx").first;
    scoped_lock<interprocess_mutex> lock(*mymtx);

    // Use vector in reverse order
    std::sort(myvector->rbegin(), myvector->rend());
    for (size_t i = 0; i < myvector->size(); i++) {
      std::cout << "vec[" << i << "] = " << myvector->at(i) << std::endl;
    }

    // When done, destroy the vector from the segment
    segment.destroy<MyVector>("MyVector");
  }

  return;
}
