/*
	Azuriranje datoteke proizvoda
*/

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
FILE* greske = NULL;

/*
	GLobalni signal koji nam pokazuje da li su promene stanja azurirane
*/
int azuriranePromene = 0;

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
void azurirajDatotekuPromena();
void pretraziDatotekuPromena();
void pretraziDatotekuProizvoda();

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

		printf("*********************************\n");
		printf("*         Meni 'Prikazi'        *\n");
		printf("* 1. Prikazi datoteku proizvoda *\n");
		printf("* 2. Prikazi datoteku promena   *\n");
		printf("* 3. Pretrazi datoteku proizvoda*\n");
		printf("* 4. Pretrazi datoteku promena  *\n");
		printf("* 5. Povratak u glavni meni     *\n");
		printf("*********************************\n");
		printf("Vas odabir? ");

		scanf("%d", &odabir);

		switch (odabir) {
			case 1: prikaziDatotekuProizvoda(); break;

			case 2: prikaziDatotekuPromena(); break;

			case 3: pretraziDatotekuProizvoda(); break;

			case 4: pretraziDatotekuPromena(); break;

			case 5: return;

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
		printf("* 6. Azuriraj datoteku promena   *\n");
		printf("* 7. Povratak u glavni meni      *\n");
		printf("**********************************\n");
		printf("Vas odabir? ");

		scanf("%d", &odabir);

		switch (odabir) {
		case 1: dodajNoviProizvod(); break;

		case 2: dodajNovuPromenuStanja(); break;
			
		case 3: obrisiPostojeciProizvod(); break;

		case 4: obrisiPostojecuPromenuStanja(); break;

		case 5: azurirajDatotekuProizvoda(); break;

		case 6: azurirajDatotekuPromena(); break;

		case 7: return;

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

		datotekaProizvoda = fopen("Proizvod.dat","rb");

		while (fread(&P, sizeof(proizvod),1,datotekaProizvoda) != 0) {
			printf("%2d|%20s|%5.2lf|%4d\n" , P.sifra, P.naziv, P.cena, P.stanje); i++;
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

		datotekaPromena = fopen("Promena.dat", "rb");

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

	int odabir;
	printf("Da li ste sigurni? 1 za DA, 2 za NE? ");
	scanf("%d", &odabir);

	switch (odabir) {
	case 1: break;
	case 2: printf("Brisanje ponisteno\n"); return;
	default: printf("Uneli ste nepostojecu vrednost, brisanje ponisteno\n"); return;
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

	int odabir;
	printf("Da li ste sigurni? 1 za DA, 2 za NE? ");
	scanf("%d", &odabir);

	switch (odabir) {
	case 1: break;
	case 2: printf("Brisanje ponisteno\n"); return;
	default: printf("Uneli ste nepostojecu vrednost, brisanje ponisteno\n"); return;
	}

	datotekaPromena = fopen("Promena.dat", "wb");
	datotekaPromena = NULL;

	printf("Datoteka promena je obrisana\n");
}

/*
	Funkcija za dodavanje proizvoda u binarnu datoteku
*/
void dodajNoviProizvod() {

	if (datotekaProizvoda == NULL) {
		printf("Datoteka jos uvek nije kreirana\n");
		return;
	}

	proizvod p;
	datotekaProizvoda = fopen("Proizvod.dat", "a+b");

	printf("Dodavanje novog proizvoda: \n");
	printf("Unesite sifru: ");
	scanf("%d", &p.sifra);
	getchar();
	printf("Unesite naziv: ");
	gets(p.naziv);
	printf("Unesite cenu: ");
	scanf(" %lf", &p.cena);
	getchar();
	printf("Unesite stanje: ");
	scanf("%d", &p.stanje);
	getchar();

	printf("\nProizvod je uspesno unet u datoteku!\n");

	fwrite(&p, sizeof(proizvod), 1, datotekaProizvoda);
	fclose(datotekaProizvoda);
}

/*
	Funkcija za dodavanje promena u binarnu datoteku
*/
void dodajNovuPromenuStanja() {

	if (datotekaPromena == NULL) {
		printf("Datoteka jos uvek nije kreirana\n");
		return;
	}

	promena p;
	datotekaPromena = fopen("Promena.dat", "a+b");

	printf("Dodavanje nove promene stanja: \n");
	printf("Unesite sifru: ");
	scanf("%d", &p.sifra);
	getchar();
	printf("Ukoliko dodajete kolicinu na stanje, ukucajte U. U suprotnom, ukucajte I: ");
	scanf(" %c", &p.tip);
	getchar();
	printf("Unesite kolicinu: ");
	scanf(" %d", &p.kolicina);
	getchar();

	printf("\Promena je uspesno uneta u datoteku!\n");

	fwrite(&p, sizeof(promena), 1, datotekaPromena);
	fclose(datotekaPromena);
	azuriranePromene = 0;
}

/*
	Funkcija za brisanje proizvoda iz binarne datoteke
*/
void obrisiPostojeciProizvod() {
	
	if (datotekaProizvoda == NULL) {
		printf("Datoteka nije kreirana\n");
		return;
	}

	FILE* privremenaDatoteka;
	int nadjen = 0;
	int sifraZaBrisanje;
	char novoIme[] = "Proizvod.dat";
	char staroIme[] = "Privremena.dat";
	datotekaProizvoda = fopen("Proizvod.dat", "rb");
	privremenaDatoteka = fopen("Privremena.dat", "wb");
	proizvod p;

	printf("Sifra proizvoda koji zelite da obrisete:\n");
	scanf("%d", &sifraZaBrisanje);

	while (fread(&p, sizeof(proizvod), 1, datotekaProizvoda))
	{
		if (sifraZaBrisanje!=p.sifra)
		{
			fwrite(&p, sizeof(proizvod), 1, privremenaDatoteka);

		}
		else {
			nadjen = 1;
			printf("Pronadjen je proizvod sa istom sifrom, i zatim je obrisan.\n");

		}

	}

	if (nadjen==0) {
		printf("Nije pronadjen proizvod sa istom sifrom.\n");

	}

	fclose(datotekaProizvoda);
	fclose(privremenaDatoteka);
	remove(novoIme);
	rename(staroIme, novoIme);

}

/*
	Funkcija za brisanje promene iz binarne datoteke
*/
void obrisiPostojecuPromenuStanja() {

	if (datotekaPromena == NULL) {
		printf("Datoteka nije kreirana\n");
		return;
	}

	FILE* privremenaDatoteka;
	int nadjen = 0;
	int sifraZaBrisanje;
	char novoIme[] = "Promena.dat";
	char staroIme[] = "Privremena.dat";
	datotekaPromena = fopen("Promena.dat", "rb");
	privremenaDatoteka = fopen("Privremena.dat", "wb");
	promena p;

	printf("Sifra promene koju zelite da obrisete:\n");
	scanf("%d", &sifraZaBrisanje);

	while (fread(&p, sizeof(promena), 1, datotekaPromena))
	{
		if (sifraZaBrisanje != p.sifra)
		{
			fwrite(&p, sizeof(promena), 1, privremenaDatoteka);

		}
		else {
			nadjen = 1;
			printf("Pronadjena je promena sa istom sifrom, i zatim je obrisana.\n");
		}

	}

	if (nadjen == 0) {
		printf("Nije pronadjena promena sa istom sifrom.\n");

	}

	fclose(datotekaPromena);
	fclose(privremenaDatoteka);
	remove(novoIme);
	rename(staroIme, novoIme);

}

/*
	Funkcija za azuriranje proizvoda u binaranoj datoteci
*/
void azurirajDatotekuProizvoda() {
	
	int i = 0;
	promena P;
	proizvod pr;

	char staroIme[] = "Privremena.dat";
	char novoIme[] = "Proizvod.dat";

	if (datotekaProizvoda == NULL) {
		printf("Datoteka nije kreirana\n");
		return;
	}

	if (azuriranePromene == 0) {
		printf("Morate prvo azurirati datoteku promena\n");
		return;
	}

	FILE* privremenaDatoteka = fopen(staroIme, "w+b");
	datotekaProizvoda = fopen("Proizvod.dat", "r+b");
	datotekaPromena= fopen("Promena.dat", "r+b");
	greske = fopen("Greske.txt", "w+");

	while (fread(&P, sizeof(promena), 1, datotekaPromena)) {

		int uspesno = 0;

		while (fread(&pr, sizeof(proizvod), 1, datotekaProizvoda)) {

			if (pr.sifra == P.sifra) {
				proizvod glavni;
				glavni.sifra = pr.sifra;
				glavni.stanje = pr.stanje;
				glavni.cena = pr.cena;
				strcpy(glavni.naziv, pr.naziv);

				if (P.tip == 'u' || P.tip == 'U') {
					glavni.stanje += P.kolicina;
				}
				else {
					glavni.stanje -= P.kolicina;
				}

				if(glavni.stanje>=0) {
					fwrite(&glavni, sizeof(proizvod), 1, privremenaDatoteka);
					uspesno = 1;
				}
				else {
					fwrite(&pr, sizeof(proizvod), 1, privremenaDatoteka);
				}
			}
		}

		if (uspesno == 0) {
			fprintf(greske,"Doslo je do greske pri ubacivanju date promene: %2d|%2c|%2d\n",
				P.sifra, P.tip, P.kolicina);
		}


		fseek(datotekaProizvoda, 0, SEEK_SET);
	}

	fclose(greske);
	fclose(datotekaPromena);
	fclose(datotekaProizvoda);
	fclose(privremenaDatoteka);
	remove(novoIme);
	rename(staroIme, novoIme);
	printf("Datoteka proizvoda je azurirana\n");
	return;

}

/*
	Funkcija za azuriranje promena u binaranoj datoteci
*/
void azurirajDatotekuPromena() {

	int i = 0;
	promena P;

	char staroIme[] = "Privremena.dat";
	char novoIme[] = "Promena.dat";

	if (datotekaPromena == NULL) {
		printf("Datoteka nije kreirana\n");
		return;
	}


	FILE* privremenaDatoteka = fopen(staroIme, "w+b");
	datotekaPromena = fopen("Promena.dat","rb");

	int brojac = 1;
	int nizGotovih[100]; int brN = 0;
	int read;

	while (1 == 1) {

		fseek(datotekaPromena, 0, SEEK_SET);

		for (int i = 1; i <= brojac; i++)
			read = fread(&P, sizeof(promena), 1, datotekaPromena);

		if (read == 0) {
			fclose(datotekaPromena);
			fclose(privremenaDatoteka);
			remove(novoIme);
			rename(staroIme, novoIme);
			printf("Datoteka promena je azurirana\n");
			azuriranePromene = 1;
			return;			
		}

		brojac++;
		int signal = 1;
		for (int i = 0; i < brN; i++) {
			if (P.sifra == nizGotovih[i]) signal = 0;
		}

		if (signal == 0) continue;

		nizGotovih[brN++] = P.sifra;
		promena glavna;
		glavna.sifra = P.sifra;
		glavna.kolicina = P.kolicina;
		glavna.tip = P.tip;

		if (glavna.tip == 'U' || glavna.tip == 'u') glavna.kolicina = P.kolicina;
		else glavna.kolicina = -P.kolicina;


		while (fread(&P, sizeof(promena), 1, datotekaPromena) != 0) {
			if (glavna.sifra == P.sifra) {
				if (P.tip == 'U' || P.tip == 'u') glavna.kolicina += P.kolicina;
				else glavna.kolicina -= P.kolicina;
			}
		}

		if (glavna.kolicina > 0) 
					glavna.tip = 'u';
		else {
			glavna.tip = 'i';
			glavna.kolicina = -glavna.kolicina;
		}

		fwrite(&glavna, sizeof(promena), 1, privremenaDatoteka);
		
	}



}

/*
	Funkcija za pretrazivanje promena u binaranoj datoteci
*/
void pretraziDatotekuPromena() {

	int i = 0;
	promena P;
	int unetaSifra;

	if (datotekaPromena == NULL) {
		printf("Datoteka nije kreirana\n");
		return;
	}

	datotekaProizvoda = fopen("Promena.dat", "rb");

	printf("Unesite sifru po kojoj pretrazujete: ");
	scanf("%d", &unetaSifra);

	printf("\nPromene sa datom sifrom:\n");

	while (fread(&P, sizeof(promena), 1, datotekaPromena) != 0) {
		if (P.sifra == unetaSifra)
		{
			printf("%2d|%2c|%3d\n", P.sifra, P.tip, P.kolicina); i++;
		}
	}

	if (i == 0) printf("   Ne postoje promene sa datom sifrom\n");

	fclose(datotekaPromena);
}

/*
	Funkcija za pretrazivanje proizvoda u binaranoj datoteci
*/
void pretraziDatotekuProizvoda() {

	int i = 0;
	proizvod P;
	int unetaSifra;

	if (datotekaProizvoda == NULL) {
		printf("Datoteka nije kreirana\n");
		return;
	}

	printf("Unesite sifru po kojoj pretrazujete: ");
	scanf("%d", &unetaSifra);

	printf("\nProizvodi sa zadatom sifrom:\n");

	datotekaProizvoda = fopen("Proizvod.dat", "rb");

	while (fread(&P, sizeof(proizvod), 1, datotekaProizvoda) != 0) {
		if (P.sifra == unetaSifra) 
		{
			printf("%2d|%20s|%5.2lf|%4d\n", P.sifra, P.naziv, P.cena, P.stanje); 
			i++;
		}
	}

	if (i == 0) printf("   Ne postoji proizvod sa zadatom sifrom\n");

	fclose(datotekaProizvoda);
}