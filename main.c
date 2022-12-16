// Praktikum 5
// PV-Rechner
// Pearse-Danker & Dora 
// Version 1.0
// 08.12.22

#define _CRT_SECURE_NO_WARNINGS

#define ROWS 4
#define COLS 12

#include <stdio.h>      // Scanf;printf
#include <stdlib.h>     // system(cls)   
#include <stdbool.h>    // bool (True/False)

void horizontal_surfaces(float result1[], float array1[], float array2[]);                  // multiplies days in month with the daily radiation, stores result in array
void print_months();                                                                        // prints months
void print_array(float array[]);                                                            // helper funtion to print array
float sum(float result_1[], int length);                                                    // adds values from result array to a sum
short get_short(char text[], short, short);
float get_float(char text[], float, float);


int main(void)
{
    system("cls");

    printf("---------------------------------------------------\n");
    printf("Globalstrahlung auf horizontalen Fl%cchen in Hamburg\n",132);
    printf("---------------------------------------------------\n");

    const int MONTHS = 12;
 
    //Declaring Variables

    float daily_radiation[COLS] = { 0.52f, 1.13f, 2.23f, 3.55f, 4.67f, 5.44f, 4.82f, 4.34f, 2.79f, 1.49f, 0.67f, 0.40f };
    float days_in_month[COLS] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    float monthly_radiation[COLS] = { 0 };
    float angles_30[COLS] = { 0 };
    float angles_60[COLS] = { 0 };

    float result[COLS] = { 0 };

    float correcting_factor[][COLS] = {{1.00f, 1.00f, 1.00f, 1.00f, 1.00f, 1.00f, 1.00f, 1.00f, 1.00f, 1.00f, 1.00f, 1.00f},  // Neigungswnkel 0
                                       {1.44f, 1.40f, 1.17f, 1.08f, 1.00f, 0.96f, 0.97f, 1.03f, 1.17f, 1.30f, 1.47f, 1.42f},   // Neigungswnkel 30
                                       {1.57f, 1.50f ,1.19f ,1.05f, 0.94f, 0.90f, 0.91f, 1.00f, 1.18f, 1.37f, 1.61f, 1.55f},   // Neigungswnkel 45
                                       {1.63f, 1.54f, 1.15f, 0.98f, 0.85f, 0.81f, 0.83f, 0.92f, 1.14f, 1.38f, 1.68f, 1.61f} }; // Neigungswnkel 60

    int standorte[][COLS] = {    {19, 33, 75, 128, 160, 166, 158, 134, 94, 51, 26, 15},     // Berlin
                                 {20, 34, 77, 123, 150, 162, 154, 132, 90, 52, 25, 16},     // Kassel
                                 {29, 45, 85, 130, 153, 174, 164, 140, 99, 62, 36, 24},     // Stuttgart
                                 {29, 45, 84, 129, 153, 172, 166, 141, 104, 63, 38, 24} };  // Freiburg 


    // -----------------------------------
    // Aufgabe 1.1
    // Mittlere monatliche Globalstrahlung
    // -----------------------------------
    printf("\n");
    printf("Mittlere Monatliche Globalstrahlung in Hamburg\n");
    printf("\n");

    horizontal_surfaces(monthly_radiation, days_in_month, daily_radiation);

    // -----------------------------------
    // Aufgabe 1.2
    // Mittlere jährliche Globalstrahlung
    // -----------------------------------

    printf("\n\nDie mittlere j%chrliche Globalstrahlung betr%cgt : %.2f\n",132,132, sum(monthly_radiation, 12));

    // // -----------------------------------
    // // Aufgabe 1.3
    // // Globalstrahlung auf geneigte Flächen
    // // -----------------------------------

    //Globalstrahlung auf geneigte Strahlung für 30 Grad
    printf("------------------------------------------------------------------\n\n");
    printf("Mittlere Monatliche Globalstrahlung auf geneigte Fl%cchen in Hamburg (30 Grad)\n",132);
    printf("\n");

    for (int i = 0; i < COLS; i++)
    {
        angles_30[i] = monthly_radiation[i] * correcting_factor[1][i];
    }

    print_array(angles_30);

    printf("\n");
    printf("Die mittlere j%chrliche Globalstrahlung f%cr 30 Grad betr%cgt : %.2f\n",132,129,132, sum(angles_30, MONTHS));
    printf("---------------------------------------------------------------------\n\n");

    //Globalstrahlung auf geneigte Strahlung für 60 Grad
    printf("Mittlere Monatliche Globalstrahlung auf geneigte Fl%cchen in Hamburg (60 Grad)\n",132);
    printf("\n");

    for (int i = 0; i < COLS; i++)
    {
        angles_60[i] = monthly_radiation[i] * correcting_factor[3][i];
    }

    print_array(angles_60);

    printf("\n");
    printf("Die mittlere j%chrliche Globalstrahlung f%cr 60 Grad betr%cgt : %.2f\n",132,129,132, sum(angles_60, MONTHS));
    printf("---------------------------------------------------------------------\n\n");

    // // // -----------------------------------
    // // // Aufgabe 2
    // // // Mittlere monatliche Globalstrahlung für Berlin, Kassel, Stuttgart und Freiburg

    printf("-------------------------------------\n");
    printf("Einfacher Rechner f%cr ihren PV-Ertrag\n",129);
    printf("-------------------------------------\n");

    // // Declaring Variables

    int standort, ausrichtung;
    float peakPerformance;

    // Prompting Input Question

    // Prompting Location
    standort =  get_short("Geben Sie eine Zahl ein: (1 = Berlin, 2 = Kassel, 3 = Stuttgart, 4 = Freiburg, 5 = Hamburg)", 1, 5); 
    printf("\n");
     
    // Prompting angle
    char text[256];
    sprintf(text, "Wie wird die PV-Anlage ausgerichtet? (1 = horizontal, 2 = S%cd 30%c, 3 = S 45%c, 4 = S 60%c)", 129, 248, 248, 248);
    ausrichtung = get_short(text, 1, 4);
    printf("\n");

    //Prompting performance
    sprintf(text, "Wie gro%c ist die Spitzenleistung ? (kwp)(1 - 30, alter Wert : 10)", 225);

    peakPerformance = get_float(text, 1, 30);
    printf("\n");

    standort--;
    ausrichtung--;
   
    // Calculation Perfomance
    printf("\n");
    printf("---------------------\n");
    printf("Berechneter PV-Ertrag\n");
    printf("---------------------\n");
    
    if (standort > 3)
    {
        // Hamburg
        for (int i = 0; i < 12; i++)
        {
            result[i] = correcting_factor[ausrichtung][i] * monthly_radiation[i] * peakPerformance;
        }
        print_array(result);
    }
    else
    {
        // restliche Standorte
        for (int i = 0; i < 12; i++)
        {
            result[i] = correcting_factor[ausrichtung][i] * standorte[standort][i] * peakPerformance;
        }
        print_array(result);
    }


    printf("\n");
    printf("Gesamt in kwh : %.2f\n", sum(result, COLS));
    printf("---------------------------------------------------------------------\n\n");

    return 0;
}

//-----------------------------------------------------------------------------

void horizontal_surfaces(float result1[], float array1[], float array2[])
{

    print_months();
    for (int i = 0; i < 12; i++)
    {
        result1[i] = array1[i] * array2[i];

        printf("%10.2f|", result1[i]);
    }
}


float sum(float result_1[], int length)
{
    float sum_value = 0;
    for (int i = 0; i < length; i++)
    {
        sum_value = sum_value + result_1[i];
    }

    return sum_value;

}

void print_months()
{

    char months[][10] = { "Jan", "Feb", "Maer", "Apr", "Mai", "Jun", "Jul", "Aug", "Sep", "Okt", "Nov", "Dez" };

    for (int i = 0; i < 12; i++)
    {
        printf("%10s|", months[i]);
    }

    printf("\n");

}

void print_array(float array[])
{
    print_months();
    for (int j = 0; j < COLS; j++)
    {
        printf("%10.2f|", array[j]);
    }
    printf("\n");
}

// Checking user input

short get_short(char text[], short MIN, short MAX)
{
    //declare working variables 
    short value;
    int finished = 0; //0 für FALSE
    char ch;
    int retVal;


    do
    {
        printf("%s: ", text); //Abkürzung "s" für "string" / Zeichenkette

        ch = '\0'; // \0 wird als ein Buchstabe gewertet; O ist nicht die Zahl 0 sondern ein "Null Character"; Null Character hat in der Ascii Tabelle auch den Wert 0

        retVal = scanf("%hd%c", &value, &ch); // -> "hd" steht für short -> Adresse ist "Value"; scanf gibt auch einen Wert zurück, diesen speichern wir in retVal 

        // check for valid user input

        if (retVal != 2) printf("Das war keine korrekte Zahl!\n");

        else if (ch != '\n') printf("Unerwartete Zeichen hinter der Zahl!\n");

        else if (value < MIN) printf("Zahl ist zu klein (MIN: %hd)\n",MIN);

        else if (value > MAX) printf("Zahl ist zu gro%c (MAX: %hd)\n",225,MAX);

        else finished = 1; // falls die Variable tatsächlich 2 ist; und der character ein newline, ist alles richtig und die loop wird beendet

        //Variable finished wird auf 1 gesetzt -> weil 1 für TRUE

        //clear input stream buffer

        while (ch != '\n') scanf("%c", &ch); //Variation mit scanf von getchar

    } while (!finished); //repeat if not finished 

    //return user input
    return value; //wer auch immer die Funktion get_short aufruft bekomm "value" zurück
}

float get_float(char text[], float MIN, float MAX)
{
    //declare working variables 
    float value;
    int finished = 0; //0 für FALSE
    char ch;
    int retVal;


    do
    {
        printf("%s: ", text); //Abkürzung "s" für "string" / Zeichenkette

        ch = '\0'; // \0 wird als ein Buchstabe gewertet; O ist nicht die Zahl 0 sondern ein "Null Character"; Null Character hat in der Ascii Tabelle auch den Wert 0

        retVal = scanf("%f%c", &value, &ch); // -> "hd" steht für short -> Adresse ist "Value"; scanf gibt auch einen Wert zurück, diesen speichern wir in retVal 

        // check for valid user input

        if (retVal != 2) printf("Das war keine korrekte Zahl!\n");

        else if (ch != '\n') printf("Unerwartete Zeichen hinter der Zahl!\n");

        else if (value < MIN) printf("Zahl ist zu klein (MIN: %f)\n", MIN);

        else if (value > MAX) printf("Zahl ist zu gro%c (MAX: %f)\n",225, MAX);

        else finished = 1; // falls die Variable tatsächlich 2 ist; und der character ein newline, ist alles richtig und die loop wird beendet

        //Variable finished wird auf 1 gesetzt -> weil 1 für TRUE

        //clear input stream buffer

        while (ch != '\n') scanf("%c", &ch); //Variation mit scanf von getchar

    } while (!finished); //repeat if not finished 

    //return user input
    return value; //wer auch immer die Funktion get_short aufruft bekomm "value" zurück
}

