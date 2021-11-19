#ifndef ZIPPERITERATOR_HPP_
#define ZIPPERITERATOR_HPP_

    #include <iterator>
    #include <utility>
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
            using iterator_tuple = std::tuple<iterator_t<Container>...>;

            friend containers::zipper<Containers...>;
            ZipperIterator(iterator_tuple const &it_tuple, size_t max) {

            }

        public:
            ZipperIterator(ZipperIterator const &z) {

            }

            ZipperIterator operator++() {

            }

            ZipperIterator &operator++(int) {

            }

            value_type operator*() {

            }

            value_type operator->() {
                
            }

            friend bool operator==(ZipperIterator const &lhs, ZipperIterator const &rhs) {
                
            }

            friend bool operator!=(ZipperIterator const &lhs, ZipperIterator const &rhs) {

            }
        
        private:
            template <size_t ...Is>
            void incrAll(std::index_sequence<Is...>) {

            }

            template <size_t ...Is>
            void allSet(std::index_sequence<Is...>) {

            }
        
            template <size_t ...Is>
            value_type to_value(std::index_sequence<Is...>) {

            }

        private:
            iterator_tuple _current;
            size_t _max;
            size_t _idx;

            static constexpr std::index_sequence_for<Containers ...> _seq{};

    };

#endif /* !ZIPPERITERATOR_HPP_ */
