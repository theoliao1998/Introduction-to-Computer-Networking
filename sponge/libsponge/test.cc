#include "wrapping_integers.hh"

#include <cstdint>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main() {
    cout << unwrap(WrappingInt32(1), WrappingInt32(0), 0)<< endl;
    cout <<unwrap(WrappingInt32(1), WrappingInt32(0), UINT32_MAX)<< endl;
    cout << (unwrap(WrappingInt32(UINT32_MAX - 1), WrappingInt32(0), 3 * (1ul << 32)))<< endl;
    cout << unwrap(WrappingInt32(UINT32_MAX - 10), WrappingInt32(0), 3 * (1ul << 32))<< endl;
    cout << unwrap(WrappingInt32(UINT32_MAX), WrappingInt32(10), 3 * (1ul << 32))<< endl;
    cout << unwrap(WrappingInt32(UINT32_MAX), WrappingInt32(0), 0)<< endl;
    cout << unwrap(WrappingInt32(16), WrappingInt32(16), 0)<< endl;
    cout <<unwrap(WrappingInt32(15), WrappingInt32(16), 0)<< endl;
    cout << unwrap(WrappingInt32(0), WrappingInt32(INT32_MAX), 0)<< endl;
    cout <<unwrap(WrappingInt32(UINT32_MAX), WrappingInt32(INT32_MAX), 0)<< endl;
    cout <<unwrap(WrappingInt32(UINT32_MAX), WrappingInt32(1ul << 31), 0)<< endl;

    cout<<"test"<<endl;
    cout<<static_cast<uint64_t>(UINT32_MAX)<<endl;
    cout<<static_cast<uint64_t>(INT32_MAX)+2<<endl;
    cout<<(static_cast<uint64_t>(1)<<31)<<endl;
    cout<<(static_cast<uint64_t>(UINT32_MAX)>>1)<<endl;

}