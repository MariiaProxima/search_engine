#pragma once
#include <iostream>
#include <vector> 
#include <fstream>
#include <string>
#include <exception>
#include "nlohmann_json/nlohmann_json/single_include/nlohmann/json.hpp"


class ConverterJSON {
private:
    nlohmann::json objJson;
    std::fstream fileInput;
    int responsesLimit = 5;

public:
    ConverterJSON() = default;
    // Ôóíêöèÿ âîçâðàùàåò ñïèñîê äîêóìåíòîâ, â êîòîðûõ íàäî ïðîèçâåñòè ïîèñê
    std::vector<std::string> GetTextDocuments();

    // Ôóíêöèÿ âîçâðàùàåò ñïèñîê çàïðîñîâ, ïî êîòîðûì íàäî ïðîèçâåñòè ïîèñê â äîêóìåíòàõ
    std::vector<std::string> GetRequests();

    // Ôóíêöèÿ äëÿ ïîëó÷åíèÿ âåêòîðà ñ äàííûìè ïî ðåëåâàòíîñòè äîêóìåíòîâ êàæäîìó çàïðîñó
    void putAnswers(std::vector<std::vector<std::pair<int, float>>>answers);

    void checkFileConfigJSON();

    // Ôóíêöèÿ âîçâðàùàåò ìàêñèìàëüíîå êîëè÷åñòâî îòâåòîâ íà îäèí çàïðîñ
    int GetResponsesLimit() const;
};

