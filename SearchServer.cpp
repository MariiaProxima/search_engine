#include "SearchServer.h"


std::mutex updateDate;

SearchServer::SearchServer(InvertedIndex& idx) {
    index = idx;
}

// ������������ ��������� ������, �������� ��������������� ������� ���������� ������� ��� ��������
std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& inQueries, int responsesLimit) {
    std::vector<std::thread> searchThread;
    if (inQueries.size() > 1000)
    {
        std::cerr << "The number of requests is more than 1000";
        resultSearch.resize(1000);
    }
    else
        resultSearch.resize(inQueries.size());
    for (int i = 0; i < inQueries.size() && inQueries.size() != 1000; ++i)
    {
        searchThread.emplace_back(&SearchServer::handleRequest, this, std::ref(inQueries[i]), i, responsesLimit);
    }
    for (auto& i : searchThread)
        i.join();
    return resultSearch;
}

// �������� ��������������� ������� ���������� ������� ��� ��������� �������
void SearchServer::handleRequest(const std::string& request, int i, int responsesLimit)
{
    RelativeIndex relativeIndex{};
    std::vector<RelativeIndex> result;
    // ������� ��������� ������� �� �������
    InvertedIndex invertedIndex;
    invertedIndex.PutFreqDictionary(request, i);
    // ������� ��������� map ��� ���������� ������� �������
    std::map <std::string, std::vector<Entry>> mapsFreqDictionary = invertedIndex.GetFreqDictionary();
    // ������� ��������� map ��� �������� ���������� ���� �� ������� � �� ����������
    std::map<std::string, size_t> wordsCount;
    // ��������� ��������� map ����������� �������
    int count = 0;
    for (const auto& it : mapsFreqDictionary)
    {
        wordsCount.insert({ it.first, it.second[0].count });
        count += it.second[0].count;
    }
    if (count > 10)
    {
        std::cerr << "No-correct size request #" << i << std::endl;
        wordsCount.clear();
    }
    // ������� ��������� multimap, ��� ������ �������� ���������� ������������� ����� � �������, � ��������� ���
    std::multimap<size_t, std::string> countWords;
    for (const auto& itWordsCount : wordsCount)
        countWords.insert({ itWordsCount.second,itWordsCount.first });
    // ������� ��������� set ��� �������� ������ ����������, � ������� ����������� ����� �� �������
    std::set<size_t> listNumberDocId;
    std::set<size_t> ::iterator itThree;
    // ��������� ��������� set �������� ����������
    for (const auto& itCountWords : countWords)
    {
        if (index.GetWordCount(itCountWords.second).empty())
            continue;
        for (int k = 0; k < index.GetWordCount(itCountWords.second).size(); ++k)
            listNumberDocId.insert(index.GetWordCount(itCountWords.second)[k].docId);
    }
    // �� ������� ������� � ��������� ������ ��������� ������ ������, ���� ������ ���������� ����
    std::lock_guard<std::mutex> guard(updateDate);
    if (listNumberDocId.empty())
    {
        resultSearch[i] = result;
    }
    else // ��������� ������
    {
        float maxAbsoluteRelative = 0; // ������������ �������� ���������� ������������
        // ������������ ���������� ������������ ������� ��������� ������������ �������
        for (itThree = listNumberDocId.begin(); itThree != listNumberDocId.end(); ++itThree)
        {
            relativeIndex.rank = 0;
            relativeIndex.docId = *itThree;
            // ������������ ���������� ������������ ������� ����� �� ������� � ����� ���������
            for (const auto& itCountWords : countWords)
            {
                for (int k = 0; k < index.GetWordCount(itCountWords.second).size(); ++k)
                {
                    if (index.GetWordCount(itCountWords.second)[k].docId == relativeIndex.docId)
                        relativeIndex.rank += (float)index.GetWordCount(itCountWords.second)[k].count;
                }
            }
            // ������������ �������� ����� ���������� ������������ ����� ���������
            // ���� ���������� ������������ ��������� ������ ������������ ���������� �������������
            if (relativeIndex.rank > maxAbsoluteRelative)
                maxAbsoluteRelative = relativeIndex.rank;
            // ��������� ������ ������������ � ������ ����������
            result.push_back(relativeIndex);
        }
        // ��������� ������ � ������� ���������� ������������
        for (int j = 0; j < result.size(); ++j)
        {
            for (int k = 0; k < result.size() - 1 - j; ++k)
            {
                if (result[k].rank < result[k + 1].rank)
                    std::swap(result[k], result[k + 1]);
            }
        }
        auto begin = result.cbegin();
        auto end = result.cend();
        // ������� ������ ��������, ���� ���������� ����������� ������ ������������� ���������� ������� �� �������
        if (result.size() >= responsesLimit)
            result.erase(begin + responsesLimit, end);
        // ����������� ���������� ������������ � �������������
        for (auto& j : result)
            j.rank /= maxAbsoluteRelative;
        // ��������� ��������� �� ������� � ����� ���������� ��������� �������
        resultSearch[i] = result;
    }
}