#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define	DAYS_IN_MONTH 29		// number of days we process
#define EMPLOYEE_COUNT 12	// number of employees
#define WORKING_DAYS ((int)( DAYS_IN_MONTH * 0.8 ))	// maximum number of days an employee work
#define DESK_COUNT ((int)( EMPLOYEE_COUNT * 0.8 ))	// number of employee working simultaneously

typedef int bool;
#define true 1
#define false 0

bool* schedule_table;

void print_table(int current_day, int current_employee) {
	int day,employee;
	printf("--------------- day: %d  , employee: %d  ----------\n", current_day, current_employee);
	printf("          ");
	for (employee = 0; employee < EMPLOYEE_COUNT; employee++) {
		printf("%s    ", employee==current_employee?"|":" ");
	}
	printf("\n");
	for (day = 0; day < DAYS_IN_MONTH; day++) {
		printf("Day %2d:   ", day+1);
		for (employee = 0; employee < EMPLOYEE_COUNT; employee++) {
			printf("%s    ", schedule_table[day*EMPLOYEE_COUNT+employee]?"x":"-");
		}
		if (day==current_day) {
			printf("%s", "<-");
		}
		printf("\n");
	}
	printf("--------------------------------------\n");
}

bool is_employee_full(int employee){
	int day,sum=0;
	for (day = 0; day < DAYS_IN_MONTH; day++) {
		if (schedule_table[day*EMPLOYEE_COUNT+employee]){
			sum++;
		}
	}
	return sum >= WORKING_DAYS;
}

bool is_day_full(int day){
	int employee,sum=0;
	for (employee = 0; employee < EMPLOYEE_COUNT; employee++) {
		if (schedule_table[day*EMPLOYEE_COUNT+employee]){
			sum++;
		}
	}
	return sum >= DESK_COUNT;
}

bool is_working(int day, int employee){
	return schedule_table[day*EMPLOYEE_COUNT+employee];
}
void set_working(int day, int employee){
	schedule_table[day*EMPLOYEE_COUNT+employee] = true;
}

void clear_employee(int until_day, int employee){
	int day;
	for (day = 0; day < until_day; day++) {
		schedule_table[day*EMPLOYEE_COUNT+employee] = false;
	}
}

int main() {
	int day = 0;
	int employee = 0;
	int steps = 0;
	
	printf("\nDays: %d, working days per employee: %d, number of employees: %d, simultaneously working employees: %d\n\n", DAYS_IN_MONTH, WORKING_DAYS, EMPLOYEE_COUNT, DESK_COUNT);
	
	schedule_table = (bool*) malloc( DAYS_IN_MONTH * EMPLOYEE_COUNT * sizeof(bool) );
	
	do {
		
		//print_table(day,employee);
		//getchar();
		steps++;
		
		if (!is_working(day,employee) && !is_employee_full(employee)){	// only set working, if not already full
			set_working(day,employee);
		}
		
		if (is_day_full(day)) {	
			day++;								// skip the remaining employees, move to the next day
			employee=0;
			continue;
		}
		
		employee++;								// move to the next employee
		
		if (employee>=EMPLOYEE_COUNT){			// if all employee examined (but the desks still isn't full)
			if (day==0) {						// if this occurred on the first day, give up
				break;							// 	because this means the scheduler impossible without employee overtime
			}
			employee=0;
			while (is_working(day,employee)){	// find the first, who not working on that day
				employee++;
			}
			set_working(day,employee);			// 	and set working
			
			clear_employee(day,employee);		// clear it's previous days
			day=0;								// restart from the first day from the currently changed employee
		}
		
	} while(day<DAYS_IN_MONTH);
	
	if (day<DAYS_IN_MONTH) {
		printf("\nSorry, but it's impossible to accomplish this schedule with the given parameters!\n\n");
		return 1;
	} else {
		print_table(day,employee);
		printf("\nSteps taken: %d (bruteforce would be: %.0lf)\n\n", steps, pow(2,DAYS_IN_MONTH*EMPLOYEE_COUNT));
		return 0;
	}
}