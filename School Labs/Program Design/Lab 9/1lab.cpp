#include <stdio.h>

struct SalaryRecord {
    int id;
    float salary, epf, tax, net;
};

void calcNetSalary(struct SalaryRecord staff[]) {
    for (int i = 0; i < 4; i++) {
        staff[i].epf = staff[i].salary * 0.11;

        if (staff[i].salary >= 10000) {
            staff[i].tax = staff[i].salary * 0.15;
        } else if (staff[i].salary >= 5000) {
            staff[i].tax = staff[i].salary * 0.1;
        } else if (staff[i].salary >= 3000) {
            staff[i].tax = staff[i].salary * 0.08;
        } else {
            staff[i].tax = 0;
        }

        staff[i].net = staff[i].salary - staff[i].epf - staff[i].tax;
    }
}

int main() {
    struct SalaryRecord staff[4];

    for (int i = 0; i < 4; i++) {
        printf("\nEmployee %d:", i + 1);
        printf("\n---Employee ID: ");
        scanf("%d", &staff[i].id);
        getchar(); // Consume the newline character
        printf("---Employee Basic Salary: ");
        scanf("%f", &staff[i].salary);
        getchar(); // Consume the newline character
    }

    calcNetSalary(staff);

    printf("\nNet Salary for each employee:\n");
    for (int i = 0; i < 4; i++) {
        printf("Employee %d: ID=%d, Net Salary=%.2f\n", i + 1, staff[i].id, staff[i].net);
    }

    return 0;
}
