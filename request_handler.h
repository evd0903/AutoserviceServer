#pragma once

#include "json_builder.h"
#include "server.h"


class RequestHandler {
public:
	RequestHandler(Server& server)
		: server_(server)
	{
	}

	std::optional<json::Document> HandleRequest(std::istream& input = std::cin);

	void AddDetail(const Detail detail);

	void AddEmployee(const Employee employee);

	void AddVehicle(const Vehicle vehicle);

	void AddClient(const Client client);

	void AddSale(const Sale sale);

	void DeleteDetail(int id);

	void DeleteEmployee(int id);

	void DeleteClient(int id);

	void DeleteVehicle(int id);

	void DeleteSale(int id);

	std::optional<json::Dict> FindDetailById(int id);

	std::optional<json::Dict> FindEmployeeById(int id);

	std::optional<json::Dict> FindVehicleById(int id);

	std::optional<json::Dict> FindClientById(int id);

	std::optional<json::Dict> FindSaleById(int id);

	std::optional<json::Dict> FindDetails(DetailToQuery entity);

	std::optional<json::Dict> FindEmployees(EmployeeToQuery entity);

	std::optional<json::Dict> FindClients(ClientToQuery entity);

	std::optional<json::Dict> FindVehicles(VehicleToQuery entity);

	std::optional<json::Dict> FindSales(SaleToQuery entity);

	double ComputeIncome(std::string start_date, std::string end_date);

private:
	Server& server_;
};