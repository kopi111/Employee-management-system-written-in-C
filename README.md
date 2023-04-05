# Employee-management-system-written-in-C
The code is a basic employee management system written in C.

The code is a basic employee management system written in C. It includes three main functionalities: creating a new employee, printing all employees, and editing or deleting an existing employee.

The program utilizes three different structures to store employee data: empdata, employee, and empdeduction. Empdata stores the personal information of an employee, employee stores the financial information such as hourly rate and gross pay, and empdeduction stores tax and insurance information to calculate the net pay of an employee.

The createEmployee() function prompts the user to input information for a new employee and stores it in a text file named employee.txt. The printAllEmployee() function reads the employee data from the text file and displays it on the console. The deleteEmployee() function deletes an employee's data from the text file based on the given employee ID. The editEmployee() function allows the user to modify an existing employee's data, and it also stores the changes in the text file.

Overall, this program provides a basic framework for managing employees' information, but it lacks security features such as authentication and validation of input data.
