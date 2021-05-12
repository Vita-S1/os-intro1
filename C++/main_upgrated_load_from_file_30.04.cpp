#include <iostream>
#include <string>
using namespace std;

class elem{
    string name;
    int id;
    string surname;
    elem* next;
    elem* prev;
public:
    elem(string name_ = "")
    {
        name = name_;
        next = nullptr;
        prev = nullptr;
        cout<<"elem with name "<<name<<" created\n";
    }
    void set_next(elem* next_) { next = next_; }
    void set_prev(elem* prev_) { prev = prev_; }
    elem* get_next() { return next; }
    elem* get_prev() { return prev; }
    elem(elem &other) { this->name = other.name; }
    void set_name(string name_) { name = name_;}
    string get_name() { return name;}
    ~elem() {cout<<"elem with name "<<name<<" deleted\n";}
    //elem operator= (elem &other) { cout<<"= called\n"; this->name = other.name; return other;}
};

class list
{
public:
    elem* head;
    elem* tail;
    int count; //количество элементов
    list() { head = nullptr; tail = nullptr; count = 0;}
    ~list()
    {
        elem* cur_elem = head;
        while(cur_elem != nullptr)
        {
            elem* del_elem = cur_elem;
            cur_elem = cur_elem->get_next();
            delete del_elem;
        }
    }

    void print()
    {
        elem* cur_elem = head;
        while(cur_elem != nullptr)
        {
            cout<<cur_elem->get_name()<<"\n";
            cur_elem = cur_elem->get_next();
        }
    }
    void inverted_print()
    {
        elem* cur_elem = tail;
        while(cur_elem != nullptr)
        {
            cout<<cur_elem->get_name()<<"\n";
            cur_elem = cur_elem->get_prev();
        }
    }

    void push_back(elem* last)//
    {
        cout<<"push_back is called\n";
        elem *add = new elem(last->get_name());
        if(head == nullptr)//в списке нет элементов
        {
            head = add;
            tail = add;
            count++;
            return;
        }
        elem* cur_elem = tail;
        cur_elem->set_next(add);//устанавливаем прямой указатель
        add->set_prev(tail);//установаливаем обратный указатель
        tail = add;//меняем значение указателя на последний элемент
        count++;
    }

    void push_front(elem* front) //положить элемент в начало списка
    {
        elem *add = new elem();
        add->set_name(front->get_name());
        if(head == nullptr)
        {
            head = add;
            tail = add;
            count++;
            return;
        }
        add->set_next(head);
        head->set_prev(add);
        head = add;
        count++;
    }
    void insert(int place, elem* new_elem)
    {
        if(head == nullptr)
            return;
        if(place >= count)
        {
            cout<<"Error! Not enough elements in list!\n";
            return;
        }
        else if(place + 1 == count)
            push_back(new_elem);
        else
        {
            elem *add = new elem(new_elem->get_name());
            int k = 0;
            elem* cur_elem = head;
            while(k < place)
            {
                cur_elem = cur_elem->get_next();
                if(cur_elem == nullptr)
                    break;
                k++;
            }
            add->set_next(cur_elem->get_next());
            add->set_prev(cur_elem);
            cur_elem->get_next()->set_prev(add);
            cur_elem->set_next(add);
            count++;
        }
    }
    void insert(elem after, elem* new_elem)
    {
        if(head == nullptr)
            return;
        if(after.get_name() == tail->get_name())
            push_back(new_elem);
        else
        {
            elem* add = new elem(new_elem->get_name());
            elem* cur_elem = head;
            while(cur_elem != nullptr && cur_elem->get_name() != after.get_name())
                cur_elem = cur_elem->get_next();
            if(cur_elem == nullptr)
            {
                cout<<"Element with required name is not found\n";
                return;
            }
            add->set_next(cur_elem->get_next());
            add->set_prev(cur_elem);
            cur_elem->get_next()->set_prev(add);
            cur_elem->set_next(add);
            count++;
        }
    }
};

int main()
{
    list my_list;
    int elem_num;
    cout<<"Input amount of elements:"<<endl;
    cin>>elem_num;
    elem new_elem;
    for(int i=0; i<elem_num; i++)
    {
        string name, after_name;
        int index;
        int operation = 0;
        cout<<"Insert name of element:"<<endl;
        cin>>name;
        new_elem.set_name(name);
        cout<<"Now we have "<<my_list.count<<" elements\n";
        cout<<"Choose operation: \n 1 - push_front\n \
2 - push_back\n \
3 - insert after index\n \
4 - insert after element\n";
        cin>>operation;
        if(operation <=0 || operation > 4)
        {
            cout<<"Error! wrong operation! Insert 1,2,3 or 4\n";
            i--;
            continue;
        }
        if(operation == 3)
        {
            cout<<"Insert index:\n";
            cin>>index;
        }
        else if(operation == 4)
        {

            cout<<"Insert name:\n";
            cin>>after_name;
        }
        new_elem.set_name(name);
        if(operation == 1)
            my_list.push_front(&new_elem);
        else if(operation == 2)
            my_list.push_back(&new_elem);
        else if(operation == 3)
            my_list.insert(index, &new_elem);
        else if(operation == 4)
        {
            elem after_elem(after_name);
            my_list.insert(after_elem, &new_elem);
        }
    }
    my_list.print();
    return 0;
}

