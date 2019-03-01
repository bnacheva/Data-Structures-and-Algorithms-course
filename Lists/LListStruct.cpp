#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct LinkedList {
private:
    struct Node {
        Node * next;
        int value;

        Node(int _value, Node * _next = NULL) : value(_value), next(_next) {}
    };

    Node * head;
    size_t size;
public:
    LinkedList() {
        head = NULL;
        size = 0;
    }

    void add(int x, int pos) {
        if (pos < 0 || pos > size) {
            cout << "add_last";
            pos = size;
        }

        if (!head || pos == 0) {
            head = new Node(x, head);
        } else {
            Node * cur = head;

            while (pos > 1) {
                pos--;
                cur = cur->next;
            }

            cur->next = new Node(x, cur->next);
        }

        size++;
    }

    void remove(int pos) {
        if (pos < 0 || pos >= size) {
            cout << "remove_failed";
            return;
        }

        Node * prev = NULL;
        Node * cur = head;

        while (pos > 0) {
            prev = cur;
            cur = cur->next;
            pos--;
        }

        if (prev == NULL) {
            prev = head->next;
            delete head;
            head = prev;
        } else {
            prev->next = cur->next;
            delete cur;
        }

        size--;
    }
    void print() {
        Node * temp = head;

        while (temp != NULL) {
            cout << temp->value << "#";
            temp = temp->next;
        }
    }

    void reverse() {
        Node * reversed = NULL;

        while (head != NULL) {
            Node * temp = head->next;

            head->next = reversed;
            reversed = head;
            head = temp;
        }

        head = reversed;
    }

    void is_palindrome() {
        int * values = new int[size];
        Node * cur = head;

        for (int i = 0; i < size; i++, cur = cur->next) {
            values[i] = cur->value;
        }

        for (int i = 0; i < size / 2; i++) {
            if (values[i] != values[size - 1 - i]) {
                cout << "false";
                delete[] values;
                return;
            }
        }

        delete[] values;
        cout << "true";
    }

    void count(int x) {
        int counter = 0;

        Node * temp = head;

        while (temp != NULL) {
            if (temp->value == x) {
                counter++;
            }

            temp = temp->next;
        }

        cout << counter;
    }

    void remove_all(int x) {
        Node * cur = head;

        while (cur && cur->next) {
            if (cur->next->value == x) {
                Node * temp = cur->next->next;
                delete cur->next;
                cur->next = temp;
                size--;
            } else {
                cur = cur->next;
            }
        }

        if (head && head->value == x) {
            Node * temp = head->next;
            delete head;
            head = temp;
            size--;
        }
    }

    void group(int startPos, int endPos) {
        if (startPos < 0 || endPos >= size || endPos < startPos) {
            cout << "fail_grouping";
        } else {
            int elements_to_delete = endPos - startPos;
            Node * cur = head;

            while (startPos > 0) {
                cur = cur->next;
                startPos--;
            }

            while (elements_to_delete > 0) {
                Node * temp = cur->next->next;
                cur->value += cur->next->value;
                delete cur->next;
                cur->next = temp;

                elements_to_delete--;
                size--;
            }
        }
    }
};

int main() {
    int cases;
    std::cin >> cases;
    for (int i = 0; i < cases; i++) {
        LinkedList ll;
        int ops;
        std::string op;
        std::cin >> ops;
        for (int j = 0; j < ops; j++) {
            std::cin >> op;

            if (op == "count") {
                int arg1;
                std::cin >> arg1;
                ll.count(arg1);
            }

            if (op == "add") {
                int arg1, arg2;
                std::cin >> arg1 >> arg2;
                ll.add(arg1, arg2);
            }

            if (op == "print") {
                ll.print();
            }

            if (op == "remove") {
                int arg1;
                std::cin >> arg1;
                ll.remove(arg1);
            }

            if (op == "reverse") {
                ll.reverse();
            }

            if (op == "remove_all") {
                int arg1;
                std::cin >> arg1;
                ll.remove_all(arg1);
            }

            if (op == "group") {
                int arg1, arg2;
                std::cin >> arg1 >> arg2;
                ll.group(arg1, arg2);
            }

            if (op == "is_palindrom") {
                ll.is_palindrome();
            }
        }

        std::cout << std::endl;

    }
    return 0;
}
