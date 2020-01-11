#include "stream_reassembler.hh"
#include <iostream>

// Dummy implementation of a stream reassembler.

// For Lab 1, please replace with a real implementation that passes the
// automated checks run by `make check_lab1`.

// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

StreamReassembler::StreamReassembler(const size_t capacity) 
    : _output(capacity), _capacity(capacity), _tmp(std::set<Packet, cmp_Packet>()), tmp_size(0) {}

//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
void StreamReassembler::push_substring(const string &data, const size_t index, const bool eof) {
    if (_output.input_ended())
        return;
    
    if(_output.bytes_written() >= index && _output.bytes_written() <= index + data.size()) {
        _output.write(data.substr(_output.bytes_written()-index, data.size() - (_output.bytes_written()-index)));
        while (!_tmp.empty() && _output.bytes_written() >= _tmp.begin()->index){
            if(_output.bytes_written() >= _tmp.begin()->index + _tmp.begin()->data.size()){
                tmp_size -= _tmp.begin()->add;
                _tmp.erase(_tmp.begin());
            } else {
                const string d = _tmp.begin()->data;
                const size_t i = _tmp.begin()->index;
                const bool e = _tmp.begin()->eof;
                tmp_size -= _tmp.begin()->add;
                _tmp.erase(_tmp.begin());
                this->push_substring(d, i, e);
            }
        }

        if (eof) {
            _output.end_input();
        }
    }
    else if(_output.bytes_written() < index) {
        auto res = _tmp.emplace(index,data,eof);
        if (res.second){

            if (res.first == _tmp.begin() && res.first == std::prev(_tmp.end())) {
                res.first->add = data.size();
            } else if (res.first == _tmp.begin()) {
                while (res.first != std::prev(_tmp.end()) && std::next(res.first)->index + std::next(res.first)->data.size() <= index + data.size()){
                    tmp_size -= std::next(res.first)->add;
                    _tmp.erase(std::next(res.first));
                }
                if (res.first == std::prev(_tmp.end()))
                    res.first->add = data.size();
                else
                    res.first->add = std::next(res.first)->index < (index + data.size()) ? (std::next(res.first)->index - index):data.size();
            } else if (res.first == std::prev(_tmp.end())) {
                if (std::prev(res.first)->index + std::prev(res.first)->data.size() < index + data.size())
                    res.first->add = (std::prev(res.first)->index + std::prev(res.first)->data.size()) > index ? ((index+data.size())-(std::prev(res.first)->index + std::prev(res.first)->data.size())):data.size();
            } else {
                if (std::prev(res.first)->index + std::prev(res.first)->data.size() < index + data.size()){
                    while (res.first != std::prev(_tmp.end()) && std::next(res.first)->index + std::next(res.first)->data.size() <= index + data.size()){
                        tmp_size -= std::next(res.first)->add;
                        _tmp.erase(std::next(res.first));
                    }
                    size_t begin = (std::prev(res.first)->index + std::prev(res.first)->data.size()) > index ? (std::prev(res.first)->index + std::prev(res.first)->data.size()) : index;
                    size_t end;
                    if (res.first == std::prev(_tmp.end()))
                        end = index + data.size();
                    else
                        end = std::next(res.first)->index < (index + data.size()) ? std::next(res.first)->index : (index + data.size());
                    res.first->add = end - begin;
                }
                
            }
            tmp_size += res.first->add;
            //std::cout<<tmp_size<<std::endl;
        };
    } 

}

size_t StreamReassembler::unassembled_bytes() const { 
    return tmp_size; 

}

bool StreamReassembler::empty() const { 
    return tmp_size == 0;
}
