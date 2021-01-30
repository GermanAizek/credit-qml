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
		picojson::value value;
		std::string err = picojson::parse(value, json_str);
		if (!err.empty()) {
			//show_messagebox("Ошибка", QString("Ошибка парсинга json файла:\n%1").arg(err.c_str()));
			throw int(ErrorType::kFailedParse);
		}

		if (!value.is<picojson::array>()) {
			//show_messagebox("Ошибка", "Json файл не является массивом, проверьте правильность написания в нем.");
			throw int(ErrorType::kNotArray);
		}

		ClientsVector clients;
		picojson::array arr = value.get<picojson::array>();
		for (JsonArray::const_iterator i = arr.begin(); i != arr.end(); ++i) {
			Info data_client;
			data_client.fullname		= i->get("fullname").get<std::string>();
			data_client.credit_amount	= i->get("credit_amount").get<int64_t>();
			data_client.term_begin		= i->get("term_begin").get<int64_t>();
			data_client.term_end		= i->get("term_end").get<int64_t>();
			data_client.term_current	= i->get("term_current").get<int64_t>();
			data_client.total_paid		= i->get("total_paid").get<int64_t>();
			data_client.interest_rate	= i->get("interest_rate").get<int64_t>();
			clients.push_back(data_client);
			qDebug() << data_client.fullname.c_str();
		}

		/*
		vector<int> vi;
		for (array::const_iterator it = arr.begin(); it != arr.end(); ++it) {
		  vi.push_back((int)(*it).get("name").get<double>());
		}
		sort(vi.begin(), vi.end());
		*/

		return clients;
	} catch (int error) {
		show_messagebox("Ошибка", QString(error_messages[error]));
		return {};
	}
}

int main(int argc, char** argv) {
	QApplication app(argc, argv);

	std::string json_str = load_json("db.json");
	if (json_str.empty()) {
		show_messagebox("Ошибка", "Файл db.json не найден, проверьте правильность сборки проекта или возьмите из каталога examples.");
		app.exit();
	}

	if (parse_json(json_str).empty()) {
		// TODO: подумать нужен ли выход
		app.exit();
	}

	// TODO: Запуск основного вьювера с таблицей

	return app.exec();
}
