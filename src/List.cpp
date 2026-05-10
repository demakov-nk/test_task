#include "List.hpp"

using namespace std;

/*********************************************************/
/********************** class List ***********************/
/*********************************************************/

/********** PUBLIC **********/

List::List(size_t size, const string& fill_value)
{
    if (size == 0) return;

    while (m_size < size) {
        push_back(fill_value);
    }
}

List& List::operator= (const List& rhs) noexcept
{
    if (this == &rhs) return *this;

    clear();

    for (const auto& rhs_elem : rhs) {
        push_back(rhs_elem);
    }
    return *this;
}

List& List::operator= (List&& rhs) noexcept
{
    if (this == &rhs) return *this;

    clear();
    m_head = rhs.m_head;
    m_tail = rhs.m_tail;
    m_tail.prev->next = &m_tail;
    m_size = rhs.m_size;
    

    rhs.m_head = rhs.m_tail.prev = nullptr;
    rhs.m_size = 0;
    return *this;
}

void List::push_front(const string& new_elem, int rand_index)
{
    ListNode* new_node = new ListNode;
    new_node->data = new_elem;
    new_node->rand = node_from_index(rand_index);

    if (!m_head) {
        new_node->next = &m_tail;
        m_tail.prev = new_node;
    } else {
        new_node->next = m_head;
        m_head->prev = new_node;
    }
    m_head = new_node;
    ++m_size;
}

void List::push_front(string&& new_elem, int rand_index)
{
    ListNode* new_node = new ListNode;
    new_node->data = std::move(new_elem);
    new_node->rand = node_from_index(rand_index);

    if (!m_head) {
        new_node->next = &m_tail;
        m_tail.prev = new_node;
    } else {
        new_node->next = m_head;
        m_head->prev = new_node;
    }
    m_head = new_node;
    ++m_size;
}

void List::push_back(const string& new_elem, int rand_index)
{
    ListNode* new_node = new ListNode;
    new_node->data = new_elem;
    new_node->next = &m_tail;

    if (m_head) {
        new_node->prev = m_tail.prev;
        m_tail.prev->next = new_node;
        m_tail.prev = new_node;
    } else {
        m_head = new_node;
        m_tail.prev = m_head;
    }
    ++m_size;

    new_node->rand = node_from_index(rand_index);
}

void List::push_back(string&& new_elem, int rand_index)
{
    ListNode* new_node = new ListNode;
    new_node->data = std::move(new_elem);
    new_node->next = &m_tail;

    if (m_head) {
        new_node->prev = m_tail.prev;
        m_tail.prev->next = new_node;
        m_tail.prev = new_node;
    } else {
        m_head = new_node;
        m_tail.prev = m_head;
    }
    ++m_size;

    new_node->rand = node_from_index(rand_index);
}

void List::pop_front()
{
    if (m_size == 0) return;

    make_null_if_rand(m_head);
    m_head = m_head->next;
    delete m_head->prev;
    if (m_head == &m_tail) {
        m_head = m_tail.prev = nullptr;
    }
    --m_size;
}

void List::pop_back()
{
    if (m_size == 0) return;

    if (m_size == 1) {
        pop_front();
    } else {
        make_null_if_rand(m_tail.prev);
        ListNode* x = m_tail.prev->prev;
        delete m_tail.prev;
        x->next = &m_tail;
        m_tail.prev = x;
        --m_size;
    }
}

void List::remove(const string& elem)
{
    if (m_size == 0) return;

    ListNode* node = m_head;
    while (node->data != elem)
    {
        if (node == &m_tail) return;
        node = node->next;
    }

    if (node == m_head) pop_front();
    else if (node == m_tail.prev) pop_back();
    else {
        make_null_if_rand(node);
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        --m_size;
    }
}

void List::add_rand(int index, int rand_index)
{
    if (index < 0 || index >= m_size) return;
    if (rand_index < 0 || rand_index >= m_size) return;

    ListNode* node = m_head;
    int i = 0;
    while (i < index) {
        node = node->next;
        i++;
    }

    node->rand = node_from_index(rand_index);
}

void List::clear()
{
    while (m_size > 0) {
        pop_front();
    }
}

/********** PRIVATE **********/

List::ListNode* List::node_from_index(int index)
{
    if (index < 0 || index >= m_size) return nullptr;

    ListNode* node = m_head;
    int i = 0;
    while (i < index) {
        node = node->next;
        i++;
    }
    return node;
}

int List::index_from_node(const ListNode* node) const
{
    if (!node) return -1;

    int i = 0;
    ListNode* n = m_head;
    while (n != node) {
        n = n->next;
        i++;
    }

    return i;
}

void List::make_null_if_rand(const ListNode* rand)
{
    if (!rand) return;

    ListNode* node = m_head;
    while (node != &m_tail) {
        if (node->rand == rand) {
            node->rand = nullptr;
        }
        node = node->next;
    }
}
