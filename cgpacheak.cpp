
#include <iostream>
using namespace std;
int main(){
    FILE *fptr;
    fptr= fopen ("studenet.txt", "w");
    char name[100];
    int age;
    float cgpa;
    printf("Enter name: ");
    scanf("%s", name);
    printf("Enter age: ");
    scanf("%d", &age);
    printf("Enter cgpa: ");
    scanf("%f", &cgpa);
    fprintf (fptr,"student name: %s\n", name);
    fprintf (fptr,"student age: %d\n", age);
    fprintf (fptr,"student cgpa: %.2f\n", cgpa);
     fclose(fptr);
        return 0;
}
