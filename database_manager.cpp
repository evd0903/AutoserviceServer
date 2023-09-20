#include "database_manager.h"

using namespace std;

void DataBaseManager::AddDetail(const Detail&& detail) {
	try
	{
		db_ << "INSERT INTO details (Name, Count, Code, BuyPrice, SalePrice) VALUES(?, ?, ?, ?, ?);"
			<< detail.name << detail.count << detail.code
			<< detail.buy_price << detail.sale_price;
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}
}

void DataBaseManager::AddEmployee(const Employee&& employee) {
	try
	{
		db_ << "INSERT INTO employees (Name, Role, Salary) VALUES(?, ?, ?);"
			<< employee.name << employee.role << employee.salary;
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}
}

void DataBaseManager::AddClient(const Client&& client) {
	try
	{
		db_ << "INSERT INTO clients (Name, INN) VALUES(?, ?);"
			<< client.name << client.INN;
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}
}

void DataBaseManager::AddVehicle(const Vehicle&& vehicle) {
	try
	{
		db_ << "INSERT INTO vehicles (Name, Code, ClientId) VALUES(?, ?, ?);"
			<< vehicle.name << vehicle.code << vehicle.client_id;
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}
}

void DataBaseManager::AddSale(const Sale&& sale) {
	try
	{
		db_ << "INSERT INTO saled_details (SaleCount, SaleDateTime, Income, DetailId, ClientId, VehicleId) VALUES(?, ?, ?, ?, ?, ?);"
			<< sale.sale_count << sale.sale_date.AsString() << sale.income << sale.detail_id
			<< sale.client_id << sale.vehicle_id;
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}
}

void DataBaseManager::DeleteDetail(int id) {
	try
	{
		db_ << "DELETE FROM details WHERE Id = ?;" << id;
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}
}

void DataBaseManager::DeleteEmployee(int id) {
	try
	{
		db_ << "DELETE FROM employees WHERE Id = ?;" << id;
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}
}

void DataBaseManager::DeleteClient(int id) {
	try
	{
		db_ << "DELETE FROM clients WHERE Id = ?;" << id;
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}
}

void DataBaseManager::DeleteVehicle(int id) {
	try
	{
		db_ << "DELETE FROM vehicles WHERE Id = ?;" << id;
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}
}

void DataBaseManager::DeleteSale(int id) {
	try
	{
		db_ << "DELETE FROM saled_details WHERE Id = ?;" << id;
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}
}

void DataBaseManager::UpdateDetail(int id, DetailToQuery detail) {
	string query = "UPDATE details SET Id = ?";

	if (detail.name.has_value()) {
		query += "Name = \"" + *detail.name + "\"";
	}
	if (detail.count.has_value()) {
		query += ", Count = \"" + to_string(*detail.count) + "\"";
	}
	if (detail.code.has_value()) {
		query += ", Code = \"" + *detail.code + "\"";
	}
	if (detail.buy_price.has_value()) {
		query += ", BuyPrice = \"" + to_string(*detail.buy_price) + "\"";
	}
	if (detail.sale_price.has_value()) {
		query += ", SalePrice = \"" + to_string(*detail.sale_price) + "\"";
	}

	query += " WHERE Id = ?;";

	try {
		db_ << query << id << id;

	}
	catch (const exception& e) {
		cerr << e.what() << endl;
	}
}

void DataBaseManager::UpdateEmployee(int id, EmployeeToQuery employee) {
	string query = "UPDATE employees SET Id = ?";

	if (employee.name.has_value()) {
		query += "Name = \"" + *employee.name + "\"";
	}
	if (employee.role.has_value()) {
		query += ", Role = \"" +*employee.role + "\"";
	}
	if (employee.salary.has_value()) {
		query += ", Salary = \"" + to_string(*employee.salary) + "\"";
	}

	query += " WHERE Id = ?;";

	try {
		db_ << query << id << id;

	}
	catch (const exception& e) {
		cerr << e.what() << endl;
	}
}

void DataBaseManager::UpdateClient(int id, ClientToQuery client) {
	string query = "UPDATE clients SET Id = ?";

	if (client.name.has_value()) {
		query += "Name = \"" + *client.name + "\"";
	}
	if (client.INN.has_value()) {
		query += ", INN = \"" + *client.INN + "\"";
	}

	query += " WHERE Id = ?;";

	try {
		db_ << query << id << id;

	}
	catch (const exception& e) {
		cerr << e.what() << endl;
	}
}

void DataBaseManager::UpdateVehicle(int id, VehicleToQuery vehicle) {
	string query = "UPDATE vehicles SET Id = ?";

	if (vehicle.name.has_value()) {
		query += "Name = \"" + *vehicle.name + "\"";
	}
	if (vehicle.code.has_value()) {
		query += ", Code = \"" + *vehicle.code + "\"";
	}
	if (vehicle.client_id.has_value()) {
		query += ", ClientId = \"" + to_string(*vehicle.client_id) + "\"";
	}

	query += " WHERE Id = ?;";

	try {
		db_ << query << id << id;

	}
	catch (const exception& e) {
		cerr << e.what() << endl;
	}
}

void DataBaseManager::UpdateSale(int id, SaleToQuery sale) {
	string query = "UPDATE saled_details SET Id = ?";

	if (sale.sale_count.has_value()) {
		query += "SaleCount = \"" + to_string(*sale.sale_count) + "\"";
	}
	if (sale.sale_date.has_value()) {
		query += ", SaleDateTime = \"" + sale.sale_date->AsString() + "\"";
	}
	if (sale.income.has_value()) {
		query += ", Income = \"" + to_string(*sale.income) + "\"";
	}
	if (sale.client_id.has_value()) {
		query += ", ClientId = \"" + to_string(*sale.client_id) + "\"";
	}
	if (sale.detail_id.has_value()) {
		query += ", DetailID = \"" + to_string(*sale.detail_id) + "\"";
	}
	if (sale.vehicle_id.has_value()) {
		query += ", VehicleId = \"" + to_string(*sale.vehicle_id) + "\"";
	}

	query += " WHERE Id = ?;";

	try {
		db_ << query << id << id;

	}
	catch (const exception& e) {
		cerr << e.what() << endl;
	}
}

int DataBaseManager::GetLastId(EntityType entity_type) {
	try
	{
		int id;

		switch (entity_type)
		{
		case DETAIL:
			db_ << "SELECT last_id FROM entity_ids WHERE entity_type = ?;" << "detail" >> id;
			break;
		case EMPLOYEE:
			db_ << "SELECT last_id FROM entity_ids WHERE entity_type = ?;" << "employee" >> id;
			break;
		case CLIENT:
			db_ << "SELECT last_id FROM entity_ids WHERE entity_type = ?;" << "client" >> id;
			break;
		case VEHICLE:
			db_ << "SELECT last_id FROM entity_ids WHERE entity_type = ?;" << "vehicle" >> id;
			break;
		case SALE:
			db_ << "SELECT last_id FROM entity_ids WHERE entity_type = ?;" << "sale" >> id;
			break;
		}

		return id;
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}
}

void DataBaseManager::UpdateLastId(EntityType entity_type) {
	try
	{
		switch (entity_type)
		{
		case DETAIL:
			db_ << "UPDATE entity_ids SET last_id = last_id + 1 WHERE entity_type = ?;" << "detail";
			break;
		case EMPLOYEE:
			db_ << "UPDATE entity_ids SET last_id = last_id + 1 WHERE entity_type = ?;" << "employee";
			break;
		case CLIENT:
			db_ << "UPDATE entity_ids SET last_id = last_id + 1 WHERE entity_type = ?;" << "client";
			break;
		case VEHICLE:
			db_ << "UPDATE entity_ids SET last_id = last_id + 1 WHERE entity_type = ?;" << "vehicle";
			break;
		case SALE:
			db_ << "UPDATE entity_ids SET last_id = last_id + 1 WHERE entity_type = ?;" << "sale";
			break;
		}
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}
}

std::optional<Detail> DataBaseManager::FindDetailById(int id) {
	try
	{
		int count = 0;
		db_ << "select count(*) from details WHERE Id = ?;" << id >> count;

		if (count) {
			Detail ans;

			for (auto&& row : db_ << "SELECT * FROM details WHERE Id = ?;" << id) {
				row >> ans.id >> ans.name >> ans.count >> ans.code >> ans.buy_price >> ans.sale_price;
			}

			return ans;
		}
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}

	return nullopt;
}

std::optional<Employee> DataBaseManager::FindEmployeeById(int id) {
	try
	{
		int count = 0;
		db_ << "select count(*) from employees WHERE Id = ?;" << id >> count;

		if (count) {
			Employee ans;

			for (auto&& row : db_ << "SELECT * FROM employees WHERE Id = ?;" << id) {
				row >> ans.id >> ans.name >> ans.role >> ans.salary;
			}

			return ans;
		}
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}

	return nullopt;
}

std::optional<Vehicle> DataBaseManager::FindVehicleById(int id) {
	try
	{
		int count = 0;
		db_ << "select count(*) from vehicles WHERE Id = ?;" << id >> count;

		if (count) {
			Vehicle ans;

			for (auto&& row : db_ << "SELECT * FROM vehicles WHERE Id = ?;" << id) {
				row >> ans.id >> ans.name >> ans.code >> ans.client_id;
			}

			return ans;
		}
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}

	return nullopt;
}

std::optional<Client> DataBaseManager::FindClientById(int id) {
	try
	{
		int count = 0;
		db_ << "select count(*) from clients WHERE Id = ?;" << id >> count;

		if (count) {
			Client ans;

			for (auto&& row : db_ << "SELECT * FROM clients WHERE Id = ?;" << id) {
				row >> ans.id >> ans.name >> ans.INN;
			}

			return ans;
		}
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}

	return nullopt;
}

std::optional<Sale> DataBaseManager::FindSaleById(int id) {
	try
	{
		int count = 0;
		db_ << "select count(*) from saled_details WHERE Id = ?;" << id >> count;

		if (count) {
			Sale ans;

			for (auto&& row : db_ << "SELECT * FROM saled_details WHERE Id = ?;" << id) {
				string date;

				row >> ans.id >> ans.detail_id >> ans.client_id >> ans.vehicle_id >> ans.sale_count >> date >> ans.income;

				ans.sale_date = Date{ date };
			}

			return ans;
		}
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}

	return nullopt;
}

double DataBaseManager::ComputeIncome(std::string start_date, std::string end_date) {

	string query = "SELECT SUM(Income) FROM saled_details WHERE SaleDateTime BETWEEN ? AND ?;";

	double income = 0.0;

	try
	{
		db_ << query << start_date << end_date >> income;

	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}

	return income;
}