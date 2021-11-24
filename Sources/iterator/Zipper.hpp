#ifndef ZIPPER_HPP_
#define ZIPPER_HPP_

#include "ZipperIterator.hpp"
#include <algorithm>

template <class ...Containers>
class Zipper {
    public:
        using iterator = ZipperIterator<Containers...>;
        using iterator_tuple = typename iterator::iterator_tuple;
        
        Zipper(Containers &... cs)
            : _size(0) {
            _size = _computeSize(cs...);
            _end = _computeEnd(cs...);
            _begin = _computeBegin(cs...);
        };

        iterator begin() {
            return iterator(_begin, _size);
        }
        iterator end() {
            return iterator(_end, 0);
        }

    private:
        static size_t _computeSize(Containers &... containers) {
            return std::min({(containers.size())...});
        }

        static iterator_tuple _computeBegin(Containers &... containers) {
            return std::tie((containers.begin())...);
        }

        static iterator_tuple _computeEnd(Containers &... containers) {
            return std::tie((containers.begin() + _size)...);
        }
    
    private:
        iterator_tuple _begin;
        iterator_tuple _end;
        size_t _size;
};

#endif /* !ZIPPER_HPP_ */
