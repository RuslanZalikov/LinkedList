#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;

template <typename type_node>
struct Node{
    type_node data;
    Node* next;
    Node(type_node data = 0, Node* next = nullptr){
        this->data = data;
        this->next = next;
    }
};

template <typename type>
class LinkedList{
public:
    Node<type>* start = new Node<type>;
    Node<type>* finish = new Node<type>;
    void add(type value){      //добавление в список
        Node<type>* temp = new Node<type>;
        temp->data = value;
        if (start->next == nullptr){
            start->next = temp;
        }
        else{
            finish->next = temp;
        }
        finish = temp;
    }

    void add_begin(type value){   //добавить в начало
        Node<type>* temp = new Node<type>;
        temp->data = value;
        if (start->next == nullptr){
            start->next = temp;
            finish = temp;
        }
        else{
            temp->next = start->next;
            start->next = temp;
        }
    }

    void addByIndex(type value, int index){ //добавить в любое место списка по индексу,
        index--;                            //кроме начала и конца, для этого использовать add и add_begin
        Node<type>* temp;
        index = min(index, this->len());
        int count = 0;
        temp = this->start->next;
        while(count != index){
            count++;
            temp = temp->next;
        }
        Node<type>* newnode = new Node<type>;
        newnode->data = value;
        newnode->next = temp->next;
        temp->next = newnode;
    }

    bool isEmpty(){       //проверка на пустоту
        if (start->next == nullptr) return true;
        return false;
    }

    void error(Node<type>* n){  //Обработка исключения выхода за пределы списка
        if(n == nullptr){
            throw "Заступ за пределы";
        }
    }

    type find(int index){     //Возвращения значения по индексу
        Node<type>* temp;
        temp = this->start;
        for (int i = 0; i <= index; i++){
            temp = temp->next;
            try{
                error(temp);
            }
            catch(const exception& e){
                cout << e.what();
            }
        }
        return temp->data;
    }

    Node<type>* find_node(int index){     //Возвращения самого элемента(Node) по индексу
        Node<type>* temp;
        temp = this->start;
        for (int i = 0; i <= index; i++){
            temp = temp->next;
            try{
                error(temp);
            }
            catch(const exception& e){
                cout << e.what();
            }
        }
        return temp;
    }

    void del(int index){    //удаление элемента по индексу
        Node<type>* target;
        if (index == 0){
            target = start->next;
            start->next = target->next;
            delete target;
        }
        else if (index == this->len() - 1){
            Node<type>* temp;
            temp = this->find_node(index-1);
            target = this->find_node(index);
            temp->next = target->next;
            finish = temp;
            delete target;
        }
        else {
            Node<type>* temp;
            temp = this->find_node(index-1);
            target = this->find_node(index);
            temp->next = target->next;
            delete target;
        }
    }

    int len(){       //Длина списка
        int count = 0;
        Node<type>* temp;
        temp = this->start->next;
        while(temp != this->finish->next){
            temp = temp->next;
            count++;
        }
        return count;
    }

    vector<type> ListToVector(){ //Превращение списка в вектор
        vector<type> vec;
        Node<type>* temp;
        temp = this->start->next;
        while(temp != this->finish->next){
            vec.push_back(temp->data);
            temp = temp->next;
        }
        return vec;
    }

    map<type, int> ListToMap(){ //Превращение списка в словарь, значения - это количество повторов элемента
        map<type, int> mp;
        Node<type>* temp;
        temp = this->start->next;
        while(temp != this->finish->next){
            if(mp.find(temp->data) == mp.end()){
                mp.insert(make_pair(temp->data, 1));
            }
            else {
                mp[temp->data]++;
            }
            temp = temp->next;
        }
        return mp;
    }

    void print(){ // Вывод списка с начала до конца
        cout << "\n";
        Node<type>* temp;
        temp = this->start->next;
        while(temp != this->finish->next){
            cout << temp->data << " ";
            temp = temp->next;
        }
    }

    void rprint(){ // Вывод списка с конца до начала
        cout << "\n";
        for (int index = this->len()-1; index >= 0; index--){
            Node<type>* temp = this->find_node(index);
            cout << temp->data << " ";
        }
    }

    int search(type value, int repeat = 1){ //поиск по уникальным и неуникальным признакам, простыми словами поиск индекса какого либо элемента
        map<type, int> mp = this->ListToMap();  //второй аргумент это, если есть повторные элементы, то какой по порядку повторный элемент взять, по умолчанию первый попавшийся
        int index = 0;
        if(mp.find(value) == mp.end() || index > this->len()-1){
            error(nullptr);
        }
        else{
            repeat = min(repeat, mp[value]);
            int count = 1;
            Node<type>* temp;
            temp = this->start->next;
            while(temp != this->finish->next){
                if(value == temp->data && count == repeat){
                    return index;
                }
                else if(value == temp->data && count != repeat){
                    count++;
                }
                index++;
                temp = temp->next;
            }
        }
    }
    int rsearch(type value, int repeat = 1){ //тоже самое что и обычный search только с конца
        map<type, int> mp = this->ListToMap();
        int index = this->len()-1;
        if(mp.find(value) == mp.end() || index < 0){
            error(nullptr);
        }
        else{
            repeat = min(repeat, mp[value]);
            int count = 1;
            Node<type>* temp;
            temp = this->finish;
            while(temp != start){
                if(value == temp->data && count == repeat){
                    return index;
                }
                else if(value == temp->data && count != repeat){
                    count++;
                }
                index--;
                temp = this->find_node(index);
            }
        }
    }

    void addLinkedList(LinkedList<type> newList){ //добавить связный список
        this->finish->next = newList.start->next;
        this->finish = newList.finish;
    }

    LinkedList<type> Double(type value){ //удвоение заданных элементов
        LinkedList<type> newList;
        Node<type>* temp;
        temp = this->start->next;
        while(temp != this->finish->next){
            newList.add(temp->data);
            temp = temp->next;
        }
        bool flag = false;
        int count = 1;
        int newcount = 1;
        while(!flag){
            int i;
            i = this->search(value, count);
            if (i == 0){
                newList.add_begin(value);
            }
            else if (i == this->len()-1){
                newList.add(value);
            }
            else{
                newList.addByIndex(value, newList.search(value, newcount));
            }
            if(i == this->rsearch(value)){
                flag = true;
            }
            count++;
            newcount += 2;
        }
        return newList;
    }

};

int main() {
    LinkedList<int> firstList;
    LinkedList<int> secondList;
    cout << "Введите первый список: ";

    string s, buf;
    getline(cin, s); // считали все в строку
    s.push_back(' '); // заэкранировали конец строки для получения последнего числа
    for (int i = 0; i < s.length(); i++){ // цикл в котором сканируются все числа из строки
        if (s[i] != ' '){ // если не пробел
            buf += s[i]; // ложить очередной символ в буфер
        } else {
            if (buf.length() != 0) // если строка не пустая
                firstList.add(atoi(buf.c_str())); // преоброзовать в число и положить в вектор

            buf.clear(); // очищаем буфер под следующие символы
        }
    }


    cout << "Введите второй список: ";

    getline(cin, s); // считали все в строку
    s.push_back(' '); // заэкранировали конец строки для получения последнего числа
    for (int i = 0; i < s.length(); i++){ // цикл в котором сканируются все числа из строки
        if (s[i] != ' '){ // если не пробел
            buf += s[i]; // ложить очередной символ в буфер
        } else {
            if (buf.length() != 0) // если строка не пустая
                secondList.add(atoi(buf.c_str())); // преоброзовать в число и положить в вектор

            buf.clear(); // очищаем буфер под следующие символы
        }
    }



    firstList.addLinkedList(secondList); //сцепляем их
    cout << "Сцепленный список: ";
    firstList.print(); //выводим сцепленный список
    cout << "\n";

    cout << "\nДлина сцепленного списка: " << firstList.len(); // выводим длину сцепленного списка
    cout << "\n";

    LinkedList<int> newList;  //новый список
    int ch;
    cout << "\nВведите число, которое хотите удвоить в списке: ";
    cin >> ch;
    newList = firstList.Double(ch); //удваиваем все элементы со значением 6
    cout << "\nНовый список с удвоинными элементами: ";
    newList.print();
}
