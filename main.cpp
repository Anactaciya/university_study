#include <string>
#include <fstream>
#include <memory>
#include <unordered_map>
#include <iostream>


/*
Класс, отвечающий за запись в файл использует RAII
Для этого используется умный указатель
*/
class FileWriter {
    std::unique_ptr<std::ofstream> file_;
public:
    explicit FileWriter(const std::string& filename) : file_(std::make_unique<std::ofstream>(filename, std::ios::app)) {
        if (!file_->is_open()) {
            throw std::runtime_error("Can't open file: " + filename);
        }
    }

    ~FileWriter() {
        if (file_ && file_->is_open()) {
            file_->close();
        }
    }

    // запрещаем копирование
    FileWriter(const FileWriter&) = delete;
    FileWriter& operator=(const FileWriter&) = delete;

    // разрешаем перемещение
    FileWriter(FileWriter&& other) noexcept = default;
    FileWriter& operator=(FileWriter&& other) noexcept = default;

    void Write(const std::string& data) {
        if (file_ && file_->is_open()) {
            *file_ << data << std::flush;
        }
    }

};

// Базовый класс для сущностей
class Entity {
    FileWriter writer_;
public:
    explicit Entity(std::string filename) : writer_(std::move(filename)) {}

    virtual ~Entity() = default;

    // запрещаем копирование
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

    // разрешаем перемещение
    Entity(Entity&& other) noexcept = default;
    Entity& operator=(Entity&& other) noexcept = default;

    void Add(const std::string& key, const std::string& value) {
        writer_.Write("{\"" + key + "\":\"" + value + "\"}\n");
    }
};


// заводим сущности
class AnimalEntity : public Entity {
public:
    AnimalEntity() : Entity("animals.json") {}
};

class ProductEntity : public Entity {
public:
    ProductEntity() : Entity("products.json") {}
};


int main() {
    AnimalEntity animal1;
    animal1.Add("type", "cat");
    animal1.Add("sound", "meow");
    animal1.Add("food", "fish");

    // Проверка перемещения
    AnimalEntity animal2 = std::move(animal1);
    animal2.Add("color", "black");

    ProductEntity product;
    product.Add("title", "Laptop");
    product.Add("price", "1000");

    return 0;
}
