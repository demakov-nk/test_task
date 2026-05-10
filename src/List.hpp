#pragma once

#include <string>

class List
{
    struct ListNode 
    {
        ListNode* prev = nullptr;
        ListNode* next = nullptr;
        ListNode* rand = nullptr; 
        std::string data; 
    };

    class Iterator
    {
        friend List;

        ListNode* m_node = nullptr;

    public:
        inline constexpr Iterator(ListNode* node);
        inline constexpr Iterator(const Iterator& rhs) noexcept;

        inline constexpr Iterator& operator= (const Iterator& rhs) noexcept;
        inline constexpr Iterator& operator++ ();
        inline constexpr Iterator operator++ (int);
        inline constexpr Iterator& operator-- ();
        inline constexpr Iterator operator-- (int);
        inline std::string& operator* () const;
        inline std::string* operator-> () const;

        inline constexpr bool operator== (const Iterator& other) const;
        inline constexpr bool operator!= (const Iterator& other) const;
    };

    class ConstIterator
    {
        friend List;

        const ListNode* m_node = nullptr;

    public:
        inline constexpr ConstIterator(const ListNode* node);
        inline constexpr ConstIterator(const ConstIterator& rhs) noexcept;

        inline constexpr ConstIterator& operator= (const ConstIterator& rhs) noexcept;
        inline constexpr ConstIterator& operator++ ();
        inline constexpr ConstIterator operator++ (int);
        inline constexpr ConstIterator& operator-- ();
        inline constexpr ConstIterator operator-- (int);
        inline const std::string& operator* () const;
        inline const std::string* operator-> () const;

        inline constexpr bool operator== (const ConstIterator& other) const;
        inline constexpr bool operator!= (const ConstIterator& other) const;
    };

    ListNode* m_head = nullptr;
    ListNode m_tail;
    size_t m_size;

public:
    explicit List(size_t size = 0, const std::string& fill_value = "");
    inline List(const List& rhs) noexcept;
    inline List(List&& rhs) noexcept;
    inline ~List();

    List& operator= (const List& rhs) noexcept;
    List& operator= (List&& rhs) noexcept;

    inline constexpr Iterator begin();
    inline constexpr ConstIterator begin() const;
    inline constexpr Iterator end();
    inline constexpr ConstIterator end() const;

    inline constexpr size_t size() const;
    
    void push_front(const std::string& new_elem, int rand_index = -1);
    void push_front(std::string&& new_elem, int rand_index = -1);
    void push_back(const std::string& new_elem, int rand_index = -1);
    void push_back(std::string&& new_elem, int rand_index = -1);

    void pop_front();
    void pop_back();
    void remove(const std::string& elem);

    void add_rand(int index, int rand_index);
    inline int get_rand_index(const Iterator& it) const;
    inline int get_rand_index(const ConstIterator& it) const;

    void clear();

private:
    ListNode* node_from_index(int index);
    int index_from_node(const ListNode* node) const;
    void make_null_if_rand(const ListNode* rand);
};


/* inline List methods */
// public
inline List::List(const List& rhs) noexcept
    { *this = rhs; }
inline List::List(List&& rhs) noexcept
    { *this = std::move(rhs); }
inline List::~List()
    { clear(); }
inline constexpr size_t List::size() const
    { return m_size; }
inline constexpr List::Iterator List::begin()
    { if (m_head) return Iterator(m_head); return Iterator(&m_tail); }
inline constexpr List::ConstIterator List::begin() const
    { if (m_head) return ConstIterator(m_head); return ConstIterator(&m_tail); }
inline constexpr List::Iterator List::end()
    { return Iterator(&m_tail); }
inline constexpr List::ConstIterator List::end() const
    { return ConstIterator(&m_tail); }
inline int List::get_rand_index(const Iterator& it) const
    { return index_from_node(it.m_node->rand); }
inline int List::get_rand_index(const ConstIterator& it) const
    { return index_from_node(it.m_node->rand); }

/* inline Iterator methods */
//public
inline constexpr List::Iterator::Iterator(ListNode* node)
    : m_node(node) {}
inline constexpr List::Iterator::Iterator(const Iterator& rhs) noexcept
    { *this = rhs; }
inline constexpr List::Iterator& List::Iterator::operator= (const List::Iterator& rhs) noexcept
    { if (this == &rhs) return *this; m_node = rhs.m_node; return *this; }
inline constexpr List::Iterator& List::Iterator::operator++ ()
    { m_node = m_node->next; return *this; }
inline constexpr List::Iterator List::Iterator::operator++ (int)
    { Iterator old = *this; ++(*this); return old; }
inline constexpr List::Iterator& List::Iterator::operator-- ()
    { m_node = m_node->prev; return *this; }
inline constexpr List::Iterator List::Iterator::operator-- (int)
    { Iterator old = *this; --(*this); return old; }
inline std::string& List::Iterator::operator* () const
    { return m_node->data; }
inline std::string* List::Iterator::operator-> () const
    { return &(m_node->data);  }
inline constexpr bool List::Iterator::operator== (const Iterator& other) const
    { return m_node == other.m_node; }
inline constexpr bool List::Iterator::operator!= (const Iterator& other) const
    { return !operator==(other); }

/* inline ConstIterator methods */
//public
inline constexpr List::ConstIterator::ConstIterator(const ListNode* node)
    : m_node(node) {}
inline constexpr List::ConstIterator::ConstIterator(const ConstIterator& rhs) noexcept
    { *this = rhs; }
inline constexpr List::ConstIterator& List::ConstIterator::operator= (const ConstIterator& rhs) noexcept
    { if (this == &rhs) return *this; m_node = rhs.m_node; return *this; }
inline constexpr List::ConstIterator& List::ConstIterator::operator++ ()
    { m_node = m_node->next; return *this; }
inline constexpr List::ConstIterator List::ConstIterator::operator++ (int)
    { ConstIterator old = *this; ++(*this); return old; }
inline constexpr List::ConstIterator& List::ConstIterator::operator-- ()
    { m_node = m_node->prev; return *this; }
inline constexpr List::ConstIterator List::ConstIterator::operator-- (int)
    { ConstIterator old = *this; --(*this); return old; }
inline const std::string& List::ConstIterator::operator* () const
    { return m_node->data; }
inline const std::string* List::ConstIterator::operator-> () const
    { return &(m_node->data); }
inline constexpr bool List::ConstIterator::operator== (const ConstIterator& other) const
    { return m_node == other.m_node; }
inline constexpr bool List::ConstIterator::operator!= (const ConstIterator& other) const
    { return !operator==(other); }
