#pragma once

#include "sqlite_modern_cpp.h"

#include <chrono>
#include <string>

struct Date {
	Date() = default;

	Date(const std::string s) {
		year = std::stoi(s.substr(0, 4));

		int pos = 0;

		for (int i = 5; i != s.size(); ++i) {
			if (s[i] == '-') {
				pos = i;
				break;
			}
		}

		month = std::stoi(s.substr(5, pos - 5));
		day = std::stoi(s.substr(pos + 1));
	}

	Date(const int d, const int m, const int y)
		: year(y)
		, month(m)
		, day(d)
	{
	}

	bool operator==(const Date& other) {
		return year == other.year && month == other.month && day == other.day;
	}

	int day;
	int month;
	int year;

	std::string AsString() const {
		std::string s = std::to_string(year) + '-';

		if (month < 10) {
			s += "0" + std::to_string(month) + "-";
		}
		else {
			s += std::to_string(month) + "-";
		}

		if (day < 10) {
			s += "0" + std::to_string(day) + "-";
		}
		else {
			s += std::to_string(day) + "-";
		}

		return s;
	}
};

struct Detail {
	int id;
	std::string name;
	std::string code;
	int count;
	double buy_price;
	double sale_price;

	static Detail FromRow(sqlite::row_iterator::value_type& row) {
		Detail detail;

		row >> detail.id >> detail.name >> detail.count >> detail.code >> detail.buy_price >> detail.sale_price;

		return detail;
	}
};

struct Employee {
	int id;
	std::string name;
	std::string role;
	double salary;

	static Employee FromRow(sqlite::row_iterator::value_type& row) {
		Employee employee;

		row >> employee.id >> employee.name >> employee.role >> employee.salary;

		return employee;
	}
};

struct Client {
	int id;
	std::string name;
	std::string INN;

	static Client FromRow(sqlite::row_iterator::value_type& row) {
		Client client;

		row >> client.id >> client.name >> client.INN;

		return client;
	}
};

struct Vehicle {
	int id;
	std::string name;
	std::string code;
	int client_id;

	static Vehicle FromRow(sqlite::row_iterator::value_type& row) {
		Vehicle vehicle;

		row >> vehicle.id >> vehicle.name >> vehicle.code >> vehicle.client_id;

		return vehicle;
	}
};

struct Sale {
	int id;
	int sale_count;
	Date sale_date;
	double income;
	int detail_id;
	int client_id;
	int vehicle_id;

	static Sale FromRow(sqlite::row_iterator::value_type& row) {
		Sale sale;

		std::string date;

		row >> sale.id >> sale.detail_id >> sale.client_id >> sale.vehicle_id >> sale.sale_count >> date >> sale.income;

		sale.sale_date = Date{ date };

		return sale;
	}
};

struct DetailToQuery {
	std::optional<int> id;
	std::optional<std::string> name;
	std::optional<std::string> code;
	std::optional<int> count;
	std::optional<double> buy_price;
	std::optional<double> sale_price;
};

struct EmployeeToQuery {
	std::optional<int> id;
	std::optional<std::string> name;
	std::optional<std::string> role;
	std::optional<double> salary;
};

struct ClientToQuery {
	std::optional<int> id;
	std::optional<std::string> name;
	std::optional<std::string> INN;
};

struct VehicleToQuery {
	std::optional<int> id;
	std::optional<std::string> name;
	std::optional<std::string> code;
	std::optional<int> client_id;
};

struct SaleToQuery {
	std::optional<int> id;
	std::optional<int> sale_count;
	std::optional<Date> sale_date;
	std::optional<double> income;
	std::optional<int> detail_id;
	std::optional<int> client_id;
	std::optional<int> vehicle_id;
};