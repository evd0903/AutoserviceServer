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

	std::optional<json::Array> FindDetails(DetailToFind entity);

	std::optional<json::Array> FindEmployees(EmployeeToFind entity);

	std::optional<json::Array> FindClients(ClientToFind entity);

	std::optional<json::Array> FindVehicles(VehicleToFind entity);

	std::optional<json::Array> FindSales(SaleToFind entity);

	double ComputeIncome(int month_number);

private:
	Server& server_;
};

