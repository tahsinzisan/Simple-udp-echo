#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
#include <array>

using boost::asio::ip::udp;

class UDPEchoServer {
public:
    UDPEchoServer(boost::asio::io_context& io_context, short port);

private:
    void start_receive();
    void send_response(std::size_t length);

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    std::array<char, 1024> recv_buffer_;
};

#endif
