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
    // ������� ���������� ������ ����������, � ������� ���� ���������� �����
    std::vector<std::string> GetTextDocuments();

    // ������� ���������� ������ ��������, �� ������� ���� ���������� ����� � ����������
    std::vector<std::string> GetRequests();

    // ������� ��� ��������� ������� � ������� �� ������������ ���������� ������� �������
    void putAnswers(std::vector<std::vector<std::pair<int, float>>>answers);

    void checkFileConfigJSON();

    // ������� ���������� ������������ ���������� ������� �� ���� ������
    int GetResponsesLimit() const;
};

