#include "include/client.h"
#include <string> 
#include <iostream>
using namespace std;
using namespace boost::asio;

UDPEchoClient::UDPEchoClient(io_context& io_context, const string& server_ip, short server_port)
    : socket_(io_context, udp::endpoint(udp::v4(), 0)) {
    udp::resolver resolver(io_context);
    server_endpoint_ = *resolver.resolve(udp::v4(), server_ip, to_string(server_port)).begin();
}

void UDPEchoClient::send_message(const string& message) {
    socket_.send_to(buffer(message), server_endpoint_);

    char reply[1024];
    udp::endpoint sender_endpoint;
    size_t length = socket_.receive_from(buffer(reply), sender_endpoint);

    cout << "Server replied: " << string(reply, length) << endl;
}

int main() {
    try {
        io_context io_context;
        UDPEchoClient client(io_context, "127.0.0.1", 1337);

        string message;
        cout << "Enter message: ";
        getline(cin, message);

        client.send_message(message);
    } catch (exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}
