#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#define PICOJSON_USE_INT64
#include "picojson/picojson.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QMetaObject>
#include <fstream>
#include <sstream>
#include <vector>
//#include <cstdint>
const char* error_messages[2] = {
	"Ошибка парсинга json файла:\n%1",
	"Json файл не является массивом, проверьте правильность написания в нем."
};

enum class ErrorType {
	kFailedParse = 0,
	kNotArray
};

struct Info {
	std::string fullname;
	int64_t credit_amount;
	int64_t term_begin;
	int64_t term_end;
	int64_t term_current;
	int64_t total_paid;
	float interest_rate;
};

typedef picojson::value::array JsonArray;
typedef std::vector<Info> ClientsVector;

#endif // JSON_PARSER_H
