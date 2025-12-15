#include <iostream>

class SparseVector{
    private:
        class Node
        {
        public:
            int index;
            int value;
            Node *next;
            Node(int index, int value, Node *next = nullptr):
            index(index), value(value), next(next) { }
        };
        Node *head;
        int s;
        void clear();
        void copyList(const SparseVector &sv);
        void SetNonezeroel(int idx, int val);
        void remzerel(int idx);
        void checklistorder();        
        void addSubVector(const SparseVector &sv, bool add);
        void removeZeros();
    public:
        SparseVector(int size){
            head = nullptr;
            s = size;
        }
        SparseVector(const SparseVector& other) {
            head = nullptr;
            s = other.s;
            copyList(other);
        }
        ~SparseVector(){
            clear();
        }
        int getSize() const{
            return s;
        }
        void push_back(int index, int value);
        SparseVector& operator=(const SparseVector& other);
        bool operator==(const SparseVector& other) const;
        bool operator!=(const SparseVector& other) const;
        SparseVector& operator+=(const SparseVector& other);
        SparseVector& operator-=(const SparseVector& other);
        SparseVector operator+(const SparseVector &) const;
        SparseVector operator-(const SparseVector &) const;
        int getElem(int idx);
        void setElem(int index, int value);
};
void SparseVector::clear(){
    Node *curient = head;
    while(curient != nullptr){
        Node *next = curient->next;
        delete curient;
        curient = next;
    }
    head = nullptr;
};
void SparseVector::copyList(const SparseVector &sv){
    this->s = sv.s;
    if (sv.head == nullptr) {
        this->head = nullptr;
        return;
    }
    this->head = new Node(sv.head->index, sv.head->value);
    Node *curient_this = this->head;
    Node *curient_next = sv.head->next;
    while(curient_next != nullptr){
        curient_this->next = new Node(curient_next->index, curient_next->value);
        curient_this = curient_this->next;
        curient_next = curient_next->next;
    }
    checklistorder();
};
void SparseVector::push_back(int index, int value){
    if (head == nullptr)
    {
        head = new Node(index, value);
    }
    else
    {   
        Node *curient = this->head;
        while(curient->next != nullptr){
            curient = curient->next;
        }
        curient->next = new Node(index, value);
        }
    
};
SparseVector& SparseVector::operator=(const SparseVector& other){
    if (this == &other){
        return *this;
    }
    clear();
    s = other.s;
    if (other.head != nullptr){
        copyList(other);
    }
    return *this;
};
int SparseVector::getElem(int idx){
    checklistorder();
    Node *curient = head;
    while (curient != nullptr)
    {
        if (curient->index == idx){
            return curient->value;
        }
        if (curient->index > idx){
            return 0;
        }
        curient = curient -> next;
    } 
    return 0;
};
void SparseVector::SetNonezeroel(int idx, int val){
    // Если список пустой
    if (head == nullptr){
        head = new Node(idx, val);
        return;
    }
    // Если нужно вставить перед первым элементом
    if (head->index > idx){
        head = new Node(idx, val, head);
        return;
    }
    // Если первый элемент имеет нужный индекс
    if (head->index == idx){
        head->value = val;
        return;
    }
    // Ищем место для вставки
    Node* current = head;
    while (current->next != nullptr && current->next->index < idx) {
        current = current->next;
    }
    // Если нашли элемент с таким же индексом
    if (current->next != nullptr && current->next->index == idx) {
        current->next->value = val;
        return;
    }
    // Вставляем новый элемент
    current->next = new Node(idx, val, current->next);
    checklistorder();
};
void SparseVector::remzerel(int idx){
    if (head == nullptr) {
        return;
    }
    // Если удаляем первый элемент
    if (head->index == idx) {
        Node *temp = head;
        head = head->next;
        delete temp;
        return;
    }
    // Ищем элемент для удаления
    Node *current = head;
    Node *previous = nullptr;
    
    while (current != nullptr && current->index != idx) {
        previous = current;
        current = current->next;
    }
    // Если нашли элемент для удаления
    if (current != nullptr && current->index == idx) {
        previous->next = current->next;
        delete current;
    }
};
void SparseVector::setElem(int index, int value){
    if (index >= s){
        return;
    }
    if (value == 0){
        remzerel(index);
        return;
    }
    if (value != 0){
        SetNonezeroel(index,value);
        return;
    }
};
void SparseVector::checklistorder(){
    if (head == nullptr) {
        return;  // пустой список - ок
    }
    
    Node* current = head;
    while (current != nullptr && current->next != nullptr) {
        // Проверяем: следующий индекс должен быть БОЛЬШЕ текущего
        if (current->index >= current->next->index) {
            std::cout << "Ошибка порядка: " << current->index 
                      << " >= " << current->next->index << std::endl;
            return;
        }
        current = current->next;
    }
}
bool SparseVector::operator==(const SparseVector& other)const{
    if (s != other.s){
        return false;
    }
    Node *cur1 = head;
    Node *cur2 = other.head;
    while (cur1 != nullptr and cur2 != nullptr){
        if(cur1 -> value != cur2 -> value or cur1 -> index != cur2 -> index){
            return false;
        }
        cur1 = cur1->next;
        cur2 = cur2->next;
    }
    return (cur1 == nullptr and cur2 == nullptr);
}
bool SparseVector::operator!=(const SparseVector& other)const{
    if (not(*this == other)){
        return true;
    }
    return false;
}
void SparseVector::removeZeros() {
    if (head == nullptr) {
        return;
    }
    // 1. Удаляем нули в начале списка
    while (head != nullptr && head->value == 0) {
        Node* toDelete = head;
        head = head->next;
        delete toDelete;
    }
    if (head == nullptr) {
        return;  // весь список состоял из нулей
    }
    // 2. Удаляем нули в середине/конце списка
    Node* current = head->next;
    Node* prev = head;
    while (current != nullptr) {
        if (current->value == 0) {
            prev->next = current->next;
            delete current;
            current = prev->next;  // переходим к следующему после удалённого
        } else {
            prev = current;
            current = current->next;
        }
    }
}
void SparseVector::addSubVector(const SparseVector &sv, bool add){
    if (s != sv.s){
        std::cout<<"размеры векторов не совпадают";
        return;
    }
    int sign = (add ? 1 : -1);
    Node* cur1 = head;
    Node* cur2 = sv.head;
    Node* prev = nullptr;
    
    while (cur2 != nullptr) {
        // Случай A: cur1 закончился или cur1->index > cur2->index
        if (cur1 == nullptr || cur1->index > cur2->index) {
            Node* newNode = new Node(cur2->index, sign * cur2->value);
            
            if (prev == nullptr) {
                // Вставка в начало
                newNode->next = head;
                head = newNode;
                prev = head;
            } else {
                // Вставка между prev и cur1
                newNode->next = prev->next;
                prev->next = newNode;
                prev = newNode;
            }
            cur2 = cur2->next;
        }
        // Случай B: cur1->index == cur2->index
        else if (cur1->index == cur2->index) {
            cur1->value += sign * cur2->value;
            prev = cur1;
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        // Случай C: cur1->index < cur2->index
        else {
            prev = cur1;
            cur1 = cur1->next;
        }
    }
    removeZeros();
}


SparseVector& SparseVector::operator+=(const SparseVector& other){
    addSubVector(other,true);
    return *this;
}
SparseVector& SparseVector::operator-=(const SparseVector& other){
    addSubVector(other,false);
    return *this;
}
SparseVector SparseVector::operator+(const SparseVector& other)const{
    SparseVector new_vec(*this);
    new_vec += other;
    return new_vec;
}
SparseVector SparseVector::operator-(const SparseVector& other)const{
    SparseVector new_vec(*this);
    new_vec -= other;
    return new_vec;
}



int main() {
    SparseVector vec(10);
    SparseVector vec1(10);
    vec.setElem(7,100);
    vec1.setElem(7,200);
    std::cout<<vec.getElem(7);
    return 0;
}
