#pragma once

#include "framework.h"
#include "resource.h"


class eSqlite3 {
public:
	eSqlite3() {
		rc = sqlite3_open("mian.db", &db);
		buffer = sqlite3_errmsg(db);
		onSqlError(rc, "Error occurred on opening the database code: 132 reason: " + buffer);
		if (checkFile("mian.db") == 1) {
			initializeDb();
		}
	}

	~eSqlite3() {
		file.open("mian.log", std::ios_base::app);
		file << "desructor called\r\n";
		if (sqlite3_close(db) != SQLITE_OK) {
			buffer = sqlite3_errmsg(db);
			file << "failed to close db code: 127 reason: " + buffer + "\r\n";
		}
		file.close();
	}

	int checkFile(std::string fileName);
	int initializeDb();
	int createLog();
	int writeToDb(
		std::string employee1,
		std::string costumer,
		std::string date,
		std::string desc
	);
	int searchDb(
		int employee1Length,
		int costumerLength,
		int dateFromLength,
		int dateToLength,
		int descLength,
		std::string employee1,
		std::string costumer,
		std::string fromDate,
		std::string toDate,
		std::string desc
	);
	int searchDbExtNormal(std::string column, std::string value);
	int searchDbExtDate(
		std::string column,
		std::string value,
		std::string fromDate,
		std::string toDate
	);
	int updateDb(std::string idPrimary, std::string column, std::string data);
	int dbDeleteInfo(std::string idPrimary);
	int onSqlError(int rc1, std::string errorDesc);
	int getLastId();
	std::wstring stringToWString(std::string inString);

private:
	sqlite3* db;
	std::fstream file;
	char* errMsg = nullptr;
	int rc;
	int lastId;
	errno_t err;
	size_t elementsWritten;
	std::string buffer;
	std::wstring wBuffer;
	std::string initDb = "INSERT INTO mian (id, employee, costumer, date, description)"
		"VALUES (0, 'john doe', 'john doe', '2020-01-01', 'empty');";
	std::string selectMaxIdQuery = "SELECT MAX(id) FROM mian;";
	std::string sql_table = "CREATE TABLE IF NOT EXISTS mian("
		"id INT PRIMARY KEY,"
		"employee VARCHAR NOT NULL,"
		"costumer VARCHAR NOT NULL,"
		"date DATE NOT NULL,"
		"description VARCHAR);";
};

class eSqlite3Derived : public eSqlite3 {
	// this class is just for calling the desructor at the process termination: case WM_DESTROY
public:
	eSqlite3Derived() {

	}
};

class employee {
public:
	int globalBoxes(HWND hWnd);
	int mainWindow(HWND hWnd);
	int searchWindow(HWND hWnd);
	int editWindow(HWND hWnd);
	int deleteWindow(HWND hWnd);
	int destroyMainWindow();
	int destroySearchWindow();
	int destroyEditWindow();
	int destroyDeleteWindow();
	int onNextPageButtonPressed(HWND hWnd);
	int onLastPageButtonPressed(HWND hWnd);
	int onCommitButtonPressed(HWND hWnd);
	int onSearchButtonPressed(HWND hWnd);
	int onEditButtonPressed(HWND hWnd);
	int onDeleteButtonPressed(HWND hWnd);
	int checkInput(int bufferLenght, int size);
	int writeFileToBuffer();
	std::string wchartToString(wchar_t* wstr);
	std::wstring stringToWString(std::string inString);
	LPCWSTR stringToWchar(const std::string& buffer);

private:
	// start of static boxes

	// global boxes
	HWND sLogBox;
	
	// main window boxes
	HWND mainWindowDesc;
	HWND sEmployee;
	HWND sCostumer;
	HWND sDate;
	HWND sDesc;
	HWND sDateDesc;

	// search window boxes
	HWND ssEmployee; // ssEmployee = static search employee
	HWND ssCostumer;
	HWND ssFromDate;
	HWND ssToDate;
	HWND ssDesc;

	// edit window boxes
	HWND editWindowDesc;
	HWND sId;
	HWND seEmployee; // seEmployee = static edit employee
	HWND seCostumer;
	HWND seDate;
	HWND seDesc;

	//delete window boxes
	HWND deleteWindowDesc;
	HWND sdId;

	// end of static boxes


	
	// start of edit boxes
	 
	// main window boxes
	HWND eEmployee;
	HWND eCostumer;
	HWND eDate;
	HWND eDesc;

	// search window boxes
	HWND searchWindowDesc;
	HWND esEmployee; // ssEmployee = edit search employee
	HWND esCostumer;
	HWND esFromDate;
	HWND esToDate;
	HWND esDesc;

	// edit window boxes
	HWND eId;
	HWND eeEmployee; // eeEmployee = edit(box) edit employee
	HWND eeCostumer;
	HWND eeDate;
	HWND eeDesc;

	// delete window boxes
	HWND edId; // edId = edit delete id

	// end of static boxes



	// start of button boxes

	// global boxes
	HWND nextPageButton;
	HWND lastPageButton;
	
	// main window boxes
	HWND commitButton;

	// search window boxes
	HWND searchButton;

	// edit window boxes
	HWND editButton;

	// delete window boxes
	HWND deleteButton;

	// end of button boxes



	// description variables
	wchar_t dDesc[34] = _T("با این فرمت وارد کنید: 30-12-1343");

	// other stuff
	std::fstream file;
	std::string buffer;
	std::wstring wBuffer;
	int page = 0;
	wchar_t* idBuffer = nullptr;
	wchar_t* employeeBuffer = nullptr;
	wchar_t* costumerBuffer = nullptr;
	wchar_t* dateBuffer = nullptr;
	wchar_t* descBuffer = nullptr;
	wchar_t* fromDateBuffer = nullptr;
	wchar_t* toDateBuffer = nullptr;
	wchar_t* logBuffer = nullptr;
	int bufferLength1 = 0;
	int bufferLength2 = 0;
	int bufferLength3 = 0;
	int bufferLength4 = 0;
	int bufferLength5 = 0;
	int bufferLength6 = 0;
};

static int callback(void* notUsed, int argc, char** argv, char** azColName) {
	MessageBox(NULL, "callback function called", "info", MB_OK | MB_ICONINFORMATION);
	std::string buffer = "callback -> ";
	for (int i = 0; i < argc; i++) {
		buffer += azColName[i];
		buffer += " = ";
		buffer += argv[i] ? argv[i] : "NULL";
	}
	buffer += "\r\n";
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::wstring wBuffer = converter.from_bytes(buffer);
	buffer = converter.to_bytes(wBuffer);

	std::fstream file("mian.log", std::ios_base::app);
	if (file.is_open()) {
		file << buffer;
	}
	else {
		MessageBox(NULL, "Error occurred on opening log file code: 153", "Error", MB_OK | MB_ICONERROR);
	}
	file.close();

	return 0;
}

int eSqlite3::checkFile(std::string fileName) {
	std::ifstream file(fileName);
	if (file) {
		std::ifstream inputFile(fileName);
		std::ofstream outputFile(fileName, std::ios_base::app);
		if (!inputFile.is_open()) {
			MessageBox(NULL, "Cannot read the database.", "Error", MB_OK | MB_ICONERROR);
			inputFile.close();
			outputFile.close();
			PostQuitMessage(1);
		}
		else if (!outputFile.is_open()) {
			MessageBox(NULL, "Cannot write the database.", "Error", MB_OK | MB_ICONERROR);
			inputFile.close();
			outputFile.close();
			PostQuitMessage(1);
		}
		else {
			inputFile.close();
			outputFile.close();
		}
	}
	else {
		return 0;
	}
	return 1;
}

int eSqlite3::initializeDb() {
	sqlite3_stmt* stmt;
	buffer = "SELECT name FROM sqlite_master WHERE "
		"type='table' AND name='mian';";
	rc = sqlite3_prepare_v2(db, buffer.c_str(), -1, &stmt, nullptr);
	buffer = sqlite3_errmsg(db);
	onSqlError(rc, "Failed to execute query code:124 reason: " + buffer);
	
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_ROW) {
		MessageBox(NULL, "table does not exist, initializing database", "Info", MB_OK);
		rc = sqlite3_exec(db, sql_table.c_str(), callback, 0, &errMsg);
		buffer = sqlite3_errmsg(db);
		onSqlError(rc, "Error occurred on creating table code: 133 reason: " + buffer);

		rc = sqlite3_exec(db, initDb.c_str(), callback, 0, &errMsg);
		buffer = sqlite3_errmsg(db);
		onSqlError(rc, "Error occurred on initializing db code: 134 reason: " + buffer);
	}
	else if (rc == SQLITE_ROW) {
		MessageBox(NULL, "table exists", "info", MB_OK);
	}
	
	rc = sqlite3_finalize(stmt);
	buffer = sqlite3_errmsg(db);
	onSqlError(rc, "Error occurred on finalizing sqlite stmt code: 142 reason:" + buffer);
	return 0;
}

int eSqlite3::createLog() {
	std::fstream fileName("mian.log", std::ios_base::out);
	if (fileName.is_open()) {
		fileName << "start of log file" << "\r\n";
	}
	else {
		MessageBox(NULL, "Failed to create log file", "Error", MB_OK | MB_ICONERROR);
		PostQuitMessage(1);
	}
	return 0;
}
int eSqlite3::writeToDb(
	std::string employee1,
	std::string costumer,
	std::string date,
	std::string desc = "empty"
)   {

	sqlite3_stmt* stmt;
	getLastId();
	lastId++;
	buffer = "id which is going to be written to db is: " + std::to_string(lastId);
	MessageBox(NULL, buffer.c_str(), "info", MB_OK);
	buffer = "INSERT INTO mian (id, employee, costumer, date, description) VALUES "
		"(?, ?, ?, ?, ?);";
	rc = sqlite3_prepare_v2(db, buffer.c_str(), -1, &stmt, nullptr);
	buffer = sqlite3_errmsg(db);
	onSqlError(rc, "Error occurred on preparing staement code: 140 reason: " + buffer);
	rc = sqlite3_bind_int(stmt, 1, lastId++);
	buffer = sqlite3_errmsg(db);
	onSqlError(rc, "Error occurred on preparing staement code: 135 reason: " + buffer);
	rc = sqlite3_bind_text(stmt, 2, employee1.c_str(), -1, SQLITE_STATIC);
	buffer = sqlite3_errmsg(db);
	onSqlError(rc, "Error occurred on preparing staement code: 136 reason: " + buffer);
	rc = sqlite3_bind_text(stmt, 3, costumer.c_str(), -1, SQLITE_STATIC);
	buffer = sqlite3_errmsg(db);
	onSqlError(rc, "Error occurred on preparing staement code: 137 reason: " + buffer);
	rc = sqlite3_bind_text(stmt, 4, date.c_str(), -1, SQLITE_STATIC);
	buffer = sqlite3_errmsg(db);
	onSqlError(rc, "Error occurred on preparing staement code: 138 reason: " + buffer);
	rc = sqlite3_bind_text(stmt, 5, desc.c_str(), -1, SQLITE_STATIC);
	buffer = sqlite3_errmsg(db);
	onSqlError(rc, "Error occurred on preparing staement code: 139 reason: " + buffer);
	rc = sqlite3_step(stmt);
	buffer = sqlite3_errmsg(db);
	if (rc != SQLITE_DONE) {
		onSqlError(rc, "Error occurred on preparing staement code: 140 reason: " + buffer);
	}
	rc = sqlite3_finalize(stmt);
	buffer = sqlite3_errmsg(db);
	onSqlError(rc, "Error occurred on finalizing sqlite stmt code: 142 reason:" + buffer);
	errMsg = nullptr;
	return 0;
}

int eSqlite3::searchDb(
	int employee1Length,
	int costumerLength,
	int dateFromLength,
	int dateToLength,
	int descLength,
	std::string employee1 = "",
	std::string costumer = "",
	std::string fromDate = "",
	std::string toDate = "",
	std::string desc = ""
) {
	if (
		dateFromLength == 0 &&
		dateToLength == 0
		) {
		if (employee1Length != 0) {
			searchDbExtNormal("employee", employee1);
			return 0;
		}
		else if (costumerLength != 0) {
			searchDbExtNormal("costumer", costumer);
			return 0;
		}
		else if (descLength != 0) {
			searchDbExtNormal("description", desc);
			return 0;
		}
	}
	else if (
		dateFromLength != 0 &&
		dateToLength != 0
		) {
		if (employee1Length != 0) {
			searchDbExtDate("employee", employee1, fromDate, toDate);
			return 0;
		}
		else if (costumerLength != 0) {
			searchDbExtDate("costumer", costumer, fromDate, toDate);
			return 0;
		}
		else if (descLength != 0) {
			searchDbExtDate("description", desc, fromDate, toDate);
			return 0;
		}
	}
	return 0;
}

int eSqlite3::searchDbExtNormal(std::string column, std::string value) {

	buffer = "SELECT * FROM mian WHERE " + column + "='" + value + "';";
	//buffer = "SELECT * FROM mian WHERE id=1";

	rc = sqlite3_exec(db, buffer.c_str(), callback, 0, &errMsg);
	buffer = "Error occurred on searching db, code: 150, reason: ";
	buffer += sqlite3_errmsg(db);

	if (rc != SQLITE_OK) {
		MessageBox(NULL, buffer.c_str(), "info", MB_OK | MB_ICONINFORMATION);
	}
	
	return 0;
}

int eSqlite3::searchDbExtDate(
	std::string column,
	std::string value,
	std::string fromDate,
	std::string toDate
) {

	buffer = "SELECT ";
	buffer.append(column);
	buffer.append(" WHERE date >= '");
	buffer.append(fromDate);
	buffer.append("' AND date <= '");
	buffer.append(toDate);
	buffer.append("';");

	rc = sqlite3_exec(db, buffer.c_str(), callback, 0, &errMsg);
	buffer = "Error occurred on searching db, code: 150, reason: ";
	buffer += sqlite3_errmsg(db);

	if (rc != SQLITE_OK) {
		MessageBox(NULL, buffer.c_str(), "info", MB_OK | MB_ICONINFORMATION);
	}

	return 0;
}

int eSqlite3::updateDb(std::string idPrimary, std::string column, std::string data) {
	// TODO: debug this wBuffer instead of buffer
	buffer = "UPDATE mian SET " + column + " = '" + data + "' WHERE id = " + idPrimary + ";";

	rc = sqlite3_exec(db, buffer.c_str(), NULL, 0, &errMsg);
	buffer = sqlite3_errmsg(db);
	onSqlError(rc, "Error occurred on editing data code: 130 reason: " + buffer + std::to_string(*errMsg));
	return 0;
}

int eSqlite3::dbDeleteInfo(std::string idPrimary) {
	buffer = "DELETE FROM mian WHERE id = " + idPrimary + ";";

	rc = sqlite3_exec(db, buffer.c_str(), callback, 0, &errMsg);
	buffer = sqlite3_errmsg(db);
	onSqlError(rc, "Error occurred on deleting data code: 131 reason: " + buffer);

	return 0;
}

int eSqlite3::onSqlError(int rc1, std::string errorDesc) {
	if (rc1 != SQLITE_OK) {
		MessageBox(NULL, errorDesc.c_str(), "Error", MB_OK | MB_ICONERROR);
		file.open("mian.log", std::ios_base::app);
		if (!file.is_open()) {
			MessageBox(NULL, "Error occurred on opening log file code: 139", "Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		buffer = errorDesc;
		buffer += sqlite3_errmsg(db);
		buffer += "\r\n";
		file << buffer;

		rc = sqlite3_close(db);
		if (rc != SQLITE_OK) {
			buffer = "Error occurred on closing database code: 400 reason: ";
			buffer += sqlite3_errmsg(db);
			buffer += "\r\n";
			file.open("mian.log", std::ios_base::app);
			file << buffer;
		}
		file.close();
		PostQuitMessage(1);
	}
	return 0;
}

int eSqlite3::getLastId() {
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(db, selectMaxIdQuery.c_str(), -1, &stmt, 0);
	if (rc == SQLITE_OK) {
		
		if (sqlite3_step(stmt) == SQLITE_ROW) {

			lastId = sqlite3_column_int(stmt, 0);
		}
		else {
			buffer = "Error occurred on fetching data from db, error code: 141, reason: ";
			buffer += sqlite3_errmsg(db);
			buffer += "\r\n";
			MessageBoxW(NULL, wBuffer.c_str(), L"Error", MB_OK);
			onSqlError(rc, buffer);
		}
	}
	else {
		buffer = "Error occured on preparing db, error code: 123, reason: ";
		buffer += sqlite3_errmsg(db);
		buffer += "\r\n";
		MessageBox(NULL, buffer.c_str(), "Error", MB_OK | MB_ICONERROR);
		lastId = 0;
	}
	sqlite3_finalize(stmt);
	return 0;
}

int employee::globalBoxes(HWND hWnd) {
	
	nextPageButton = CreateWindowW(
		_T("Button"),
		_T("صفحه بعد"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | BS_CENTER,
		0,
		160,
		100,
		30,
		hWnd,
		(HMENU)NEXT_PAGE_BUTTON,
		NULL,
		NULL
	);

	lastPageButton = CreateWindowW(
		_T("Button"),
		_T("صفحه قبل"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | BS_CENTER,
		120,
		160,
		100,
		30,
		hWnd,
		(HMENU)LAST_PAGE_BUTTON,
		NULL,
		NULL
	);
	
	EnableWindow(lastPageButton, FALSE);

	sLogBox = CreateWindowW(
		_T("Edit"),
		_T(""),
		WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL | ES_RIGHT | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE,
		0,
		200,
		783,
		340,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	return 0;
}

int employee::mainWindow(HWND hWnd) {
	mainWindowDesc = CreateWindowW(
		_T("Static"),
		_T("ثبت اطلاعات"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
		0,
		0,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	sEmployee = CreateWindowW(
		_T("Static"),
		_T(":کارشناس"),
		WS_VISIBLE | WS_CHILD | SS_RIGHT,
		670,
		0,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);
	eEmployee = CreateWindowW(
		_T("Edit"),
		_T(""),
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_RIGHT,
		570,
		0,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	sCostumer = CreateWindowW(
		_T("Static"),
		_T(":مشتری"),
		WS_VISIBLE | WS_CHILD | SS_RIGHT,
		670,
		40,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	eCostumer = CreateWindowW(
		_T("Edit"),
		_T(""),
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_RIGHT,
		570,
		40,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);
	
	sDate = CreateWindowW(
		_T("Static"),
		_T(":تاریخ"),
		WS_VISIBLE | WS_CHILD | SS_RIGHT,
		670,
		80,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	eDate = CreateWindowW(
		_T("Edit"),
		_T(""),
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_LEFT,
		570,
		80,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	sDesc = CreateWindowW(
		_T("Static"),
		_T(":توضیحات"),
		WS_VISIBLE | WS_CHILD | SS_RIGHT,
		670,
		120,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	eDesc = CreateWindowW(
		_T("Edit"),
		_T(""),
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_RIGHT,
		570,
		120,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	sDateDesc = CreateWindowW(
		_T("Static"),
		dDesc,
		WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
		250,
		80,
		300,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	commitButton = CreateWindowW(
		_T("Button"),
		_T("ثبت اطلاعات"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | BS_CENTER,
		650,
		160,
		120,
		30,
		hWnd,
		(HMENU)COMMIT_BUTTON,
		NULL,
		NULL
	);

	return 0;
}

int employee::searchWindow(HWND hWnd) {
	searchWindowDesc = CreateWindowW(
		_T("Static"),
		_T("جستوجو اطلاعات"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
		0,
		0,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);
	
	ssEmployee = CreateWindowW(
		_T("Static"),
		_T(":کارشناس"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,
		670,
		0,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);
	
	esEmployee = CreateWindowW(
		_T("Edit"),
		_T(""),
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_RIGHT,
		570,
		0,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);
	
	ssCostumer = CreateWindowW(
		_T("Static"),
		_T(":مشتری"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,
		670,
		40,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);
	
	esCostumer = CreateWindowW(
		_T("Edit"),
		_T(""),
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_RIGHT,
		570,
		40,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);
	
	ssFromDate = CreateWindowW(
		_T("Static"),
		_T(":از تاریخ"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,
		670,
		80,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);
	
	esFromDate = CreateWindowW(
		_T("Edit"),
		_T(""),
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_RIGHT,
		570,
		80,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	ssToDate = CreateWindowW(
		_T("Static"),
		_T(":تا تاریخ"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,
		450,
		80,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	esToDate = CreateWindowW(
		_T("Edit"),
		_T(""),
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_RIGHT,
		350,
		80,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);
	
	ssDesc = CreateWindowW(
		_T("Static"),
		_T(":توضیحات"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,
		670,
		120,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);
	
	esDesc = CreateWindowW(
		_T("Edit"),
		_T(""),
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_RIGHT,
		570,
		120,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);
	
	searchButton = CreateWindowW(
		_T("Button"),
		_T("جستوجو"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | BS_CENTER,
		650,
		160,
		120,
		30,
		hWnd,
		(HMENU)SEARCH_BUTTON,
		NULL,
		NULL
	);
	
	return 0;
}

int employee::editWindow(HWND hWnd) {
	editWindowDesc = CreateWindowW(
		_T("Static"),
		_T("تغییر اطلاعات"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
		0,
		0,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	sId = CreateWindowW(
		_T("Static"),
		_T(":ایدی"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,
		450,
		0,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	eId = CreateWindowW(
		_T("Edit"),
		_T(""),
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_RIGHT,
		350,
		0,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);
	
	seEmployee = CreateWindowW(
		_T("Static"),
		_T(":کارشناس"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,
		670,
		0,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);
	eeEmployee = CreateWindowW(
		_T("Edit"),
		_T(""),
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_RIGHT,
		570,
		0,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);
	seCostumer = CreateWindowW(
		_T("Static"),
		_T(":مشتری"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,
		670,
		40,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	eeCostumer = CreateWindowW(
		_T("Edit"),
		_T(""),
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_RIGHT,
		570,
		40,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);
	
	seDate = CreateWindowW(
		_T("Static"),
		_T(":تاریخ"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,
		670,
		80,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);
	
	eeDate = CreateWindowW(
		_T("Edit"),
		_T(""),
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_RIGHT,
		570,
		80,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);
	
	seDesc = CreateWindowW(
		_T("Static"),
		_T(":توضیحات"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,
		670,
		120,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);
	
	eeDesc = CreateWindowW(
		_T("Edit"),
		_T(""),
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_RIGHT,
		570,
		120,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	editButton = CreateWindowW(
		_T("Button"),
		_T("تغییر اطلاعات"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | BS_CENTER,
		650,
		160,
		120,
		30,
		hWnd,
		(HMENU)EDIT_BUTTON,
		NULL,
		NULL
	);
	return 0;
}

int employee::deleteWindow(HWND hWnd) {
	deleteWindowDesc = CreateWindowW(
		_T("Static"),
		_T("حذف اطلاعات"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
		0,
		0,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);
	
	sdId = CreateWindowW(
		_T("Static"),
		_T(":ایدی"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,
		670,
		0,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);
	
	edId = CreateWindowW(
		_T("Edit"),
		_T(""),
		WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT,
		570,
		0,
		100,
		30,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	deleteButton = CreateWindowW(
		_T("Button"),
		_T("حذف اطلاعات"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | BS_CENTER,
		650,
		160,
		120,
		30,
		hWnd,
		(HMENU)DELETE_BUTTON,
		NULL,
		NULL
	);

	return 0;
}

int employee::destroyMainWindow() {
	DestroyWindow(mainWindowDesc);
	DestroyWindow(sEmployee);
	DestroyWindow(sCostumer);
	DestroyWindow(sDate);
	DestroyWindow(sDesc);
	DestroyWindow(sDateDesc);
	DestroyWindow(eEmployee);
	DestroyWindow(eCostumer);
	DestroyWindow(eDate);
	DestroyWindow(eDesc);
	DestroyWindow(commitButton);

	return 0;
}

int employee::destroySearchWindow() {
	DestroyWindow(searchWindowDesc);
	DestroyWindow(ssEmployee);
	DestroyWindow(ssCostumer);
	DestroyWindow(ssFromDate);
	DestroyWindow(ssToDate);
	DestroyWindow(ssDesc);
	DestroyWindow(esEmployee);
	DestroyWindow(esCostumer);
	DestroyWindow(esFromDate);
	DestroyWindow(esToDate);
	DestroyWindow(esDesc);
	DestroyWindow(searchButton);

	return 0;
}

int employee::destroyEditWindow() {
	DestroyWindow(editWindowDesc);
	DestroyWindow(sId);
	DestroyWindow(seEmployee);
	DestroyWindow(seCostumer);
	DestroyWindow(seDate);
	DestroyWindow(seDesc);
	DestroyWindow(eId);
	DestroyWindow(eeEmployee);
	DestroyWindow(eeCostumer);
	DestroyWindow(eeDate);
	DestroyWindow(eeDesc);
	DestroyWindow(editButton);
	return 0;
}

int employee::destroyDeleteWindow() {
	DestroyWindow(deleteWindowDesc);
	DestroyWindow(sdId);
	DestroyWindow(edId);
	DestroyWindow(deleteButton);
	return 0;
}

int employee::onNextPageButtonPressed(HWND hWnd) {
	switch (page)
	{
	case 0:
		destroyMainWindow();
		searchWindow(hWnd);
		EnableWindow(lastPageButton, TRUE);
		break;
	case 1:
		destroySearchWindow();
		editWindow(hWnd);
		break;
	case 2:
		destroyEditWindow();
		deleteWindow(hWnd);
		EnableWindow(nextPageButton, FALSE);
		break;
	}

	page++;

	return 0;
}

int employee::onLastPageButtonPressed(HWND hWnd) {
	switch (page)
	{
	case 1:
		destroySearchWindow();
		mainWindow(hWnd);
		EnableWindow(lastPageButton, FALSE);
		break;
	case 2:
		destroyEditWindow();
		searchWindow(hWnd);
		break;
	case 3:
		destroyDeleteWindow();
		editWindow(hWnd);
		EnableWindow(nextPageButton, TRUE);
		break;
	}

	page--;

	return 0;
}

int employee::onCommitButtonPressed(HWND hWnd) {

	bufferLength1 = GetWindowTextLengthW(eEmployee);
	bufferLength2 = GetWindowTextLengthW(eCostumer);
	bufferLength3 = GetWindowTextLengthW(eDate);
	bufferLength4 = GetWindowTextLengthW(eDesc);
	
	if (
		bufferLength1 < 5 ||
		bufferLength2 < 5 ||
		bufferLength3 != 10
		) {
		MessageBoxW(NULL, L"لطفا اطلاعات را به صورت صحبح وارد کنید", L"Error", MB_OK);
		return 0;
	}

	employeeBuffer = new wchar_t[bufferLength1 + 1];
	costumerBuffer = new wchar_t[bufferLength2 + 1];
	dateBuffer = new wchar_t[bufferLength3 + 1];

	GetWindowTextW(eEmployee, employeeBuffer, bufferLength1 + 1);
	GetWindowTextW(eCostumer, costumerBuffer, bufferLength2 + 1);
	GetWindowTextW(eDate, dateBuffer, bufferLength3 + 1);
	if (bufferLength4 != 0) {
		descBuffer = new wchar_t[bufferLength4 + 1];
		GetWindowTextW(eDesc, descBuffer, bufferLength4 + 1);
		wBuffer = L"employee: " + std::wstring(employeeBuffer) + L"\r\n";
		wBuffer += L"costumer: " + std::wstring(costumerBuffer) + L"\r\n";
		wBuffer += L"date: " + std::wstring(dateBuffer) + L"\r\n";
		wBuffer += L"desc: " + std::wstring(descBuffer) + L"\r\n";
	}
	else {
		wBuffer = L"employee: " + std::wstring(employeeBuffer) + L"\r\n";
		wBuffer += L"costumer: " + std::wstring(costumerBuffer) + L"\r\n";
		wBuffer += L"date: " + std::wstring(dateBuffer) + L"\r\n";
	}

	file.open("mian.log", std::ios_base::binary | std::ios_base::app);
	
	if (file.is_open()) {
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		buffer = converter.to_bytes(wBuffer);
		file << buffer;
	}
	else {
		MessageBox(NULL, "Error occurred on opening log, code: 143", "Error", MB_OK | MB_ICONERROR);
	}
	file.close();

	{
		eSqlite3 esql;
		if (bufferLength4 == 0) {
			esql.writeToDb(
				wchartToString(employeeBuffer),
				wchartToString(costumerBuffer),
				wchartToString(dateBuffer)
			);
		}
		else {
			esql.writeToDb(
				wchartToString(employeeBuffer),
				wchartToString(costumerBuffer),
				wchartToString(dateBuffer),
				wchartToString(descBuffer)
			);
		}
	}

	delete[] employeeBuffer;
	delete[] costumerBuffer;
	delete[] dateBuffer;
	if (bufferLength4 != 0) {
		delete[] descBuffer;
	}

	writeFileToBuffer();
	return 0;
}

int employee::onSearchButtonPressed(HWND hWnd) {

	bufferLength1 = GetWindowTextLengthW(esEmployee);
	bufferLength2 = GetWindowTextLengthW(esCostumer);
	bufferLength3 = GetWindowTextLengthW(esFromDate);
	bufferLength4 = GetWindowTextLengthW(esToDate);
	bufferLength5 = GetWindowTextLengthW(esDesc);

	employeeBuffer = new wchar_t[bufferLength1 + 1];
	costumerBuffer = new wchar_t[bufferLength2 + 1];
	fromDateBuffer = new wchar_t[bufferLength3 + 1];
	toDateBuffer = new wchar_t[bufferLength4 + 1];
	descBuffer = new wchar_t[bufferLength5 + 1];
	if (
		bufferLength1 == 0 &&
		bufferLength2 == 0 &&
		bufferLength3 == 0 &&
		bufferLength4 == 0 &&
		bufferLength5 == 0
		) {
		MessageBoxW(NULL, L"لطفا اطلاعات را به صورت صحبح وارد کنید", L"Error", MB_OK);
		return 0;
	}
	else {
		if (bufferLength1 != 0) {
			GetWindowTextW(esEmployee, employeeBuffer, bufferLength1 + 1);
		}
		if (bufferLength2 != 0) {
			GetWindowTextW(esCostumer, costumerBuffer, bufferLength2 + 1);
		}
		if (bufferLength3 != 0) {
			GetWindowTextW(esFromDate, fromDateBuffer, bufferLength3 + 1);
		}
		if (bufferLength4 != 0) {
			GetWindowTextW(esToDate, toDateBuffer, bufferLength4 + 1);
		}
		if (bufferLength5 != 0) {
			GetWindowTextW(esDesc, descBuffer, bufferLength5 + 1);
		}

		{
			eSqlite3 esql;
			esql.searchDb(
				bufferLength1,
				bufferLength2,
				bufferLength3,
				bufferLength4,
				bufferLength5,
				(bufferLength1 != 0) ? wchartToString(employeeBuffer) : "",
				(bufferLength2 != 0) ? wchartToString(costumerBuffer) : "",
				(bufferLength3 != 0) ? wchartToString(fromDateBuffer) : "",
				(bufferLength4 != 0) ? wchartToString(toDateBuffer) : "",
				(bufferLength5 != 0) ? wchartToString(descBuffer) : ""
			);
		}

		if (bufferLength1 != 0) {
			delete[] employeeBuffer;
		}
		if (bufferLength2 != 0) {
			delete[] costumerBuffer;
		}
		if (bufferLength3 != 0) {
			delete[] fromDateBuffer;
		}
		if (bufferLength4 != 0) {
			delete[] toDateBuffer;
		}
		if (bufferLength5 != 0) {
			delete[] descBuffer;
		}

		employeeBuffer = nullptr;
		costumerBuffer = nullptr;
		fromDateBuffer = nullptr;
		toDateBuffer = nullptr;
		descBuffer = nullptr;

		writeFileToBuffer();
	}
	return 0;
}

int employee::onEditButtonPressed(HWND hWnd) {
	bufferLength1 = GetWindowTextLengthW(eeEmployee);
	bufferLength2 = GetWindowTextLengthW(eeCostumer);
	bufferLength3 = GetWindowTextLengthW(eeDate);
	bufferLength4 = GetWindowTextLengthW(eeDesc);
	bufferLength5 = GetWindowTextLengthW(eId);

	if (bufferLength5 != 0) {
		if (
			bufferLength1 != 0 ||
			bufferLength2 != 0 ||
			bufferLength3 != 0 ||
			bufferLength4 != 0
		) {
			employeeBuffer = new wchar_t[bufferLength1 + 1];
			costumerBuffer = new wchar_t[bufferLength2 + 1];
			fromDateBuffer = new wchar_t[bufferLength3 + 1];
			descBuffer = new wchar_t[bufferLength4 + 1];
			idBuffer = new wchar_t[bufferLength5 + 1];

			if (
				bufferLength1 != 0 &&
				bufferLength2 == 0 &&
				bufferLength3 == 0 &&
				bufferLength4 == 0
			) {
				GetWindowTextW(eeEmployee, employeeBuffer, bufferLength1 + 1);
				{
					eSqlite3 esql;
					esql.updateDb(
						wchartToString(idBuffer),
						"employee",
						wchartToString(employeeBuffer)
					);
				}
			}
			else if (
				bufferLength1 == 0 &&
				bufferLength2 != 0 &&
				bufferLength3 == 0 &&
				bufferLength4 == 0
			) {
				GetWindowTextW(eeCostumer, costumerBuffer, bufferLength2 + 1);
				{
					eSqlite3 esql;
					esql.updateDb(
						wchartToString(idBuffer),
						"costumer",
						wchartToString(costumerBuffer)
					);
				}
			}
			else if (
				bufferLength1 == 0 &&
				bufferLength2 == 0 &&
				bufferLength3 != 0 &&
				bufferLength4 == 0
				) {
				GetWindowTextW(eeDate, dateBuffer, bufferLength3 + 1);
				{
					eSqlite3 esql;
					esql.updateDb(
						wchartToString(idBuffer),
						"date",
						wchartToString(dateBuffer)
					);
				}
			}
			else if (
				bufferLength1 == 0 &&
				bufferLength2 == 0 &&
				bufferLength3 == 0 &&
				bufferLength4 != 0
			) {
				GetWindowTextW(eeDesc, descBuffer, bufferLength4 + 1);
				{
					eSqlite3 esql;
					esql.updateDb(
						wchartToString(idBuffer),
						"description",
						wchartToString(descBuffer)
					);
				}
			}
			else {
				MessageBoxW(NULL, L"لطفا اطلاعات را به صورت صحبح وارد کنید", L"Error", MB_OK);
				return 0;
			}
		}
		else {
			MessageBoxW(NULL, L"لطفا اطلاعات را به صورت صحبح وارد کنید", L"Error", MB_OK);
			return 0;
		}
	}
	else {
		MessageBoxW(NULL, L"لطفا اطلاعات را به صورت صحبح وارد کنید", L"Error", MB_OK);
		return 0;
	}

	if (bufferLength1 != 0) {
		delete[] employeeBuffer;
	}
	if (bufferLength2 != 0) {
		delete[] costumerBuffer;
	}
	if (bufferLength3 != 0) {
		delete[] fromDateBuffer;
	}
	if (bufferLength4 != 0) {
		delete[] toDateBuffer;
	}
	if (bufferLength5 != 0) {
		delete[] descBuffer;
	}

	employeeBuffer = nullptr;
	costumerBuffer = nullptr;
	dateBuffer = nullptr;
	descBuffer = nullptr;
	idBuffer = nullptr;

	file.open("mian.log", std::ios_base::app);
	if (file.is_open()) {
		wBuffer = L"اطلاعات با موفقیت تغییر داده شد";
		wBuffer += L"\r\n";
		std::wstring_convert<std::codecvt_utf16<wchar_t>> converter;
		buffer = converter.to_bytes(wBuffer);
		file << buffer;
	}
	else {
		MessageBoxW(NULL, L"خطا در باز کردن فایل لاگ", L"Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	file.close();
	writeFileToBuffer();

	return 0;
}

int employee::writeFileToBuffer() {
	file.open("mian.log", std::ios_base::in);
	if (file.is_open()) {
		std::ostringstream oss;
		oss << file.rdbuf();
		buffer = oss.str();
		wBuffer = stringToWString(buffer);
		std::wstring_convert<std::codecvt_utf16<wchar_t>> converter;
		buffer = converter.to_bytes(wBuffer);
		SetWindowTextW(sLogBox, wBuffer.c_str());
	}
	else {
		MessageBox(NULL, "Error occurred on writing log to buffer", "Error", MB_OK | MB_ICONERROR);
	}
	file.close();
	return 0;
}

int employee::onDeleteButtonPressed(HWND hWnd) {
	bufferLength1 = GetWindowTextLengthW(edId);
	if (bufferLength1 != 0) {
		idBuffer = new wchar_t[bufferLength1 + 1];
		GetWindowTextW(edId, idBuffer, bufferLength1 + 1);
		{
			eSqlite3 esql;
			esql.dbDeleteInfo(wchartToString(idBuffer));
		}
		file.open("mian.log", std::ios_base::app);
		if (file.is_open()) {
			buffer = "Deleted " + wchartToString(idBuffer) + "from database \r\n";
			file << buffer;
		}
		else {
			MessageBoxW(NULL, L"خطا در باز کردن فایل لاگ code: 161", L"Error", MB_OK | MB_ICONERROR);
		}
		file.close();
	}
	else {
		MessageBoxW(NULL, L"اطلاعات را به صورت صحبح پر کنید", L"Error", MB_OK | MB_ICONERROR);
	}
	writeFileToBuffer();

	return 0;
}

std::string employee::wchartToString(wchar_t* wstr) {
	std::wstring wstringObj(wstr);
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::string narrowString = converter.to_bytes(wstringObj);
	return narrowString;
}

std::wstring employee::stringToWString(std::string inString) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(inString);
}

std::wstring eSqlite3::stringToWString(std::string inString) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(inString);
}

LPCWSTR employee::stringToWchar(const std::string& buffer) {
	int size = MultiByteToWideChar(CP_UTF8, 0, buffer.c_str(), -1, nullptr, 0);
	wchar_t* wcharBuffer = new wchar_t[size];
	MultiByteToWideChar(CP_UTF8, 0, buffer.c_str(), -1, wcharBuffer, size);
	return wcharBuffer;
}
