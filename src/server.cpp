#include "include/server.h"
#include <iostream>

UDPEchoServer::UDPEchoServer(boost::asio::io_context& io_context, short port)
    : socket_(io_context, udp::endpoint(udp::v4(), port)) {
    start_receive();
}

void UDPEchoServer::start_receive() {
    socket_.async_receive_from(
        boost::asio::buffer(recv_buffer_), remote_endpoint_,
        [this](boost::system::error_code ec, std::size_t bytes_recvd) {
            if (!ec) {
                send_response(bytes_recvd);
            }
            start_receive();  // Continue listening for next messages
        });
}

void UDPEchoServer::send_response(std::size_t length) {
    socket_.async_send_to(
        boost::asio::buffer(recv_buffer_, length), remote_endpoint_,
        [](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/) {});
}

int main() {
    try {
        boost::asio::io_context io_context;
        UDPEchoServer server(io_context, 1337);
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
