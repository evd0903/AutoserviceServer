#include "database_manager.h"

using namespace std;

void DataBaseManager::AddDetail(const Detail && detail) {
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

void DataBaseManager::AddEmployee(const Employee && employee) {
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

void DataBaseManager::AddClient(const Client && client) {
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

void DataBaseManager::AddVehicle(const Vehicle && vehicle) {
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

void DataBaseManager::AddSale(const Sale && sale) {
	try
	{
		db_ << "INSERT INTO saled_details (SaleCount, SaleDateTime, Income, DetailId, ClientId, VehicleId) VALUES(?, ?, ?, ?, ?, ?);"
			<< sale.sale_count << sale.sale_date << sale.income << sale.detail_id 
			<< sale.client_id << sale.vehicle_id;
	}
	catch (const std::exception& e)
	{
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

	//db_ << "SELECT * FROM details WHERE Id = ?;" << id >> detail.id >> detail.name >> detail.count;

	int count = 0;
	db_ << "select count(*) from details WHERE Id = ?;" << id >> count;

	if (count) {
		Detail ans;

		for (auto&& row : db_ << "SELECT * FROM details WHERE Id = ?;" << id) {
			row >> ans.id >> ans.name >> ans.count >> ans.code >> ans.buy_price >> ans.sale_price;
		}

		return ans;
	}
	/*if (result.begin() != result.end()) {
		auto row = *result.begin();


		row >> detail.name >> detail.count >> detail.code >> detail.buy_price >> detail.sale_price;

		return detail;
	}*/
}

std::optional<Employee> DataBaseManager::FindEmployeeById(int id) {
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

std::optional<Vehicle> DataBaseManager::FindVehicleById(int id) {
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

std::optional<Client> DataBaseManager::FindClientById(int id) {
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

std::optional<Sale> DataBaseManager::FindSaleById(int id) {
	int count = 0;
	db_ << "select count(*) from saled_details WHERE Id = ?;" << id >> count;

	if (count) {
		Sale ans;

		for (auto&& row : db_ << "SELECT * FROM saled_details WHERE Id = ?;" << id) {
			row >> ans.id >> ans.detail_id >> ans.client_id >> ans.vehicle_id >> ans.sale_count >> ans.sale_date >> ans.income;
		}

		return ans;
	}
}