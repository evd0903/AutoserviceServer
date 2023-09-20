#pragma once

#include "domain.h"
#include "database_manager.h"
#include "sqlite_modern_cpp.h"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <Windows.h>

class Server {
public:
	Server(std::string& db_name)
		: DataBaseManager_(db_name)
	{
	};

	~Server() {
	};

	void SaveCacheToDataBase();

	void AddDetail(const Detail&& detail);

	void AddEmployee(const Employee&& employee);

	void AddClient(const Client&& client);

	void AddVehicle(const Vehicle&& vehicle);

	void AddSale(const Sale&& sale);

	void NewSale(int detail_id, int sale_count, int client_id, int vehicle_id);

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

	std::optional<Detail> FindDetailById(int id);

	std::optional<Employee> FindEmployeeById(int id);

	std::optional<Vehicle> FindVehicleById(int id);

	std::optional<Client> FindClientById(int id);

	std::optional<Sale> FindSaleById(int id);

	std::optional<std::vector<Detail>> FindDetails(DetailToQuery entity);

	std::optional<std::vector<Employee>> FindEmployees(EmployeeToQuery entity);

	std::optional<std::vector<Client>> FindClients(ClientToQuery entity);

	std::optional<std::vector<Vehicle>> FindVehicles(VehicleToQuery entity);

	std::optional<std::vector<Sale>> FindSales(SaleToQuery entity);

	double ComputeIncome(std::string start_date, std::string end_date);

private:
	bool CheckDetailId(int id);

	bool CheckEmployeeId(int id);

	bool CheckClientId(int id);

	bool CheckVehicleId(int id);

	bool CheckSaleId(int id);

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