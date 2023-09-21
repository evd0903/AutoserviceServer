#include <iostream>
#include <string>

#include "request_handler.h"

using namespace std;

int main()
{
	string db_name = "MyDB.db";
	/*Server server(db_name);
	

	DetailToQuery detail;
	detail.buy_price = 8000;


	try {
		server.UpdateDetail(16, detail);

	}
	catch (const exception& e) {
		cerr << e.what() << endl;
	}*/
	Server server(db_name);

	RequestHandler rq(server);


	try {
		for (int i = 0; i != 2; ++i) {
			auto ans = rq.HandleRequest();

			json::Print(*ans, cout);
		}
	}
	catch (const exception& e) {
		cerr << e.what();
	}
	/*try {
		server.DeleteDetail(14);
	}
	catch (exception& e) {
		cerr << e.what() << endl;
	}*/
	/*DetailToFind d;

	d.name = "Tormoza10";


	auto ans1 = *server.FindDetails(d);

	for (auto ans : ans1) {
		cout << ans.name << " " << ans.count << " " << ans.code << " " << ans.buy_price << " " << ans.sale_price;
	}*/

	
	/*DataBaseManager dbm("MyDB.db");
	Detail detail;
	detail.name = "Tormoza10";
	detail.count = 4;
	detail.code = "41151553";
	detail.buy_price = 10000;
	detail.sale_price = 12500;

	dbm.AddDetail(move(detail));*/

	//Detail ans = *dbm.FindDetailById(14);

	

	/*vector<Detail> ans1 = *dbm.ExecuteCustomQuery<Detail>("SELECT * FROM details WHERE Id = 14;");


	auto ans = ans1[0];

	cout << ans.name << " " << ans.count << " " << ans.code << " " << ans.buy_price << " " << ans.sale_price;*/
	/*Sale sale;
	sale.sale_count = 1;
	sale.sale_date = "23/08/2023";
	sale.income = 5000;
	sale.detail_id = 1;
	sale.client_id = 1;
	sale.vehicle_id = 1;

	dbm.AddSale(move(sale));*/


	//db << "Create table if not exists users1 (id Integer primary key, login Text)";
	//db << "Insert into users1 (login) VALUES (?);" << "petr2000";

	/**sqlite3* db;
	int rc;
	rc = sqlite3_open("MyDB.db", &db);
	if (rc != SQLITE_OK) {
		cout << "NO" << endl;
	}
	else {
		cout << "YES" << endl;
	}

	const char* createTableSQL = "Create table if not exists users (id Integer primary key, login Text)";
	char * errorMessage;
	rc = sqlite3_exec(db, createTableSQL, 0, 0, &errorMessage);

	if (rc != SQLITE_OK) {
		cout << "Error" << endl;
		sqlite3_free(errorMessage);
	}
	else {
		cout << "OK" << endl;
	}


	sqlite3_close(db);*/
	
	
	return 0;
}

