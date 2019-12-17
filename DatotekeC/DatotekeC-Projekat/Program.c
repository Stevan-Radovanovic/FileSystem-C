#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
/*
	Poslednje dve include naredbe su uvedene za slucaj da nam
	je potreban neki veci rad sa stringovima, ili postavljanje pocetne vrednosti
	pri trazenju nekog maksimuma
*/

/*
	Sledi odeljak za strukture, u kome ce biti predstavljene strukture 
	proizvoda i promene stanja
*/
typedef struct proizvod {
	int sifra;
	char naziv[20];
	double cena;
	int stanje;
} proizvod;

typedef struct promena {
	int sifra;
	char tip; /*U za povecanje stanja (Ulaz), I za smanjenje stanja (Izlaz)*/
	int kolicina;
} promena;

/*
	Sledi odeljak za definiciju globalnih pokazivaca na fajlove koje cemo koristiti u aplikaciji
*/
FILE* datotekaProizvoda = NULL;
FILE* datotekaPromena = NULL;

/*
	Radi preglednosti, sve funkcije ce biti deklarisane iznad main funkcije,
	a njihov kod ce biti iskucan ispod main funkcije

*/
void meni();
void podmeniKreiraj();
void podmeniPrikazi();
void podmeniObrisi();
void podmeniAzuriraj();
void kreirajDatotekuProizvoda();
void kreirajDatotekuPromena();
void prikaziDatotekuProizvoda();
void prikaziDatotekuPromena();
void obrisiDatotekuProizvoda();
void obrisiDatotekuPromena();
void dodajNoviProizvod();
void dodajNovuPromenuStanja();
void obrisiPostojeciProizvod();
void obrisiPostojecuPromenuStanja();
void azurirajDatotekuProizvoda();

void main() {

	//uvodna poruka uz pauzu pre prikaza glavnog menija
	printf("Dobrodosli u aplikaciju!\n");
	system("pause");
	system("cls");

	meni();

}

/*
	Funkcija iz koje ce se pozivati ostale funkcije sve dok korisnik ne odluci
	da zeli da prekine proces. Prvih nekoliko printf naredbi predstavljaju vizuelni deo menija,
	dok nakon toga korisnicki odabir prolazi kroz switch koji dalje poziva funkcije
*/
void meni() {
	system("cls");
	int odabir;
	while (1 == 1) {

		printf("********************************\n");
		printf("*         Glavni meni          *\n");
		printf("* 1. Kreiraj datoteke          *\n");
		printf("* 2. Prikazi datoteke          *\n");
		printf("* 3. Azuriraj datoteke         *\n");
		printf("* 4. Izbrisi datoteke          *\n");
		printf("* 5. Izlazak iz aplikacije     *\n");
		printf("********************************\n");
		printf("Vas odabir? ");

		scanf("%d", &odabir);

		switch (odabir) {
			case 1: podmeniKreiraj(); break;

			case 2: podmeniPrikazi(); break;

			case 3: podmeniAzuriraj(); break;

			case 4: podmeniObrisi(); break;

			case 5: {
				printf("Dovidjenja!\n");
				system("pause");
				return;
			}

			default: {
				printf("Uneli ste nepostojecu vrednost, pokusajte ponovo.\n"); 
				break;
			}
		}

		system("pause");
		system("cls");
	}

}

/*
	Funkcija funkcionise isto kao funkcija meni, vrsi dalji poziv funkcija
*/
void podmeniKreiraj() {

	system("cls");
	int odabir;

	while (1 == 1) {

		printf("********************************\n");
		printf("*         Meni 'Kreiraj'       *\n");
		printf("* 1. Kreiraj datoteku proizvoda*\n");
		printf("* 2. Kreiraj datoteku promena  *\n");
		printf("* 3. Povratak u glavni meni    *\n");
		printf("********************************\n");
		printf("Vas odabir? ");

		scanf("%d", &odabir);

		switch (odabir) {
			case 1: kreirajDatotekuProizvoda(); break;

			case 2: kreirajDatotekuPromena(); break;

			case 3: return;

			default: {
				printf("Uneli ste nepostojecu vrednost, pokusajte ponovo.\n");
				break;
			}
		}

		system("pause");
		system("cls");
	}
}

/*
	Funkcija funkcionise isto kao funkcija meni, vrsi dalji poziv funkcija
*/
void podmeniObrisi() {

	system("cls");
	int odabir;

	while (1 == 1) {

		printf("********************************\n");
		printf("*         Meni 'Obrisi'        *\n");
		printf("* 1. Obrisi datoteku proizvoda *\n");
		printf("* 2. Obrisi datoteku promena   *\n");
		printf("* 3. Povratak u glavni meni    *\n");
		printf("********************************\n");
		printf("Vas odabir? ");

		scanf("%d", &odabir);

		switch (odabir) {
		case 1: obrisiDatotekuProizvoda(); break;

		case 2: obrisiDatotekuPromena(); break;

		case 3: return;

		default: {
			printf("Uneli ste nepostojecu vrednost, pokusajte ponovo.\n");
			break;
		}
		}

		system("pause");
		system("cls");
	}
}


/*
	Funkcija funkcionise isto kao funkcija meni, vrsi dalji poziv funkcija
*/
void podmeniPrikazi() {
	system("cls");
	int odabir;

	while (1 == 1) {

		printf("********************************\n");
		printf("*         Meni 'Prikazi'       *\n");
		printf("* 1. Prikazi datoteku proizvoda*\n");
		printf("* 2. Prikazi datoteku promena  *\n");
		printf("* 3. Povratak u glavni meni    *\n");
		printf("********************************\n");
		printf("Vas odabir? ");

		scanf("%d", &odabir);

		switch (odabir) {
			case 1: prikaziDatotekuProizvoda(); break;

			case 2: prikaziDatotekuPromena(); break;

			case 3: return;

			default: {
				printf("Uneli ste nepostojecu vrednost, pokusajte ponovo.\n");
				break;
			}
		}

		system("pause");
		system("cls");
	}
}

/*
	Funkcija funkcionise isto kao funkcija meni, vrsi dalji poziv funkcija
*/
void podmeniAzuriraj() {

	system("cls");
	int odabir;

	while (1 == 1) {

		printf("**********************************\n");
		printf("*         Meni 'Azuriraj'        *\n");
		printf("* 1. Dodaj novi proizvod         *\n");
		printf("* 2. Registruj promenu stanja    *\n");
		printf("* 3. Obrisi postojeci proizvod   *\n");
		printf("* 4. Obrisi promenu stanja       *\n");
		printf("* 5. Azuriraj datoteku proizvoda *\n");
		printf("* 6. Povratak u glavni meni      *\n");
		printf("**********************************\n");
		printf("Vas odabir? ");

		scanf("%d", &odabir);

		switch (odabir) {
		case 1: dodajNoviProizvod(); break;

		case 2: dodajNovuPromenuStanja(); break;
			
		case 3: obrisiPostojeciProizvod(); break;

		case 4: obrisiPostojecuPromenuStanja(); break;

		case 5: azurirajDatotekuProizvoda(); break;

		case 6: return;

		default: {
			printf("Uneli ste nepostojecu vrednost, pokusajte ponovo.\n");
			break;
		}
		}

		system("pause");
		system("cls");
	}
}

/*
	Funkcija za kreiranje binarne datoteke
*/
void kreirajDatotekuProizvoda() {

	if (datotekaProizvoda != NULL) {
		printf("Datoteka je vec kreirana ranije, ponovno kreiranje je nemoguce\n");
		return;
	}

	datotekaProizvoda = fopen("Proizvod.dat", "wb");
	fclose(datotekaProizvoda);

	printf("Datoteka proizvoda je kreirana\n");
}

/*
	Funkcija za kreiranje binarne datoteke
*/
void kreirajDatotekuPromena() {

	if (datotekaPromena != NULL) {
		printf("Datoteka je vec kreirana ranije, ponovno kreiranje je nemoguce\n");
		return;
	}

	datotekaPromena = fopen("Promena.dat", "wb");
	fclose(datotekaPromena);

	printf("Datoteka promena je kreirana\n");
}

/*
	Funkcija za prikaz binarne datoteke
*/
void prikaziDatotekuProizvoda() {

		int i = 0;
		proizvod P;
		
		if (datotekaProizvoda == NULL) {
			printf("Datoteka nije kreirana\n");
			return;
		}

		printf("\nPrikaz proizvoda:\n");

		while (fread(&P, sizeof(proizvod),1,datotekaProizvoda) != 0) {
			printf("%2d|%20s|%5lf|%4d\n" , P.sifra, P.naziv, P.cena, P.stanje); i++;
		}

		if (i == 0) printf("   Datoteka je prazna\n");

		fclose(datotekaProizvoda);
}

/*
	Funkcija za prikaz binarne datoteke
*/
void prikaziDatotekuPromena() {

		int i = 0;
		promena P;

		if (datotekaPromena == NULL) {
			printf("Datoteka nije kreirana\n");
			return;
		}

		printf("\nPrikaz promena:\n");

		while (fread(&P, sizeof(promena), 1, datotekaPromena) != 0) {
			printf("%2d|%2c|%3d\n", P.sifra, P.tip, P.kolicina); i++;
		}

		if (i == 0) printf("   Datoteka je prazna\n");

		fclose(datotekaPromena);
}

/*
	Funkcija za brisanje binarne datoteke
*/
void obrisiDatotekuProizvoda() {

	if (datotekaProizvoda == NULL) {
		printf("Datoteka jos uvek nije kreirana\n");
		return;
	}
	datotekaProizvoda = fopen("Proizvod.dat", "wb");
	datotekaProizvoda = NULL;

	printf("Datoteka proizvoda je obrisana\n");
}

/*
	Funkcija za brisanje binarne datoteke
*/
void obrisiDatotekuPromena() {

	if (datotekaPromena == NULL) {
		printf("Datoteka jos uvek nije kreirana\n");
		return;
	}

	datotekaPromena = fopen("Promena.dat", "wb");
	datotekaPromena = NULL;

	printf("Datoteka promena je obrisana\n");
}

void dodajNoviProizvod() {
	printf("Funkcija nije implementirana\n");
}

void dodajNovuPromenuStanja() {
	printf("Funkcija nije implementirana\n");
}

void obrisiPostojeciProizvod() {
	printf("Funkcija nije implementirana\n");
}

void obrisiPostojecuPromenuStanja() {
	printf("Funkcija nije implementirana\n");
}

void azurirajDatotekuProizvoda() {
	printf("Funkcija nije implementirana\n");
}
