#include "InvertedIndex.h"

std::mutex addingDate;

// ��������� ���� ����������
void InvertedIndex::UpdateDocumentBase(std::vector<std::string> inDocs) {
    // ��������� ��������� �� ������ ����������
    std::vector<std::thread> updateThread;
    for (int i = 0; i < inDocs.size(); ++i) {
        std::fstream file;
        file.open(inDocs[i]);
        if (!file) {
            std::cerr << inDocs[i] + " file not found \n";
            continue;
        }
        std::string words;
        std::getline(file, words);
        docs.push_back(words);
        file.close();
        // �������� ����� ���������� ���������� �������
        updateThread.emplace_back(&InvertedIndex::PutFreqDictionary, this, words, i);
    }
    for (auto& i : updateThread)
        i.join();
}

// ��������� ��������� �������
void InvertedIndex::PutFreqDictionary(std::string inWords, int i) {
    Entry entry{};
    std::string oneWord;
    std::istringstream words(inWords);
    int countWords = 0;
    // ��������� ������ �� ��������� ����� � ��������� ��������� �������
    while (std::getline(words, oneWord, ' '))
    {
        std::vector<Entry> vectorEntry;
        std::lock_guard<std::mutex> guard(addingDate);
        // ���������� ����� � ���������� ����������, ���� ������ ����� ������ 100 ��������
        if (oneWord.length() > 100)
        {
            std::cerr << "No-correct size words in file #" << i << std::endl;
            continue;
        }
        // ���������� ����, ��������� ����������� ���������, ���� ������� ���� � ����� ������ 1000
        if (countWords > 1000)
        {
            std::cerr << "No-correct size file #" << i << std::endl;
            break;
        }
        // ��������� ����� ����, ���� ������ ����� �� ������� � ��������� �������
        if (!freqDictionary.count(oneWord))
        {
            entry.docId = i;
            entry.count = 1;
            vectorEntry.push_back(entry);

            freqDictionary.insert({ oneWord, vectorEntry });

        }
        else // ��������� ������ ����� �� ������� � ���� ���������
        {
            auto it = freqDictionary.find(oneWord);
            bool found = false;
            for (auto& k : it->second)
            {
                // ����������� ����������, ���� ������ ����� ��� ����������� � ������ ���������
                if (k.docId == i)
                {
                    k.count++;
                    found = true;
                    break;
                }
            }
            // ��������� ����� ����, ���� ������ ����� �� ����������� � ������ ���������
            if (!found)
            {
                entry.docId = i;
                entry.count = 1;
                it->second.push_back(entry);
            }
        }
        ++countWords;
    }
}

// ����������� ��������� �������
std::map<std::string, std::vector<Entry>> InvertedIndex::GetFreqDictionary() {
    return freqDictionary;
}

// ��������� ���������� ��������� ����� � ��������� �������
std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) {
    auto it = freqDictionary.find(word);
    if (freqDictionary.count(word))
        return it->second;
    else
    {
        std::vector<Entry> emptyVector;
        return emptyVector;
    }
}
