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
}

void Server::AddDetail(const Detail && detail) {
    Detail new_detail = detail;
    new_detail.id = DataBaseManager_.GetLastId(EntityType::DETAIL) + 1;

    details_.push_back(new_detail);
    detail_by_id_[new_detail.id] = &details_.back();
    DataBaseManager_.UpdateLastId(EntityType::DETAIL);
}

void Server::AddEmployee(const Employee && employee) {
    Employee new_employee = employee;
    new_employee.id = DataBaseManager_.GetLastId(EntityType::EMPLOYEE) + 1;

    employees_[new_employee.id] = new_employee;
    DataBaseManager_.UpdateLastId(EntityType::EMPLOYEE);
}

void Server::AddClient(const Client && client) {
    Client new_client = client;
    new_client.id = DataBaseManager_.GetLastId(EntityType::CLIENT) + 1;

    clients_[new_client.id] = new_client;
    DataBaseManager_.UpdateLastId(EntityType::CLIENT);
}

void Server::AddVehicle(const Vehicle && vehicle) {
    Vehicle new_vehicle = vehicle;
    new_vehicle.id = DataBaseManager_.GetLastId(EntityType::VEHICLE) + 1;

    vehicles_[new_vehicle.id] = new_vehicle;
    DataBaseManager_.UpdateLastId(EntityType::VEHICLE);
}

void Server::AddSale(const Sale && sale) {
    Sale new_sale = sale;
    new_sale.id = DataBaseManager_.GetLastId(EntityType::SALE) + 1;

    sales_[new_sale.id] = new_sale;
    DataBaseManager_.UpdateLastId(EntityType::SALE);
}

std::optional<Detail> Server::FindDetailById(int id) {
    if (detail_by_id_.count(id)) {
        return details_.at(id);
    }
    else {
        return DataBaseManager_.FindDetailById(id);
    }
}

std::optional<Employee> Server::FindEmployeeById(int id) {
    if (employee_by_id_.count(id)) {
        return employees_.at(id);
    }
    else {
        return DataBaseManager_.FindEmployeeById(id);
    }
}

std::optional<Vehicle> Server::FindVehicleById(int id) {
    if (vehicle_by_id_.count(id)) {
        return vehicles_.at(id);
    }
    else {
        return DataBaseManager_.FindVehicleById(id);
    }
}

std::optional<Client> Server::FindClientById(int id) {
    if (client_by_id_.count(id)) {
        return clients_.at(id);
    }
    else {
        return DataBaseManager_.FindClientById(id);
    }
}

std::optional<Sale> Server::FindSaleById(int id) {
    if (sale_by_id_.count(id)) {
        return sales_ .at(id);
    }
    else {
        return DataBaseManager_.FindSaleById(id);
    }
}

std::optional<std::vector<Detail>> Server::FindDetails(DetailToFind entity) {
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

    std::copy_if(details_.begin(), details_.end(), back_inserter(result), [&entity](const auto& entity) {
        return (!detail.id.has_value() || *detail.id == entity.id) &&
            (!detail.name.has_value() || *detail.name == entity.name) &&
            (!detail.count.has_value() || *detail.count == entity.count) &&
            (!detail.code.has_value() || *detail.code == entity.code) &&
            (!detail.buy_price.has_value() || *detail.buy_price == entity.buy_price) &&
            (!detail.sale_price.has_value() || *detail.sale_price == entity.sale_price);
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
}

std::optional<std::vector<Employee>> Server::FindEmployees(EmployeeToFind entity) {
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

    std::copy_if(details_.begin(), details_.end(), back_inserter(result), [&entity](const auto& entity) {
        return (!detail.id.has_value() || *detail.id == entity.id) &&
            (!detail.name.has_value() || *detail.name == entity.name) &&
            (!detail.count.has_value() || *detail.count == entity.count) &&
            (!detail.code.has_value() || *detail.code == entity.code) &&
            (!detail.buy_price.has_value() || *detail.buy_price == entity.buy_price) &&
            (!detail.sale_price.has_value() || *detail.sale_price == entity.sale_price);
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
}

std::optional<std::vector<Client>> Server::FindClients(ClientToFind entity) {
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

    std::copy_if(details_.begin(), details_.end(), back_inserter(result), [&entity](const auto& entity) {
        return (!detail.id.has_value() || *detail.id == entity.id) &&
            (!detail.name.has_value() || *detail.name == entity.name) &&
            (!detail.count.has_value() || *detail.count == entity.count) &&
            (!detail.code.has_value() || *detail.code == entity.code) &&
            (!detail.buy_price.has_value() || *detail.buy_price == entity.buy_price) &&
            (!detail.sale_price.has_value() || *detail.sale_price == entity.sale_price);
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
}

std::optional<std::vector<Vehicle>> Server::FindVehicles(VehicleToFind entity) {
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

    std::copy_if(details_.begin(), details_.end(), back_inserter(result), [&entity](const auto& entity) {
        return (!detail.id.has_value() || *detail.id == entity.id) &&
            (!detail.name.has_value() || *detail.name == entity.name) &&
            (!detail.count.has_value() || *detail.count == entity.count) &&
            (!detail.code.has_value() || *detail.code == entity.code) &&
            (!detail.buy_price.has_value() || *detail.buy_price == entity.buy_price) &&
            (!detail.sale_price.has_value() || *detail.sale_price == entity.sale_price);
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
}

std::optional<std::vector<Sale>> Server::FindSales(SaleToFind entity) {
    unordered_set<int> entity_ids;
    vector<Sale> result;

    string query = "SELECT * FROM saled_details WHERE";

    if (entity.id.has_value()) {
        query += " Id = " + to_string(*entity.id);
    }

    if (entity.sale_date.has_value()) {
        query += " SaleDateTime = \"" + *entity.sale_date + '\"';
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

    std::copy_if(details_.begin(), details_.end(), back_inserter(result), [&entity](const auto& entity) {
        return (!detail.id.has_value() || *detail.id == entity.id) &&
            (!detail.name.has_value() || *detail.name == entity.name) &&
            (!detail.count.has_value() || *detail.count == entity.count) &&
            (!detail.code.has_value() || *detail.code == entity.code) &&
            (!detail.buy_price.has_value() || *detail.buy_price == entity.buy_price) &&
            (!detail.sale_price.has_value() || *detail.sale_price == entity.sale_price);
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
}