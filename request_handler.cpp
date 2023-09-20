#include <iomanip>

#include "request_handler.h"


using namespace std;

std::optional<json::Document> RequestHandler::HandleRequest(std::istream& input) {
	json::Document full_request = json::Load(input);

	std::string requestType = full_request.GetRoot().AsDict().at("type").AsString();

	try {
		if (requestType == "add_detail"s) {
			Detail detail;
			json::Dict request = full_request.GetRoot().AsDict().at("request").AsDict();
			detail.name = request.at("name").AsString();
			detail.code = request.at("code").AsString();
			detail.count = request.at("count").AsInt();
			detail.buy_price = request.at("buy_price").AsDouble();
			detail.sale_price = request.at("sale_price").AsDouble();

			AddDetail(detail);
		}
		else if (requestType == "add_employee"s) {
			Employee employee;
			json::Dict request = full_request.GetRoot().AsDict().at("request").AsDict();
			employee.name = request.at("name").AsString();
			employee.role = request.at("role").AsString();
			employee.salary = request.at("salary").AsDouble();

			AddEmployee(employee);
		}
		else if (requestType == "add_vehicle") {
			Vehicle vehicle;
			json::Dict request = full_request.GetRoot().AsDict().at("request").AsDict();
			vehicle.name = request.at("name").AsString();
			vehicle.code = request.at("code").AsString();
			//vehicle.owner_name = request.at("owner_name").AsString();
		}
		else if (requestType == "add_client") {
			Client client;
			json::Dict request = full_request.GetRoot().AsDict().at("request").AsDict();
			client.name = request.at("name").AsString();
			client.INN = request.at("INN").AsString();
		}
		else if (requestType == "add_sale") {
			Sale sale;
			json::Dict request = full_request.GetRoot().AsDict().at("request").AsDict();
			sale.sale_count = request.at("sale_count").AsInt();
			sale.income = request.at("income").AsDouble();
			//sale.detail_name = request.at("detail_name").AsString();
			//sale.client_name = request.at("client_name").AsString();
			//sale.vehicle_name = request.at("vehicle_name").AsString();

			string date = request.at("sale_date").AsString();
			std::tm timeStruct{};

			/*std::istringstream ss(date);
			ss >> std::get_time(&timeStruct, "%Y-%m-%d %H:%M:%S");

			if (ss.fail()) {
				throw std::exception("Failed to parse date");
			}*/

			

			AddSale(sale);
		}
		else if (requestType == "new_sale") {
			json::Dict request = full_request.GetRoot().AsDict().at("request").AsDict();

			int detail_id = request.at("detail_id").AsInt();
			int sale_count = request.at("sale_count").AsInt();
			int client_id = request.at("client_id").AsInt();
			int vehicle_id = request.at("vehicle_id").AsInt();

			try {
				server_.NewSale(detail_id, sale_count, client_id, vehicle_id);
			}
			catch (exception& e) {
				cerr << e.what() << endl;
			}
		}
		else if (requestType == "find_detail_by_id") {
			int id = full_request.GetRoot().AsDict().at("request").AsDict().at("id").AsInt();

			auto ans = FindDetailById(id);

			if (ans.has_value()) {
				return json::Document{ *ans };
			}
		}
		else if (requestType == "find_employee_by_id") {
			int id = full_request.GetRoot().AsDict().at("request").AsDict().at("id").AsInt();

			auto ans = FindEmployeeById(id);

			if (ans.has_value()) {
				return json::Document{ *ans };
			}
		}
		else if (requestType == "find_client_by_id") {
			int id = full_request.GetRoot().AsDict().at("request").AsDict().at("id").AsInt();

			auto ans = FindClientById(id);

			if (ans.has_value()) {
				return json::Document{ *ans };
			}
		}
		else if (requestType == "find_vehicle_by_id") {
			int id = full_request.GetRoot().AsDict().at("request").AsDict().at("id").AsInt();

			auto ans = FindVehicleById(id);

			if (ans.has_value()) {
				return json::Document{ *ans };
			}
		}
		else if (requestType == "find_sale_by_id") {
			int id = full_request.GetRoot().AsDict().at("request").AsDict().at("id").AsInt();

			auto ans = FindSaleById(id);

			if (ans.has_value()) {
				return json::Document{ *ans };
			}
		}
		else if (requestType == "find_details") {
			json::Dict request = full_request.GetRoot().AsDict().at("request").AsDict();

			DetailToQuery detail;

			for (auto [key, item] : request) {
				if (key == "id") {
					detail.id = item.AsInt();
				}
				else if (key == "name") {
					detail.name = item.AsString();
				}
				else if (key == "count") {
					detail.count = item.AsInt();
				}
				else if (key == "code") {
					detail.code = item.AsString();
				}
				else if (key == "buy_price") {
					detail.buy_price = item.AsDouble();
				}
				else if (key == "sale_price") {
					detail.sale_price = item.AsDouble();
				}
			}

			auto ans = FindDetails(detail);

			if (ans.has_value()) {
				return json::Document{ *ans };
			}
		}
		else if (requestType == "find_employees") {
			json::Dict request = full_request.GetRoot().AsDict().at("request").AsDict();

			EmployeeToQuery employee;

			for (auto [key, item] : request) {
				if (key == "id") {
					employee.id = item.AsInt();
				}
				else if (key == "name") {
					employee.name = item.AsString();
				}
				else if (key == "role") {
					employee.role = item.AsString();
				}
				else if (key == "salary") {
					employee.salary = item.AsDouble();
				}
			}

			auto ans = FindEmployees(employee);

			if (ans.has_value()) {
				return json::Document{ *ans };
			}
		}
		else if (requestType == "find_clients") {
			json::Dict request = full_request.GetRoot().AsDict().at("request").AsDict();

			ClientToQuery client;

			for (auto [key, item] : request) {
				if (key == "id") {
					client.id = item.AsInt();
				}
				else if (key == "name") {
					client.name = item.AsString();
				}
				else if (key == "INN") {
					client.INN = item.AsString();
				}
			}

			auto ans = FindClients(client);

			if (ans.has_value()) {
				return json::Document{ *ans };
			}
		}
		else if (requestType == "find_vehicles") {
			json::Dict request = full_request.GetRoot().AsDict().at("request").AsDict();

			VehicleToQuery vehicle;

			for (auto [key, item] : request) {
				if (key == "id") {
					vehicle.id = item.AsInt();
				}
				else if (key == "name") {
					vehicle.name = item.AsString();
				}
				else if (key == "code") {
					vehicle.code = item.AsString();
				}
			}

			auto ans = FindVehicles(vehicle);

			if (ans.has_value()) {
				return json::Document{ *ans };
			}
		}
		else if (requestType == "find_sales") {
			json::Dict request = full_request.GetRoot().AsDict().at("request").AsDict();

			SaleToQuery sale;

			for (auto [key, item] : request) {
				if (key == "id") {
					sale.id = item.AsInt();
				}
				else if (key == "sale_count") {
					sale.sale_count = item.AsInt();
				}
				else if (key == "sale_date") {
					sale.sale_date = item.AsString();
				}
				else if (key == "income") {
					sale.income = item.AsDouble();
				}
				else if (key == "detail_id") {
					sale.detail_id = item.AsInt();
				}
				else if (key == "client_id") {
					sale.client_id = item.AsInt();
				}
				else if (key == "vehicle_id") {
					sale.vehicle_id = item.AsInt();
				}
			}

			auto ans = FindSales(sale);

			if (ans.has_value()) {
				return json::Document{ *ans };
			}
		}

		return json::Document{ json::Node{} };
	}
	catch (const exception& e) {
		cerr << e.what() << endl;
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

void RequestHandler::DeleteDetail(int id) {
	server_.DeleteDetail(id);
}

void RequestHandler::DeleteEmployee(int id) {
	server_.DeleteEmployee(id);
}

void RequestHandler::DeleteClient(int id) {
	server_.DeleteClient(id);
}

void RequestHandler::DeleteVehicle(int id) {
	server_.DeleteVehicle(id);
}

void RequestHandler::DeleteSale(int id) {
	server_.DeleteSale(id);
}

std::optional<json::Dict> RequestHandler::FindDetailById(int id) {
	auto tmp = server_.FindDetailById(id);

	if (tmp.has_value()) {
		json::Dict ans;

		ans = json::Builder{}.StartDict()
			.Key("type").Value("detail"s)
			.Key("reply").StartDict()
			.Key("id").Value(tmp->id).Key("name").Value(tmp->name).Key("code").Value(tmp->code).Key("count").Value(tmp->count)
			.Key("buy_price").Value(tmp->buy_price).Key("sale_price").Value(tmp->sale_price)
			.EndDict()
			.EndDict().Build().AsDict();

		return ans;
	}

	return nullopt;
}

std::optional<json::Dict> RequestHandler::FindEmployeeById(int id) {
	auto tmp = server_.FindEmployeeById(id);

	if (tmp.has_value()) {
		json::Dict ans;

		ans = json::Builder{}.StartDict()
			.Key("type").Value("detail"s)
			.Key("reply").StartDict()
			.Key("id").Value(tmp->id).Key("name").Value(tmp->name)
			.Key("role").Value(tmp->role).Key("salary").Value(tmp->salary)
			.EndDict()
			.EndDict().Build().AsDict();

		return ans;
	}

	return nullopt;
}

std::optional<json::Dict> RequestHandler::FindVehicleById(int id) {
	auto tmp = server_.FindVehicleById(id);

	if (tmp.has_value()) {
		json::Dict ans;

		ans = json::Builder{}.StartDict()
			.Key("type").Value("detail"s)
			.Key("reply").StartDict()
			.Key("id").Value(tmp->id).Key("name").Value(tmp->name)
			.Key("code").Value(tmp->code).Key("client_id").Value(tmp->client_id)
			.EndDict()
			.EndDict().Build().AsDict();

		return ans;
	}

	return nullopt;
}

std::optional<json::Dict> RequestHandler::FindClientById(int id) {
	auto tmp = server_.FindClientById(id);

	if (tmp.has_value()) {
		json::Dict ans;

		ans = json::Builder{}.StartDict()
			.Key("type").Value("detail"s)
			.Key("reply").StartDict()
			.Key("id").Value(tmp->id).Key("name").Value(tmp->name)
			.Key("INN").Value(tmp->INN)
			.EndDict()
			.EndDict().Build().AsDict();

		return ans;
	}

	return nullopt;
}

std::optional<json::Dict> RequestHandler::FindSaleById(int id) {
	auto tmp = server_.FindSaleById(id);

	if (tmp.has_value()) {
		json::Dict ans;

		ans = json::Builder{}.StartDict()
			.Key("type").Value("detail"s)
			.Key("reply").StartDict()
			.Key("id").Value(tmp->id).Key("sale_count").Value(tmp->sale_count).Key("sale_date").Value(tmp->sale_date.AsString())
			.Key("income").Value(tmp->income).Key("detail_id").Value(tmp->detail_id).Key("client_id").Value(tmp->client_id)
			.Key("vehicle_id").Value(tmp->vehicle_id)
			.EndDict()
			.EndDict().Build().AsDict();

		return ans;
	}

	return nullopt;
}

std::optional<json::Dict> RequestHandler::FindDetails(DetailToQuery entity) {

	auto result = server_.FindDetails(entity);

	if (result.has_value()) {
		json::Dict ans;
		json::Array rep;

		for (auto item : *result) {
			json::Node dict;

			dict = json::Builder{}.StartDict()
				.Key("id").Value(item.id).Key("name").Value(item.name).Key("code").Value(item.code).Key("count").Value(item.count)
				.Key("buy_price").Value(item.buy_price).Key("sale_price").Value(item.sale_price)
				.EndDict().Build().AsDict();

			rep.push_back(dict);
		}

		ans = json::Builder{}.StartDict()
			.Key("type").Value("array_of_details"s)
			.Key("reply").Value(rep)
			.EndDict().Build().AsDict();

		return ans;
	}
}

std::optional<json::Dict> RequestHandler::FindEmployees(EmployeeToQuery entity) {

	auto result = server_.FindEmployees(entity);

	if (result.has_value()) {
		json::Dict ans;
		json::Array rep;

		for (auto item : *result) {
			json::Node dict;

			dict = json::Builder{}.StartDict()
				.Key("id").Value(item.id).Key("name").Value(item.name)
				.Key("role").Value(item.role).Key("salary").Value(item.salary)
				.EndDict().Build().AsDict();

			rep.push_back(dict);
		}

		ans = json::Builder{}.StartDict()
			.Key("type").Value("array_of_employees"s)
			.Key("reply").Value(rep)
			.EndDict().Build().AsDict();

		return ans;
	}
}

std::optional<json::Dict> RequestHandler::FindClients(ClientToQuery entity) {

	auto result = server_.FindClients(entity);

	if (result.has_value()) {
		json::Dict ans;
		json::Array rep;

		for (auto item : *result) {
			json::Node dict;

			dict = json::Builder{}.StartDict()
				.Key("id").Value(item.id).Key("name").Value(item.name)
				.Key("INN").Value(item.INN)
				.EndDict().Build().AsDict();

			rep.push_back(dict);
		}

		ans = json::Builder{}.StartDict()
			.Key("type").Value("array_of_clients"s)
			.Key("reply").Value(rep)
			.EndDict().Build().AsDict();

		return ans;
	}
}

std::optional<json::Dict> RequestHandler::FindVehicles(VehicleToQuery entity) {

	auto result = server_.FindVehicles(entity);

	if (result.has_value()) {
		json::Dict ans;
		json::Array rep;

		for (auto item : *result) {
			json::Node dict;

			dict = json::Builder{}.StartDict()
				.Key("id").Value(item.id).Key("name").Value(item.name)
				.Key("code").Value(item.code).Key("client_id").Value(item.client_id)
				.EndDict().Build().AsDict();

			rep.push_back(dict);
		}

		ans = json::Builder{}.StartDict()
			.Key("type").Value("array_of_vehicles"s)
			.Key("reply").Value(rep)
			.EndDict().Build().AsDict();

		return ans;
	}
}

std::optional<json::Dict> RequestHandler::FindSales(SaleToQuery entity) {

	auto result = server_.FindSales(entity);

	if (result.has_value()) {
		json::Dict ans;
		json::Array rep;

		for (auto item : *result) {
			json::Node dict;

			dict = json::Builder{}.StartDict()
				.Key("id").Value(item.id).Key("sale_count").Value(item.sale_count).Key("sale_date").Value(item.sale_date.AsString()).Key("income").Value(item.income)
				.Key("detail_id").Value(item.detail_id).Key("vehicle_id").Value(item.vehicle_id).Key("client_id").Value(item.client_id)
				.EndDict().Build().AsDict();

			rep.push_back(dict);
		}

		ans = json::Builder{}.StartDict()
			.Key("type").Value("array_of_sale"s)
			.Key("reply").Value(rep)
			.EndDict().Build().AsDict();

		return ans;
	}
}

double RequestHandler::ComputeIncome(std::string start_date, std::string end_date) {
	return 0.0;
}