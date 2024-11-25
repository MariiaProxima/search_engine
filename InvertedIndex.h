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

    // ������� ��� ��������� ������� �� ������� ����������
    void UpdateDocumentBase(std::vector<std::string> inDocs);

    // ������� ��� ��������� ������ � ������� �� ��������� � ��� ����������� ������
    void PutFreqDictionary(std::string inWords, int i);

    // ������� ��� ��������� ���������� �������
    std::map<std::string, std::vector<Entry>> GetFreqDictionary();

    // �������� �����, �� �������� ������ ����� � ��������� �������
    // ������� ���������� ��������� ������ �� ������� �����
    std::vector<Entry> GetWordCount(const std::string& word);
};


