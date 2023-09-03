#include <iomanip>

#include "request_handler.h"

using namespace std;

std::optional<json::Document> RequestHandler::HandleRequest(std::istream & input) {
	json::Document full_request = json::Load(input);

	std::string requestType = full_request.GetRoot().AsMap().at("type").AsString();

	if (requestType == "add_detail"s) {
		Detail detail;
		json::Dict request = full_request.GetRoot().AsMap().at("request").AsMap();
		detail.name = request.at("name").AsString();
		detail.code = request.at("code").AsString();
		detail.count = request.at("count").AsInt();
		detail.buy_price = request.at("buy_price").AsDouble();
		detail.sale_price = request.at("sale_price").AsDouble();
		
		AddDetail(detail);
	}
	else if (requestType == "add_employee"s) {
		Employee employee;
		json::Dict request = full_request.GetRoot().AsMap().at("request").AsMap();
		employee.name = request.at("name").AsString();
		employee.role = request.at("role").AsString();
		employee.salary = request.at("salary").AsDouble();

		AddEmployee(employee);
	}
	else if (requestType == "add_vehicle") {
		Vehicle vehicle;
		json::Dict request = full_request.GetRoot().AsMap().at("request").AsMap();
		vehicle.name = request.at("name").AsString();
		vehicle.code = request.at("code").AsString();
		//vehicle.owner_name = request.at("owner_name").AsString();
	}
	else if (requestType == "add_client") {
		Client client;
		json::Dict request = full_request.GetRoot().AsMap().at("request").AsMap();
		client.name = request.at("name").AsString();
		client.INN = request.at("INN").AsString();
	}
	else if (requestType == "add_sale") {
		Sale sale;
		json::Dict request = full_request.GetRoot().AsMap().at("request").AsMap();
		sale.sale_count = request.at("sale_count").AsInt();
		sale.income = request.at("income").AsDouble();
		//sale.detail_name = request.at("detail_name").AsString();
		//sale.client_name = request.at("client_name").AsString();
		//sale.vehicle_name = request.at("vehicle_name").AsString();

		string date = request.at("sale_date").AsString();
		std::tm timeStruct{};

		std::istringstream ss(date);
		ss >> std::get_time(&timeStruct, "%Y-%m-%d %H:%M:%S");

		if (ss.fail()) {
			throw std::exception("Failed to parse date");
		}

		sale.sale_date = std::mktime(&timeStruct);

		AddSale(sale);
	}
}

void RequestHandler::AddDetail(const Detail detail) {
	server_.AddDetail(std::move(detail));
}

void RequestHandler::AddEmployee(const Employee employee) {
	server_.AddEmployee(std::move(employee));
}

void RequestHandler::AddVehicle(const Vehicle vehicle) {
	server_.AddVehicle(std::move(vehicle));
}

void RequestHandler::AddClient(const Client client) {
	server_.AddClient(std::move(client));
}

void RequestHandler::AddSale(const Sale sale) {
	server_.AddSale(std::move(sale));
}
