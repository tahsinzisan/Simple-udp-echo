#ifndef CLIENT_H
#define CLIENT_H

#include <boost/asio.hpp>
#include <string>

using boost::asio::ip::udp;

class UDPEchoClient {
public:
    UDPEchoClient(boost::asio::io_context& io_context, const std::string& server_ip, short server_port);
    void send_message(const std::string& message);

private:
    udp::socket socket_;
    udp::endpoint server_endpoint_;
};

#endif
