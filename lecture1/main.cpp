#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <locale>
struct Person{
    std::string name;
    int friend_index;
};
Person* getFriend(int person_index,std::vector<Person>& Journal){
    if (person_index>=0 && person_index<Journal.size()){
        int friend_index = Journal[person_index].friend_index;
        if (friend_index>=0 && friend_index<Journal.size()){
            return &Journal[friend_index];
        }
    }
    return nullptr;
}
void showallpeople(std::vector<Person>& Journal){
    for (int i = 0;i<Journal.size();++i){
        std::cout<<Journal[i].name<<std::endl;
        Person* friend_ptr = getFriend(i,Journal);
        if (friend_ptr){
            std::cout<<"->"<<friend_ptr->name;
        }
        else{
            std::cout<<" -> интроверт";
        }
        std::cout<<std::endl;
    }
}
void showintroverts(const std::vector<Person>& Journal){
    bool found = false;
    for (int i = 0;i<Journal.size();++i){
        if (Journal[i].friend_index == -1){
            std::cout<<Journal[i].name<<std::endl;
            found = true;
        }
    }
    if (!found){
        std::cout<<"Интровертов Нет";
    }
}
void showverybestfriends(std::vector<Person>& Journal){
    bool found = false;
    for (int i = 0;i<Journal.size();++i){
        Person* friend_ptr = getFriend(i,Journal);
        if (friend_ptr){
            int friend_index = Journal[i].friend_index;
            if (friend_index>=0 && friend_index < Journal.size()){
                if (Journal[friend_index].friend_index == i){
                    if (i<friend_index){
                        std::cout<<Journal[i].name<<"<->"<<friend_ptr->name<<std::endl;
                        found = true;
                    }
                }
            }
        }

    }
    if (!found){
        std::cout<<"Пар very best friends"<<std::endl;
    }
}
void secret(std::vector<Person>& Journal){
    std::string name;
    std::cout<<"От кого начинаем ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin,name);
    int current_index = -1;
    for (int i = 0;i<Journal.size();++i){
        if (Journal[i].name == name){
            current_index = i;
            break;
        }
    }
    if (current_index == -1){
        std::cout<<"Человек не найден"<<std::endl;
        return;
    }
    std::cout<<"Цепочка секрета: ";
    bool visited[100] = {false};
    int current = current_index;
    while (current != -1 && !visited[current]){
        visited[current] = true;
        std::cout<<Journal[current].name;
        int next_index = Journal[current].friend_index;
        if (next_index != -1 && next_index<Journal.size() && !visited[next_index]){
            std::cout<<" -> ";
            current = next_index;
        }
        else{
            current = -1;
        }

    std::cout<<std::endl;

    }
}
bool PersonExits(const std::string& name,const std::vector<Person>& Journal){
    for (int i = 0;i<Journal.size();++i){
        if (Journal[i].name == name){
            return true;
        }
    }
    return false;
}
void addNeWperson(std::vector<Person>& Journal){
    std::string name;
    std::cout<<"Введите имя нового человека";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin,name);
    if (PersonExits(name,Journal)){
        std::cout<<"ОШИБКА.Такой человек уже существует в журнале"<<std::endl;
    }
    //Добавляем нового человека(интроверта)
    Person new_person;
    new_person.name = name;
    new_person.friend_index = -1;
    Journal.push_back(new_person);
    std::cout<<"Добавлен: "<<name<<std::endl;

}
int main(){
    setlocale(LC_ALL,"ru_RU.UTF-8");
    std::vector<Person> journal = { 
        {"Vanya",1},
        {"Petya",2},
        {"Vova",0},
        {"Sergey",4},
        {"eVGENIY",3},
        {"Aleksey",2},
        {"Masha",-1},
        {"Elena",-1}
    };
    int choice;
    do{
        std::cout<<"\n===МЕНЮ===\n";
        std::cout<<"1.Просмотр всех людей"<<std::endl;
        std::cout<<"2.Цепочка секрета"<<std::endl;
        std::cout<<"3.Показать интровертов"<<std::endl;
        std::cout<<"4.Very best friends"<<std::endl;
        std::cout<<"5.Создание нового элемента"<<std::endl;
        std::cout<<"0.Выход"<<std::endl;
        std::cin>>choice;
        switch(choice){
            case 1:
                showallpeople(journal);
                break;
            case 2:
                secret(journal);
                break;
            case 3:
                showintroverts(journal);
                break;
            case 4:
                showverybestfriends(journal);
                break;
            case 5:
                addNeWperson(journal);
                break;
            case 0:
                return 0;
            default:
                std::cout<<"Выбран неверный пункт меню"<<std::endl;
                break;
        }
    } while(choice!=0);


    return 0;
}