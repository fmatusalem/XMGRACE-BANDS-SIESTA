/*BY FILIPE MATUSALEM, JUNE 2019     filipematus@gmail.com */
/*To compile use: g++ -o fmgraceband-siesta fmgraceband-siesta-v1.c*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



int main(int argc, char *argv[])
{
FILE *siesta_bands,*xmgrace;
float ref,efermi,kmin,kmax,Emin,Emax,min,max,a;
int i,j,k,nbands,kpts,spin,simpt;
char str[150],ch;


printf("\nPROGRAM TO GENERATE GRACE BAND STRUCTURES FROM SIESTA RESULTS (NON-SPIN)\n\n");
printf("Usage: fmgraceband-siesta SIESTALABEL.band or fmgraceband-siesta SIESTALABEL.band fermi to set zero energy to Fermi level. \n");
printf("To set yaxis range use:  fmgraceband-siesta SIESTALABEL.band fermi -10 10\n\n");
printf("by Filipe Matusalem - June 2019\n");

printf("-----------------------------------------------------------------------------------------------\n\n");

if( argc < 2 ){
printf("\n\n");
printf("EEEEEEE   RRRRRRRR   RRRRRRRR   OOOOOOO   RRRRRRRR\n");
printf("EE        RR    RR   RR    RR   OO   OO   RR    RR\n");
printf("EE        RR    RR   RR    RR   OO   OO   RR    RR\n");
printf("EEEE      RRRRRRRR   RRRRRRRR   OO   OO   RRRRRRRR\n");
printf("EE        RRRR       RRRR       OO   OO   RRRR\n");
printf("EE        RR  RR     RR  RR     OO   OO   RR  RR\n");
printf("EEEEEEE   RR    RR   RR    RR   OOOOOOO   RR    RR\n\n");

printf("Enter the SIESTALABEL.band as argument for the program! e.g. fmgraceband-siesta SIESTALABEL.band\n");
printf("\n\n"); exit(0);}

strcpy(str,argv[1]);

siesta_bands = fopen(str,"r"); /* Arquivo ASCII, para leitura */
if(!siesta_bands)
{
printf( "Error opening SIESTALABEL.band file\n");
exit(0);
}

fscanf(siesta_bands,"%f",&efermi);
fscanf(siesta_bands,"%f",&kmin);
fscanf(siesta_bands,"%f",&kmax);
fscanf(siesta_bands,"%f",&Emin);
fscanf(siesta_bands,"%f",&Emax);
fscanf(siesta_bands,"%d",&nbands);
fscanf(siesta_bands,"%d",&spin);
fscanf(siesta_bands,"%d",&kpts);

if( argc > 2 ){
if(strcmp(argv[2],"fermi")==0)ref=efermi;
else {ref=atof(argv[2]);}}


if(argc > 3){
min = atof(argv[3]);
max = atof(argv[4]);}
else {
min=(efermi-ref)-5;max=(efermi-ref)+5;
}

xmgrace = fopen("GRACE-BAND.agr","w"); /* Arquivo ASCII, para escrita */
if(!xmgrace)
{
printf( "Error creating GRACE-BAND.agr file\n");
exit(0);
}

do
ch = getc(siesta_bands);              /*chega ao fim da linha*/
while(ch!='\n');

float mtx[kpts][nbands+1];

for(i=0;i<kpts;i++)for(j=0;j<nbands+1;j++)fscanf(siesta_bands,"%f",&mtx[i][j]);

fscanf(siesta_bands,"%d",&simpt);

float pts[simpt];
char label[simpt][20];

for(i=0;i<simpt;i++){
fscanf(siesta_bands,"%f",&pts[i]);
fscanf(siesta_bands,"%s",label[i]);
}

for(i=0;i<simpt;i++)sscanf(label[i],"\'%[^\']",label[i]);  /*para eliminar apóstrofos. sscanf lê a partir de ' até '*/

fprintf(xmgrace,"# Grace project file\n");
fprintf(xmgrace,"#\n");
fprintf(xmgrace,"@version 50125\n");
fprintf(xmgrace,"@map font 4 to \"Times-Roman\", \"Times-Roman\"\n");
fprintf(xmgrace,"@map font 8 to \"Symbol\", \"Symbol\"\n");
fprintf(xmgrace,"@g0 on\n");
fprintf(xmgrace,"@g0 type XY\n");
fprintf(xmgrace,"@with g0\n");
fprintf(xmgrace,"@    stack world 0, 0, 0, 0\n");
fprintf(xmgrace,"@    view 0.150000, 0.150000, 0.850000, 0.850000\n");

fprintf(xmgrace,"@    world 0,   %f, %f,     %f\n",min,pts[simpt-1]/kmax,max);

for(i=0;i<nbands;i++){
fprintf(xmgrace,"@    s%d line linestyle 1\n",i);
fprintf(xmgrace,"@    s%d line color 1\n",i);
}

for(i=nbands;i<nbands+simpt;i++){
fprintf(xmgrace,"@    s%d line linestyle 3\n",i);
fprintf(xmgrace,"@    s%d line color 1\n",i);
}


fprintf(xmgrace,"@    xaxis  on\n");
fprintf(xmgrace,"@    xaxis  tick off\n");
fprintf(xmgrace,"@    xaxis  tick major 0.4\n");
fprintf(xmgrace,"@    xaxis  tick minor ticks 1\n");
fprintf(xmgrace,"@    xaxis  label \"\"\n");
fprintf(xmgrace,"@    xaxis  label place spec\n");
fprintf(xmgrace,"@    xaxis  label place 0.000000, -0.13\n");
fprintf(xmgrace,"@    xaxis  label font 4\n");
fprintf(xmgrace,"@    xaxis  label color 1\n");
fprintf(xmgrace,"@    xaxis  label char size 1.50000\n");
fprintf(xmgrace,"@    xaxis  ticklabel off\n");
fprintf(xmgrace,"@    xaxis  ticklabel prec 6\n");
fprintf(xmgrace,"@    xaxis  ticklabel op bottom\n");
fprintf(xmgrace,"@    xaxis  ticklabel font 4\n");
fprintf(xmgrace,"@    xaxis  ticklabel color 1\n");
fprintf(xmgrace,"@    xaxis  ticklabel char size 1.50000\n");
fprintf(xmgrace,"@    xaxis  tick major off\n");
fprintf(xmgrace,"@    xaxis  tick minor off\n");
fprintf(xmgrace,"@    xaxis  tick out\n");
fprintf(xmgrace,"@    xaxis  tick major color 1\n");
fprintf(xmgrace,"@    xaxis  tick major linestyle 1\n");
fprintf(xmgrace,"@    xaxis  tick minor color 1\n");
fprintf(xmgrace,"@    xaxis  tick minor linestyle 1\n");
fprintf(xmgrace,"@    xaxis  tick size 0.500000\n");
fprintf(xmgrace,"@    xaxis  tick minor size 0.500000\n");
fprintf(xmgrace,"@    xaxis  tick op bottom\n");

fprintf(xmgrace,"@    yaxis  on\n");
fprintf(xmgrace,"@    yaxis  tick on\n");
fprintf(xmgrace,"@    yaxis  tick major 1\n");
fprintf(xmgrace,"@    yaxis  tick minor ticks 1\n");
fprintf(xmgrace,"@    yaxis  label \"Energy (eV)\"\n");
fprintf(xmgrace,"@    yaxis  label font 4\n");
fprintf(xmgrace,"@    yaxis  label color 1\n");
fprintf(xmgrace,"@    yaxis  label char size 1.50000\n");
fprintf(xmgrace,"@    yaxis  ticklabel on\n");
fprintf(xmgrace,"@    yaxis  ticklabel prec 6\n");
fprintf(xmgrace,"@    yaxis  ticklabel op left\n");
fprintf(xmgrace,"@    yaxis  ticklabel font 4\n");
fprintf(xmgrace,"@    yaxis  ticklabel color 1\n");
fprintf(xmgrace,"@    yaxis  ticklabel char size 1.50000\n");
fprintf(xmgrace,"@    yaxis  tick major on\n");
fprintf(xmgrace,"@    yaxis  tick minor on\n");
fprintf(xmgrace,"@    yaxis  tick out\n");
fprintf(xmgrace,"@    yaxis  tick major color 1\n");
fprintf(xmgrace,"@    yaxis  tick major linestyle 1\n");
fprintf(xmgrace,"@    yaxis  tick minor color 1\n");
fprintf(xmgrace,"@    yaxis  tick minor linestyle 1\n");
fprintf(xmgrace,"@    yaxis  tick size 0.750000\n");
fprintf(xmgrace,"@    yaxis  tick minor size 0.500000\n");
fprintf(xmgrace,"@    yaxis  tick op left\n");
fprintf(xmgrace,"@    legend off\n");
fprintf(xmgrace,"@    frame on\n");
fprintf(xmgrace,"@    frame linestyle 1\n");
fprintf(xmgrace,"@    frame color 1\n");
fprintf(xmgrace,"@    frame background color 0\n");

for(i=0;i<simpt;i++){
fprintf(xmgrace,"@with string\n");
fprintf(xmgrace,"@    string on\n");
fprintf(xmgrace,"@    string loctype world\n");
/*fprintf(xmgrace,"@    string g0\n");*/
fprintf(xmgrace,"@    string %.4f, %.4f\n",pts[i]/kmax-0.02,1.1*min);
fprintf(xmgrace,"@    string color 1\n");
fprintf(xmgrace,"@    string rot 0\n");
fprintf(xmgrace,"@    string font 4\n");
fprintf(xmgrace,"@    string just 0\n");
fprintf(xmgrace,"@    string char size 1.500000\n");
fprintf(xmgrace,"@    string def \"%s\"\n",label[i]);}



for(j=1;j<nbands+1;j++){
    fprintf(xmgrace,"@target G0.S%d\n",j-1);
    fprintf(xmgrace,"@type xy\n");
       for(i=0;i<kpts;i++){
          fprintf(xmgrace,"%16.4f %16.4f\n",mtx[i][0]/kmax,mtx[i][j]-ref);
          }}

for(i=0;i<simpt;i++){
    fprintf(xmgrace,"@target G0.S%d\n",nbands+i);
    fprintf(xmgrace,"@type xy\n");
    fprintf(xmgrace,"%16.4f %16.4f\n",pts[i]/kmax,Emin);
    fprintf(xmgrace,"%16.4f %16.4f\n",pts[i]/kmax,Emax);}



fclose(siesta_bands);
fclose(xmgrace);
}






