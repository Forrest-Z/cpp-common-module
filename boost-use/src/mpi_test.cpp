// #include <gtest/gtest.h>

// #include <boost/mpi.hpp>

// void mpi_func() {
//   mpi::environment env;
//   mpi::communicator world;

//   if (world.rank() == 0) {
//     // 主进程
//     int data_to_send = 42;

//     // 发送数据到进程1
//     world.send(1, 0, data_to_send);

//     std::cout << "Process 0 sent data to Process 1: " << data_to_send
//               << std::endl;
//   } else if (world.rank() == 1) {
//     // 进程1
//     int received_data;

//     // 接收来自进程0的数据
//     world.recv(0, 0, received_data);

//     std::cout << "Process 1 received data from Process 0: " << received_data
//               << std::endl;
//   }
// }

// TEST(boost, mpi) {
//   auto ret = fork();
//   std::cout << "pid : " << ret << std::endl;
//   sleep(1);
//   mpi_func();
// }