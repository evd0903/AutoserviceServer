#pragma once

#include "sqlite_modern_cpp.h"

#include <chrono>
#include <string>

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
	std::string sale_date;
	double income;
	int detail_id;
	int client_id;
	int vehicle_id;

	static Sale FromRow(sqlite::row_iterator::value_type& row) {
		Sale sale;

		row >> sale.id >> sale.detail_id >> sale.client_id >> sale.vehicle_id >> sale.sale_count >> sale.sale_date >> sale.income;

		return sale;
	}
};

struct DetailToFind
{
	std::optional<int> id;
	std::optional<std::string> name;
	std::optional<std::string> code;
	std::optional<int> count;
	std::optional<double> buy_price;
	std::optional<double> sale_price;
};

struct EmployeeToFind
{
	std::optional<int> id;
	std::optional<std::string> name;
	std::optional<std::string> role;
	std::optional<double> salary;
};

struct ClientToFind {
	std::optional<int> id;
	std::optional<std::string> name;
	std::optional<std::string> INN;
};

struct VehicleToFind {
	std::optional<int> id;
	std::optional<std::string> name;
	std::optional<std::string> code;
	std::optional<int> client_id;
};

struct SaleToFind {
	std::optional<int> id;
	std::optional<int> sale_count;
	std::optional<std::string> sale_date;
	std::optional<double> income;
	std::optional<int> detail_id;
	std::optional<int> client_id;
	std::optional<int> vehicle_id;
};