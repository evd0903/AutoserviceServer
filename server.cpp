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
    if (details_.count(id)) {
        return details_.at(id);
    }
    else {
        return DataBaseManager_.FindDetailById(id);
    }
}

std::optional<Employee> Server::FindEmployeeById(int id) {
    if (employees_.count(id)) {
        return employees_.at(id);
    }
    else {
        return DataBaseManager_.FindEmployeeById(id);
    }
}

std::optional<Vehicle> Server::FindVehicleById(int id) {
    if (vehicles_.count(id)) {
        return vehicles_.at(id);
    }
    else {
        return DataBaseManager_.FindVehicleById(id);
    }
}

std::optional<Client> Server::FindClientById(int id) {
    if (clients_.count(id)) {
        return clients_.at(id);
    }
    else {
        return DataBaseManager_.FindClientById(id);
    }
}

std::optional<Sale> Server::FindSaleById(int id) {
    if (sales_.count(id)) {
        return sales_ .at(id);
    }
    else {
        return DataBaseManager_.FindSaleById(id);
    }
}

std::optional<std::vector<Detail>> Server::FindDetails(DetailToFind detail) {
    //unordered_set<Detail> entities;
    vector<Detail> result;

    string query = "SELECT * FROM details WHERE";

    if (detail.id.has_value()) {
        query += " Id = " + to_string(*detail.id);
    }

    if (detail.name.has_value()) {
        query += " Name = " + *detail.name;
    }

    if (detail.count.has_value()) {
        query += " Count = " + to_string(*detail.count);
    }

    if (detail.code.has_value()) {
        query += " Code = " + *detail.code;
    }

    if (detail.buy_price.has_value()) {
        query += " BuyPrice = " + to_string(*detail.buy_price);
    }

    if (detail.sale_price.has_value()) {
        query += " SalePrice = " + to_string(*detail.sale_price);
    }

    query += ";";

    std::copy_if(details_.begin(), details_.end(), back_inserter(result), [&detail](const auto& entity) {
        return (!detail.id.has_value() || *detail.id == entity.second->id) &&
            (!detail.name.has_value() || *detail.name == entity.second->name) &&
            (!detail.count.has_value() || *detail.count == entity.second->count) &&
            (!detail.code.has_value() || *detail.code == entity.second->code) &&
            (!detail.buy_price.has_value() || *detail.buy_price == entity.second->buy_price) &&
            (!detail.sale_price.has_value() || *detail.sale_price == entity.second->sale_price);
        });

    auto request = DataBaseManager_.ExecuteCustomQuery<Detail>(query);

    

   /* if (request.has_value()) {
        for (auto& item : *request) {
            entities.insert(move(item));
        }
    }

    for (auto& entity : entities) {
        result.push_back(move(entity));
    }*/

    return result;
}

std::optional<std::vector<Employee>> Server::FindEmployees(EmployeeToFind detail)
{
    return std::optional<std::vector<Employee>>();
}

std::optional<std::vector<Client>> Server::FindClients(ClientToFind detail)
{
    return std::optional<std::vector<Client>>();
}

std::optional<std::vector<Vehicle>> Server::FindVehicles(VehicleToFind detail)
{
    return std::optional<std::vector<Vehicle>>();
}

std::optional<std::vector<Sale>> Server::FindSales(SaleToFind detail)
{
    return std::optional<std::vector<Sale>>();
}
