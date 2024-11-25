#pragma once
#include <set>
#include "ConverterJSON.h"
#include "InvertedIndex.h"

struct RelativeIndex
{
    size_t docId;
    float rank;
    bool operator ==(const RelativeIndex& other) const {
        return (docId == other.docId && rank == other.rank);
    }
};


class SearchServer {
private:
    InvertedIndex index;
    std::vector<std::vector<RelativeIndex>> resultSearch;
public:
    // Получаем экземпляр класса InvertedIndex
    explicit SearchServer(InvertedIndex& idx);

    // Получаем вектор с запросами для поиска и максимальное количество ответов на один запрос
    // Функция возвращает вектор с данными по релеватности документов каждому запросу 
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& inQueries, int responsesLimit);

    // Функция для получения строки с одним запросом, номера запроса и максимального количества ответов на один запрос
    void handleRequest(const std::string& request, int i, int responsesLimit);
};

