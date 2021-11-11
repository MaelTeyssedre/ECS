#ifndef ENTITY_HPP_
    #define ENTITY_HPP_

    class Registry;

    class Entity {
        public:
            operator size_t() const;
            ~Entity() = default;
        protected:
            friend class Registry;
            explicit Entity(size_t id);
        private:
            size_t _id;
    };

#endif /* !ENTITY_HPP_ */
