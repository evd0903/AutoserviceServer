#pragma once

#include "json.h"
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

	template <typename DetailPredicate>
	std::optional<json::Array> FindDetails(DetailPredicate detail_predicate);

	template <typename EmployeePredicate>
	std::optional<json::Array> FindEmployees(EmployeePredicate employee_predicate);

	template <typename ClientPredicate>
	std::optional<json::Array> FindClients(ClientPredicate client_predicate);

	template <typename VehiclePredicate>
	std::optional<json::Array> FindVehicles(VehiclePredicate client_predicate);

	template <typename SalePredicate>
	std::optional<json::Array> FindSales(SalePredicate sale_predicate);

	double ComputeIncome(int month_number);

private:
	Server& server_;
};

