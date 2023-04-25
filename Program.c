#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning(disable:4996)

#define MAX_READ 1024

typedef struct {
	char id[6];
	char name[31];
	char gender;
	char contactNumber[11];
	int isDeleted;
} Member;

typedef struct {
	char sales_order_id[10];
	char item_code[10];
	int quantity_ordered;
	double price;
	char member_id[10];
} SalesRecord;

void addMember();
void displayAllMember();
void searchMember();
void updateMember();
void deleteMember();
void compactMemberFile();

void load_sales_records(SalesRecord* sales_records, int* num_records);
void save_sales_records(SalesRecord* sales_records, int num_records);
void add_sales_record(SalesRecord* sales_records, int* num_records);
void search_sales_record(SalesRecord* sales_records, int num_records);
void modify_sales_record(SalesRecord* sales_records, int num_records);
void display_sales_records(SalesRecord* sales_records, int num_records);
void sales_summary_by_item_code(SalesRecord* sales_records, int num_records);
void delete_sales_record(SalesRecord* sales_records, int* num_records);

int main()
{
	char command[3];
	SalesRecord sales_records[MAX_READ];
	int num_records = 0;

	load_sales_records(sales_records, &num_records);
	do {
		printf(" ____  ____ _________   ____   ____  _____      _______ ____  ____  _______ _________ _________ ____    ____ \n");
		printf("|_  _||_  _|_   ___  |.'    \\.|_   \\|_   _|    /  ___  |_  _||_  _|/  ___  |  _   _  |_   ___  |_   \\  /   _|\n");
		printf("  \\ \\  / /   | |_  \\_|  .--.  \\ |   \\ | |     |  (__ \\_| \\ \\  / / |  (__ \\_|_/ | | \\_| | |_  \\_| |   \\/   | \n");
		printf("   > \\' <    |  _|  _| |    | | | |\\ \\| |      '.___\\-.   \\ \\/ /   '.___\\-.    | |     |  _|  _  | |\\  /| |\n");
		printf(" _/ /'\\\\ \\_ _| |___/ |  \\--'  /_| |_\\   |_    |\\\\____) |  _|  |_  |\\\\____) |  _| |_   _| |___/ |_| |_\\/_| |_ \n");
		printf("|____||____|_________|\\.____.'|_____|\\____|   |_______.' |______| |_______.' |_____| |_________|_____||_____|\n");
		printf("");
		printf("\n                                                      Menu\n");
		printf("=============================================================================================================\n");
		printf("\nMember Module\n");
		printf("=============\n");
		printf("M1 - Add New Member\n");
		printf("M2 - Display All Members\n");
		printf("M3 - Search Member\n");
		printf("M4 - Update Member\n");
		printf("M5 - Delete Member\n");
		printf("   - Delete Member will only marked the targeted member as deleted in the binary file.\n");
		printf("   - It does not remove the targeted member from the binary file.\n");
		printf("M6 - Compact Member File\n");
		printf("   - Compact Member File will remove member(s) that are marked as deleted in the binary file.\n");
		printf("   - Please execute this command wisely.\n");
		printf("\nSales Information Module\n");
		printf("========================\n");
		printf("S1 - Add a new record\n");
		printf("S2 - Search for a record\n");
		printf("S3 - Modify a record\n");
		printf("S4 - Display all records\n");
		printf("S5 - Display total sales of item\n");
		printf("S6 - Delete a record\n");

		printf("\nCommand (XX to exit) > ");
		rewind(stdin);
		scanf("%s", &command);

		switch (toupper(command[0]))
		{
		case 'M':
			switch (command[1])
			{
			case '1':
				addMember();
				system("pause");
				system("cls");
				break;

			case '2':
				displayAllMember();
				system("pause");
				system("cls");
				break;

			case '3':
				searchMember();
				system("pause");
				system("cls");
				break;

			case '4':
				updateMember();
				system("pause");
				system("cls");
				break;

			case '5':
				deleteMember();
				system("pause");
				system("cls");
				break;

			case '6':
				compactMemberFile();
				system("pause");
				system("cls");
				break;
			}
			break;

		case 'S':

			switch (command[1])
			{
			case '1':
				add_sales_record(sales_records, &num_records);
				system("pause");
				system("cls");
				break;

			case '2':
				search_sales_record(sales_records, num_records);
				system("pause");
				system("cls");
				break;
			case '3':
				modify_sales_record(sales_records, num_records);
				system("pause");
				system("cls");
				break;

			case '4':
				display_sales_records(sales_records, num_records);
				system("pause");
				system("cls");
				break;

			case '5':
				sales_summary_by_item_code(sales_records, num_records);
				system("pause");
				system("cls");
				break;

			case '6':
				delete_sales_record(sales_records, &num_records);
				system("pause");
				system("cls");
				break;
			}
			break;
		}
	} while (strcmp(command, "XX") != 0);
	save_sales_records(sales_records, num_records);
	printf("\nSee you again!\n");
}

/// <summary>
/// Append Member into the member.dat binary file.
/// </summary>
void addMember() {
	FILE* fp = fopen("member.dat", "ab");
	if (fp == NULL)
	{
		printf("Unable to locate the required files, please ensure this program have write/read permission.\n");
		exit(-1);
	}

	Member member = { "", "", "", "", 1 };
	int count = 1;

	printf("\n\n");
	printf("%-20s %s: %d\n", "Add New Member", "Count", count);
	printf("=============================\n");

	printf("%-48s", "Please enter member id (XXX to stop): ");
	rewind(stdin);
	scanf("%s", &member.id);

	while (strcmp(member.id, "XXX") != 0) {
		printf("%-48s", "Please enter member name: ");
		rewind(stdin);
		gets(member.name);

		printf("%-48s", "Please enter member gender (M=Male, F=Female): ");
		rewind(stdin);
		scanf("%c", &member.gender);

		printf("%-47s +60", "Please enter member contact number: ");
		rewind(stdin);
		gets(member.contactNumber);

		fwrite(&member, sizeof(member), 1, fp);
		count++;

		printf("\n\n");
		printf("%-20s %s: %d\n", "Add New Member", "Count", count);
		printf("=============================\n");

		printf("%-48s", "Please enter member id (XXX to stop): ");
		rewind(stdin);
		scanf("%s", &member.id);
	}

	printf("Total Member(s) stored in this session: %d\n", count - 1);

	fclose(fp);
}

/// <summary>
/// Display all members from member.dat binary file.
/// </summary>
void displayAllMember() {
	FILE* fp = fopen("member.dat", "rb");
	if (fp == NULL)
	{
		printf("Unable to locate the required files, please ensure this program have write/read permission.\n");
		exit(-1);
	}

	printf("\n\n");
	printf("%-30s\n", "List of Members");
	printf("==================================================================================\n");
	printf("%-15s %-15s %-15s %-25s %-15s\n", "Member ID", "Member Name", "Member Gender", "Member Contact Number", "Deleted?");

	Member member;
	int count = 0;
	clock_t start, end;
	double cputime;
	start = clock();
	while (fread(&member, sizeof(member), 1, fp))
	{
		count++;

		if (member.isDeleted != 0)
			printf("%-15s %-15s %-15s +60%-22s %d\n",
				member.id,
				member.name,
				member.gender == 'M' ? "Male" : "Female",
				member.contactNumber, member.isDeleted);
	}

	end = clock();
	cputime = ((double)(end - start)) / CLOCKS_PER_SEC;

	printf("Total Member(s) stored: %d\n", count);
	printf("Execution time: %f seconds\n", cputime);

	fclose(fp);
}

/// <summary>
/// Search member according to the Member ID from member.dat binary file.
/// memberTarget: Used to store user prompt data.
/// memberBuffer: Used to store data after it's read from the binary file.
/// </summary>
void searchMember() {
	FILE* fp = fopen("member.dat", "rb");
	if (fp == NULL)
	{
		printf("Unable to locate the required files, please ensure this program have write/read permission.\n");
		exit(-1);
	}

	Member memberTarget;
	printf("\n\n");
	printf("%-30s\n", "Member Search");
	printf("=====================================================================\n");
	printf("Please enter the member id: ");
	rewind(stdin);
	gets(memberTarget.id);

	printf("\n%-30s\n", "Member's Details");
	printf("=====================================================================\n");
	printf("%-15s %-15s %-15s %-25s\n", "Member ID", "Member Name", "Member Gender", "Member Contact Number");

	Member memberBuffer;
	int count = 0;
	clock_t start, end;
	double cputime;
	start = clock();
	while (strcmp(memberTarget.id, memberBuffer.id) != 0 && memberBuffer.isDeleted != 0 && fread(&memberBuffer, sizeof(memberBuffer), 1, fp))
	{
		count++;
	}

	end = clock();
	cputime = ((double)(end - start)) / CLOCKS_PER_SEC;

	if (strcmp(memberTarget.id, memberBuffer.id) == 0 && memberBuffer.isDeleted != 0)
		printf("%-15s %-15s %-15s +60%-22s\n",
			memberBuffer.id,
			memberBuffer.name,
			memberBuffer.gender == "M" ? "Female" : "Male",
			memberBuffer.contactNumber);
	else
		printf("Requested member not found!\n");

	printf("Iterations: %d\n", count);
	printf("Execution time: %f seconds\n", cputime);

	fclose(fp);
}

/// <summary>
/// Update member according to the Member ID from user prompt and update in member.dat binary file.
/// memberTarget: Used to store user prompt data.
/// memberBuffer: Used to store data after it's read from the binary file.
/// </summary>
void updateMember() {
	FILE* fp = fopen("member.dat", "rb+");
	if (fp == NULL)
	{
		printf("Unable to locate the required files, please ensure this program have write/read permission.\n");
		exit(-1);
	}

	Member memberTarget;
	printf("\n\n");
	printf("%-30s\n", "Member Update");
	printf("=====================================================================\n");
	printf("%-48s", "Please enter member id: ");
	rewind(stdin);
	gets(memberTarget.id);

	printf("%-48s", "Please enter new member name: ");
	rewind(stdin);
	gets(memberTarget.name);

	printf("%-48s", "Please enter new member gender (M=Male, F=Female): ");
	rewind(stdin);
	scanf("%c", &memberTarget.gender);

	printf("%-47s +60", "Please enter new member contact number: ");
	rewind(stdin);
	gets(memberTarget.contactNumber);

	Member memberBuffer;
	int position = -1;
	clock_t start, end;
	double cputime;
	start = clock();
	while (strcmp(memberTarget.id, memberBuffer.id) != 0 && fread(&memberBuffer, sizeof(memberBuffer), 1, fp))
	{
		position++;
	}

	if (strcmp(memberTarget.id, memberBuffer.id) == 0 && memberTarget.isDeleted != 0)
	{
		memberTarget.isDeleted = 1;
		fseek(fp, position * sizeof(Member), SEEK_SET);
		fwrite(&memberTarget, sizeof(memberTarget), 1, fp);
	}

	fclose(fp);

	end = clock();
	cputime = ((double)(end - start)) / CLOCKS_PER_SEC;

	if (strcmp(memberTarget.id, memberBuffer.id) == 0)
		printf("%-15s %-15s %-15s +60%-22s\n",
			memberTarget.id,
			memberTarget.name,
			memberTarget.gender == "M" ? "Female" : "Male",
			memberTarget.contactNumber);
	else
		printf("Requested member not found!\n");

	printf("Member updated successfull!\n");
	printf("Iterations: %d\n", position + 1);
	printf("Execution time: %f seconds\n", cputime);
}

/// <summary>
/// Update member according to the Member ID from user prompt and update in member.dat binary file.
/// memberTarget: Used to store user prompt data.
/// memberBuffer: Used to store data after it's read from the binary file.
/// </summary>
void deleteMember() {
	FILE* fp = fopen("member.dat", "rb+");
	if (fp == NULL)
	{
		printf("Unable to locate the required files, please ensure this program have write/read permission.\n");
		exit(-1);
	}

	Member memberTarget;
	printf("\n\n");
	printf("%-30s\n", "Member Delete");
	printf("=====================================================================\n");
	printf("%-48s", "Please enter member id: ");
	rewind(stdin);
	gets(memberTarget.id);

	Member memberBuffer;
	int position = -1;
	clock_t start, end;
	double cputime;
	start = clock();
	while (strcmp(memberTarget.id, memberBuffer.id) != 0 && fread(&memberBuffer, sizeof(memberBuffer), 1, fp))
	{
		position++;
	}

	if (strcmp(memberTarget.id, memberBuffer.id) == 0)
	{
		memberBuffer.isDeleted = 0;
		fseek(fp, position * sizeof(Member), SEEK_SET);
		fwrite(&memberBuffer, sizeof(memberTarget), 1, fp);
	}

	end = clock();
	cputime = ((double)(end - start)) / CLOCKS_PER_SEC;

	fclose(fp);

	if (strcmp(memberTarget.id, memberBuffer.id) == 1)
		printf("Requested member not found!\n");

	printf("Member deleted successfull!\n");
	printf("Iterations: %d\n", position + 1);
	printf("Execution time: %f seconds\n", cputime);
}

/// <summary>
/// Compact member file.
/// Remove Member where Member IsDeleted is true.
/// </summary>
void compactMemberFile() {
	FILE* readFP = fopen("member.dat", "rb");
	if (readFP == NULL)
	{
		printf("Unable to locate the required files, please ensure this program have write/read permission.\n");
		exit(-1);
	}

	printf("Compacting Member File\n");
	printf("======================\n");
	printf("Reading existing member file..\n");

	Member memberArray[MAX_READ];
	Member memberBuffer;
	int count = 0, compactedCount = 0, notCompactedCount = 0;
	clock_t start, end;
	double cputime;
	start = clock();
	while (fread(&memberBuffer, sizeof(memberBuffer), 1, readFP))
	{
		if (memberBuffer.isDeleted != 0)
		{
			memberArray[compactedCount] = memberBuffer;
			compactedCount++;
		}
		else
			notCompactedCount++;

		count++;
	}

	printf("Finished reading existing member file..\n");
	printf("Compacting member file..\n");

	fclose(readFP);

	FILE* writeFP = fopen("member.dat", "wb");
	if (writeFP == NULL)
	{
		printf("Unable to locate the required files, please ensure this program have write/read permission.\n");
		exit(-1);
	}

	for (int i = 0; i < compactedCount; i++)
	{
		fwrite(&memberArray[i], sizeof(memberArray[i]), 1, writeFP);
	}

	printf("Finished compacting member file!\n");
	printf("Total old member count: %d\n", count);
	printf("Removed member count: %d\n", notCompactedCount);
	printf("Total new member count: %d\n", compactedCount);

	fclose(writeFP);
}

/// <summary>
/// Load the information that save in binary file.
/// </summary>
/// <param name="sales_records"></param>
/// <param name="num_records"></param>
void load_sales_records(SalesRecord* sales_records, int* num_records) {
	FILE* fp = fopen("sales_records.dat", "rb");
	if (fp != NULL) {
		fread(num_records, sizeof(int), 1, fp);
		fread(sales_records, sizeof(SalesRecord), *num_records, fp);
		fclose(fp);
	}
}

/// <summary>
/// Save the record that add/modify/delete into the binary file.
/// </summary>
/// <param name="sales_records"></param>
/// <param name="num_records"></param>
void save_sales_records(SalesRecord* sales_records, int num_records) {
	FILE* fp = fopen("sales_records.dat", "wb");
	if (fp != NULL) {
		fwrite(&num_records, sizeof(int), 1, fp);
		fwrite(sales_records, sizeof(SalesRecord), num_records, fp);
		fclose(fp);
	}
}

/// <summary>
/// Allows the user to add a new sales record.
/// </summary>
/// <param name="sales_records"></param>
/// <param name="num_records"></param>
void add_sales_record(SalesRecord* sales_records, int* num_records) {
	if (*num_records >= MAX_READ) {
		printf("Maximum number of sales records reached!\n");
		return;
	}
	SalesRecord new_record;
	printf("\nAdd a new record\n");
	printf("========================\n\n");
	printf("Enter sales order ID: ");
	scanf("%s", new_record.sales_order_id);
	printf("Enter item code: ");
	scanf("%s", new_record.item_code);
	printf("Enter quantity ordered: ");
	scanf("%d", &new_record.quantity_ordered);
	printf("Enter price: ");
	scanf("%lf", &new_record.price);
	printf("Enter member ID: ");
	scanf("%s", new_record.member_id);
	sales_records[*num_records] = new_record;
	(*num_records)++;
	printf("\nSales record added successfully!\n\n");
}

/// <summary>
/// Prompts the user to enter a sales order ID and searches record.
/// </summary>
/// <param name="sales_records"></param>
/// <param name="num_records"></param>
void search_sales_record(SalesRecord* sales_records, int num_records) {
	char sales_order_id[10];
	int i;
	printf("Enter sales order ID: ");
	scanf("%s", sales_order_id);
	for (i = 0; i < num_records; i++) {
		if (strcmp(sales_records[i].sales_order_id, sales_order_id) == 0) {
			printf("\nSales record\n");
			printf("========================\n\n");
			printf("Sales Order ID    : %s\nItem Code\t  : %s\nQuantity Ordered  : %d\nPrice\t\t  : %.2f\nMember ID\t  : %s\n\n", sales_records[i].sales_order_id, sales_records[i].item_code, sales_records[i].quantity_ordered, sales_records[i].price, sales_records[i].member_id);
			return;
		}
	}
	printf("\nSales record not found!\n\n");
}

/// <summary>
/// Prompts the user to enter a sales order ID and searches for a record with a matching ID and prompts the user to enter new values for each field in the record, and updates the record with the new values or press Enter to keep the same values.
/// </summary>
/// <param name="sales_records"></param>
/// <param name="num_records"></param>
void modify_sales_record(SalesRecord* sales_records, int num_records) {
	char sales_order_id[10];
	int i;
	int found = 0;
	char new_sales_order_id[10];
	char new_item_code[10];
	char new_quantity[10];
	char new_price[10];
	char new_member_id[10];

	printf("\nEnter sales order ID to modify: ");
	scanf("%s", sales_order_id);

	for (i = 0; i < num_records; i++) {
		if (strcmp(sales_records[i].sales_order_id, sales_order_id) == 0) {
			printf("\nSales Detail\n");
			printf("========================\n\n");
			printf("Sales Order ID    : %s\n", sales_records[i].sales_order_id);
			printf("Item Code\t  : %s\n", sales_records[i].item_code);
			printf("Quantity Ordered  : %d\n", sales_records[i].quantity_ordered);
			printf("Price\t\t  : %.2f\n", sales_records[i].price);
			printf("Member ID\t  : %s\n\n", sales_records[i].member_id);

			fflush(stdin);
			while (getchar() != '\n');
			printf("Update Sale\n");
			printf("========================\n\n");
			printf("Enter new sales order ID (or press Enter to keep the same): ");
			fflush(stdin);
			fgets(new_sales_order_id, 10, stdin);
			new_sales_order_id[strcspn(new_sales_order_id, "\n")] = 0;
			if (strlen(new_sales_order_id) > 0) {
				strcpy(sales_records[i].sales_order_id, new_sales_order_id);
			}

			printf("Enter new item code (or press Enter to keep the same): ");
			fflush(stdin);
			fgets(new_item_code, 10, stdin);
			new_item_code[strcspn(new_item_code, "\n")] = 0;
			if (strlen(new_item_code) > 0) {
				strcpy(sales_records[i].item_code, new_item_code);
			}

			printf("Enter new quantity ordered (or press Enter to keep the same): ");
			fflush(stdin);
			fgets(new_quantity, 10, stdin);
			new_quantity[strcspn(new_quantity, "\n")] = 0;
			if (strlen(new_quantity) > 0) {
				sales_records[i].quantity_ordered = atoi(new_quantity);
			}

			printf("Enter new price (press Enter to keep the same): ");
			fflush(stdin);
			fgets(new_price, 10, stdin);
			new_price[strcspn(new_price, "\n")] = 0;
			if (strlen(new_price) > 0) {
				sales_records[i].price = atof(new_price);
			}

			printf("Enter new member ID (or press Enter to keep the same): ");
			fflush(stdin);
			fgets(new_member_id, 10, stdin);
			new_member_id[strcspn(new_member_id, "\n")] = 0;
			if (strlen(new_member_id) > 0) {
				strcpy(sales_records[i].member_id, new_member_id);
			}

			printf("\nRecord updated successfully.\n");
			found = 1;
			break;
		}
	}

	if (!found) {
		printf("Record not found.\n");
	}
}

/// <summary>
/// Displays all the sales records and count the total quantity sales and total price sales.
/// </summary>
/// <param name="sales_records"></param>
/// <param name="num_records"></param>
void display_sales_records(SalesRecord* sales_records, int num_records) {
	int i;
	double total_sales = 0.0;
	int total_quantity = 0;

	printf("\nSales records:\n\n");
	printf("Sales Order ID  Item Code  Quantity  Price   Member ID \n");
	printf("--------------  ---------  --------  ------  --------- \n");

	for (i = 0; i < num_records; i++) {
		printf("%-14s  %-9s  %-8d  %-6.2f  %-9s\n",
			sales_records[i].sales_order_id,
			sales_records[i].item_code,
			sales_records[i].quantity_ordered,
			sales_records[i].price,
			sales_records[i].member_id);
		total_sales += sales_records[i].quantity_ordered * sales_records[i].price;
		total_quantity += sales_records[i].quantity_ordered;
	}

	if (num_records == 0) {
		printf("\nNo sales records found.\n");
	}
	else {
		printf("\nTotal quantity sales: %d\n", total_quantity);
		printf("Total price sales: %.2f\n", total_sales);
	}
}

/// <summary>
/// Prompts the user to enter an item code and calculates and displays the total sales for that items.
/// </summary>
/// <param name="sales_records"></param>
/// <param name="num_records"></param>
void sales_summary_by_item_code(SalesRecord* sales_records, int num_records) {
	char item_code[10];
	int total_quantity = 0;
	double total_sales = 0;
	int i;
	printf("\nEnter item code: ");
	scanf("%s", item_code);
	for (i = 0; i < num_records; i++) {
		if (strcmp(sales_records[i].item_code, item_code) == 0) {
			total_quantity += sales_records[i].quantity_ordered;
			total_sales += sales_records[i].quantity_ordered * sales_records[i].price;
		}
	}
	printf("Sales summary for item code %s\n", item_code);
	printf("----------------------------------\n\n");
	printf("Total quantity sold  : %d\n", total_quantity);
	printf("Total sales          : %.2f\n\n", total_sales);
}

/// <summary>
/// Prompts the user to enter a sales order ID and search for matching ID and removes the record from the binary file
/// </summary>
/// <param name="sales_records"></param>
/// <param name="num_records"></param>
void delete_sales_record(SalesRecord* sales_records, int* num_records) {
	char sales_order_id[10];
	int i, j;

	printf("\nDelete Sales\n");
	printf("========================\n\n");
	printf("Enter sales order ID: ");
	scanf("%s", sales_order_id);
	for (i = 0; i < *num_records; i++) {
		if (strcmp(sales_records[i].sales_order_id, sales_order_id) == 0) {
			for (j = i; j < *num_records - 1; j++) {
				sales_records[j] = sales_records[j + 1];
			}
			(*num_records)--;
			printf("\nSales record deleted successfully!\n");
			return;
		}
	}
	printf("\nSales record not found!\n");
}