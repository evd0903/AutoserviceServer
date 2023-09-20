#pragma once

#include "domain.h"
#include "sqlite_modern_cpp.h"

#include <string>
#include <vector>
#include <optional>


using namespace sqlite;

enum EntityType
{
	DETAIL,
	EMPLOYEE,
	CLIENT,
	VEHICLE,
	SALE
};

class DataBaseManager {
public:
	DataBaseManager(std::string db_name)
		: db_(db_name)
	{
	};

	void AddDetail(const Detail&& detail);

	void AddEmployee(const Employee&& employee);

	void AddClient(const Client&& client);

	void AddVehicle(const Vehicle&& vehicle);

	void AddSale(const Sale&& sale);

	void DeleteDetail(int id);

	void DeleteEmployee(int id);

	void DeleteClient(int id);

	void DeleteVehicle(int id);

	void DeleteSale(int id);

	void UpdateDetail(int id, DetailToQuery detail);

	void UpdateEmployee(int id, EmployeeToQuery employee);

	void UpdateClient(int id, ClientToQuery client);

	void UpdateVehicle(int id, VehicleToQuery vehicle);

	void UpdateSale(int id, SaleToQuery sale);

	int GetLastId(EntityType entity_type);

	void UpdateLastId(EntityType entity_type);

	std::optional<Detail> FindDetailById(int id);

	std::optional<Employee> FindEmployeeById(int id);

	std::optional<Vehicle> FindVehicleById(int id);

	std::optional<Client> FindClientById(int id);

	std::optional<Sale> FindSaleById(int id);

	double ComputeIncome(std::string start_date, std::string end_date);

	template <typename Entity>
	std::optional<std::vector<Entity>> ExecuteCustomQuery(const std::string& query) {

		std::vector<Entity> result;

		auto prep = db_ << query;

		for (auto&& row : prep) {
			result.push_back(Entity::FromRow(row));
		}

		if (result.size()) {
			return result;
		}

		return std::nullopt;
	}

private:
	database db_;
};