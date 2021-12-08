#include <iostream>
/**
 * @author DYLAN SOARES
 * Dec 7th 2021
 * @version 2
 * Addition now works thanks to Kaval
 * */

using namespace std;

struct Node {
    char data{};
    Node *next;

    Node() {
        next = nullptr;
    }
};

class LinkedList {
private:
    Node *head;
    int len;
public:
    LinkedList() {
        head = nullptr;
        len = 0;
    }

    void insertEnd(char data) {
        Node *curr = head;
        if (curr != nullptr) {
            while (curr->next != nullptr) {
                curr = curr->next;
            }

            Node *node = new Node();
            node->data = data;
            curr->next = node;
        } else {
            insertStart(data);
        }
        this->len++;
    }

    void insertStart(char data) {
        Node *temp = new Node();
        temp->data = data;
        temp->next = head;
        head = temp;
        this->len++;
    }

    void printList() {
        Node *curr = head;
        while (curr != nullptr) {
            std::cout << curr->data;
            curr = curr->next;
        }
    }

    //TODO remove by data
    //TODO remove start
    //TODO remove end

    void reverse() {
        Node *next;
        Node *curr = head;
        Node *prev = nullptr;
        while (curr != nullptr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    int length() {
        return this->len;
    }

    LinkedList operator+(LinkedList list2) {
        auto resultList = new LinkedList;
        int sum;
        int carry = 0;

        this->reverse();
        list2.reverse();

        Node *curr1 = this->head;
        Node *curr2 = list2.head;

        while (curr1 != nullptr && curr2 != nullptr) {
            sum = ((int) (curr1->data - 48) + (int) (curr2->data - 48)) + carry;
            if(sum+48 >= 48) {
                if (sum > 9) {
                    carry = 1;
                } else {
                    carry = 0;
                }
                resultList->insertStart((char) (sum%10 + 48));
            }
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        if (carry > 0) {
            resultList->insertStart('1');
        }

        /*resultList->reverse();*/
        return *resultList;
    }

    void calculateDiffLength(LinkedList list2) {
        if (this->length() < list2.length()) {
            int diff = list2.length() - this->length();
            this->addPrecedingZeroes(diff);
        }
    }

    void addPrecedingZeroes(int diff) {
        for (int i = 0; i < diff; i++) {
            this->insertStart('0');
        }
    }

};


int main() {
    auto *firstNumber = new LinkedList;

    auto *secondNumber = new LinkedList;

    cout << "Enter characters as one line, press enter to finish.\nEx: 5857285297952<enter>\n";
    int c1;
    int c2;
    do {
        c1 = getchar();
        //inserting at start ensures already reversed list
        firstNumber->insertEnd(c1);
    } while (c1 != '\n');
    cout << "Enter a second number to add.\nEx: 5857285297952<enter>\n";
    do {
        c2 = getchar();
        //inserting at start ensures already reversed list
        secondNumber->insertEnd(c2);
    } while (c2 != '\n');

    firstNumber->calculateDiffLength(*secondNumber);
    secondNumber->calculateDiffLength(*firstNumber);

    cout << "Doing addition...\n";

    cout << "  ";
    firstNumber->printList();
    cout << "+ ";
    secondNumber->printList();
    cout << "__________________________________________________\n";
    //END DEBUG OUTPUT

    LinkedList resultList = *firstNumber + *secondNumber;
    cout << "  ";
    resultList.printList();
    cout << "\n";
}
