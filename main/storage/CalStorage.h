#ifndef QUESERA_CALSTORAGE_H
#define QUESERA_CALSTORAGE_H

#define LOG_TAG "CalStorage"

class CalStorage
{
    public:
        CalStorage();
        ~CalStorage();
        bool appendCalBuffer(const char *buffer);
};


#endif //QUESERA_CALSTORAGE_H
