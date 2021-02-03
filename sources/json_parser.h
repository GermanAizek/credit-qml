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
#include <cmath>

#ifdef __arm__
#include <QDebug>
#endif

struct Info {
	std::string fullname;
	int64_t credit_amount;
	int64_t term_begin;
	int64_t term_end;
	int64_t term_current;
	int64_t total_paid;
	double interest_rate;
	int64_t total_payment;
	long double avgmonthly_payment;
};

typedef picojson::value::array JsonArray;
typedef std::vector<Info> ClientsVector;

#endif // JSON_PARSER_H
