#include <stdio.h>

#include <time.h>

#include<cstdlib>

#include <stdbool.h>

#include <string.h>


struct empdata {
  char fname[100];
  char lname[100];
  char gender[10];
  char contact_number[20];
  int employee_id;
  char department[100];
};
typedef struct empdata empdata; //creating the structure

struct employee {
  int employee_id[20];
  float hourly_rate;
  int hours_worked;
  float gross_pay;
};
typedef struct employee employee; //creating the structure

struct empdeduction {
  int employee_id;
  float gross_pay;
  float tax_rate;
  float insurance_rate;
  float threshold;
  float net_pay;
  float total_deduction;
};
typedef struct empdeduction empdeduction; //creating the structure

void createEmployee() {

  int selectGender;
  struct empdata emp;

  printf("Enter employee first name: \n");
  scanf(" %s", & emp.fname);

  printf("Enter employee last name: \n");
  scanf(" %s", & emp.lname);

  printf("Enter one for male 2 for female: \n");
  scanf(" %d", & selectGender);

  if (selectGender == 1) {
    strcpy(emp.gender, "Male");
  } else if (selectGender == 2) {
    strcpy(emp.gender, "Female");
  } else {
    printf("Invalid choice. Please enter 1 for Male or 2 for Female.\n");
  }

  printf("Enter employee contact number: ");
  scanf(" %s", & emp.contact_number);

  printf("Enter employee ID: ");
  scanf(" %d", & emp.employee_id);

  printf("Enter employee department: ");
  scanf(" %s", & emp.department);

  FILE * outfile;
  // open file for writing
  outfile = fopen("employee.txt", "a+");
  if (outfile == NULL) {
    fprintf(stderr, "\nError opened file\n");
    exit(1);
  }

  // write struct to file
  int flag = 0;

  flag = flag = fprintf(outfile, "%s %s %s %s %d %s \n", emp.fname, emp.lname, emp.gender, emp.contact_number, emp.employee_id, emp.department);
  if (flag) {
    printf("Contents of the structure written "
      "successfully");
  } else
    printf("Error Writing to File!");

  // close file
  fclose(outfile);

}

void printAllEmployee() {

  struct empdata emp;
  FILE * infile;

  // open file for reading
  infile = fopen("employee.txt", "r");
  if (infile == NULL) {
    fprintf(stderr, "\nError opening file\n");
    exit(1);
  }

  // read each employee from file and print out details
  while (fscanf(infile, "%s %s %s %s %d %s", emp.fname, emp.fname, emp.gender, emp.contact_number, & emp.employee_id, emp.department) != EOF) {
    printf("Name: %s\n", emp.fname);
    printf("Name: %s\n", emp.lname);
    printf("Gender: %s\n", emp.gender);
    printf("Contact Number: %s\n", emp.contact_number);
    printf("Employee ID: %d\n", emp.employee_id);
    printf("Department: %s\n", emp.department);
    printf("\n");
  }

  // close file
  fclose(infile);
}

void deleteEmployee() {
  int idToDelete;
  printf("Enter the employee ID to delete: ");
  scanf("%d", & idToDelete);

  FILE * infile = fopen("employee.txt", "r");
  FILE * outfile = fopen("temp.txt", "w");
  if (infile == NULL) {
    printf("Error opening file.");
    return;
  }

  struct empdata emp;
  int found = 0;
  while (fscanf(infile, "%s %s %s %s %d %s", emp.fname, emp.lname, emp.gender, emp.contact_number, & emp.employee_id, emp.department) != EOF) {
    if (emp.employee_id == idToDelete) {
      found = 1;
    } else {
      fprintf(outfile, "%s %s %s %d %s\n", emp.fname, emp.lname, emp.gender, emp.contact_number, emp.employee_id, emp.department);
    }
  }

  fclose(infile);
  fclose(outfile);

  if (found) {
    remove("employee.txt");
    rename("temp.txt", "employee.txt");
    printf("Employee with ID %d deleted successfully.\n", idToDelete);
  } else {
    printf("Employee with ID %d not found.\n", idToDelete);
    remove("temp.txt");
  }
}

void editEmployee() {
  int empID, choice;
  struct empdata emp;
  FILE * infile, * outfile;

  // get employee ID to edit/delete
  printf("Enter Employee ID: ");
  scanf("%d", & empID);

  // open file for reading
  infile = fopen("employee.txt", "r");
  if (infile == NULL) {
    fprintf(stderr, "\nError opening file\n");
    exit(1);
  }

  // open temp file for writing
  outfile = fopen("temp.txt", "w");
  if (outfile == NULL) {
    fprintf(stderr, "\nError opening file\n");
    fclose(infile);
    exit(1);
  }

  int found = 0;
  // read each employee from file and edit/delete based on ID
  while (fscanf(infile, "%s %s %s %s %d %s", emp.fname, emp.lname, emp.gender, emp.contact_number, & emp.employee_id, emp.department) != EOF) {
    if (emp.employee_id == empID) {
      found = 1;
      printf("Employee Found:\n");
      printf("Name: %s\n", emp.fname);
      printf("Name: %s\n", emp.lname);
      printf("Gender: %s\n", emp.gender);
      printf("Contact Number: %s\n", emp.contact_number);
      printf("Employee ID: %d\n", emp.employee_id);
      printf("Department: %s\n", emp.department);
      printf("Select option:\n1. Edit Employee\n2. Delete Employee\n");
      scanf("%d", & choice);
      if (choice == 1) {
        printf("Enter new employee details:\n");
        printf("Enter Employee first name: ");
        scanf("%s", emp.fname);
        printf("Enter Employee last name: ");
        scanf("%s", emp.lname);
        printf("Enter one for male 2 for female: ");
        scanf("%d", & choice);
        if (choice == 1) {
          strcpy(emp.gender, "Male");
        } else if (choice == 2) {
          strcpy(emp.gender, "Female");
        } else {
          printf("Invalid choice. Please enter 1 for Male or 2 for Female.\n");
        }
        printf("Enter employee contact number: ");
        scanf("%s", emp.contact_number);
        printf("Enter employee department: ");
        scanf("%s", emp.department);
      } else if (choice == 2) {
        continue;
      } else {
        printf("Invalid choice.\n");
        continue;
      }
    }
    // write struct to temp file
    fprintf(outfile, "%s %s  %s %s %d %s\n", emp.fname, emp.lname, emp.gender, emp.contact_number, emp.employee_id, emp.department);
  }

  // close files
  fclose(infile);
  fclose(outfile);

  // delete original file and rename temp file to original file name
  remove("employee.txt");
  rename("temp.txt", "employee.txt");

  if (found == 0) {
    printf("Employee not found.\n");
  } else {
    printf("Employee details updated.\n");
  }
}

void signIn() {
  int idToSignIn;
  int hours;
  char day[16];

  printf("Enter your employee ID: ");
  scanf("%d", & idToSignIn);

  FILE * file = fopen("employee.txt", "r");
  if (file == NULL) {
    printf("Error opening file.");
    return;
  }

  struct empdata emp;
  int found = 0;
  while (fscanf(file, "%s %s %s %s %d %s", emp.fname, emp.lname, emp.gender, emp.contact_number, & emp.employee_id, emp.department) != EOF) {
    if (emp.employee_id == idToSignIn) {
      found = 1;
      printf("Enter the date (e.g., 10/12/34): ");
      scanf("%s", day);
      printf("Enter amount of hours worked: ");
      scanf("%d", & hours);
      fclose(file);

      FILE * outfile = fopen("hoursworked.txt", "a");
      if (outfile == NULL) {
        printf("Error opening file.");
        return;
      }

      int flag = fprintf(outfile, "%d %s %d\n", emp.employee_id, day, hours);
      if (flag) {
        printf("Signed in successfully.\n");
      } else {
        printf("Error writing to file!\n");
      }

      fclose(outfile);
      break;
    }
  }

  if (!found) {
    printf("Employee with ID %d not found.\n", idToSignIn);
    fclose(file);
  }
}

void calculatePay() {
  int idToCalculate;
  float hourlyRate;

  printf("Enter the employee ID: ");
  scanf("%d", & idToCalculate);

  FILE * file = fopen("employee.txt", "r");
  if (file == NULL) {
    printf("Error opening file.");
    return;
  }

  struct empdata emp;
  int found = 0;
  while (fscanf(file, "%s %s %s %s %d %s", emp.fname, emp.lname, emp.gender, emp.contact_number, & emp.employee_id, emp.department) != EOF) {
    if (emp.employee_id == idToCalculate) {
      found = 1;
      break;
    }
  }
  fclose(file);

  if (!found) {
    printf("Employee with ID %d not found.\n", idToCalculate);
    return;
  }

  printf("Enter the hourly rate: ");
  scanf("%f", & hourlyRate);

  float totalHours = 0;
  FILE * hoursFile = fopen("hoursworked.txt", "r");
  if (hoursFile == NULL) {
    printf("Error opening file.");
    return;
  }

  int empID;
  char date[16];
  int hoursWorked;
  while (fscanf(hoursFile, "%d %s %d", & empID, date, & hoursWorked) != EOF) {
    if (empID == idToCalculate) {
      totalHours += hoursWorked;
    }
  }
  fclose(hoursFile);

  float grossPay = totalHours * hourlyRate;
  float taxRate = grossPay > 150000 ? 0.2 : 0.1;
  float insuranceRate = 0.035;
  float threshold = 50000;
  float totalDeduction = grossPay * (taxRate + insuranceRate) - threshold;
  float netPay = grossPay - totalDeduction;

  printf("Employee ID: %d\n", emp.employee_id);
  printf("Name: %s %s\n", emp.fname, emp.lname);
  printf("Total Hours Worked: %.2f\n", totalHours);
  printf("Hourly Rate: %.2f\n", hourlyRate);
  printf("Gross Pay: %.2f\n", grossPay);
  printf("Tax Rate: %.2f%%\n", taxRate * 100);
  printf("Insurance Rate: %.2f%%\n", insuranceRate * 100);
  printf("Total Deduction: %.2f\n", totalDeduction);
  printf("Net Pay: %.2f\n", netPay);

  FILE * payslipFile = fopen("payslip.txt", "a+");
  if (payslipFile == NULL) {
    printf("Error creating file.");
    return;
  }

  struct empdeduction empDeduction = {
    emp.employee_id,
    grossPay,
    taxRate,
    insuranceRate,
    threshold,
    netPay,
    totalDeduction
  };
  fprintf(payslipFile, "Employee ID: %d\n", empDeduction.employee_id);
  fprintf(payslipFile, "Name: %s %s\n", emp.fname, emp.lname);
  fprintf(payslipFile, "Total Hours Worked: %.2f\n", totalHours);
  fprintf(payslipFile, "Hourly Rate: %.2f\n", hourlyRate);
  fprintf(payslipFile, "Gross Pay: %.2f\n", empDeduction.gross_pay);
  fclose(payslipFile);
}

void displayPayslips() {
  FILE * file = fopen("payslip.txt", "r");
  if (file == NULL) {
    printf("Error opening file.");
    return;
  }

  char line[100];
  while (fgets(line, 100, file) != NULL) {
    printf("%s", line);
  }

  fclose(file);
}

void menu() {
  int selection;
  struct empdata emp;

  while (1) {

    printf("\n\n\t\t\tPress 1: Create Employee\n");
	printf("\t\t\tPress 2: Sign In\n");
	printf("\t\t\tPress 3: Calculate Employee Pay\n");
	printf("\t\t\tPress 4: Display Payslips\n");
	printf("\t\t\tPress 5: Edit Employee\n");
	printf("\t\t\tPress 6: Delete Employee\n");
	printf("\t\t\tPress 7: Print All Employees\n");
	printf("\t\t\tPress 8: Exit\n\n");
	printf("\tPlease select a choice: ");
    scanf("%d", & selection);
    if (selection < 1 || selection > 8) { // Invalid input
      printf("Wrong input. Please enter a number between 1 and 4.\n");
    } else if (selection == 6) { // Exit loop if user selects 4
      break;
    } else {
      if (selection == 1) {
        createEmployee();

      } else if (selection == 2) {
        signIn();

      } else if (selection == 3) {
        calculatePay();

      } else if (selection == 4) {
        displayPayslips();

      } else if (selection == 5) {
        editEmployee();

      } else if (selection == 6) {
        deleteEmployee();

      } else if (selection == 7) {
        printAllEmployee();

      } else if (selection == 8) {
        break;

      }
    }

  }

}
int main() {

  menu(); // Call the menu function
  return 0;

}
