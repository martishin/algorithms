#pragma once

#include <memory>
#include <stdexcept>

namespace NLinkedList {
    template<typename T>
    class LinkedList {
    public:
        struct LinkedListNode {
            std::unique_ptr<LinkedListNode> Next;
            T Data;

            explicit LinkedListNode(const T& data)
                : Data(data) {}
        };

        template <bool Const = true>
        class LinkedListIterator {
        private:
            using NodeType = typename std::conditional<Const, const LinkedListNode, LinkedListNode>::type;
            LinkedListNode* NodePtr;
        public:
            explicit LinkedListIterator(LinkedListNode* node)
                : NodePtr(node)
            {}

            LinkedListIterator(const LinkedListIterator& other)
                : NodePtr(other.NodePtr)
            {}

            LinkedListIterator& operator=(LinkedListIterator other) {
                std::swap(NodePtr, other.NodePtr);
                return *this;
            }

            LinkedListIterator& operator++() {
                NodePtr = NodePtr->Next.get();
                return *this;
            }

            const LinkedListIterator operator++(int) {
                LinkedListIterator it(*this);
                NodePtr = NodePtr->Next.get();
                return it;
            }

            bool operator==(const LinkedListIterator& other) const noexcept {
                return NodePtr == other.NodePtr;
            }

            bool operator!=(const LinkedListIterator& other) const noexcept {
                return !(*this == other);
            }

            NodeType& operator*() const {
                return *NodePtr;
            }

            NodeType* operator->() const {
                return NodePtr;
            }
        };

        using iterator = LinkedListIterator<false>;
        using const_iterator = LinkedListIterator<true>;

        LinkedList() = default;

        LinkedList(std::initializer_list<T> list) {
            for (const T &data: list) {
                PushBack(data);
            }
        }

        LinkedList(const LinkedList& other) {
            for (auto it = other.cbegin(); it != other.cend(); ++it) {
                PushBack(*it);
            }
        }

        LinkedList& operator=(LinkedList other) {
            swap(*this, other);
            return *this;
        }

        LinkedList(LinkedList&& other) noexcept
            : Head(std::move(other.Head))
        {
            Size_ = other.Size_;
            other.Size_ = 0;
        }

        LinkedList& operator=(LinkedList&& other) noexcept {
            if(this != &other) {
                Head = std::move(other.Head);
                Size_ = other.Size_;
                other.Size_ = 0;
            }
            return *this;
        }

        const LinkedListNode& operator[](std::size_t position) const {
            if (position > Size() - 1) {
                throw std::out_of_range("");
            }

            auto currentNode = GetHead();

            for (size_t i = 0; i < position; ++i) {
                currentNode = currentNode->Next.get();
            }

            return *currentNode;
        }

        LinkedListNode& operator[](std::size_t position) {
            return const_cast<LinkedListNode&> (static_cast<const LinkedList&>(*this)[position]);
        }

        void PushBack(const T &data) {
            auto currentNode = GetHead();

            if (currentNode) {
                while (currentNode->Next) {
                    currentNode = currentNode->Next.get();
                }
                currentNode->Next = std::make_unique<LinkedListNode>(data);
            } else {
                Head = std::make_unique<LinkedListNode>(data);
            }

            ++Size_;
        }

        void Erase(std::size_t position) {
            auto& node = (*this)[position];

            if (position == 0) {
                Head = std::move(node.Next);
            } else if (position == Size() - 1) {
                PopBack();
            } else {
                node.Data = node.Next->Data;
                node.Next = std::move(node.Next->Next);
            }
        }

        void PopBack() {
            auto currentNode = GetHead();

            while (currentNode->Next->Next) {
                currentNode = currentNode->Next.get();
            }
            currentNode->Next = nullptr;
        }

        LinkedListNode* GetHead() {
            return Head.get();
        }

        const LinkedListNode* GetHead() const {
            return Head.get();
        }

        friend void swap(LinkedList& lhs, LinkedList& rhs) {
            std::swap(lhs.Size_, rhs.Size_);
            std::swap(lhs.Head, rhs.Head);
        }

        iterator begin() {
            return iterator(Head.get());
        }

        iterator end() {
            return iterator(nullptr);
        }

        const_iterator cbegin() const {
            return const_iterator(Head.get());
        }

        const_iterator cend() const {
            return const_iterator(nullptr);
        }

        std::size_t Size() const noexcept {
            return Size_;
        }
    private:
        std::unique_ptr<LinkedListNode> Head;
        std::size_t Size_ = 0;
    };
}

