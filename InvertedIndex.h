#pragma once
#include <iostream>
#include <mutex>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

struct Entry
{
    size_t docId, count;
    bool operator ==(const Entry& other) const {
        return (docId == other.docId &&
            count == other.count);
    }
};



class InvertedIndex {
private:
    std::vector<std::string> docs;
    std::map<std::string, std::vector<Entry>> freqDictionary;
public:
    InvertedIndex() = default;

    // Функция для получения вектора со списком документов
    void UpdateDocumentBase(std::vector<std::string> inDocs);

    // Функция для получения строки с текстом из документа и его порядкового номера
    void PutFreqDictionary(std::string inWords, int i);

    // Функция для получения частотного словаря
    std::map<std::string, std::vector<Entry>> GetFreqDictionary();

    // Получаем слово, по которому делаем поиск в частотном словаре
    // Функция возвращает частотные данные по данному слову
    std::vector<Entry> GetWordCount(const std::string& word);
};


