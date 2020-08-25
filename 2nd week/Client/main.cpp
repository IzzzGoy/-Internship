#include <iostream>
#include "Client.h"

using namespace std;



int main() {
    Client c(1488,"127.0.0.1");
    while (c.is_work()){
        this_thread::sleep_for(chrono::seconds(1));
    }
    /*WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN addr;

    WSAStartup(MAKEWORD(2,0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // replace the ip with your futur server ip address. If server AND client are running on the same computer, you can use the local ip 127.0.0.1
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1488);

    connect(server, (SOCKADDR *)&addr, sizeof(addr));
    cout << "Connected to server!" << endl;

    char buffer[1024];
    while (true){
        string input;
        cin >> input;
        if (input == "exit"){
            send(server, input.data(), sizeof(buffer), 0);
            break;
        }
        send(server, input.data(), sizeof(buffer), 0);
        recv(server,buffer,sizeof(buffer),0);
        cout << buffer << endl;
    }

    closesocket(server);
    WSACleanup();
    cout << "Socket closed." << endl << endl;*/

    return 0;
}
