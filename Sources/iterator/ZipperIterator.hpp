#ifndef ZIPPERITERATOR_HPP_
#define ZIPPERITERATOR_HPP_

    #include <iterator>
    #include <utility>
    #include "Zipper.hpp"
    #include <vector>

    template <class ...Containers>
    class ZipperIterator {
        template <class Container>
        using iterator_t = decltype(std::declval<Container>().begin());

        template <class Container>
        using it_reference_t = typename iterator_t<Container>::reference;

        public:
            using value_type = std::tuple<decltype(std::declval<it_reference_t<Container>>().value())&...>;
            using reference = value_type;
            using pointer = void;
            using difference_type = size_t;
            using iterator_category = std::forward_iterator_tag;
            using iterator_tuple = std::tuple<iterator_t<Containers>...>;

            friend Zipper<Containers...>;
            ZipperIterator(iterator_tuple const &it_tuple, size_t max) 
                : _current(it_tuple), _max(max), _idx(0) {
                if (!allSet(seq))
                    incrAll(seq);
            }

        public:
            ZipperIterator(ZipperIterator const &z)
                : _current(z._current), _max(z.max), _idx(z.idx) {}

            ZipperIterator operator++() {
                incrall(std::index_sequence<seq>);
                return *this;
            }

            ZipperIterator &operator++(int) {
                auto cpy = *this;
                incrall(std::index_sequence<seq>);
                return cpy;
            }

            value_type operator*() {
                return toValue(seq);
            }

            value_type operator->() {
                return toValue(seq);
            }

            friend bool operator==(ZipperIterator const &lhs, ZipperIterator const &rhs) {
                return lhs._current == rhs._current;
            }

            friend bool operator!=(ZipperIterator const &lhs, ZipperIterator const &rhs) {
                return lhs._current != rhs._current;
            }

        private:
            template <size_t ...Is>
            void incrAll(std::index_sequence<Is...>) {
                for (; _idx < _max && allSet(_seq); _idx++)
                    ((++(std::get<Is>(_current))), ...);
            }

            template <size_t ...Is>
            bool allSet(std::index_sequence<Is...>) {
                return (true && ... && *std::get<Is>(_current));
            }

            template <size_t ...Is>
            value_type toValue(std::index_sequence<Is...>) {
                return std::tie((*std::get<Is>(_current)).value()...);
            }

        private:
            iterator_tuple _current;
            size_t _max;
            size_t _idx;

            static constexpr std::index_sequence_for<Containers ...> _seq{};

    };

#endif /* !ZIPPERITERATOR_HPP_ */
