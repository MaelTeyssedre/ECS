#ifndef ZIPPER_HPP_
#define ZIPPER_HPP_

#include "ZipperIterator.hpp"
#include <algorithm>
namespace ecs
{
    template <class... Containers>
    class Zipper
    {
    public:
        using iterator = ZipperIterator<Containers...>;
        using iterator_tuple = typename iterator::iterator_tuple;

        Zipper(Containers &...cs)
            : _size(0)
        {
            _computeSize(cs...);
            _computeEnd(cs...);
            _computeBegin(cs...);
        };

        iterator begin()
        {
            return iterator(_begin, _size);
        }

        iterator end()
        {
            return iterator(_end, 0);
        }

    private:
        void _computeSize(Containers &...containers)
        {
            _size = std::min({(containers.size())...});
        }

        void _computeBegin(Containers &...containers)
        {
            _begin = std::forward_as_tuple((containers.begin())...);
        }

        void _computeEnd(Containers &...containers)
        {
            _end = std::forward_as_tuple((containers.begin() + _size)...);
        }

    private:
        iterator_tuple _begin;
        iterator_tuple _end;
        size_t _size;
    };
}

#endif