#include "server.h"

using namespace std;

void Server::SaveCacheToDataBase() {

	for (auto& entity : details_) {
		DataBaseManager_.AddDetail(move(entity));
	}

	for (auto& entity : employees_) {
		DataBaseManager_.AddEmployee(move(entity));
	}

	for (auto& entity : clients_) {
		DataBaseManager_.AddClient(move(entity));
	}

	for (auto& entity : vehicles_) {
		DataBaseManager_.AddVehicle(move(entity));
	}

	for (auto& entity : sales_) {
		DataBaseManager_.AddSale(move(entity));
	}

	details_.clear();
	employees_.clear();
	clients_.clear();
	vehicles_.clear();
	sales_.clear();

	detail_by_id_.clear();
	employee_by_id_.clear();
	client_by_id_.clear();
	vehicle_by_id_.clear();
	sale_by_id_.clear();
	detail_by_id_.clear();
	detail_by_id_.clear();
}

void Server::AddDetail(const Detail&& detail) {
	Detail new_detail = detail;
	new_detail.id = DataBaseManager_.GetLastId(EntityType::DETAIL) + 1;

	details_.push_back(new_detail);
	detail_by_id_[new_detail.id] = &details_.back();
	DataBaseManager_.UpdateLastId(EntityType::DETAIL);
}

void Server::AddEmployee(const Employee&& employee) {
	Employee new_employee = employee;
	new_employee.id = DataBaseManager_.GetLastId(EntityType::EMPLOYEE) + 1;

	employees_[new_employee.id] = new_employee;
	DataBaseManager_.UpdateLastId(EntityType::EMPLOYEE);
}

void Server::AddClient(const Client&& client) {
	Client new_client = client;
	new_client.id = DataBaseManager_.GetLastId(EntityType::CLIENT) + 1;

	clients_[new_client.id] = new_client;
	DataBaseManager_.UpdateLastId(EntityType::CLIENT);
}

void Server::AddVehicle(const Vehicle&& vehicle) {
	Vehicle new_vehicle = vehicle;
	new_vehicle.id = DataBaseManager_.GetLastId(EntityType::VEHICLE) + 1;

	vehicles_[new_vehicle.id] = new_vehicle;
	DataBaseManager_.UpdateLastId(EntityType::VEHICLE);
}

void Server::AddSale(const Sale&& sale) {
	Sale new_sale = sale;
	new_sale.id = DataBaseManager_.GetLastId(EntityType::SALE) + 1;

	sales_.push_back(move(new_sale));
	sale_by_id_[new_sale.id] = &sales_.back();
	DataBaseManager_.UpdateLastId(EntityType::SALE);
}

void Server::NewSale(int detail_id, int sale_count, int client_id, int vehicle_id) {
	if (!CheckDetailId(detail_id) || !CheckClientId(client_id) || !CheckVehicleId(vehicle_id)) {
		throw std::exception("DB doesn't has this id!");
	}

	Detail sale_detail = *FindDetailById(detail_id);

	SYSTEMTIME t;
	GetLocalTime(&t);


	Sale sale;
	sale.sale_count = sale_count;
	sale.sale_date = Date{t.wDay, t.wMonth, t.wYear};
	sale.income = sale_count * (sale_detail.sale_price - sale_detail.buy_price);
	sale.detail_id = detail_id;
	sale.client_id = client_id;
	sale.vehicle_id = vehicle_id;

	AddSale(move(sale));

	string query = "UPDATE details SET Count = Count - 1 WHERE Id = " + to_string(detail_id) + ";";
	DataBaseManager_.ExecuteCustomQuery<Detail>(query);
}

void Server::DeleteDetail(int id) {
	if (!CheckDetailId(id)) {
		throw std::exception("DB doesn't has this id!");
	}

	DataBaseManager_.DeleteDetail(id);
}

void Server::DeleteEmployee(int id) {
	if (!CheckEmployeeId(id) && detail_by_id_.find(id) == detail_by_id_.end()) {
		throw std::exception("DB doesn't has this id!");
	}
	else if (CheckEmployeeId(id)) {
		DataBaseManager_.DeleteEmployee(id);
	}
	else if (detail_by_id_.find(id) != detail_by_id_.end()) {
		detail_by_id_.erase(id);
	}
}

void Server::DeleteClient(int id) {
	if (!CheckClientId(id) && employee_by_id_.find(id) == employee_by_id_.end()) {
		throw std::exception("DB doesn't has this id!");
	}
	else if (CheckClientId(id)) {
		DataBaseManager_.DeleteClient(id);
	}
	else if (employee_by_id_.find(id) != employee_by_id_.end()) {
		employee_by_id_.erase(id);
	}
}

void Server::DeleteVehicle(int id) {
	if (!CheckVehicleId(id) && vehicle_by_id_.find(id) == vehicle_by_id_.end()) {
		throw std::exception("DB doesn't has this id!");
	}
	else if (CheckVehicleId(id)) {
		DataBaseManager_.DeleteVehicle(id);
	}
	else if (vehicle_by_id_.find(id) != vehicle_by_id_.end()) {
		vehicle_by_id_.erase(id);
	}
}

void Server::DeleteSale(int id) {
	if (!CheckSaleId(id) && sale_by_id_.find(id) == sale_by_id_.end()) {
		throw std::exception("DB doesn't has this id!");
	}
	else if (CheckSaleId(id)) {
		DataBaseManager_.DeleteSale(id);
	}
	else if (sale_by_id_.find(id) != sale_by_id_.end()) {
		sale_by_id_.erase(id);
	}
}

void Server::UpdateDetail(int id, DetailToQuery detail) {
	if (!CheckDetailId(id)) {
		throw exception("DB doesn't has this id!");
	}

	DataBaseManager_.UpdateDetail(id, detail);
}

void Server::UpdateEmployee(int id, EmployeeToQuery employee) {
	if (!CheckEmployeeId(id)) {
		throw exception("DB doesn't has this id!");
	}

	DataBaseManager_.UpdateEmployee(id, employee);

}

void Server::UpdateClient(int id, ClientToQuery client) {
	if (!CheckClientId(id)) {
		throw exception("DB doesn't has this id!");
	}

	DataBaseManager_.UpdateClient(id, client);

}

void Server::UpdateVehicle(int id, VehicleToQuery vehicle) {
	if (!CheckVehicleId(id)) {
		throw exception("DB doesn't has this id!");
	}

	DataBaseManager_.UpdateVehicle(id, vehicle);
}

void Server::UpdateSale(int id, SaleToQuery sale) {
	if (!CheckSaleId(id)) {
		throw exception("DB doesn't has this id!");
	}

	DataBaseManager_.UpdateSale(id, sale);
}

std::optional<Detail> Server::FindDetailById(int id) {
	if (detail_by_id_.find(id) != detail_by_id_.end()) {
		return *detail_by_id_.at(id);
	}
	else {
		auto ans = DataBaseManager_.FindDetailById(id);

		if (!ans.has_value()) {
			throw exception("DB doesn't has this id!");
		}
	}
}

std::optional<Employee> Server::FindEmployeeById(int id) {
	if (employee_by_id_.count(id) && employee_by_id_.at(id)) {
		return *employee_by_id_.at(id);
	}
	else {
		return DataBaseManager_.FindEmployeeById(id);
	}
}

std::optional<Vehicle> Server::FindVehicleById(int id) {
	if (vehicle_by_id_.count(id) && vehicle_by_id_.at(id)) {
		return *vehicle_by_id_.at(id);
	}
	else {
		return DataBaseManager_.FindVehicleById(id);
	}
}

std::optional<Client> Server::FindClientById(int id) {
	if (client_by_id_.count(id) && client_by_id_.at(id)) {
		return *client_by_id_.at(id);
	}
	else {
		return DataBaseManager_.FindClientById(id);
	}
}

std::optional<Sale> Server::FindSaleById(int id) {
	if (sale_by_id_.count(id) && sale_by_id_.at(id)) {
		return *sale_by_id_.at(id);
	}
	else {
		return DataBaseManager_.FindSaleById(id);
	}
}

std::optional<std::vector<Detail>> Server::FindDetails(DetailToQuery entity) {
	unordered_set<int> entity_ids;
	vector<Detail> result;

	string query = "SELECT * FROM details WHERE";

	if (entity.id.has_value()) {
		query += " Id = " + to_string(*entity.id);
	}

	if (entity.name.has_value()) {
		query += " Name = \"" + *entity.name + '\"';
	}

	if (entity.count.has_value()) {
		query += " Count = " + to_string(*entity.count);
	}

	if (entity.code.has_value()) {
		query += " Code = " + *entity.code;
	}

	if (entity.buy_price.has_value()) {
		query += " BuyPrice = " + to_string(*entity.buy_price);
	}

	if (entity.sale_price.has_value()) {
		query += " SalePrice = " + to_string(*entity.sale_price);
	}

	query += ";";

	std::copy_if(details_.begin(), details_.end(), back_inserter(result), [&entity](const auto& detail) {
		return (!entity.id.has_value() || *entity.id == detail.id) &&
			(!entity.name.has_value() || *entity.name == detail.name) &&
			(!entity.count.has_value() || *entity.count == detail.count) &&
			(!entity.code.has_value() || *entity.code == detail.code) &&
			(!entity.buy_price.has_value() || *entity.buy_price == detail.buy_price) &&
			(!entity.sale_price.has_value() || *entity.sale_price == entity.sale_price);
		});

	auto request = DataBaseManager_.ExecuteCustomQuery<Detail>(query);

	if (request.has_value()) {
		for (auto& item : *request) {
			entity_ids.insert(move(item.id));
		}
	}

	for (auto& entity_id : entity_ids) {
		auto detail = FindDetailById(entity_id);
		if (detail.has_value()) {
			result.push_back(move(*detail));
		}
	}

	if (result.size()) {
		return result;
	}

	return nullopt;
}

std::optional<std::vector<Employee>> Server::FindEmployees(EmployeeToQuery entity) {
	unordered_set<int> entity_ids;
	vector<Employee> result;

	string query = "SELECT * FROM employees WHERE";

	if (entity.id.has_value()) {
		query += " Id = " + to_string(*entity.id);
	}

	if (entity.name.has_value()) {
		query += " Name = \"" + *entity.name + '\"';
	}

	if (entity.role.has_value()) {
		query += " Role = \"" + *entity.role + '\"';
	}

	if (entity.salary.has_value()) {
		query += " Salary = " + to_string(*entity.salary);
	}

	query += ";";

	std::copy_if(employees_.begin(), employees_.end(), back_inserter(result), [&entity](const auto& employee) {
		return (!entity.id.has_value() || *entity.id == employee.id) &&
			(!entity.name.has_value() || *entity.name == employee.name) &&
			(!entity.role.has_value() || *entity.role == employee.role) &&
			(!entity.salary.has_value() || *entity.salary == employee.salary);
		});

	auto request = DataBaseManager_.ExecuteCustomQuery<Detail>(query);

	if (request.has_value()) {
		for (auto& item : *request) {
			entity_ids.insert(move(item.id));
		}
	}

	for (auto& entity_id : entity_ids) {
		auto entity = FindEmployeeById(entity_id);
		if (entity.has_value()) {
			result.push_back(move(*entity));
		}
	}

	if (result.size()) {
		return result;
	}

	return nullopt;
}

std::optional<std::vector<Client>> Server::FindClients(ClientToQuery entity) {
	unordered_set<int> entity_ids;
	vector<Client> result;

	string query = "SELECT * FROM clients WHERE";

	if (entity.id.has_value()) {
		query += " Id = " + to_string(*entity.id);
	}

	if (entity.name.has_value()) {
		query += " Name = \"" + *entity.name + '\"';
	}

	if (entity.INN.has_value()) {
		query += " INN = \"" + *entity.INN + '\"';
	}

	query += ";";

	std::copy_if(clients_.begin(), clients_.end(), back_inserter(result), [&entity](const auto& client) {
		return (!entity.id.has_value() || *entity.id == client.id) &&
			(!entity.name.has_value() || *entity.name == client.name) &&
			(!entity.INN.has_value() || *entity.INN == client.INN);
		});

	auto request = DataBaseManager_.ExecuteCustomQuery<Detail>(query);

	if (request.has_value()) {
		for (auto& item : *request) {
			entity_ids.insert(move(item.id));
		}
	}

	for (auto& entity_id : entity_ids) {
		auto entity = FindClientById(entity_id);
		if (entity.has_value()) {
			result.push_back(move(*entity));
		}
	}

	if (result.size()) {
		return result;
	}

	return nullopt;
}

std::optional<std::vector<Vehicle>> Server::FindVehicles(VehicleToQuery entity) {
	unordered_set<int> entity_ids;
	vector<Vehicle> result;

	string query = "SELECT * FROM vehicles WHERE";

	if (entity.id.has_value()) {
		query += " Id = " + to_string(*entity.id);
	}

	if (entity.name.has_value()) {
		query += " Name = \"" + *entity.name + '\"';
	}

	if (entity.code.has_value()) {
		query += " Code = \"" + *entity.code + '\"';
	}

	if (entity.client_id.has_value()) {
		query += " ClientId = " + to_string(*entity.client_id);
	}

	query += ";";

	std::copy_if(vehicles_.begin(), vehicles_.end(), back_inserter(result), [&entity](const auto& vehicle) {
		return (!entity.id.has_value() || *entity.id == vehicle.id) &&
			(!entity.name.has_value() || *entity.name == vehicle.name) &&
			(!entity.code.has_value() || *entity.code == vehicle.code) &&
			(!entity.client_id.has_value() || *entity.client_id == vehicle.client_id);
		});

	auto request = DataBaseManager_.ExecuteCustomQuery<Detail>(query);

	if (request.has_value()) {
		for (auto& item : *request) {
			entity_ids.insert(move(item.id));
		}
	}

	for (auto& entity_id : entity_ids) {
		auto entity = FindVehicleById(entity_id);
		if (entity.has_value()) {
			result.push_back(move(*entity));
		}
	}

	if (result.size()) {
		return result;
	}

	return nullopt;
}

std::optional<std::vector<Sale>> Server::FindSales(SaleToQuery entity) {
	unordered_set<int> entity_ids;
	vector<Sale> result;

	string query = "SELECT * FROM saled_details WHERE";

	if (entity.id.has_value()) {
		query += " Id = " + to_string(*entity.id);
	}

	if (entity.sale_date.has_value()) {
		query += " SaleDateTime = \"" + entity.sale_date->AsString() + '\"';
	}

	if (entity.sale_count.has_value()) {
		query += " SaleCount = \"" + *entity.sale_count + '\"';
	}

	if (entity.income.has_value()) {
		query += " Income = " + to_string(*entity.income);
	}

	if (entity.detail_id.has_value()) {
		query += " DetailId = " + to_string(*entity.detail_id);
	}

	if (entity.client_id.has_value()) {
		query += " ClientId = " + to_string(*entity.client_id);
	}

	if (entity.vehicle_id.has_value()) {
		query += " VehicleId = " + to_string(*entity.vehicle_id);
	}

	query += ";";

	std::copy_if(sales_.begin(), sales_.end(), back_inserter(result), [&entity](const auto& sale) {
		return (!entity.id.has_value() || *entity.id == sale.id) &&
			(!entity.sale_count.has_value() || *entity.sale_count == sale.sale_count) &&
			(!entity.sale_date.has_value() || *entity.sale_date == sale.sale_date) &&
			(!entity.income.has_value() || *entity.income == sale.income) &&
			(!entity.detail_id.has_value() || *entity.detail_id == sale.detail_id) &&
			(!entity.client_id.has_value() || *entity.client_id == sale.client_id) &&
			(!entity.vehicle_id.has_value() || *entity.vehicle_id == sale.vehicle_id);
		});

	auto request = DataBaseManager_.ExecuteCustomQuery<Detail>(query);

	if (request.has_value()) {
		for (auto& item : *request) {
			entity_ids.insert(move(item.id));
		}
	}

	for (auto& entity_id : entity_ids) {
		auto entity = FindSaleById(entity_id);
		if (entity.has_value()) {
			result.push_back(move(*entity));
		}
	}

	if (result.size()) {
		return result;
	}

	return nullopt;
}

bool Server::CheckDetailId(int id) {
	auto tmp = DataBaseManager_.FindDetailById(id);

	if (tmp.has_value()) {
		return true;
	}

	return false;
}

bool Server::CheckEmployeeId(int id) {
	return DataBaseManager_.FindEmployeeById(id).has_value();
}

bool Server::CheckClientId(int id)
{
	return DataBaseManager_.FindClientById(id).has_value();
}

bool Server::CheckVehicleId(int id)
{
	return DataBaseManager_.FindVehicleById(id).has_value();
}

bool Server::CheckSaleId(int id) {
	return DataBaseManager_.FindSaleById(id).has_value();
}

double Server::ComputeIncome(std::string start_date, std::string end_date) {
	return DataBaseManager_.ComputeIncome(start_date, end_date);
}