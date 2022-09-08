/**
 * \file Zipper.hpp
 *
 * \brief file where the Zipper class is defined
 */
#ifndef ZIPPER_HPP_
#define ZIPPER_HPP_

#include "ZipperIterator.hpp"
#include <algorithm>
namespace ecs
{
    /**
     * \class Zipper Zipper.hpp
     *
     * \brief Zipper of the ECS
     */
    template <class... Containers>
    class Zipper
    {
    public:
        using iterator = ZipperIterator<Containers...>;
        using iterator_tuple = typename iterator::iterator_tuple;

        /**
         * \fn Zipper(Containers &... cs)
         *
         * \brief ctor which take a reference of a variadic Containers object
         *
         * \param cs reference to a list of Containers object
         */
        Zipper(Containers &...cs)
            : _size(0)
        {
            _computeSize(cs...);
            _computeEnd(cs...);
            _computeBegin(cs...);
        };

        /**
         * \fn auto begin() -> iterator
         *
         * \brief go to the beginning of the Containers object
         */
        auto begin() -> iterator
        {
            return iterator(_begin, _size);
        }

        /**
         * \fn auto end() -> iterator
         *
         * \brief go to the end of the Containers object
         */
        auto end() -> iterator
        {
            return iterator(_end, 0);
        }

    private:
        /**
         * \fn auto _computeSize(Containers & ... containers) -> void
         *
         * \brief calculate the size of the shortest maximal size
         *
         * \param containers reference to a variadic Containers object
         */
        auto _computeSize(Containers &...containers) -> void
        {
            _size = std::min({(containers.size())...});
        }

        /**
         * \fn auto _computeBegin(Containers & ... containers) -> void
         *
         * \brief calculate the first tuple iterator tuple position
         *
         * \param containers reference to a variadic Containers object
         */
        auto _computeBegin(Containers &...containers) -> void
        {
            _begin = std::forward_as_tuple((containers.begin())...);
        }

        /**
         * \fn auto _computeEnd(Containers &  ...  containers) -> void
         *
         * \brief calculate the last tuple iterator tuple position
         *
         * \param containers reference to a variadic Containers object
         */
        auto _computeEnd(Containers &...containers) -> void
        {
            _end = std::forward_as_tuple((containers.begin() + _size)...);
        }

    private:
        iterator_tuple _begin; /*! first iterator of the element tuple */
        iterator_tuple _end;   /*! last iterator of the element tuple */
        size_t _size;          /*! size of the shortest maximal size */
    };
}

#endif /* !ZIPPER_HPP_ */