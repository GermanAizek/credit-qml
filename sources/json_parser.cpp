#include "json_parser.h"

int show_messagebox(const QString& title, const QString& text) {
	QQmlEngine engine;
	QQmlComponent component(&engine,
			QUrl::fromLocalFile("components/messagebox.qml"));
	QObject* object = component.create();
	int retVal;
	QMetaObject::invokeMethod(object, "displayMessageBox",
			Q_RETURN_ARG(int, retVal),
			Q_ARG(QString, title),
			Q_ARG(QString, text));

	//delete object;
	return retVal;
}

std::string load_json(const char* filename) {
	std::ifstream json;
	std::stringstream buffer;
	json.open(filename, std::ios::binary);
	if (!json.is_open()) {
		return std::string();
	}

	buffer << json.rdbuf();
	json.close();

	return buffer.str();
}

ClientsVector parse_json(const std::string& json_str) {
	try {
		picojson::value object;
		std::string err = picojson::parse(object, json_str);
		if (!err.empty()) {
			throw QString("Ошибка парсинга json файла:\n%1").arg(err.c_str());
		}

		if (!object.is<picojson::array>()) {
			throw QString("Json файл не является массивом, проверьте правильность написания в нем.");
		}

		ClientsVector clients;
		picojson::array arr = object.get<picojson::array>();
		for (JsonArray::const_iterator i = arr.begin(); i != arr.end(); ++i) {
			Info data_client;

			picojson::value value = i->get("fullname");
			if (value.is<std::string>()) {
				data_client.fullname = value.get<std::string>();
			} else {
				throw QString("Ошибка парсинга json файла:\nПоле \"ФИО\" определено не текстовым форматом.");
			}

			value = i->get("credit_amount");
			if (value.is<int64_t>()) {
				data_client.credit_amount = value.get<int64_t>();
			} else {
				throw QString("Ошибка парсинга json файла:\nПоле \"Сумма кредита\" определено не числовым форматом.");
			}

			value = i->get("term_begin");
			if (value.is<int64_t>()) {
				data_client.term_begin = value.get<int64_t>();
			} else {
				throw QString("Ошибка парсинга json файла:\nПоле \"Срок начала\" определено не числовым форматом.");
			}

			value = i->get("term_end");
			if (value.is<int64_t>()) {
				data_client.term_end = value.get<int64_t>();
			} else {
				throw QString("Ошибка парсинга json файла:\nПоле \"Срок окончания\" определено не числовым форматом.");
			}

			value = i->get("term_current");
			if (value.is<int64_t>()) {
				data_client.term_current = value.get<int64_t>();
			} else {
				throw QString("Ошибка парсинга json файла:\nПоле \"Срок на данный момент\" определено не числовым форматом.");
			}

			value = i->get("total_paid");
			if (value.is<int64_t>()) {
				data_client.total_paid = value.get<int64_t>();
			} else {
				throw QString("Ошибка парсинга json файла:\nПоле \"Выплачено\" определено не числовым форматом.");
			}

			value = i->get("interest_rate");
			if (value.is<double>()) {
				data_client.interest_rate = value.get<double>();
			} else {
				throw QString("Ошибка парсинга json файла:\nПоле \"Процентная ставка\" определено не числовым форматом.");
			}

			data_client.total_payment = 0;
			data_client.avgmonthly_payment = 0.0;

			clients.push_back(data_client);
		}

		/*
		vector<int> vi;
		for (array::const_iterator it = arr.begin(); it != arr.end(); ++it) {
		  vi.push_back((int)(*it).get("name").get<double>());
		}
		sort(vi.begin(), vi.end());
		*/

		return clients;
	} catch (const QString& error) {
		show_messagebox("Ошибка", error);
		return {};
	}
}

void calc_payment(ClientsVector clients) {
	for (auto& client : clients) {
		//uint64_t end_monts = client.term_end - client.term_current;
		std::vector<long double> payments_vec = { 0 };
		for (auto month = client.term_begin; month < client.term_end; month++) {
			double unit = client.interest_rate / 1200;
			double coefficient = unit * pow((1 + unit), month) / (pow((1 + unit), month) - 1);
			long double payment = coefficient * client.credit_amount;
			payments_vec.push_back(payment);
			qDebug() << QString("%1").arg(payment, 0, 'f', 5);
			qDebug() << "=";
		}

		// calculate avg vector
		auto avg_payment = 1.0 * std::accumulate(payments_vec.begin(), payments_vec.end(), 0LL) / payments_vec.size();
		client.avgmonthly_payment = avg_payment;
		client.total_payment = client.credit_amount - client.total_paid;
		qDebug() << QString("%1").arg(client.avgmonthly_payment, 0, 'f', 2);
		qDebug() << QString("%1").arg(client.total_payment);
		qDebug() << "-------";
	}
}

int main(int argc, char** argv) {
	QApplication app(argc, argv);

	std::string json_str = load_json("db.json");
	if (json_str.empty()) {
		show_messagebox("Ошибка", "Файл db.json не найден, проверьте правильность сборки проекта или возьмите из каталога examples.");
		app.exit();
	}

	ClientsVector clients = parse_json(json_str);
	if (clients.empty()) {
		// TODO: подумать нужен ли выход
		app.exit();
	}

	calc_payment(clients);
	// TODO: Запуск основного вьювера с таблицей

	return app.exec();
}
