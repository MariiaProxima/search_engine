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
    // �������� ��������� ������ InvertedIndex
    explicit SearchServer(InvertedIndex& idx);

    // �������� ������ � ��������� ��� ������ � ������������ ���������� ������� �� ���� ������
    // ������� ���������� ������ � ������� �� ������������ ���������� ������� ������� 
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& inQueries, int responsesLimit);

    // ������� ��� ��������� ������ � ����� ��������, ������ ������� � ������������� ���������� ������� �� ���� ������
    void handleRequest(const std::string& request, int i, int responsesLimit);
};

