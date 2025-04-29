#include <stdio.h>

//just to make things pretty
void work();
void speed();
void convert();
void NANI();

int main()
{
    //choices and your choice
    int choice[]={1,2,3}, MyChoice;

    //enter choice
    printf("\n --------------------------");
    printf("\n1. Calculate Speed\n\n2. Calculate Work\n\n3. Convert radian to degree\n");
    printf("\n --------------------------");    
    printf("\n Enter your Choice:");
    scanf("%i", &MyChoice);

    //choice bridges
    if(MyChoice == choice[0]){
        speed();
    }else if(MyChoice == choice[1]){
        work();
    }else if(MyChoice == choice[2]){
        convert();
    }else{
        NANI();
    }

}

void speed()
{
    float distance, time, speed;

    printf("\n Enter Distance (km):");
    scanf("%f", &distance);
    printf("Enter Time (h):");
    scanf("%f", &time);

    speed = distance / time;
    printf("\n The speed(km/h): %.2f\n", speed);
}
void work()
{
    float mass, height, work;

    printf("\n Enter mass (kg):");
    scanf("%f", &mass);
    printf("Enter height (m):");
    scanf("%f", &height);

    work = mass * 9.8 * height;
    printf("\n The work is %f Joules\n", work);
}
void convert(){
    float radian,degree;

    printf("\n Enter radian:");
    scanf("%f", &radian);

    degree = radian * 57.2958;
    printf("\n %f radian is equals to %f\n", radian, degree);
}
void NANI(){
    printf("\nStuupiittt");
}