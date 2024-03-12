
// #include <gtest/gtest.h>

// #include <thread>
// #include <zmqpp/zmqpp.hpp>

// // apt install libzmqpp-dev

// static void TcpServer() {
//   const std::string endpoint = "tcp://*:5555";

//   // initialize the 0MQ context
//   zmqpp::context context;

//   // generate a pull socket
//   zmqpp::socket_type type = zmqpp::socket_type::reply;
//   zmqpp::socket socket(context, type);

//   // bind to the socket
//   socket.bind(endpoint);
//   while (1) {
//     // receive the message
//     zmqpp::message message;
//     // decompose the message
//     socket.receive(message);
//     std::string text;
//     message >> text;
//     std::cout << "receive : " << text << std::endl;

//     // Do some 'work'
//     std::this_thread::sleep_for(std::chrono::seconds(1));
//     std::cout << "send world" << std::endl;
//     socket.send("World");
//   }
// }

// static void TcpClient() {
//   const std::string endpoint = "tcp://localhost:5555";

//   // initialize the 0MQ context
//   zmqpp::context context;

//   // generate a push socket
//   zmqpp::socket_type type = zmqpp::socket_type::req;
//   zmqpp::socket socket(context, type);

//   // open the connection
//   std::cout << "Connecting to hello world server…" << std::endl;
//   socket.connect(endpoint);
//   int request_nbr;
//   for (request_nbr = 0; request_nbr != 10; request_nbr++) {
//     // send a message
//     std::cout << "Sending Hello " << request_nbr << "…" << std::endl;
//     zmqpp::message message;
//     // compose a message from a string and a number
//     message << "Hello";
//     socket.send(message);
//     std::string buffer;
//     socket.receive(buffer);

//     std::cout << "Received World " << request_nbr << std::endl;
//   }
// }

// TEST(boost, zmq) {
//   auto ret = fork();
//   std::cout << "pid : " << ret << std::endl;
//   if (ret > 0)  // sub process
//   {
//     TcpClient();
//     printf("TcpClient end \n");
//     return;
//   }

//   //
//   TcpServer();
//   printf("TcpServer end \n");
// }