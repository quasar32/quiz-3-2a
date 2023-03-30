#include <iostream>
// include additional necessary headers

void query(/*add necessary parameters*/) {
    // Should print: the print number (starting from 0), "SYN", and the three dots "..."
}

void response(/*add necessary parameters*/) {
    // Should print "ACK"
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: ./handshake <count>\n");
        exit(1);
    }

    /**
     * Steps to follow:
     * 1. Get the "count" from cmd args
     * 2. Create necessary synchronization primitive(s)
     * 3. Create two threads, one for "SYN" and the other for "ACK"
     * 4. Provide the threads with necessary args
     * 5. Update the "query" and "response" functions to synchronize the output
    */
   
    return 0;
}