#include "byte_stream.hh"

#include <algorithm>
#include <iterator>
#include <stdexcept>

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) : 
    cpty(capacity), end(false), written_num(0), read_num(0), buffer(deque<char>()) {
}

size_t ByteStream::write(const string &data) {
    if(this->end)
        return 0;
    size_t i;
    for(i = 0; i<data.length(); i++) {
        if(this->cpty>0){
            this->cpty--;
            this->buffer.push_back(data[i]);
        } else {
            break;
        }
    }
    this->written_num += i;
    return i;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    string res = "";
    size_t l = len < this->buffer_size() ? len : this->buffer_size();
    for(size_t i=0; i<l; i++){
        res += this->buffer[i];
    }
    return res;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    size_t l = len < this->buffer_size() ? len : this->buffer_size();
    for(size_t i=0; i<l; i++){
        this->buffer.pop_front();
    }
    this->read_num += l;
    this->cpty += l;
}

void ByteStream::end_input() {
    this->end = true;
}

bool ByteStream::input_ended() const {
    return this->end;
}

size_t ByteStream::buffer_size() const {
    return this->buffer.size();
}

bool ByteStream::buffer_empty() const {
    return this->buffer.empty();
}

bool ByteStream::eof() const {
    return this->buffer_empty() && this->input_ended();
}

size_t ByteStream::bytes_written() const {
    return this->written_num;
}

size_t ByteStream::bytes_read() const { 
    return this->read_num;
}

size_t ByteStream::remaining_capacity() const { 
    return this->cpty;
}
