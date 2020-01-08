#include "socket.hh"
#include "util.hh"
#include <arpa/inet.h>
#include <cstdlib>
#include <iostream>

using namespace std;

void get_URL(const string &host, const string &path) {
    
    // You will need to connect to the "http" service on
    // the computer whose name is in the "host" string,
    // then request the URL path given in the "path" string.
    TCPSocket sock{};
    hostent * record = gethostbyname(host.c_str());
    if(record == NULL){
		cerr << host << " is unavailable" << endl;
		exit(1);
	}
    in_addr * address = (in_addr * )record->h_addr;
    string ip_address = inet_ntoa(* address);

    sock.connect(Address(ip_address, 80));
    string s = "GET " + path + " HTTP/1.1\r\nHost: " + host +"\r\n\r\n";
    sock.write(s);
    sock.shutdown(SHUT_WR);

    // Then you'll need to print out everything the server sends back,
    // (not just one call to read() -- everything) until you reach
    // the "eof" (end of file).

    string r;
    while (!(r = sock.read()).empty()){
        cout << r;
    }
    sock.shutdown(SHUT_RD);

    // cerr << "Function called: get_URL(" << host << ", " << path << ").\n";
    // cerr << "Warning: get_URL() has not been implemented yet.\n";
}

int main(int argc, char *argv[]) {
    try {
        if (argc <= 0) {
            abort();  // For sticklers: don't try to access argv[0] if argc <= 0.
        }

        // The program takes two command-line arguments: the hostname and "path" part of the URL.
        // Print the usage message unless there are these two arguments (plus the program name
        // itself, so arg count = 3 in total).
        if (argc != 3) {
            cerr << "Usage: " << argv[0] << " HOST PATH\n";
            cerr << "\tExample: " << argv[0] << " stanford.edu /class/cs144\n";
            return EXIT_FAILURE;
        }

        // Get the command-line arguments.
        const string host = argv[1];
        const string path = argv[2];

        // Call the student-written function.
        get_URL(host, path);
    } catch (const exception &e) {
        cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
