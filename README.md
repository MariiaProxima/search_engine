# Search engine | Поисковый движок

## Описание 
Консольное приложение, осуществляющее поиск слов среди набора документов.


## Принцип работы
1. Перед запуском приложения в конфигурационном файле **`config.json`** задаются названия файлов, по которым необходимо осуществить поиск слов.
2. Выполняется запрос (набор слов, по которым нужно найти документы) через файл JSON-формата **`requests.json`**. Поисковый движок обходит всё файлы и индексирует их таким образом, чтобы найти наиболее релвантые документы по поисковому запросу.
3. Запрос преобразуется в список слов.
4. В индексе происходит поиск документов, на которых встречаются данные слова.
5. Результаты ранжируются и сортируются. Максимальное количество возможных документов задаётся в конфигурационном файле. Результаты поиска записываются в **`answers.json`**, сформированный программой.

## Используемые технологии
![cpp](https://img.shields.io/badge/C++-14-purple) 

![gtest](https://img.shields.io/badge/GTEST-1.15.2-darkyellow)<br>
https://github.com/google/googletest

![json](https://img.shields.io/badge/JSON-3.11.0-brown)<br>
https://github.com/nlohmann/json

## Описание JSON-файлов
+ config.json
  
  Содержит название поискового движка, его версию, время обновления базы, максимальное колиество вариантов в ответе.
  ```json
  {
  "config": {
    "name": "SkillboxSearchEngine",
    "version": "0.1",
    "max_responses": 5
  },
  "files": [
    "resources/file001.txt",
    "resources/file002.txt",
    "resources/file003.txt",
    "resources/file004.txt",
    "resources/file005.txt"
  ]
  }

+ requests.json

  Содержит запросы, которые необходимо обработать поисковому движку
  ```json
  {
  "requests": [
    "apple orange melon",
    "cat dog horse",
    "purple yellow pink",
    "star planet dust",
    "forest desert mountains"
  ]
  }

+ answers.json
  
  Содержит результаты работы поискового движка.
  ```json
  {
  "Answers:": {
    "request0:": {
      "relevance:": [
        {
          "docid:": 0,
          "rank:": 1.0
        },
        {
          "docid:": 2,
          "rank:": 0.5
        }
      ],
      "result:": "true"
    },
    "request1:": {
      "relevance:": [
        {
          "docid:": 1,
          "rank:": 1.0
        }
      ],
      "result:": "true"
    },
    "request2:": {
      "relevance:": [
        {
          "docid:": 2,
          "rank:": 1.0
        }
      ],
      "result:": "true"
    },
    "request3:": {
      "relevance:": [
        {
          "docid:": 3,
          "rank:": 1.0
        }
      ],
      "result:": "true"
    },
    "request4:": {
      "relevance:": [
        {
          "docid:": 4,
          "rank:": 1.0
        }
      ],
      "result:": "true"
    }
  }
  }

