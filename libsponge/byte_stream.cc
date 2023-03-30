#include "byte_stream.hh"

#include <algorithm>
#include <iterator>
#include <stdexcept>

using namespace std;

ByteStream::ByteStream(const size_t capacity)
    :_que(), 
     _capacity(capacity),
     _n_write(0),
     _n_read(0),
     _end_input(false),
     _error(false) {}

size_t ByteStream::write(const string &data) {
    if(_end_input) return 0;
    size_t n_write = min(data.size(), _capacity - _que.size());
    _n_write += n_write;
    for(size_t i = 0; i < n_write; i++) _que.push_back(data[i]);
    return n_write;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    int peek_size = min(len, _que.size());
    return string(_que.begin(), _que.begin() + peek_size);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) { 
    int pop_size = min(_que.size(), len);
    _n_read += pop_size;
    while(pop_size --) _que.pop_front();
}

void ByteStream::end_input() { _end_input = true; }

bool ByteStream::input_ended() const { return _end_input; }

size_t ByteStream::buffer_size() const { return _que.size(); }

bool ByteStream::buffer_empty() const { return _que.empty(); }

bool ByteStream::eof() const { return _end_input && _que.empty(); }

size_t ByteStream::bytes_written() const { return _n_write; }

size_t ByteStream::bytes_read() const { return _n_read; }

size_t ByteStream::remaining_capacity() const { return _capacity - _que.size(); }
