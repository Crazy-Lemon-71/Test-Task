/*
В данной программе выбор задания и навигация по меню осуществляются с помощью конструкции switch-case,
которая заключена в бесконечный цикл while. Благодаря этой конструкции меню выводится снова и снова на каждой итерации цикла,
что позволяет пользователю выбрать необходимый функционал или завершить работу программы путём ввода номера с клавиатуры.

Во всех заданиях предусмотрена проверка корректности введённых данных,
включая выбор неправильного пункта меню или ввод некорректного идентификатора.
В случае ошибки программа незамедлительно сообщит об этом.

Также в заданиях проверяется повторное назначение одних и тех же данных.
В случае, если программа обнаружит, что статус или другое поле уже имеет данное значение,
она выдаст об этом соответствующее сообщение.

Данная программа написана на языке программирования C++
*/

#include <iostream>
#include <list>
#include <ctime>
#include <iomanip>

using namespace std;


// ЗАДАНИЕ 1


class Document {
private:
	int Id;
	string Title;
	string Status;

public:
	int getId() const {
		return Id;
	}

	string getTitle() const {
		return Title;
	}

	string getStatus() const {
		return Status;
	}

	void setStatus(const string& newStatus) {
		Status = newStatus;
	}

	void outputInformation() {
		cout << "\nID: " << Id << ", Title: " << Title << ", Status: " << Status;
	}

	Document(int Id, const string& Title, const string& Status) : Id(Id), Title(Title), Status(Status) {}
};

// Вывод информации о всех документах

void OutputInformationAboutAllDocuments(list<Document> documents) {
	cout << "\nСписок всех документов:";
	for (auto& document : documents) {
		document.outputInformation();
	}
	cout << endl;
}

// Вывод информации о всех документах с определённым статусом

void OutputInformationAboutSomeDocuments(list<Document> documents) {
	int numberStatus;
	string status;

	// Выбор желаемого статуса
	while (true) {
		cout << "\nВведите номер статуса для фильтрации (1 - Создан, 2 - На согласовании, 3 - Согласован): ";
		cin >> numberStatus;

		if (numberStatus == 1) {
			status = "Создан";
			break;
		}
		else if (numberStatus == 2) {
			status = "На согласовании";
			break;
		}
		else if (numberStatus == 3) {
			status = "Согласован";
			break;
		}
		else {
			cout << "Введите корректный номер!\n";
		}
	}

	cout << "\nСписок отфильтрованных документов:";
	for (auto& document : documents) {
		if (document.getStatus() == status) {
			document.outputInformation();
		}
	}
	cout << endl;
}

// Изменение статуса требуемого документа

void ChangeStatusDocuments(list<Document>& documents) {
	int id;
	int numberStatus;
	string newStatus;

	bool found = false;

	cout << "\nВведите ID документа для которого вы хотите изменить статус: ";
	cin >> id;

	// Поиск документа по введённому идентификатору
	for (auto& document : documents) {
		if (document.getId() == id) {
			found = true;

			// Выбор желаемого статуса
			while (true) {
				cout << "\nВведите номер желаемого статуса (1 - Создан, 2 - На согласовании, 3 - Согласован): ";
				cin >> numberStatus;

				if (numberStatus == 1) {
					newStatus = "Создан";
					break;
				}
				else if (numberStatus == 2) {
					newStatus = "На согласовании";
					break;
				}
				else if (numberStatus == 3) {
					newStatus = "Согласован";
					break;
				}
				else {
					cout << "Введите корректный номер!\n";
				}
			}

			if (document.getStatus() != newStatus) {
				document.setStatus(newStatus);
				cout << "\nСтатус документа был успешно измнён!\n";
				break;
			}
			else {
				cout << "\nТакой статус документа уже был установлен!\n";
				break;
			}
		}
	}

	// Проверка наличия документа с введённым идентификатором
	if (!found) {
		cout << "\nДокумент с требуемым ID не найден!\n";
	}
}

void Task1() {
	cout << "\nЗадание 1";

	// Создание экземпляров класса
	list<Document> documents = {
	Document(1, "Документ 1", "Создан"),
	Document(2, "Документ 2", "На согласовании"),
	Document(3, "Документ 3", "Согласован"),
	Document(4, "Документ 4", "Создан"),
	Document(5, "Документ 5", "На согласовании") };

	while (true) {
		int choice;

		cout << "\n1. Вывод информации о всех документах" << "\n2. Вывод информации о всех документах с определённым статусом"
			<< "\n3. Изменение статуса требуемого документа" << "\n4. Выход" << "\n> ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			OutputInformationAboutAllDocuments(documents);
			break;
		case 2:
			OutputInformationAboutSomeDocuments(documents);
			break;
		case 3:
			ChangeStatusDocuments(documents);
			break;
		case 4:
			return;
		default:
			cout << "Введите корректный номер!\n";
			break;
		}
	}
}


// ЗАДАНИЕ 2


class ApprovalRequest {
private:
	int Id;
	string DocumentTitle;
	bool IsApproved;

public:
	int getId() const {
		return Id;
	}

	string getDocumentTitle() const {
		return DocumentTitle;
	}

	bool getIsApproved() const {
		return IsApproved;
	}

	void outputInformation() {
		cout << "\nID: " << Id << ", DocumentTitle: " << DocumentTitle << ", IsApproved: " << IsApproved;
	}

	void Approve() {
		IsApproved = true;
	}

	void Reject() {
		IsApproved = false;

		// Проверка, заканчивается ли название на "(Отклонено)"
		if ((DocumentTitle.size() < 11) || (DocumentTitle.substr(DocumentTitle.size() - 11) != "(Отклонено)")) {
			DocumentTitle += " (Отклонено)";
		}
	}

	ApprovalRequest(int Id, const string& DocumentTitle) : Id(Id), DocumentTitle(DocumentTitle), IsApproved(false) {}
};

// Вывод информации о всех заявках

void OutputInformationAboutAllApprovalRequests(list<ApprovalRequest> approvalRequests) {
	cout << "\nСписок всех заявок:";
	for (auto& approvalRequest : approvalRequests) {
		approvalRequest.outputInformation();
	}
	cout << endl;
}

// Изменение статуса требуемой заявки

void ChangeStatusApprovalRequests(list<ApprovalRequest>& approvalRequests) {
	int id;
	int numberStatus;

	bool found = false;

	cout << "\nВведите ID заявки для которой вы хотите изменить статус: ";
	cin >> id;

	// Поиск заявки по введённому идентификатору
	for (auto& approvalRequest : approvalRequests) {
		if (approvalRequest.getId() == id) {
			found = true;

			// Выбор желаемого статуса
			while (true) {
				cout << "\nВведите номер желаемого статуса (1 - True, 2 - False): ";
				cin >> numberStatus;

				if (numberStatus == 1) {
					if ((approvalRequest.getIsApproved() == false) && (approvalRequest.getDocumentTitle().size() > 11)
						&& (approvalRequest.getDocumentTitle().substr(approvalRequest.getDocumentTitle().size() - 11) == "(Отклонено)")) {
						cout << "\nДанная заявка уже была отклонена!\n";
						break;
					}
					else if (approvalRequest.getIsApproved() == true) {
						cout << "\nТакой статус заявки уже был установлен ранее!\n";
						break;
					}
					else {
						approvalRequest.Approve();
						cout << "\nСтатус заявки был успешно измнён!\n";
						break;
					}
				}
				else if (numberStatus == 2) {
					if ((approvalRequest.getIsApproved() == false) && (approvalRequest.getDocumentTitle().size() > 11)
						&& (approvalRequest.getDocumentTitle().substr(approvalRequest.getDocumentTitle().size() - 11) == "(Отклонено)")) {
						cout << "\nТакой статус заявки уже был установлен ранее!\n";
						break;
					}
					else if (approvalRequest.getIsApproved() == true) {
						cout << "\nДанная заявка уже была одобрена!\n";
						break;
					}
					else {
						approvalRequest.Reject();
						cout << "\nСтатус заявки был успешно измнён!\n";
						break;
					}
				}
				else {
					cout << "Введите корректный номер!\n";
				}
			}
		}
	}

	// Проверка наличия заявки с введённым идентификатором
	if (!found) {
		cout << "\nЗаявка с требуемым ID не найдена!\n";
	}
}

void Task2() {
	cout << "\nЗадание 2";

	// Создание экземпляров класса
	list<ApprovalRequest> approvalRequests = {
	ApprovalRequest(1, "Документ 1"),
	ApprovalRequest(2, "Документ 2"),
	ApprovalRequest(3, "Документ 3"),
	ApprovalRequest(4, "Документ 4"),
	ApprovalRequest(5, "Документ 5") };

	while (true) {
		int choice;

		cout << "\n1. Вывод информации о всех заявках" << "\n2. Изменение статуса требуемой заявки" << "\n3. Выход" << "\n> ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			OutputInformationAboutAllApprovalRequests(approvalRequests);
			break;
		case 2:
			ChangeStatusApprovalRequests(approvalRequests);
			break;
		case 3:
			return;
		default:
			cout << "Введите корректный номер!\n";
			break;
		}
	}
}


// ЗАДАНИЕ 3


void CountingTheNumberDocuments(list<Document> documents) {
	int numberDocumentsCreated = 0;
	int numberDocumentsApproved = 0;
	int numberDocumentsAgreed = 0;
	int numberDocumentsRejected = 0;

	cout << "\nПодсчитанное количество документов:";
	for (auto& document : documents) {
		if (document.getStatus() == "Создан") {
			numberDocumentsCreated += 1;
		}
		else if (document.getStatus() == "На согласовании") {
			numberDocumentsApproved += 1;
		}
		else if (document.getStatus() == "Согласован") {
			numberDocumentsAgreed += 1;
		}
		else if (document.getStatus() == "Отклонен") {
			numberDocumentsRejected += 1;
		}
		else {
			continue;
		}
	}
	
	cout << "\nСоздан: " << numberDocumentsCreated
		<< "\nНа согласовании: " << numberDocumentsApproved
		<< "\nСогласован: " << numberDocumentsAgreed
		<< "\nОтклонен: " << numberDocumentsRejected << endl;
}

void Task3() {
	cout << "\nЗадание 3";

	// Создание экземпляров класса
	list<Document> documents = {
	Document(1, "Документ 1", "Создан"),
	Document(2, "Документ 2", "На согласовании"),
	Document(3, "Документ 3", "Согласован"),
	Document(4, "Документ 4", "Создан"),
	Document(5, "Документ 5", "На согласовании"),
	Document(6, "Документ 6", "Создан"),
	Document(7, "Документ 7", "На согласовании"),
	Document(8, "Документ 8", "Согласован"),
	Document(9, "Документ 9", "На согласовании"),
	Document(10, "Документ 10", "Отклонен") };

	while (true) {
		int choice;

		cout << "\n1. Вывод информации о всех документах" << "\n2. Подсчёт количества документов по статусам" << "\n3. Выход" << "\n> ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			OutputInformationAboutAllDocuments(documents);
			break;
		case 2:
			CountingTheNumberDocuments(documents);
			break;
		case 3:
			return;
		default:
			cout << "Введите корректный номер!\n";
			break;
		}
	}
}


// ЗАДАНИЕ 4


class DocumentWithDate {
private:
	int Id;
	string Title;
	tm CreatedDate;

public:
	int getId() const {
		return Id;
	}

	string getTitle() const {
		return Title;
	}
	
	tm getCreatedDate() const {
		return CreatedDate;
	}

	void outputInformation() {
		cout << "\nID: " << Id << ", Title: " << Title << ", CreatedDate: " << put_time(&CreatedDate, "%d.%m.%Y");
	}

	DocumentWithDate(int Id, const string& Title, const tm& CreatedDate) : Id(Id), Title(Title), CreatedDate(CreatedDate) {}
};

// Преобразование даты в цифровой формат

tm createDate(int day, int month, int year) {
	tm date = {};
	date.tm_mday = day;
	date.tm_mon = month - 1;		// Месяцы от 0 до 11
	date.tm_year = year - 1900;		// Год относительно 1900
	return date;
}

// Ввод даты с клавиатуры

tm inputDate(string prompt) {
	int day, month, year;
	cout << prompt;
	cin >> day >> month >> year;
	return createDate(day, month, year);
}

// Фильтрация документов по заданным параметрам

list<DocumentWithDate> filterDocumentsByDate(list<DocumentWithDate> documents, tm startDate, tm endDate) {
	list<DocumentWithDate> filteredDocuments;
	for (auto& document : documents) {
		tm documentDate = document.getCreatedDate();
		time_t documentTime = mktime(&documentDate);

		tm startDateCopy = startDate;
		tm endDateCopy = endDate;
		time_t startTime = mktime(&startDateCopy);
		time_t endTime = mktime(&endDateCopy);

		if (documentTime >= startTime && documentTime <= endTime) {
			filteredDocuments.push_back(document);
		}
	}
	return filteredDocuments;
}

// Вывод информации о всех документах

void OutputInformationAboutAllDocumentsWithDate(list<DocumentWithDate> documents) {
	cout << "\nСписок всех документов:";
	for (auto& document : documents) {
		document.outputInformation();
	}
	cout << endl;
}

// Вывод информации о документах за определённый период

void OutputInformationAboutSomeDocumentsWithDate(list<DocumentWithDate> documents) {
	tm startDate = inputDate("\nВведите начальную дату фильтрации (DD MM YYYY): ");
	tm endDate = inputDate("Введите конечную дату фильтрации (DD MM YYYY): ");

	list<DocumentWithDate> filteredDocuments = filterDocumentsByDate(documents, startDate, endDate);

	if (filteredDocuments.empty()) {
		cout << "\nДокументов, соответствующих заданным параметрам, не найдено!\n";
	}
	else {
		cout << "\nСписок отфильтрованных документов:";
		for (auto& document : filteredDocuments) {
			document.outputInformation();
		}
		cout << endl;
	}
}

void Task4() {
	cout << "\nЗадание 4";

	// Создание экземпляров класса
	list<DocumentWithDate> documents = {
	DocumentWithDate(1, "Документ 1", createDate(3, 1, 2020)),
	DocumentWithDate(2, "Документ 2", createDate(6, 2, 2020)),
	DocumentWithDate(3, "Документ 3", createDate(9, 3, 2021)),
	DocumentWithDate(4, "Документ 4", createDate(12, 4, 2021)),
	DocumentWithDate(5, "Документ 5", createDate(15, 5, 2022)),
	DocumentWithDate(6, "Документ 6", createDate(18, 6, 2022)),
	DocumentWithDate(7, "Документ 7", createDate(21, 7, 2023)),
	DocumentWithDate(8, "Документ 8", createDate(24, 8, 2023)),
	DocumentWithDate(9, "Документ 9", createDate(27, 9, 2024)),
	DocumentWithDate(10, "Документ 10", createDate(30, 10, 2024)) };

	while (true) {
		int choice;

		cout << "\n1. Вывод информации о всех документах"
			<< "\n2. Вывод информации о документах за определённый период"
			<< "\n3. Выход" << "\n> ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			OutputInformationAboutAllDocumentsWithDate(documents);
			break;
		case 2:
			OutputInformationAboutSomeDocumentsWithDate(documents);
			break;
		case 3:
			return;
		default:
			cout << "Введите корректный номер!\n";
			break;
		}
	}
}


// ЗАДАНИЕ 5


class TravelRequest {
private:
	int Id;
	string EmployeeName;
	string Destination;
	bool IsApproved;

public:
	int getId() const {
		return Id;
	}

	string getEmployeeName() const {
		return EmployeeName;
	}

	string getDestination() const {
		return Destination;
	}

	bool getIsApproved() const {
		return IsApproved;
	}

	void outputInformation() {
		cout << "\nID: " << Id << ", EmployeeName: " << EmployeeName
			<< ", Destination: " << Destination << ", IsApproved: " << IsApproved;
	}

	void Approve() {
		IsApproved = true;
	}

	void Reject() {
		IsApproved = false;
	}

	TravelRequest(int Id, const string& EmployeeName, const string& Destination)
		: Id(Id), EmployeeName(EmployeeName), Destination(Destination), IsApproved(false) {}
};

// Вывод информации о всех заявках

void OutputInformationAboutAllTravelRequests(list<TravelRequest> travelRequests) {
	cout << "\nСписок всех заявок:";
	for (auto& travelRequest : travelRequests) {
		travelRequest.outputInformation();
	}
	cout << endl;
}

// Изменение статуса требуемой заявки

void ChangeStatusTravelRequests(list<TravelRequest>& travelRequests) {
	int id;
	int numberStatus;

	bool found = false;

	cout << "\nВведите ID заявки для которой вы хотите изменить статус: ";
	cin >> id;

	// Поиск заявки по введённому идентификатору
	for (auto& travelRequest : travelRequests) {
		if (travelRequest.getId() == id) {
			found = true;

			// Выбор желаемого статуса
			while (true) {
				cout << "\nВведите номер желаемого статуса (1 - True, 2 - False): ";
				cin >> numberStatus;

				if (numberStatus == 1) {
					if (travelRequest.getIsApproved() == true) {
						cout << "\nТакой статус заявки уже был установлен ранее!\n";
						break;
					}
					else {
						travelRequest.Approve();
						cout << "\nСтатус заявки был успешно измнён!\n";
						break;
					}
				}
				else if (numberStatus == 2) {
					travelRequest.Reject();
					cout << "\nСтатус заявки был успешно измнён!\n";
					break;
				}
				else {
					cout << "Введите корректный номер!\n";
				}
			}
		}
	}

	// Проверка наличия заявки с введённым идентификатором
	if (!found) {
		cout << "\nЗаявка с требуемым ID не найдена!\n";
	}
}

void Task5() {
	cout << "\nЗадание 5";

	// Создание экземпляров класса
	list<TravelRequest> travelRequests = {
	TravelRequest(1, "Сотрудник 1", "Пункт назначения 1"),
	TravelRequest(2, "Сотрудник 2", "Пункт назначения 2"),
	TravelRequest(3, "Сотрудник 3", "Пункт назначения 3"),
	TravelRequest(4, "Сотрудник 4", "Пункт назначения 4"),
	TravelRequest(5, "Сотрудник 5", "Пункт назначения 5")};

	while (true) {
		int choice;

		cout << "\n1. Вывод информации о всех заявках" << "\n2. Изменение статуса требуемой заявки" << "\n3. Выход" << "\n> ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			OutputInformationAboutAllTravelRequests(travelRequests);
			break;
		case 2:
			ChangeStatusTravelRequests(travelRequests);
			break;
		case 3:
			return;
		default:
			cout << "Введите корректный номер!\n";
			break;
		}
	}
}

int main() {
	setlocale(LC_ALL, "Russian");

	while (true) {
		int choice;

		cout << "\n1. Задание 1" << "\n2. Задание 2" << "\n3. Задание 3"
			<< "\n4. Задание 4" << "\n5. Задание 5" << "\n6. Выход" << "\n> ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			Task1();
			break;
		case 2:
			Task2();
			break;
		case 3:
			Task3();
			break;
		case 4:
			Task4();
			break;
		case 5:
			Task5();
			break;
		case 6:
			return 0;
		default:
			cout << "Введите корректный номер!\n";
			break;
		}
	}
}