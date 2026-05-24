#pragma once
#include <cstddef>

#include "exceptions.hpp"

template <typename T>
class LinkedList
{
   private:
    struct Node
    {
        T value;
        Node* next{nullptr};
        Node(const T& val) : value{val}, next{nullptr}
        {
        }
    };

    Node* head{nullptr};

   public:
    LinkedList()
    {
    }
    void Append(T item)
    {
        Node* newNode = new Node(item);
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node* current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }
    template <size_t N>
    LinkedList(T (&items)[N])
    {
        for (size_t i = 0; i < N; i++)
        {
            Append(items[i]);
        }
    }
    LinkedList(const LinkedList<T>& other)
    {
        Node* current = other.head;
        while (current != nullptr)
        {
            Append(current->value);
            current = current->next;
        }
    }
    ~LinkedList()
    {
        while (head != nullptr)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    LinkedList<T>& operator=(const LinkedList<T>& other)
    {
        if (this == &other)
        {
            return *this;
        }

        while (head != nullptr)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }

        Node* current = other.head;
        while (current != nullptr)
        {
            Append(current->value);
            current = current->next;
        }

        return *this;
    }
    class iterator
    {
       private:
        Node* current;

       public:
        iterator(Node* node) : current(node)
        {
        }
        T& operator*()
        {
            return current->value;
        }
        iterator& operator++()
        {
            current = current->next;
            return *this;
        }
        bool operator!=(const iterator& other) const
        {
            return current != other.current;
        }
    };

    iterator begin()
    {
        return iterator(head);
    }
    iterator end()
    {
        return iterator(nullptr);
    }
    T GetFirst() const
    {
        if (head == nullptr)
        {
            throw NullPointer{};
        }
        return head->value;
    }
    T GetLast() const
    {
        if (head == nullptr)
        {
            throw NullPointer{};
        }
        Node* current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        return current->value;
    }
    T Get(size_t index) const
    {
        if (index >= GetLength())
        {
            throw IndexOutOfRange{index, GetLength()};
        }
        Node* current = head;
        for (size_t i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current->value;
    }
    size_t GetLength() const
    {
        size_t length = 0;
        for (auto tmp = head; tmp != nullptr; tmp = tmp->next, length++);
        return length;
    }
    void Prepend(T item)
    {
        Node* newNode = new Node(item);
        newNode->next = head;
        head = newNode;
    }
    void InsertAt(T item, size_t index)
    {
        if (index > GetLength())
        {
            throw IndexOutOfRange{index, GetLength()};
        }

        if (index == 0)
        {
            Prepend(item);
            return;
        }

        if (index == GetLength())
        {
            Append(item);
            return;
        }

        Node* newNode = new Node(item);
        Node* current = head;
        for (size_t i = 0; i < index - 1; i++)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    LinkedList<T>* GetSubList(size_t from, size_t to) const
    {
        if (from > to || to >= GetLength())
        {
            throw InvalidArgument{};
        }

        LinkedList<T>* result = new LinkedList<T>();
        Node* current = head;
        for (size_t i = 0; i < from; i++)
        {
            current = current->next;
        }
        for (size_t i = from; i <= to; i++)
        {
            result->Append(current->value);
            current = current->next;
        }
        return result;
    }
    LinkedList<T>* Concat(LinkedList<T>* other) const
    {
        if (other == nullptr)
        {
            throw NullPointer{};
        }

        LinkedList<T>* result = new LinkedList<T>();
        Node* current = head;
        while (current != nullptr)
        {
            result->Append(current->value);
            current = current->next;
        }
        current = other->head;
        while (current != nullptr)
        {
            result->Append(current->value);
            current = current->next;
        }
        return result;
    }
    T& GetRef(size_t index)
    {
        if (index >= GetLength())
        {
            throw IndexOutOfRange{index, GetLength()};
        }
        Node* current = head;
        for (size_t i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current->value;
    }

    const T& GetRef(size_t index) const
    {
        if (index >= GetLength())
        {
            throw IndexOutOfRange{index, GetLength()};
        }
        const Node* current = head;
        for (size_t i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current->value;
    }
};