#pragma once

#include "domain.h"
#include "database_manager.h"
#include "sqlite_modern_cpp.h"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

class Server {
public:
	Server(std::string& db_name)
		: DataBaseManager_(db_name)
	{
	};

	void SaveCacheToDataBase();

	void AddDetail(const Detail&& detail);

	void AddEmployee(const Employee&& employee);

	void AddClient(const Client&& client);

	void AddVehicle(const Vehicle&& vehicle);
	
	void AddSale(const Sale&& sale);

	std::optional<Detail> FindDetailById(int id);

	std::optional<Employee> FindEmployeeById(int id);

	std::optional<Vehicle> FindVehicleById(int id);

	std::optional<Client> FindClientById(int id);

	std::optional<Sale> FindSaleById(int id);

	std::optional<std::vector<Detail>> FindDetails(DetailToFind detail);

	std::optional<std::vector<Employee>> FindEmployees(EmployeeToFind detail);

	std::optional<std::vector<Client>> FindClients(ClientToFind detail);

	std::optional<std::vector<Vehicle>> FindVehicles(VehicleToFind detail);

	std::optional<std::vector<Sale>> FindSales(SaleToFind detail);

private: 
	std::vector<Detail> details_;
	std::vector<Employee> employees_;
	std::vector<Client> clients_;
	std::vector<Vehicle> vehicles_;
	std::vector<Sale> sales_;
	std::unordered_map<int, Detail*> detail_by_id_;
	std::unordered_map<int, Employee*> employee_by_id_;
	std::unordered_map<int, Client*> client_by_id_;
	std::unordered_map<int, Vehicle*> vehicle_by_id_;
	std::unordered_map<int, Sale*> sale_by_id_;
	DataBaseManager DataBaseManager_;
};