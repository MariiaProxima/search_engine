#pragma once
#include <iostream>
#include <vector> 
#include <fstream>
#include <string>
#include <exception>
#include "../nlohmann_json/nlohmann_json/single_include/nlohmann/json.hpp"


class ConverterJSON {
private:
    nlohmann::json objJson;
    std::fstream fileInput;
    int responsesLimit = 5;

public:
    ConverterJSON() = default;
    // Функция возвращает список документов, в которых надо произвести поиск
    std::vector<std::string> GetTextDocuments();

    // Функция возвращает список запросов, по которым надо произвести поиск в документах
    std::vector<std::string> GetRequests();

    // Функция для получения вектора с данными по релеватности документов каждому запросу
    void putAnswers(std::vector<std::vector<std::pair<int, float>>>answers);

    void checkFileConfigJSON();

    // Функция возвращает максимальное количество ответов на один запрос
    int GetResponsesLimit() const;
};

