#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <locale>

struct Person {
    std::string name;
    int friend_index;
};

Person* getFriend(int person_index, std::vector<Person>& Journal) {
    if (person_index >= 0 && person_index < Journal.size()) {
        int friend_index = Journal[person_index].friend_index;
        if (friend_index >= 0 && friend_index < Journal.size()) {
            return &Journal[friend_index];
        }
    }
    return nullptr;
}

void showallpeople(std::vector<Person>& Journal) {
    std::cout << "=== ВСЕ ЛЮДИ В ЖУРНАЛЕ ===" << std::endl;
    for (size_t i = 0; i < Journal.size(); ++i) {
        std::cout << i + 1 << ". " << Journal[i].name;
        Person* friend_ptr = getFriend(i, Journal);
        if (friend_ptr) {
            std::cout << " -> " << friend_ptr->name;
        } else {
            std::cout << " -> интроверт";
        }
        std::cout << std::endl;
    }
}

void showintroverts(const std::vector<Person>& Journal) {
    std::cout << "=== ИНТРОВЕРТЫ ===" << std::endl;
    bool found = false;
    for (size_t i = 0; i < Journal.size(); ++i) {
        if (Journal[i].friend_index == -1) {
            std::cout << Journal[i].name << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "Интровертов нет" << std::endl;
    }
}

void showverybestfriends(std::vector<Person>& Journal) {
    std::cout << "=== VERY BEST FRIENDS ===" << std::endl;
    bool found = false;
    for (size_t i = 0; i < Journal.size(); ++i) {
        Person* friend_ptr = getFriend(i, Journal);
        if (friend_ptr) {
            int friend_index = Journal[i].friend_index;
            if (friend_index >= 0 && friend_index < Journal.size()) {
                if (Journal[friend_index].friend_index == i) {
                    if (i < friend_index) {  // Чтобы не выводить пары дважды
                        std::cout << Journal[i].name << " <-> " << friend_ptr->name << std::endl;
                        found = true;
                    }
                }
            }
        }
    }
    if (!found) {
        std::cout << "Пар very best friends нет" << std::endl;
    }
}

void secret(std::vector<Person>& Journal) {
    std::string name;
    std::cout << "От кого начинаем: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, name);
    
    int current_index = -1;
    for (size_t i = 0; i < Journal.size(); ++i) {
        if (Journal[i].name == name) {
            current_index = i;
            break;
        }
    }
    
    if (current_index == -1) {
        std::cout << "Человек не найден" << std::endl;
        return;
    }
    
    std::cout << "Цепочка секрета: ";
    // Используем вектор вместо массива фиксированного размера
    std::vector<bool> visited(Journal.size(), false);
    int current = current_index;
    bool first = true;
    
    while (current != -1 && !visited[current]) {
        visited[current] = true;
        if (!first) {
            std::cout << " -> ";
        }
        std::cout << Journal[current].name;
        first = false;
        
        int next_index = Journal[current].friend_index;
        if (next_index != -1 && next_index < Journal.size() && !visited[next_index]) {
            current = next_index;
        } else {
            current = -1;
        }
    }
    std::cout << std::endl;
}

bool PersonExits(const std::string& name, const std::vector<Person>& Journal) {
    for (size_t i = 0; i < Journal.size(); ++i) {
        if (Journal[i].name == name) {
            return true;
        }
    }
    return false;
}

void addNeWperson(std::vector<Person>& Journal) {
    std::string name;
    std::cout << "Введите имя нового человека: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, name);
    
    if (PersonExits(name, Journal)) {
        std::cout << "ОШИБКА. Такой человек уже существует в журнале" << std::endl;
        return;  // Добавлен return для выхода из функции
    }
    
    // Добавляем нового человека (интроверта)
    Person new_person;
    new_person.name = name;
    new_person.friend_index = -1;
    Journal.push_back(new_person);
    std::cout << "Добавлен: " << name << std::endl;
}

void showMenu() {
    std::cout << "\n=== МЕНЮ ===" << std::endl;
    std::cout << "1. Просмотр всех людей" << std::endl;
    std::cout << "2. Цепочка секрета" << std::endl;
    std::cout << "3. Показать интровертов" << std::endl;
    std::cout << "4. Very best friends" << std::endl;
    std::cout << "5. Создание нового элемента" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "Выберите пункт: ";
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    std::vector<Person> journal = { 
        {"Vanya", 1},
        {"Petya", 2},
        {"Vova", 0},
        {"Sergey", 4},
        {"eVGENIY", 3},
        {"Aleksey", 2},
        {"Masha", -1},
        {"Elena", -1}
    };
    
    int choice;
    do {
        showMenu();
        
        if (!(std::cin >> choice)) {
            std::cout << "Ошибка ввода! Пожалуйста, введите число." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        switch(choice) {
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
                std::cout << "Выход из программы." << std::endl;
                break;
            default:
                std::cout << "Выбран неверный пункт меню" << std::endl;
                break;
        }
    } while (choice != 0);

    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <locale>

struct Person {
    std::string name;
    int age;
    int friend_index;
};

Person* getFriend(int person_index, std::vector<Person>& Journal) {
    if (person_index >= 0 && person_index < Journal.size()) {
        int friend_index = Journal[person_index].friend_index;
        if (friend_index >= 0 && friend_index < Journal.size()) {
            return &Journal[friend_index];
        }
    }
    return nullptr;
}

void showallpeople(std::vector<Person>& Journal) {
    std::cout << "=== ВСЕ ЛЮДИ В ЖУРНАЛЕ ===" << std::endl;
    for (size_t i = 0; i < Journal.size(); ++i) {
        std::cout << i + 1 << ". " << Journal[i].name << " (" << Journal[i].age << " лет)";
        Person* friend_ptr = getFriend(i, Journal);
        if (friend_ptr) {
            std::cout << " -> " << friend_ptr->name << " (" << friend_ptr->age << " лет)";
        } else {
            std::cout << " -> интроверт";
        }
        std::cout << std::endl;
    }
}

void showintroverts(const std::vector<Person>& Journal) {
    std::cout << "=== ИНТРОВЕРТЫ ===" << std::endl;
    bool found = false;
    for (size_t i = 0; i < Journal.size(); ++i) {
        if (Journal[i].friend_index == -1) {
            std::cout << Journal[i].name << " (" << Journal[i].age << " лет)" << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "Интровертов нет" << std::endl;
    }
}

void showverybestfriends(std::vector<Person>& Journal) {
    std::cout << "=== VERY BEST FRIENDS ===" << std::endl;
    bool found = false;
    for (size_t i = 0; i < Journal.size(); ++i) {
        Person* friend_ptr = getFriend(i, Journal);
        if (friend_ptr) {
            int friend_index = Journal[i].friend_index;
            if (friend_index >= 0 && friend_index < Journal.size()) {
                if (Journal[friend_index].friend_index == i) {
                    if (i < friend_index) {
                        std::cout << Journal[i].name << " (" << Journal[i].age << " лет) <-> " 
                                  << friend_ptr->name << " (" << friend_ptr->age << " лет)" << std::endl;
                        found = true;
                    }
                }
            }
        }
    }
    if (!found) {
        std::cout << "Пар very best friends нет" << std::endl;
    }
}

void secret(std::vector<Person>& Journal) {
    std::string name;
    std::cout << "От кого начинаем: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, name);
    
    int current_index = -1;
    for (size_t i = 0; i < Journal.size(); ++i) {
        if (Journal[i].name == name) {
            current_index = i;
            break;
        }
    }
    
    if (current_index == -1) {
        std::cout << "Человек не найден" << std::endl;
        return;
    }
    
    std::cout << "Цепочка секрета: ";
    std::vector<bool> visited(Journal.size(), false);
    int current = current_index;
    bool first = true;
    
    while (current != -1 && !visited[current]) {
        visited[current] = true;
        if (!first) {
            std::cout << " -> ";
        }
        std::cout << Journal[current].name << " (" << Journal[current].age << " лет)";
        first = false;
        
        int next_index = Journal[current].friend_index;
        if (next_index != -1 && next_index < Journal.size() && !visited[next_index]) {
            current = next_index;
        } else {
            current = -1;
        }
    }
    std::cout << std::endl;
}

bool PersonExits(const std::string& name, const std::vector<Person>& Journal) {
    for (size_t i = 0; i < Journal.size(); ++i) {
        if (Journal[i].name == name) {
            return true;
        }
    }
    return false;
}

void addNeWperson(std::vector<Person>& Journal) {
    std::string name;
    int age;
    
    std::cout << "\n=== ДОБАВЛЕНИЕ НОВОГО ЧЕЛОВЕКА ===" << std::endl;
    std::cout << "Введите имя нового человека: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, name);
    
    if (PersonExits(name, Journal)) {
        std::cout << "ОШИБКА. Такой человек уже существует в журнале" << std::endl;
        return;
    }
    
    std::cout << "Введите возраст нового человека: ";
    if (!(std::cin >> age)) {
        std::cout << "Ошибка ввода возраста!" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    
    if (age < 0 || age > 150) {
        std::cout << "ОШИБКА. Некорректный возраст!" << std::endl;
        return;
    }
    
    // Спросим, интроверт ли человек
    char isIntrovert;
    std::cout << "Этот человек интроверт? (y/n): ";
    std::cin >> isIntrovert;
    
    Person new_person;
    new_person.name = name;
    new_person.age = age;
    
    if (isIntrovert == 'y' || isIntrovert == 'Y') {
        // Если интроверт
        new_person.friend_index = -1;
        Journal.push_back(new_person);
        std::cout << "Добавлен интроверт: " << name << " (" << age << " лет)" << std::endl;
    } else if (isIntrovert == 'n' || isIntrovert == 'N') {
        // Если не интроверт, нужно выбрать друга
        if (Journal.empty()) {
            std::cout << "В журнале нет людей, которых можно выбрать в друзья. " 
                      << name << " будет добавлен как интроверт." << std::endl;
            new_person.friend_index = -1;
            Journal.push_back(new_person);
        } else {
            // Покажем список людей для выбора друга
            std::cout << "\nДоступные люди для дружбы:" << std::endl;
            for (size_t i = 0; i < Journal.size(); ++i) {
                std::cout << i + 1 << ". " << Journal[i].name 
                          << " (" << Journal[i].age << " лет)";
                Person* friend_ptr = getFriend(i, Journal);
                if (friend_ptr) {
                    std::cout << " -> друг: " << friend_ptr->name;
                } else {
                    std::cout << " -> интроверт";
                }
                std::cout << std::endl;
            }
            
            int friend_choice;
            std::cout << "\nВыберите номер друга для " << name << " (1-" << Journal.size() << "): ";
            if (!(std::cin >> friend_choice)) {
                std::cout << "Ошибка ввода!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return;
            }
            
            if (friend_choice < 1 || friend_choice > Journal.size()) {
                std::cout << "Неверный выбор! " << name << " будет добавлен как интроверт." << std::endl;
                new_person.friend_index = -1;
            } else {
                // Вычитаем 1, потому что пользователь видит номера с 1
                new_person.friend_index = friend_choice - 1;
                std::cout << name << " теперь друг " << Journal[new_person.friend_index].name << std::endl;
            }
            
            Journal.push_back(new_person);
            std::cout << "Добавлен: " << name << " (" << age << " лет)" << std::endl;
        }
    } else {
        std::cout << "Неверный ввод! " << name << " будет добавлен как интроверт." << std::endl;
        new_person.friend_index = -1;
        Journal.push_back(new_person);
    }
}

void showMenu() {
    std::cout << "\n=== МЕНЮ ===" << std::endl;
    std::cout << "1. Просмотр всех людей" << std::endl;
    std::cout << "2. Цепочка секрета" << std::endl;
    std::cout << "3. Показать интровертов" << std::endl;
    std::cout << "4. Very best friends" << std::endl;
    std::cout << "5. Создание нового элемента" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "Выберите пункт: ";
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    std::vector<Person> journal = { 
        {"Vanya", 25, 1},
        {"Petya", 30, 2},
        {"Vova", 22, 0},
        {"Sergey", 28, 4},
        {"eVGENIY", 35, 3},
        {"Aleksey", 19, 2},
        {"Masha", 24, -1},
        {"Elena", 27, -1}
    };
    
    int choice;
    do {
        showMenu();
        
        if (!(std::cin >> choice)) {
            std::cout << "Ошибка ввода! Пожалуйста, введите число." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        switch(choice) {
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
                std::cout << "Выход из программы." << std::endl;
                break;
            default:
                std::cout << "Выбран неверный пункт меню" << std::endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
