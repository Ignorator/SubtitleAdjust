#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct felirat{
	int sorszam;
	char idotartam[30+1];
	char elsosor[100+1];
	char masodiksor[100+1];
	char uressor;
	struct felirat *next;
	struct felirat *prev;
}felirat;

felirat *stra1;
felirat *stra2;

felirat* inicializalas()
{
	stra1=(felirat*)malloc(sizeof(felirat));
		if(stra1==NULL){
			printf("Nem sikerult a memoriafoglalas\n");
			return;}

	stra2=(felirat*)malloc(sizeof(felirat));
		if(stra2==NULL){
			printf("Nem sikerult a memoriafoglalas\n");
			return;}
stra1->sorszam=-1;
stra1->idotartam[0]=0;
stra1->idotartam[1]='\0';
stra1->elsosor[0]=0;
stra1->elsosor[1]='\0';
stra1->masodiksor[0]=0;
stra1->masodiksor[1]='\0';
stra1->uressor=0;
stra1->next=stra2;
stra1->prev=NULL;

stra2->sorszam=-1;
stra2->idotartam[0]=0;
stra2->idotartam[1]='\0';
stra2->elsosor[0]=0;
stra2->elsosor[1]='\0';
stra2->masodiksor[0]=0;
stra2->masodiksor[1]='\0';
stra2->uressor=0;
stra2->next=NULL;
stra2->prev=stra1;

return stra1;
}

void beolvasas(felirat*str1, felirat*str2)
{
	felirat*act=str1;
	felirat*ujfelirat;
	char ujsor;
	FILE* feliratp=fopen("felirat.txt", "r");
	if(feliratp==NULL){
		printf("Nem sikerult a feliratfajl beolvasasa!\n");
		return;}
	while(!feof(feliratp)){
		ujfelirat=(felirat*)malloc(sizeof(felirat));
		fscanf(feliratp,"%d", &ujfelirat->sorszam);
		fscanf(feliratp, "%c", &ujsor);
		fgets(ujfelirat->idotartam, 30, feliratp);
		if ((strlen(ujfelirat->idotartam) > 0) && (ujfelirat->idotartam[strlen (ujfelirat->idotartam) - 1] == '\n')){
			ujfelirat->idotartam[strlen (ujfelirat->idotartam) - 1] = '\0';}
		fscanf(feliratp, "%c", &ujsor);
		fgets(ujfelirat->elsosor, 100, feliratp);
		if ((strlen(ujfelirat->elsosor) > 0) && (ujfelirat->elsosor[strlen (ujfelirat->elsosor) - 1] == '\n')){
			ujfelirat->elsosor[strlen (ujfelirat->elsosor) - 1] = '\0';}
		fgets(ujfelirat->masodiksor, 100, feliratp);
		if(ujfelirat->masodiksor[0]=='\n'){
			ujfelirat->masodiksor[0]='\0';
			ujfelirat->uressor='\n';}
		else
		{
			fscanf(feliratp, "%c", &ujfelirat->uressor);
			if ((strlen(ujfelirat->masodiksor) > 0) && (ujfelirat->masodiksor[strlen (ujfelirat->masodiksor) - 1] == '\n')){
			ujfelirat->masodiksor[strlen (ujfelirat->masodiksor) - 1] = '\0';}
		}
		while(act->next!=NULL){
			act=act->next;}				//act így a stra2-re mutat
		ujfelirat->next=act;
		ujfelirat->prev=act->prev;
		act->prev->next=ujfelirat;
		act->prev=ujfelirat;
	}
	fclose(feliratp);
}

void kiir(felirat*stra1, felirat*stra2)
{
	felirat*act=stra1->next;
	FILE*feliratp=fopen("felirat2.txt", "w");
	if(feliratp==NULL){
		printf("Nem sikerult a feliratfajl letrehozasa!\n");
		return;}
	while(act->next!=NULL){
		fprintf(feliratp, "%d", act->sorszam);
		fprintf(feliratp, "\n");
		fprintf(feliratp, "%s", act->idotartam);
		fprintf(feliratp, "\n");
		fprintf(feliratp, "%s", act->elsosor);
		if(act->masodiksor[0]=='\0'){
			fprintf(feliratp, "\n");
		}
		else{
			fprintf(feliratp, "\n");
			fprintf(feliratp, "%s", act->masodiksor);
			fprintf(feliratp, "\n");
		}
		fprintf(feliratp, "\n");
		act=act->next;
	}
	fclose(feliratp);
}


void atir(felirat*stra1, felirat*stra2)
{
	char felbeszakit[12]={'f','e','l','b','e','s','z','a','k','i','t','\0'};
	char buffer[200+1];
	felirat*act=stra1->next;
	while(act->next!=NULL){

		if((strcmp(felbeszakit, act->elsosor)==0) || (strcmp(felbeszakit, act->masodiksor)==0))
			break;
	act=act->next;
	}
	if(act->next==NULL)
		act=stra1->next;


	printf("Kezdje el begepelni a feliratokat.\n");
	printf("A program lecsereli a szoveget meghagyva az idozitest.\n");

	while(act->next!=NULL)
	{
		printf("A %d. sor\n", act->sorszam);
		printf("elso sora:\n");
		fgets(buffer, 200, stdin);
		if ((strlen(buffer) > 0) && (buffer[strlen (buffer) - 1] == '\n')){
			buffer[strlen (buffer) - 1] = '\0';}
		if(strcmp(buffer,felbeszakit)==0){
			strcpy(act->elsosor, buffer);
			return;}

		strcpy(act->elsosor, buffer);

		if(act->masodiksor[0]!='\0')
		{
			printf("Masodik sora:\n");
			fgets(buffer, 200, stdin);
			if ((strlen(buffer) > 0) && (buffer[strlen (buffer) - 1] == '\n')){
				buffer[strlen (buffer) - 1] = '\0';}
			if(strcmp(buffer,felbeszakit)==0){
				strcpy(act->masodiksor, buffer);
				return;}

		strcpy(act->masodiksor, buffer);
		

		}
		act=act->next;
	}


}

void felszabadit(felirat* stra1){
	felirat*act=stra1;
	felirat*act2;
	while(act->next!=NULL)
	{
		act2=act->next;
		free(act);
		act=act2;
	}
}


int main(){
	stra1=inicializalas();
	stra2=stra1->next;
	beolvasas(stra1, stra2);
	atir(stra1, stra2);
	kiir(stra1, stra2);
	felszabadit(stra1);
	free(stra2);


return 0;
}