#include<stdio.h>
#include<stdlib.h>
#include<conio2.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include<time.h>

struct TpData
{
	int dia, mes, ano;
};

struct TpClientes 	
{
	char telefoneC[16],nomeC[30],enderecoC[35],cidadeC[35],CEPC[11],Status;
};

struct TpPizzas
{	
	int codigoP,pedP; 
	float valorP;
	char descricaoP[25],StatusP;
	
};

struct TpMotoqueiros
{
	char CPF[15],nomeM[30],enderecoM[35],telefoneM[16],StatusM;
	
	TpData DtaM; 
};

struct TpPedidos
{
	int numeroP,codigoPD,sitP;
	char telefoneP[16],CPFP[15],sitPP[15],StatusPD;
	TpData DtaP;
};

struct TpLetras
{
	char nomeL[30];
};

void LimpaQuadro();

void LimpaQuadroTelefoneP();

void LimpaQuadroPizzasP();

void LimpaQuadroCpfP();

void InsercaoDireta(FILE *PtrCli, char telefoneC[])
{
	
	TpClientes RegI,RegJ;
	
	int i,j;
	
	fseek(PtrCli,0,2);
	
	i = ftell(PtrCli)/sizeof(TpClientes)-1;
	
	while(i>0)
	{
		j=i-1;
		
		fseek(PtrCli,i*sizeof(TpClientes),0);
		fread(&RegI,sizeof(TpClientes),1,PtrCli);
		
		fseek(PtrCli,j*sizeof(TpClientes),0);
		fread(&RegJ,sizeof(TpClientes),1,PtrCli);
		
		if(strcmp(RegJ.telefoneC,RegI.telefoneC)>0)
		{
			fseek(PtrCli,j*sizeof(TpClientes),0);
			fwrite(&RegI,sizeof(TpClientes),1,PtrCli);
			
			fseek(PtrCli,i*sizeof(TpClientes),0);
			fwrite(&RegJ,sizeof(TpClientes),1,PtrCli);
			
		}
		i--;	
	}
}

int PosicaoMaiorP(FILE *PtrPiz,int qtde)
{
	TpPizzas Reg;
	
	int posmaior,maior,i;
	
	fseek(PtrPiz,0,0);
	maior=ftell(PtrPiz)/sizeof(TpPizzas);
	
	posmaior=0;
	
	for(i=0;i<qtde;i++)
	{
		fseek(PtrPiz,i*sizeof(TpPizzas),0);
		fread(&Reg,sizeof(TpPizzas),1,PtrPiz);
		
		if(maior<Reg.codigoP)
		{
			maior=Reg.codigoP;
			posmaior=i;
		}
	}
	
	return posmaior;
}


void SelecaoDiretaP(FILE *PtrPiz)
{
	TpPizzas RegM,Reg;
	
	int posmaior,qtde;
	
	fseek(PtrPiz,0,2);
	qtde=ftell(PtrPiz)/sizeof(TpPizzas)-1;
	
	while(qtde>0)
	{	
		posmaior=PosicaoMaiorP(PtrPiz,qtde);

		fseek(PtrPiz,posmaior*sizeof(TpPizzas),0);
		fread(&RegM,sizeof(TpPizzas),1,PtrPiz);
		
		fseek(PtrPiz,qtde*sizeof(TpPizzas),0);
		fread(&Reg,sizeof(TpPizzas),1,PtrPiz);
		
		if(RegM.codigoP>Reg.codigoP)
		{
					
			fseek(PtrPiz,posmaior*sizeof(TpPizzas),0);
			fwrite(&Reg,sizeof(TpPizzas),1,PtrPiz);
				
			fseek(PtrPiz,qtde*sizeof(TpPizzas),0);
			fwrite(&RegM,sizeof(TpPizzas),1,PtrPiz);
		}
		qtde--;
	}
}


void OrdenaBolhas(void)
{
	FILE *PtrCli = fopen("Clientes.dat","rb+");
	
	TpClientes RegI,RegJ;
	
	int qtde,i,j;
	
	fseek(PtrCli,0,2);
	qtde = ftell(PtrCli)/sizeof(TpClientes);
	
	for(i=0;i<qtde-1;i++)	
	 	for(j=i+1;j<qtde;j++)
		{
			fseek(PtrCli,i*sizeof(TpClientes),0);
			fread(&RegI,sizeof(TpClientes),1,PtrCli);
			
			fseek(PtrCli,j*sizeof(TpClientes),0);
			fread(&RegJ,sizeof(TpClientes),1,PtrCli);
			
			if(strcmp(RegI.telefoneC,RegJ.telefoneC)>0)
			{
				fseek(PtrCli,i*sizeof(TpClientes),0);
				fwrite(&RegJ,sizeof(TpClientes),1,PtrCli);
					
				fseek(PtrCli,j*sizeof(TpClientes),0);
				fwrite(&RegI,sizeof(TpClientes),1,PtrCli);	
			}		
		}
	
	fclose(PtrCli);
	
	printf("\nOrdenacao Concluida [TELEFONE]\n");
	getch();
}

void OrdenaBolhasP(void)
{
	FILE *PtrPiz = fopen("Pizzas.dat","rb+");
	
	TpPizzas RegI,RegJ;
	
	int qtde,i,j;
	
	fseek(PtrPiz,0,2);
	qtde = ftell(PtrPiz)/sizeof(TpPizzas);
	
	for(i=0;i<qtde-1;i++)	
	 	for(j=i+1;j<qtde;j++)
		{
			fseek(PtrPiz,i*sizeof(TpPizzas),0);
			fread(&RegI,sizeof(TpPizzas),1,PtrPiz);
			
			fseek(PtrPiz,j*sizeof(TpPizzas),0);
			fread(&RegJ,sizeof(TpPizzas),1,PtrPiz);
			
			if(RegI.codigoP>RegJ.codigoP)
			{
				fseek(PtrPiz,i*sizeof(TpPizzas),0);
				fwrite(&RegJ,sizeof(TpPizzas),1,PtrPiz);
					
				fseek(PtrPiz,j*sizeof(TpPizzas),0);
				fwrite(&RegI,sizeof(TpPizzas),1,PtrPiz);	
			}		
		}
	
	fclose(PtrPiz);
}


void OrdenaBolhasMpM(void)
{
	FILE *PtrPiz = fopen("Pizzas.dat","rb+");
	
	TpPizzas RegI,RegJ;
	
	int qtde,i,j;
	
	fseek(PtrPiz,0,2);
	qtde = ftell(PtrPiz)/sizeof(TpPizzas);
	
	for(i=0;i<qtde-1;i++)	
	 	for(j=i+1;j<qtde;j++)
		{
			fseek(PtrPiz,i*sizeof(TpPizzas),0);
			fread(&RegI,sizeof(TpPizzas),1,PtrPiz);
			
			fseek(PtrPiz,j*sizeof(TpPizzas),0);
			fread(&RegJ,sizeof(TpPizzas),1,PtrPiz);
			
			if(RegI.pedP<RegJ.pedP)
			{
				fseek(PtrPiz,i*sizeof(TpPizzas),0);
				fwrite(&RegJ,sizeof(TpPizzas),1,PtrPiz);
					
				fseek(PtrPiz,j*sizeof(TpPizzas),0);
				fwrite(&RegI,sizeof(TpPizzas),1,PtrPiz);	
			}		
		}
	
	fclose(PtrPiz);
}

void InsercaoDiretaP(FILE *PtrPiz,int codP)
{
	
	TpPizzas RegI,RegJ;
	
	int i,j;
	
	fseek(PtrPiz,0,2);
	
	i = ftell(PtrPiz)/sizeof(TpPizzas)-1;
	
	while(i>0)
	{
		j=i-1;
		
		fseek(PtrPiz,i*sizeof(TpPizzas),0);
		fread(&RegI,sizeof(TpPizzas),1,PtrPiz);
		
		fseek(PtrPiz,j*sizeof(TpPizzas),0);
		fread(&RegJ,sizeof(TpPizzas),1,PtrPiz);
		
		if(RegJ.codigoP>RegI.codigoP)
		{
			fseek(PtrPiz,j*sizeof(TpPizzas),0);
			fwrite(&RegI,sizeof(TpPizzas),1,PtrPiz);
			
			fseek(PtrPiz,i*sizeof(TpPizzas),0);
			fwrite(&RegJ,sizeof(TpPizzas),1,PtrPiz);
			
		}
		i--;	
	}
}


int BuscaExaustiva(FILE *PtrCli, char telefoneC[])
{

	TpClientes Reg;
	
	fseek(PtrCli,0,0);
	fread(&Reg,sizeof(TpClientes),1,PtrCli);
	
	while(!feof(PtrCli) && strcmp(telefoneC,Reg.telefoneC)!=0)
		fread(&Reg,sizeof(TpClientes),1,PtrCli);
		
	if(strcmp(telefoneC,Reg.telefoneC)==0)
		return ftell(PtrCli)-sizeof(TpClientes);
	else
		return -1;
}
	
	
int BuscaExaustivaP(FILE *PtrPiz, int codP)
{
	TpPizzas Reg;
	
	
	fseek(PtrPiz,0,0);
	fread(&Reg,sizeof(TpPizzas),1,PtrPiz);
	
	while(!feof(PtrPiz) && codP!=Reg.codigoP)
		fread(&Reg,sizeof(TpPizzas),1,PtrPiz);

	if(codP==Reg.codigoP)
		return ftell(PtrPiz)-sizeof(TpPizzas);
	else
		return -1;
}


int BuscaSequencialIndex(FILE *PtrCli, char telefoneC[])
{
	TpClientes Reg;
	
	fseek(PtrCli,0,0);
	fread(&Reg,sizeof(TpClientes),1,PtrCli);
	
	while(!feof(PtrCli) && strcmp(telefoneC,Reg.telefoneC)>0)
		fread(&Reg,sizeof(TpClientes),1,PtrCli);
	
	if(!feof(PtrCli) && strcmp(telefoneC,Reg.telefoneC)==0)
		return ftell(PtrCli)-sizeof(TpClientes);
	else
		return -1;
}


int BuscaBinaria(FILE *PtrCli, char telefoneC[])
{
	TpClientes RegI;
	
	int inicio=0,fim,meio;
	
	fseek(PtrCli,0,2);
	fim = ftell(PtrCli)/sizeof(TpClientes)-1;
	
	meio = fim/2;
	
	fseek(PtrCli,meio*sizeof(TpClientes),0);
	fread(&RegI,sizeof(TpClientes),1,PtrCli);
	
	while(inicio<fim && strcmp(telefoneC,RegI.telefoneC)!=0)
	{
		if(strcmp(RegI.telefoneC,telefoneC)<0)
			inicio=meio+1;
		else
			fim=meio;
			
		meio=(inicio+fim)/2;
		
		fseek(PtrCli,meio*sizeof(TpClientes),0);
		fread(&RegI,sizeof(TpClientes),1,PtrCli);
	}
	
	if(strcmp(telefoneC,RegI.telefoneC)==0)	
		return ftell(PtrCli)-sizeof(TpClientes);
	else
		return -1;
}


int BuscaComSentinela(FILE *PtrCli, char telefoneC[])
{
	
	TpClientes Reg;
	
	int fimR,fimF,i=0;
	
	fseek(PtrCli,0,2);
	fimR = ftell(PtrCli)/sizeof(TpClientes)-1;
	
	fseek(PtrCli,0,2);
	fimF= ftell(PtrCli)/sizeof(TpClientes);
	
	fseek(PtrCli,0,0);	
	fread(&Reg,sizeof(TpClientes),1,PtrCli);

	while(strcmp(telefoneC,Reg.telefoneC)!=0)	
	{
		fread(&Reg,sizeof(TpClientes),1,PtrCli);
		if(fimF==i)
			strcpy(Reg.telefoneC,telefoneC);
		i++;	
	}

	if(fimR==-1)
		fimR=0;
	
	if(i<=fimR)
		return ftell(PtrCli)-sizeof(TpClientes);
	else
		return -1;

}


int BuscaComSentinelaP(FILE *PtrPiz,int codP)
{
	TpPizzas Reg;
	
	int fimR,fimF,i=0;
	
	fseek(PtrPiz,0,2);
	fimR=ftell(PtrPiz)/sizeof(TpPizzas)-1;
	
	fseek(PtrPiz,0,2);
	fimF=ftell(PtrPiz)/sizeof(TpPizzas);
	
	fseek(PtrPiz,0,0);
	fread(&Reg,sizeof(TpPizzas),1,PtrPiz);
	
	while(codP!=Reg.codigoP)
	{
		fread(&Reg,sizeof(TpPizzas),1,PtrPiz);
		if(fimF==i)
			Reg.codigoP=codP;
		i++;
	}
	
	if(fimR==-1)
		fimR=0;
	
	if(i<=fimR)
		return ftell(PtrPiz)-sizeof(TpPizzas);
	else
		return -1;
}

int BuscaBinariaP(FILE *PtrPiz,int codP)
{
	TpPizzas Reg;
	
	int fim,inicio=0,meio;
	
	fseek(PtrPiz,0,2);
	fim=ftell(PtrPiz)/sizeof(TpPizzas)-1;
	
	meio = fim/2;
	
	fseek(PtrPiz,meio*sizeof(TpPizzas),0);
	fread(&Reg,sizeof(TpPizzas),1,PtrPiz);
	
	while(inicio<fim && codP!=Reg.codigoP)
	{
		
		if(codP>Reg.codigoP)
			inicio=meio+1;
		else
			fim=meio;
		meio=(inicio+fim)/2;
		
		fseek(PtrPiz,meio*sizeof(TpPizzas),0);
		fread(&Reg,sizeof(TpPizzas),1,PtrPiz);
	}
	
	fseek(PtrPiz,meio*sizeof(TpPizzas),0);
	fread(&Reg,sizeof(TpPizzas),1,PtrPiz);
	
	if(codP==Reg.codigoP)
		return ftell(PtrPiz)-sizeof(TpPizzas);
	else
		return -1;
}


int ValidaCPF(FILE *PtrMot,char CPF[])
{
	int ValCPF[11],i=0,mult,result,result2,tam,j=0;
	
	tam=strlen(CPF);
	
	while(i<tam)
	{
		if(CPF[i]!='.' && CPF[i]!='-')  // Separa os caracteres em numeros
		{
			
			ValCPF[j]=CPF[i]-48;
			//printf("CPF F = %c\n",CPF[i]);
			//printf("CPF FD = %d\n",CPF[i]);
			//printf("CPF = %c\n",CPF[i]-48);
			//printf("CPF EM VALIDACAO = %d  CPF NORMAL = %c\n",ValCPF[j],CPF[i]);
			j++;
		}
		i++;
	}
	
	
	for(i=0,result=0,result2=0;i<9;i++) // Valida o CPF
	{
	
		result=result+((ValCPF[i])*(10-i));
		
		result2=result2+((ValCPF[i])*(11-i));
	}
	
	//printf("RESULT1 = %d  RESULT 2 = %d\n",result,result2);
	
	result = (result*10) % 11; // Calculo do 1
	
	if(result>9)
		result=0;	
		
	result2 = (result2+(result*2))*10 % 11;   // Calculo do 2
	
	if(result2>9)
		result2=0;
	
	//gotoxy(10,20);
	//printf("RESULT1 = %d  RESULT 2 = %d\n",result,result2);
	
	//gotoxy(10,22);
	//printf("%d %d\n",ValCPF[j-2],ValCPF[j-1]);
	
	if(ValCPF[j-2]==result && ValCPF[j-1]==result2) // Penultimo e ultimo sao iguais?
		return 1;
		
	else
		return 0;
}

int BuscaExaustivaM(FILE *PtrMot,char CPF[])
{
	TpMotoqueiros Reg;
	
	fseek(PtrMot,0,0);
	fread(&Reg,sizeof(TpMotoqueiros),1,PtrMot);
	
	while(!feof(PtrMot) && strcmp(CPF,Reg.CPF)!=0)
		fread(&Reg,sizeof(TpMotoqueiros),1,PtrMot);
	
	if(strcmp(CPF,Reg.CPF)==0)
		return ftell(PtrMot)-sizeof(TpMotoqueiros);
	else
		return -1;
}


int BuscaSequencialIndexPD(FILE *PtrPed, int numeroP)
{
	TpPedidos Reg;
	
	int i=0,qtde;
	
	fseek(PtrPed,0,2);
	
	qtde= ftell(PtrPed)/sizeof(TpPedidos);
	
	fseek(PtrPed,i*sizeof(TpPedidos),0);
	fread(&Reg,sizeof(TpPedidos),1,PtrPed);
	
	while(i<qtde && numeroP>Reg.numeroP)
	{
		i++;
		fseek(PtrPed,i*sizeof(TpPedidos),0);
		fread(&Reg,sizeof(TpPedidos),1,PtrPed);		
	}
	
	if(i<qtde && numeroP==Reg.numeroP)
		return ftell(PtrPed)-sizeof(TpPedidos);
	else
		return -1;
}

void InsercaoDiretaPD(FILE *PtrPed,int numeroP)
{
	TpPedidos RegI,RegJ;
	
	int i,j;
	
	fseek(PtrPed,0,2);
	
	i = ftell(PtrPed)/sizeof(TpPedidos)-1;
	
	while(i>0)
	{
		j=i-1;
		
		fseek(PtrPed,i*sizeof(TpPedidos),0);
		fread(&RegI,sizeof(TpPedidos),1,PtrPed);
		
		fseek(PtrPed,j*sizeof(TpPedidos),0);
		fread(&RegJ,sizeof(TpPedidos),1,PtrPed);
		
		if(RegJ.numeroP>RegI.numeroP)
		{
			fseek(PtrPed,j*sizeof(TpPedidos),0);
			fwrite(&RegI,sizeof(TpPedidos),1,PtrPed);
			
			fseek(PtrPed,i*sizeof(TpPedidos),0);
			fwrite(&RegJ,sizeof(TpPedidos),1,PtrPed);
		}
		i--;	
	}
}


int BuscaExaustivaPpC(FILE *PtrPed,char telefoneC[]) // busca exaustiva Pedidos para Clientes
{
	TpPedidos Reg;

	fseek(PtrPed,0,0);
	fread(&Reg,sizeof(TpPedidos),1,PtrPed);
	
	while(!feof(PtrPed) && strcmp(telefoneC,Reg.telefoneP)!=0)
		fread(&Reg,sizeof(TpPedidos),1,PtrPed);
	
	if(strcmp(telefoneC,Reg.telefoneP)==0)
		return ftell(PtrPed)-sizeof(TpPedidos);
	else
		return -1;
}


int BuscaExaustivaPpP(FILE *PtrPed, int codP) // Busca Exaustiva Pedidos para Pizzas
{
	TpPedidos Reg;

	fseek(PtrPed,0,0);
	fread(&Reg,sizeof(TpPedidos),1,PtrPed);
	
	while(!feof(PtrPed) && codP!=Reg.codigoPD)
		fread(&Reg,sizeof(TpPedidos),1,PtrPed);

	if(codP==Reg.codigoPD)
		return ftell(PtrPed)-sizeof(TpPedidos);
	else
		return -1;
}


int BuscaExaustivaPpM(FILE *PtrPed,char CPF[])
{
	TpPedidos Reg;
	
	fseek(PtrPed,0,0);
	fread(&Reg,sizeof(TpPedidos),1,PtrPed);
	
	while(!feof(PtrPed) && strcmp(CPF,Reg.CPFP)!=0)
		fread(&Reg,sizeof(TpPedidos),1,PtrPed);
	
	if(strcmp(CPF,Reg.CPFP)==0)
		return ftell(PtrPed)-sizeof(TpPedidos);
	else
		return -1;
}


void BuscaLetras(FILE *PtrCli,FILE *PtrLet,char letra)
{
	TpClientes Reg;
	TpLetras Reg2;
	
	fseek(PtrCli,0,0);
	fread(&Reg,sizeof(TpClientes),1,PtrCli);
	
	while(!feof(PtrCli))
	{
		if(tolower(Reg.nomeC[0])==tolower(letra))
		{
			strcpy(Reg2.nomeL,Reg.nomeC);
			fwrite(&Reg2,sizeof(TpLetras),1,PtrLet);
		}	
		fread(&Reg,sizeof(TpClientes),1,PtrCli);
	}
}

//void BuscaMpM(FILE *PtrCli,FILE *PtrPed,)

void CadastroClientes(void)
{
	
	FILE *PtrCli = fopen("Clientes.dat","ab");
	
	TpClientes Reg;
	
	int pos,i;

	if(PtrCli== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else
		{
			fclose(PtrCli);
			
			FILE *PtrCli = fopen("Clientes.dat","rb+");
			
			gotoxy(83,25);
			printf("CADASTRO DE CLIENTES");
			
			gotoxy(72,30); 
			printf("Digite o Telefone: ");
			fflush(stdin);
			gets(Reg.telefoneC);
			
			while(strcmp(Reg.telefoneC,"\0")!=0)
			{	
				pos = BuscaSequencialIndex(PtrCli,Reg.telefoneC);
				
				if(pos==-1)
				{
					gotoxy(72,32); 
					printf("Digite o Nome: ");
					fflush(stdin);
					gets(Reg.nomeC);
					gotoxy(72,34); 
					printf("Digite o Endereco: ");
					fflush(stdin);
					gets(Reg.enderecoC);
					
					gotoxy(72,36); 
					printf("Digite a Cidade: ");
					fflush(stdin);
					gets(Reg.cidadeC);
					gotoxy(72,38); 
					printf("Digite o CEP: ");
					fflush(stdin);
					gets(Reg.CEPC);
					
					Reg.Status='A';
					
					fseek(PtrCli,pos,0);
					fwrite(&Reg,sizeof(TpClientes),1,PtrCli);
					
					InsercaoDireta(PtrCli,Reg.telefoneC);
					
					textcolor(11);
					gotoxy(72,40); 
					printf("Cadastro Concluido!");
					Sleep(1200);
					textcolor(7);
					LimpaQuadro();	
				}
				else
				{
					fseek(PtrCli,pos,0);
					fread(&Reg,sizeof(TpClientes),1,PtrCli);
					
					if(Reg.Status=='I')
					{
						LimpaQuadro();
						textcolor(12);
						gotoxy(72,30); 
						printf("Usuario inativo!");
						textcolor(7);
						gotoxy(72,32); 
						printf("Deseja Reativar? (S|N): ");
						
						if(toupper(getch())=='S')
						{
							LimpaQuadro();
							
							textcolor(12);
							gotoxy(72,30); 
							printf("Digite as novas Informacoes!");
							textcolor(7);
							gotoxy(72,32); 
							printf("Digite o Nome: ");
							fflush(stdin);
							gets(Reg.nomeC);
							
							gotoxy(72,34); 
							printf("Digite o Endereco: ");
							fflush(stdin);
							gets(Reg.enderecoC);
							gotoxy(72,36); 
							printf("Digite a Cidade: ");
							fflush(stdin);
							gets(Reg.cidadeC);
							gotoxy(72,38); 
							printf("Digite o CEP: ");
							fflush(stdin);
							gets(Reg.CEPC);
							
							Reg.Status='A';
							
							fseek(PtrCli,pos,0);
							fwrite(&Reg,sizeof(TpClientes),1,PtrCli);
							
							textcolor(11);
							gotoxy(72,40); 
							printf("Usuario Reativado!");
							
							Sleep(1200);
							textcolor(7);
							LimpaQuadro();
						}
						else
						{
							textcolor(12);
							gotoxy(72,34); 
							printf("Nao Reativado!");
							Sleep(1200);
							textcolor(7);
							LimpaQuadro();
						}
					}
					else
					{
						textcolor(12);
						gotoxy(72,32);
						printf("Usuario ja cadastrado!");
						Sleep(1200);
						textcolor(7);
						LimpaQuadro();
					}
				}
				
				gotoxy(72,30);
				printf("Digite o Telefone: ");
				fflush(stdin);
				gets(Reg.telefoneC);		
			}	
			fclose(PtrCli);
		}
		textcolor(11);
		gotoxy(72,32);
		printf("Saindo...");
		Sleep(1500);
		textcolor(7);
}

void ConsultarClientes(void)
{
	
	FILE *PtrCli = fopen("Clientes.dat","rb");
	
	TpClientes Reg;
	
	int pos,i;
	
	if(PtrCli== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else
		{
			gotoxy(83,25);
			printf("CONSULTAR CLIENTES");
			
			gotoxy(72,30);
			printf("Digite o telefone: ");
			fflush(stdin);
			gets(Reg.telefoneC);
			
			while(strcmp(Reg.telefoneC,"\0")!=0)
			{
				pos = BuscaBinaria(PtrCli,Reg.telefoneC);
				if(pos==-1)
				{
					textcolor(12);
					gotoxy(72,32);
					printf("Numero nao Cadastrado!");
					Sleep(1200);
					textcolor(7);
					LimpaQuadro();
				}
				else
					{
						fseek(PtrCli,pos,0);
						fread(&Reg,sizeof(TpClientes),1,PtrCli);
						
						if(Reg.Status=='A')
						{
							LimpaQuadro();
							gotoxy(72,30);
							printf("Nome: %s",Reg.nomeC);
							gotoxy(72,32);
							printf("Telefone: %s",Reg.telefoneC);
							gotoxy(72,34);
							printf("Endereco: %s",Reg.enderecoC);
							gotoxy(72,36);
							printf("Cidade: %s",Reg.cidadeC);
							gotoxy(72,38);
							printf("CEP: %s",Reg.CEPC);
							
							textcolor(12);
							gotoxy(72,40);				
							printf("----> Enter (SAIR) <----");
							textcolor(7);
							getch();
							LimpaQuadro();			
						}
						else
						{
							textcolor(12);
							gotoxy(72,32);				
							printf("Usuario Inativo!");
							Sleep(1200);
							textcolor(7);
							LimpaQuadro();
						}
					}
				gotoxy(72,30);
				printf("Digite o telefone: ");
				fflush(stdin);
				gets(Reg.telefoneC);	
			}
		
			fclose(PtrCli);
		}
		
	textcolor(11);
	gotoxy(72,32);
	printf("Saindo...");
	Sleep(1500);
	textcolor(7);
}


void AlterarClientes(void)
{
	FILE *PtrCli = fopen("Clientes.dat","rb+");
	
	TpClientes Reg;
	int pos,i;
	
	if(PtrCli== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else
		{
			gotoxy(83,25);
			printf("ALTERACAO DE CLIENTES");
			
			gotoxy(72,30);
			printf("Digite o Telefone: ");
			fflush(stdin);
			gets(Reg.telefoneC);
			
			while(strcmp(Reg.telefoneC,"\0")!=0)
			{
				pos = BuscaComSentinela(PtrCli,Reg.telefoneC);
			
				if(pos==-1)
				{
					textcolor(12);
					gotoxy(72,32);				
					printf("Usuario nao cadastrado!");
					textcolor(7);
					Sleep(1200);
					LimpaQuadro();
				}
				else
					{
						fseek(PtrCli,pos,0);
						fread(&Reg,sizeof(TpClientes),1,PtrCli);
					
						if(Reg.Status=='A')
						{
							LimpaQuadro();
							
							gotoxy(72,30);
							printf("Nome: %s",Reg.nomeC);
							gotoxy(72,32);
							printf("Telefone: %s",Reg.telefoneC);
							gotoxy(72,34);
							printf("Endereco: %s",Reg.enderecoC);
							gotoxy(72,36);
							printf("Cidade: %s",Reg.cidadeC);
							gotoxy(72,38);
							printf("CEP: %s",Reg.CEPC);
							gotoxy(72,41);
							printf("Deseja alterar? (S|N): ");
							
							if(toupper(getch())=='S')
							{
								LimpaQuadro();
								
								gotoxy(72,30);
								printf("Digite o Nome: ");
								fflush(stdin);
								gets(Reg.nomeC);
								
								gotoxy(72,32);
								printf("Digite o Endereco: ");
								fflush(stdin);
								gets(Reg.enderecoC);
								
								gotoxy(72,34);
								printf("Digite a Cidade: ");
								fflush(stdin);
								gets(Reg.cidadeC);
								
								gotoxy(72,36);
								printf("Digite o CEP: ");
								fflush(stdin);
								gets(Reg.CEPC);
								
								fseek(PtrCli,pos,0);
								
								fwrite(&Reg,sizeof(TpClientes),1,PtrCli);
								
								textcolor(11);
								gotoxy(72,38);				
								printf("Alteracao Concluida!");
								textcolor(7);
								Sleep(1200);
								LimpaQuadro();
							}
							else
							{
								textcolor(12);
								gotoxy(72,43);				
								printf("Alteracao cancelada!");
								textcolor(7);
								Sleep(1200);
								LimpaQuadro();
							}
						}
						else
						{
							textcolor(12);
							gotoxy(72,32);				
							printf("Usuario Inativo!");
							textcolor(7);
							Sleep(1200);
							LimpaQuadro();
						}
					}
					
				gotoxy(72,30);
				printf("Digite o Telefone: ");
				fflush(stdin);
				gets(Reg.telefoneC);		
			}
			fclose(PtrCli);	
		}
		
	textcolor(11);
	gotoxy(72,32);
	printf("Saindo...");
	Sleep(1500);
	textcolor(7);
}


void ExclusaoLogicaC(void)
{
	
	FILE *PtrCli = fopen("Clientes.dat","rb+");
	
	FILE *PtrPed = fopen("Pedidos.dat","ab");

	TpClientes Reg;
	
	int pos,pos2,i;
	
	if(PtrCli== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else
		{
			fclose(PtrPed);
			FILE *PtrPed = fopen("Pedidos.dat","rb");
			
			gotoxy(83,25); 		
			printf("EXCLUSAO LOGICA CLIENTE");
			
			gotoxy(72,30);
			printf("Digite o telefone: ");
			fflush(stdin);
			gets(Reg.telefoneC);
			
			while(strcmp(Reg.telefoneC,"\0")!=0)
			{
				pos = BuscaExaustiva(PtrCli,Reg.telefoneC);
				
				if(pos==-1)
				{
					textcolor(12);
					gotoxy(72,32);				
					printf("Usuario nao cadastrado!");
					textcolor(7);
					Sleep(1200);
					LimpaQuadro();					
				}
				else
					{	
						fseek(PtrCli,pos,0);
						fread(&Reg,sizeof(TpClientes),1,PtrCli);
						
						if(Reg.Status=='A')
						{
							LimpaQuadro();
							
							gotoxy(72,30);
							printf("Nome: %s",Reg.nomeC);
							
							gotoxy(72,32);
							printf("Telefone: %s",Reg.telefoneC);
							
							gotoxy(72,34);
							printf("Endereco: %s",Reg.enderecoC);
							
							gotoxy(72,36);
							printf("Cidade: %s",Reg.cidadeC);
							
							gotoxy(72,38);
							printf("CEP: %s",Reg.CEPC);	
							
							gotoxy(72,40);
							printf("Confirmar Exclusao? (S|N): ");
							
							if(toupper(getch())=='S')
							{
								pos2=BuscaExaustivaPpC(PtrPed,Reg.telefoneC);

								if(pos2==-1)
								{
									Reg.Status='I';
									
									fseek(PtrCli,pos,0);
									fwrite(&Reg,sizeof(TpClientes),1,PtrCli);
									
									textcolor(11);
									gotoxy(72,42);				
									printf("Exclusao concluida!");
									textcolor(7);
									Sleep(1200);
									LimpaQuadro();			
								}
								else
								{
									textcolor(12);
									gotoxy(72,42);				
									printf("Usuario cadastrado em Pedidos!");	
									textcolor(7);
									Sleep(1200);
									LimpaQuadro();					
								}					
							}
							else
							{
								textcolor(12);
								gotoxy(72,42);				
								printf("Exclusao cancelada!");	
								textcolor(7);
								Sleep(1200);
								LimpaQuadro();						
							}					
						}		
						else
						{
							textcolor(12);
							gotoxy(72,32);					
							printf("Palavra Inativa!");	
							textcolor(7);
							Sleep(1200);
							LimpaQuadro();											
						}
					}
				
				gotoxy(72,30);
				printf("Digite o telefone: ");
				fflush(stdin);
				gets(Reg.telefoneC);
			}
			fclose(PtrCli);
			fclose(PtrPed);		
		}

	textcolor(11);
	gotoxy(72,32);
	printf("Saindo...");
	Sleep(1500);
	textcolor(7);
}

void ExclusaoFisicaC(void)
{
	FILE *PtrCli = fopen("Clientes.dat","rb");
	
	TpClientes Reg;
	
	int i;
	
	if(PtrCli== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else
		{						
			gotoxy(82,25);
			printf("EXCLUSAO FISICA CLIENTES");
			
			gotoxy(72,30);
			printf("Excluir Arquivos Inativos? (S|N): ");
			
			if(toupper(getch())=='S')
			{
				
				FILE *PtrAux = fopen("ExclusaoAux.dat","wb");
				
				fread(&Reg,sizeof(TpClientes),1,PtrCli);
				
				while(!feof(PtrCli))
				{
					if(Reg.Status=='A')
						fwrite(&Reg,sizeof(TpClientes),1,PtrAux);
					fread(&Reg,sizeof(TpClientes),1,PtrCli);
				}
					
				fclose(PtrCli);
				fclose(PtrAux);
				
				remove("Clientes.dat");
				rename("ExclusaoAux.dat","Clientes.dat");
				
				textcolor(10);
				gotoxy(72,32);				
				printf("Exclusao Concluida!");
				Sleep(1000);
				
				textcolor(11);
				gotoxy(72,34);
				printf("Saindo...");
				Sleep(1200);
				
				textcolor(7);
						
				LimpaQuadro();					
			}
			else
			{
				textcolor(12);
				gotoxy(72,32);				
				printf("Exclusao cancelada!");
				Sleep(1000);
				
				textcolor(11);
				gotoxy(72,34);
				printf("Saindo...");
				Sleep(1200);
				
				textcolor(7);
				
				LimpaQuadro();	
								
				fclose(PtrCli);
			}			
		}


}


void RelatorioClientes(void)
{
	
	
	FILE *PtrCli = fopen("Clientes.dat","rb");
	
	TpClientes Reg;
	
	int i,x=33;
	
	if(PtrCli== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else
		{
			gotoxy(83,25);
			printf("RELATORIO DE CLIENTES");
			
			gotoxy(50,29);
			printf("============================================================================================");
			gotoxy(50,30);
			printf("  Telefone");
			gotoxy(70,30);
			printf("  Nome");
			gotoxy(90,30);
			printf("  Endereco");
			gotoxy(110,30);
			printf("    Cidade");
			gotoxy(130,30);
			printf("  CEP");
			gotoxy(50,31);
			printf("============================================================================================");
			
			fread(&Reg,sizeof(TpClientes),1,PtrCli);
			
			while(!feof(PtrCli))
			{
				if(x==49)
				{
					gotoxy(76,49);
					textcolor(12);
					printf("----> Enter (Continuar) <----");
					getch();
					LimpaQuadroPizzasP();	
					Sleep(600);
					textcolor(7);
					x=33;
				}
				if(Reg.Status=='A' || Reg.Status=='I')
				{
					gotoxy(50,x);
					printf("%s",Reg.telefoneC);
					gotoxy(70,x);
					printf("%s ",Reg.nomeC);
					gotoxy(90,x);
					printf("%s",Reg.enderecoC);
					gotoxy(110,x);
					printf("%s",Reg.cidadeC);
					gotoxy(130,x);
					printf("%s",Reg.CEPC);
					
					x=x+2;
				}
				
				fread(&Reg,sizeof(TpClientes),1,PtrCli);
			}
			fclose(PtrCli);	
		}
	
	textcolor(10);
	gotoxy(80,49);
	printf("----> Enter (Sair) <----");

	getch();
	
	textcolor(11);
	gotoxy(105,49);
	printf("Saindo...");
	Sleep(1500);
	textcolor(7);
}


void CadastroPizzas(void)
{

	FILE *PtrPiz = fopen("Pizzas.dat","ab");
	
	TpPizzas Reg;
	
	int pos,i;
	
	if(PtrPiz== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else
		{
			fclose(PtrPiz);
			
			FILE *PtrPiz = fopen("Pizzas.dat","rb+");
			
			gotoxy(83,25);
			printf("CADASTRO DE PIZZAS");
			
			gotoxy(72,30);
			printf("Digite o Codigo da Pizza: ");
			scanf("%d",&Reg.codigoP);
				
			while(Reg.codigoP>0)
			{	
				pos=BuscaExaustivaP(PtrPiz,Reg.codigoP);
				
				if(pos==-1)
				{
					gotoxy(72,32);
					printf("Digite o tipo de Pizza: ");
					fflush(stdin);
					gets(Reg.descricaoP);
					
					gotoxy(72,34);
					printf("Digite o valor: R$ ");
					scanf("%f",&Reg.valorP);
					
					Reg.StatusP='A';
					Reg.pedP=0;
					fseek(PtrPiz,pos,0);
					fwrite(&Reg,sizeof(TpPizzas),1,PtrPiz);
					
					SelecaoDiretaP(PtrPiz);
					
					//InsercaoDiretaP(PtrPiz,codP);
					textcolor(11);
					gotoxy(72,36);
					printf("Cadastro Concluido!");	
					Sleep(1200);
					textcolor(7);
					LimpaQuadro();
				}
				else
				{
					fseek(PtrPiz,pos,0);
					fread(&Reg,sizeof(TpPizzas),1,PtrPiz);
					
					if(Reg.StatusP=='I')
					{
						textcolor(12);
						gotoxy(72,32);
						printf("Pizza Inativa!");	
						textcolor(7);
						
						gotoxy(72,34);
						printf("Reativar Pizza? (S|N): ");
						
						if(toupper(getch())=='S')
						{
							Reg.StatusP='A';
							
							fseek(PtrPiz,pos,0);
							fwrite(&Reg,sizeof(TpPizzas),1,PtrPiz);
							
							textcolor(11);
							gotoxy(72,36);
							printf("Pizza Reativada!");	
							Sleep(1200);
							textcolor(7);
							LimpaQuadro();
						}
						else
						{
							textcolor(12);
							gotoxy(72,36);
							printf("Reativacao Cancelada!");	
							Sleep(1200);
							textcolor(7);
							LimpaQuadro();			
						}

					}
					else
					{
						textcolor(12);
						gotoxy(72,32);
						printf("Pizza ja Cadastrada!");	
						Sleep(1200);
						textcolor(7);
						LimpaQuadro();	
					}		
				}
				
				gotoxy(72,30);
				printf("Digite o Codigo da Pizza: ");
				scanf("%d",&Reg.codigoP);
			}
			fclose(PtrPiz);	
		}
	textcolor(11);
	gotoxy(72,32);
	printf("Saindo...");
	Sleep(1500);
	textcolor(7);
}


void AlterarPizzas(void)
{
	FILE *PtrPiz = fopen("Pizzas.dat","rb+");
	
	TpPizzas Reg;
	
	int pos,i;
	
	if(PtrPiz== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else
		{
			gotoxy(83,25);
			printf("ALTERACAO DE PIZZAS");
			
			gotoxy(72,30);
			printf("Digite o Codigo da Pizza: ");
			scanf("%d",&Reg.codigoP);
			
			while(Reg.codigoP!=0)
			{
				
				pos = BuscaComSentinelaP(PtrPiz,Reg.codigoP);
				
				if(pos==-1)
				{			
					textcolor(12);
					gotoxy(72,32);
					printf("Pizza nao cadastrada!");
					Sleep(1200);
					textcolor(7);
					LimpaQuadro();		
				}
				else
					{
						fseek(PtrPiz,pos,0);
						fread(&Reg,sizeof(TpPizzas),1,PtrPiz);
						
						if(Reg.StatusP=='A')
						{
							
							LimpaQuadro();
							
							gotoxy(72,30);
							printf("Codigo Pizza: %d",Reg.codigoP);
							
							gotoxy(72,32);
							printf("Tipo: %s",Reg.descricaoP);
							
							gotoxy(72,34);
							printf("Preco da Pizza: R$ %.2f",Reg.valorP);
						
							gotoxy(72,36);
							printf("Deseja alterar? (S|N): ");
							
							if(toupper(getch())=='S')
							{
								LimpaQuadro();
								
								gotoxy(72,30);
								printf("Digite o Tipo da Pizza: ");
								fflush(stdin);
								gets(Reg.descricaoP);
								
								gotoxy(72,32);
								printf("Digite o valor: R$ ");
								scanf("%f",&Reg.valorP);
					
								fseek(PtrPiz,pos,0);
								fwrite(&Reg,sizeof(TpPizzas),1,PtrPiz);
													
								textcolor(11);
								gotoxy(72,34);
								printf("Alteracao Concluida!");	
								Sleep(1200);
								textcolor(7);
								LimpaQuadro();	
					
							}
							else
							{
								textcolor(12);
								gotoxy(72,38);
								printf("Alteracao Cancelada!");	
								Sleep(1200);
								textcolor(7);
								LimpaQuadro();	
							}
						}
						else
						{
							textcolor(12);
							gotoxy(72,32);
							printf("Pizza Inativa!");	
							Sleep(1200);
							textcolor(7);
							LimpaQuadro();	
						}
					}
					
				gotoxy(72,30);
				printf("Digite o Codigo da Pizza: ");
				scanf("%d",&Reg.codigoP);
			}
			fclose(PtrPiz);
		}
		
	textcolor(11);
	gotoxy(72,32);
	printf("Saindo...");
	Sleep(1500);
	textcolor(7);
}


void ConsultarPizzas(void)
{
	
	FILE *PtrPiz = fopen("Pizzas.dat","rb");
	
	TpPizzas Reg;
	
	int pos,i;
	
	if(PtrPiz== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else
		{
			gotoxy(83,25);
			printf("CONSULTAR PIZZAS");
			
			gotoxy(72,30);
			printf("Digite o codigo da Pizza: ");
			scanf("%d",&Reg.codigoP);
			
			while(Reg.codigoP!=0)
			{
				pos = BuscaBinariaP(PtrPiz,Reg.codigoP);
				
				if(pos==-1)
				{
					textcolor(12);
					gotoxy(72,32);				
					printf("Pizza nao Cadastrada!");
					textcolor(7);
					Sleep(1200);
					LimpaQuadro();					
				}
				else
					{
						fseek(PtrPiz,pos,0);
						fread(&Reg,sizeof(TpPizzas),1,PtrPiz);
						
						if(Reg.StatusP=='A')
						{
							LimpaQuadro();
							gotoxy(72,30);
							printf("Codigo Pizza: %d",Reg.codigoP);
							gotoxy(72,32);
							printf("Tipo: %s",Reg.descricaoP);
							gotoxy(72,34);
							printf("Preco da Pizza: R$ %.2f",Reg.valorP);
						
							textcolor(12);
							gotoxy(72,36);				
							printf("----> Enter (SAIR) <----");
							textcolor(7);
							getch();
							LimpaQuadro();			
							
						}
						else
						{
							textcolor(12);
							gotoxy(72,32);				
							printf("Pizza Inativa!");
							textcolor(7);
							Sleep(1200);
							LimpaQuadro();								
						}	
					}	
						
				gotoxy(72,30);
				printf("Digite o codigo da Pizza: ");
				scanf("%d",&Reg.codigoP);
			}	
			fclose(PtrPiz);		
		}
	textcolor(11);
	gotoxy(72,32);
	printf("Saindo...");
	Sleep(1500);
	textcolor(7);
}


void ExclusaoLogicaP(void)
{
	FILE *PtrPiz = fopen("Pizzas.dat","rb+");
	
	FILE *PtrPed = fopen("Pedidos.dat","ab");
	
	TpPizzas Reg;
	
	int pos,pos2,i;
	
	if(PtrPiz== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else
		{
			fclose(PtrPed);
			FILE *PtrPed = fopen("Pedidos.dat","rb");
			
			gotoxy(82,25);
			printf("EXCLUSAO LOGICA PIZZAS");
			
			gotoxy(72,30);
			printf("Digite o codigo da Pizza: ");
			scanf("%d",&Reg.codigoP);
			
			while(Reg.codigoP!=0)
			{
				pos = BuscaBinariaP(PtrPiz,Reg.codigoP);
				
				if(pos==-1)
				{	
					textcolor(12);
					gotoxy(72,32);				
					printf("Pizza nao Cadastrada!");
					textcolor(7);
					Sleep(1200);
					LimpaQuadro();			
				}
				else
					{
						fseek(PtrPiz,pos,0);
						fread(&Reg,sizeof(TpPizzas),1,PtrPiz);

						if(Reg.StatusP=='A')
						{
							gotoxy(72,32);
							printf("Tipo: %s",Reg.descricaoP);
							gotoxy(72,34);
							printf("Preco da Pizza: R$ %.2f",Reg.valorP);
							
							gotoxy(72,36);
							printf("Excluir Pizza? (S|N): ");
							
							if(toupper(getch())=='S')
							{
								pos2 = BuscaExaustivaPpP(PtrPed,Reg.codigoP);
								
								if(pos2==-1)
								{
									Reg.StatusP='I';
									fseek(PtrPiz,pos,0);
									fwrite(&Reg,sizeof(TpPizzas),1,PtrPiz);
									
									textcolor(11);
									gotoxy(72,38);				
									printf("Exclusao Concluida!");
									textcolor(7);
									Sleep(1200);
									LimpaQuadro();					
								}
								else
								{
									textcolor(12);
									gotoxy(72,38);				
									printf("Pizza Cadastrada em Pedidos!");	
									textcolor(7);
									Sleep(1200);
									LimpaQuadro();				
								}			
							}
							else
							{
								textcolor(12);
								gotoxy(72,38);				
								printf("Exclusao Cancelada!");
								textcolor(7);
								Sleep(1200);
								LimpaQuadro();			
							}	
						}
						else
						{
							textcolor(12);
							gotoxy(72,32);				
							printf("Pizza Inativa!");
							textcolor(7);
							Sleep(1200);
							LimpaQuadro();			
						}					
					}
				
				gotoxy(72,30);
				printf("Digite o codigo da Pizza: ");
				scanf("%d",&Reg.codigoP);
			}
			fclose(PtrPiz);
			fclose(PtrPed);
		}
	
	textcolor(11);
	gotoxy(72,32);
	printf("Saindo...");
	Sleep(1500);
	textcolor(7);
}


void ExclusaoFisicaP(void)
{
	FILE *PtrPiz = fopen("Pizzas.dat","rb");
	
	TpPizzas Reg;
	
	int i;
	
	if(PtrPiz== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else
		{	
			gotoxy(82,25);
			printf("EXCLUSAO FISICA PIZZAS");
			
			gotoxy(72,30);
			printf("Excluir Arquivos Inativos? (S|N): ");
			
			if(toupper(getch())=='S')
			{
				FILE *PtrPizza = fopen("ExclusaoP.dat","wb");
				
				fread(&Reg,sizeof(TpPizzas),1,PtrPiz);
				
				while(!feof(PtrPiz))
				{
					if(Reg.StatusP=='A')
						fwrite(&Reg,sizeof(TpPizzas),1,PtrPizza);
					fread(&Reg,sizeof(TpPizzas),1,PtrPiz);
				}
				
				fclose(PtrPiz);
				fclose(PtrPizza);
				
				remove("Pizzas.dat");
				rename("ExclusaoP.dat","Pizzas.dat");
				
				textcolor(10);
				gotoxy(72,32);				
				printf("Exclusao Concluida!");
				Sleep(1000);
				
				textcolor(11);
				gotoxy(72,34);
				printf("Saindo...");
				Sleep(1200);
				
				textcolor(7);	
					
				LimpaQuadro();	
			}
			else
				{
					textcolor(12);
					gotoxy(72,32);				
					printf("Exclusao Cancelada!");
					Sleep(1000);
					
					textcolor(11);
					gotoxy(72,34);
					printf("Saindo...");
					Sleep(1200);
					
					textcolor(7);
							
					LimpaQuadro();	
					
					fclose(PtrPiz);
				}	
		}
		
	OrdenaBolhasP();
}


void RelatorioPizzas(void)
{
	
	FILE *PtrPiz = fopen("Pizzas.dat","rb");
	
	TpPizzas Reg;
	
	int i,x=30;
	
	if(PtrPiz== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else
		{
			gotoxy(83,25);
			printf("RELATORIO PIZZAS");
			
			fread(&Reg,sizeof(TpPizzas),1,PtrPiz);
			
			while(!feof(PtrPiz))
			{
				if(Reg.StatusP=='A')
				{
					if(x>=49)
					{
						gotoxy(76,49);
						textcolor(12);
						printf("----> Enter (Continuar) <----");
						getch();
						LimpaQuadroPizzasP();	
						Sleep(600);
						textcolor(7);
						x=30;
					}
					
					gotoxy(50,x);
					printf("Codigo: %d",Reg.codigoP);
					gotoxy(70,x);
					printf("Tipo: %s",Reg.descricaoP);
					gotoxy(110,x);
					printf("Valor da Pizza: R$ %.2f",Reg.valorP);
					
					x=x+2;
				}
				fread(&Reg,sizeof(TpPizzas),1,PtrPiz);
			}
			
			fclose(PtrPiz);
		}

	textcolor(10);
	gotoxy(80,49);
	printf("----> Enter (Sair) <----");

	getch();
	
	textcolor(11);
	gotoxy(105,49);
	printf("Saindo...");
	Sleep(1500);
	textcolor(7);
}

void CadastroMotoqueiros(void)
{
	
	FILE *PtrMot = fopen("Motoqueiros.dat","ab");
	
	TpMotoqueiros Reg;
	
	int pos,i;
	
	if(PtrMot== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else
		{
			fclose(PtrMot);
			
			FILE *PtrMot = fopen("Motoqueiros.dat","rb+");
			
			gotoxy(83,25);
			printf("CADASTRO DE MOTOQUEIROS");
			
			gotoxy(72,30);
			printf("Digite o CPF: ");
			fflush(stdin);
			gets(Reg.CPF);
			
			while(strcmp(Reg.CPF,"\0")!=0)
			{
				
				pos=ValidaCPF(PtrMot,Reg.CPF);
				
				if(pos==1)
				{
					pos = BuscaExaustivaM(PtrMot,Reg.CPF);
					
					if(pos==-1)
					{
						gotoxy(72,32);
						printf("Digite o Nome:  ");
						fflush(stdin);
						gets(Reg.nomeM);
						
						gotoxy(72,34);
						printf("Digite o telefone: ");
						fflush(stdin);
						gets(Reg.telefoneM);
						
						gotoxy(72,36);
						printf("Digite o endereco: ");
						fflush(stdin);
						gets(Reg.enderecoM);
					
						gotoxy(72,38);
						printf("Digite a Data de Admss [dd mm aaaa]: ");
						
						gotoxy(109,38);
						scanf("%d",&Reg.DtaM.dia);
						gotoxy(112,38);
						scanf("%d",&Reg.DtaM.mes);
						gotoxy(115,38);
						scanf("%d",&Reg.DtaM.ano);
						
						Reg.StatusM='A';
						
						fseek(PtrMot,pos,0);
						fwrite(&Reg,sizeof(TpMotoqueiros),1,PtrMot);
						
						textcolor(11);
						gotoxy(72,40);
						printf("Cadastro concluido!");
						Sleep(1200);
						textcolor(7);
						LimpaQuadro();
					
					}
					else
						{
							fseek(PtrMot,pos,0);
							fread(&Reg,sizeof(TpMotoqueiros),1,PtrMot);
							
							if(Reg.StatusM=='I')
							{
								LimpaQuadro();
								textcolor(12);
								gotoxy(72,30);
								printf("Usuario Inativo!");
								textcolor(7);
								
								gotoxy(72,32);
								printf("Reativar Usuario? (S|N): ");
								
								if(toupper(getch())=='S')
								{
									
									LimpaQuadro();
							
									textcolor(12);
									gotoxy(72,30); 
									printf("Digite as novas Informacoes!");
									textcolor(7);
									
									gotoxy(72,32);
									printf("Digite o Nome:  ");
									fflush(stdin);
									gets(Reg.nomeM);
									
									gotoxy(72,34);
									printf("Digite o telefone: ");
									fflush(stdin);
									gets(Reg.telefoneM);
									
									gotoxy(72,36);
									printf("Digite o endereco: ");
									fflush(stdin);
									gets(Reg.enderecoM);
								
									gotoxy(72,38);
									printf("Digite a Data de Admss [dd mm aaaa]: ");
									
									gotoxy(109,38);
									scanf("%d",&Reg.DtaM.dia);
									gotoxy(112,38);
									scanf("%d",&Reg.DtaM.mes);
									gotoxy(115,38);
									scanf("%d",&Reg.DtaM.ano);
			
									Reg.StatusM = 'A';
									fseek(PtrMot,pos,0);
									fwrite(&Reg,sizeof(TpMotoqueiros),1,PtrMot);
									
									textcolor(11);
									gotoxy(72,40);
									printf("Motoqueiro Reativado!");
									Sleep(1200);
									textcolor(7);
									LimpaQuadro();
									
								}
								else
								{
									textcolor(12);
									gotoxy(72,34);
									printf("Reativacao Cancelada!");	
									Sleep(1200);	
									textcolor(7);
									LimpaQuadro();					
								}
							}
							else
							{
								textcolor(12);
								gotoxy(72,32);
								printf("Motoqueiro ja cadastrado!");
								Sleep(1200);	
								textcolor(7);
								LimpaQuadro();
											
							}
						}
				}
				else
				{		
					textcolor(12);	
					gotoxy(72,32);
					printf("CPF Invalido!");
					Sleep(1200);
					textcolor(7);
					LimpaQuadro();
					
				}
				
				gotoxy(72,30); 
				printf("Digite o CPF: ");
				fflush(stdin);
				gets(Reg.CPF);	
			}				
			fclose(PtrMot);
		}
		textcolor(11);
		gotoxy(72,32);
		printf("Saindo...");
		Sleep(1500);
		textcolor(7);
}

void ConsultarMotoqueiros(void)
{
	FILE *PtrMot = fopen("Motoqueiros.dat","rb");
	
	TpMotoqueiros Reg;
	
	int pos,i;
	
	if(PtrMot== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else
		{
			gotoxy(83,25);
			printf("CONSULTAR MOTOQUEIROS");
			
			gotoxy(72,30);
			printf("Digite o CPF: ");
			fflush(stdin);
			gets(Reg.CPF);
			
			while(strcmp(Reg.CPF,"\0")!=0)
			{
				pos=BuscaExaustivaM(PtrMot,Reg.CPF);
			
				if(pos==-1)
				{
					textcolor(12);
					gotoxy(72,32);
					printf("CPF nao Encontrado!");
					Sleep(1200);
					textcolor(7);
					LimpaQuadro();
				}
				else
					{
						fseek(PtrMot,pos,0);
						fread(&Reg,sizeof(TpMotoqueiros),1,PtrMot);
						
						if(Reg.StatusM=='A')
						{
							LimpaQuadro();
							
							gotoxy(72,30);
							printf("CPF: %s",Reg.CPF);
							gotoxy(72,32);
							printf("Nome: %s",Reg.nomeM);
							gotoxy(72,34);
							printf("Telefone: %s",Reg.telefoneM);
							gotoxy(72,36);
							printf("Endereco: %s",Reg.enderecoM);
							gotoxy(72,38);
							printf("Data de Admss: [%d/%d/%d]",Reg.DtaM.dia,Reg.DtaM.mes,Reg.DtaM.ano);	
							
							textcolor(12);
							gotoxy(72,40);				
							printf("----> Enter (SAIR) <----");
							textcolor(7);
							getch();
							LimpaQuadro();			
						}
						else
						{
							textcolor(12);
							gotoxy(72,32);
							printf("Motoqueiro Inativo!");
							Sleep(1200);
							textcolor(7);
							LimpaQuadro();				
						}				
					}
				
				gotoxy(72,30);
				printf("Digite o CPF: ");
				fflush(stdin);
				gets(Reg.CPF);
			}
			
			fclose(PtrMot);	
		}
	textcolor(11);
	gotoxy(72,32);
	printf("Saindo...");
	Sleep(1500);
	textcolor(7);		
}


void AlterarMotoqueiros(void)
{
	FILE *PtrMot = fopen("Motoqueiros.dat","rb+");
	
	TpMotoqueiros Reg;
	
	int pos,i;
	
	if(PtrMot== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}	
	else
		{
			gotoxy(83,25);
			printf("ALTERACAO DE MOTOQUEIROS");
			
			gotoxy(72,30);
			printf("Digite o CPF: ");
			fflush(stdin);
			gets(Reg.CPF);
			
			while(strcmp(Reg.CPF,"\0")!=0)
			{
				pos = BuscaExaustivaM(PtrMot,Reg.CPF);
				
				if(pos==-1)
				{		
					textcolor(12);
					gotoxy(72,32);				
					printf("Motoqueiro nao cadastrado!");
					textcolor(7);
					Sleep(1200);
					LimpaQuadro();
				}
				else
					{
						fseek(PtrMot,pos,0);
						fread(&Reg,sizeof(TpMotoqueiros),1,PtrMot);
						
						if(Reg.StatusM=='A')
						{
							LimpaQuadro();
							
							gotoxy(72,30);
							printf("CPF: %s",Reg.CPF);
							
							gotoxy(72,32);
							printf("Nome: %s",Reg.nomeM);
							
							gotoxy(72,34);
							printf("Telefone: %s",Reg.telefoneM);
							
							gotoxy(72,36);
							printf("Endereco: %s",Reg.enderecoM);
							
							gotoxy(72,38);
							printf("Data de Admss [%d/%d/%d]",Reg.DtaM.dia,Reg.DtaM.mes,Reg.DtaM.ano);			
							
							gotoxy(72,41);
							printf("Deseja Alterar? (S|N): ");
							
							if(toupper(getch())=='S')
							{
								LimpaQuadro();
								
								gotoxy(72,30);
								printf("Digite o nome: ");
								fflush(stdin);
								gets(Reg.nomeM);
								
								gotoxy(72,32);
								printf("Digite o telefone: ");
								fflush(stdin);
								gets(Reg.telefoneM);
								
								gotoxy(72,34);
								printf("Digite o endereco: ");
								fflush(stdin);
								gets(Reg.enderecoM);
								
								gotoxy(72,36);
								printf("Digite a Data de Admss [dd/mm/aaaa]: ");
								
								gotoxy(109,36);
								scanf("%d",&Reg.DtaM.dia);
								gotoxy(112,36);
								scanf("%d",&Reg.DtaM.mes);
								gotoxy(115,36);
								scanf("%d",&Reg.DtaM.ano);
		
							
								fseek(PtrMot,pos,0);
								fwrite(&Reg,sizeof(TpMotoqueiros),1,PtrMot);
								
								textcolor(11);
								gotoxy(72,38);				
								printf("Alteracao Concluida!");
								textcolor(7);
								Sleep(1200);
								LimpaQuadro();
							}
							else
							{
								textcolor(12);
								gotoxy(72,43);				
								printf("Alteracao Cancelada!");
								textcolor(7);
								Sleep(1200);
								LimpaQuadro();
							}
						}
						else
						{
							textcolor(12);
							gotoxy(72,32);				
							printf("Motoqueiro Inativo!");	
							textcolor(7);
							Sleep(1200);
							LimpaQuadro();
						}
					}
				
				gotoxy(72,30);
				printf("Digite o CPF: ");
				fflush(stdin);
				gets(Reg.CPF);		
			}
			fclose(PtrMot);
		}

	textcolor(11);
	gotoxy(72,32);
	printf("Saindo...");
	Sleep(1500);
	textcolor(7);
}

void ExclusaoLogicaM(void)
{
	FILE *PtrMot = fopen("Motoqueiros.dat","rb+");
	FILE *PtrPed = fopen("Pedidos.dat","ab");

	TpMotoqueiros Reg;
	
	int pos,pos2,i;
	
	if(PtrMot== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}	
	else
		{
			fclose(PtrPed);
			FILE *PtrPed = fopen("Pedidos.dat","rb");
			
			gotoxy(80,25);
			printf("EXCLUSAO LOGICA MOTOQUEIROS");
			
			gotoxy(72,30);
			printf("Digite o CPF: ");
			fflush(stdin);
			gets(Reg.CPF);
			
			while(strcmp(Reg.CPF,"\0")!=0)
			{
				pos = BuscaExaustivaM(PtrMot,Reg.CPF);
				
				if(pos==-1)
				{
					textcolor(12);
					gotoxy(72,32);				
					printf("Motoqueiro nao Cadastrado!");
					textcolor(7);
					Sleep(1200);
					LimpaQuadro();		
				}	
				else
					{
						fseek(PtrMot,pos,0);
						fread(&Reg,sizeof(TpMotoqueiros),1,PtrMot);
						
						if(Reg.StatusM=='A')
						{
							LimpaQuadro();
							
							gotoxy(72,30);
							printf("CPF: %s",Reg.CPF);
							
							gotoxy(72,32);
							printf("Nome: %s",Reg.nomeM);
							
							gotoxy(72,34);
							printf("Telefone: %s",Reg.telefoneM);
							
							gotoxy(72,36);
							printf("Endereco: %s",Reg.enderecoM);
							
							gotoxy(72,38);
							printf("Data de Admss: [%d/%d/%d]",Reg.DtaM.dia,Reg.DtaM.mes,Reg.DtaM.ano);			
							
							gotoxy(72,40);
							printf("Deseja Excluir? (S|N): ");
							
							if(toupper(getch())=='S')
							{
								pos2 = BuscaExaustivaPpM(PtrPed,Reg.CPF);
								
								if(pos2==-1)
								{
								
									Reg.StatusM='I';
									
									fseek(PtrMot,pos,0);		
									fwrite(&Reg,sizeof(TpMotoqueiros),1,PtrMot);
									
									textcolor(11);
									gotoxy(72,42);				
									printf("Exclusao Concluida!");
									textcolor(7);
									Sleep(1200);
									LimpaQuadro();		
								}
								else
								{
									textcolor(12);
									gotoxy(72,42);				
									printf("Motoqueiro Cadastrado em Pedidos!");
									textcolor(7);
									Sleep(1200);
									LimpaQuadro();					
								}		
							}
							else
							{
								textcolor(12);
								gotoxy(72,42);				
								printf("Exclusao cancelada!");
								textcolor(7);
								Sleep(1200);
								LimpaQuadro();				
							}			
						}
						else
						{
							textcolor(12);
							gotoxy(72,32);				
							printf("Motoqueiro Inativo!");
							textcolor(7);
							Sleep(1200);
							LimpaQuadro();		
						}
					}
					
				gotoxy(72,30);
				printf("Digite o CPF: ");
				fflush(stdin);
				gets(Reg.CPF);
			}
			fclose(PtrMot);
			fclose(PtrPed);	
		}	

	textcolor(11);
	gotoxy(72,32);
	printf("Saindo...");
	Sleep(1500);
	textcolor(7);
}


void ExclusaoFisicaM(void)
{
	FILE* PtrMot = fopen("Motoqueiros.dat","rb");
	
	TpMotoqueiros Reg;
	
	int i;
	
	if(PtrMot== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else
		{
			gotoxy(81,25);
			printf("EXCLUSAO FISICA MOTOQUEIROS");
			
			gotoxy(72,30);
			printf("Excluir Arquivos Inativos? (S|N): ");
			
			if(toupper(getch())=='S')
			{
				FILE *PtrMoto = fopen("ExclusaoMotoqueiros","wb");
				
				fread(&Reg,sizeof(TpMotoqueiros),1,PtrMot);
				
				while(!feof(PtrMot))
				{
					if(Reg.StatusM=='A')	
						fwrite(&Reg,sizeof(TpMotoqueiros),1,PtrMoto);	
					
					fread(&Reg,sizeof(TpMotoqueiros),1,PtrMot);	
				}
				
				fclose(PtrMot);
				fclose(PtrMoto);
				
				remove("Motoqueiros.dat");
				rename("ExclusaoMotoqueiros","Motoqueiros.dat");
				
				textcolor(10);
				gotoxy(72,32);				
				printf("Exclusao Concluida!");
				Sleep(1000);
				
				textcolor(11);
				gotoxy(72,34);
				printf("Saindo...");
				Sleep(1200);
				
				textcolor(7);
						
				LimpaQuadro();	
			}
			else
			{	
				textcolor(12);
				gotoxy(72,32);				
				printf("Exclusao Cancelada!");
				Sleep(1000);
				
				textcolor(11);
				gotoxy(72,34);
				printf("Saindo...");
				Sleep(1200);
				
				textcolor(7);	
					
				LimpaQuadro();	
				
				fclose(PtrMot);
			}
		}
}

void RelatorioMotoqueiros(void)
{
	FILE *PtrMot = fopen("Motoqueiros.dat","rb");
	
	TpMotoqueiros Reg;
	
	int i,x=33;
	
	if(PtrMot== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else
		{
			gotoxy(83,25); 
			printf("RELATORIO MOTOQUEIROS");
			
			gotoxy(50,29);
			printf("============================================================================================");
			gotoxy(50,30);
			printf("      CPF");
			gotoxy(70,30);
			printf("  Nome");
			gotoxy(90,30);
			printf("  Telefone");
			gotoxy(110,30);
			printf(" Endereco");
			gotoxy(130,30);
			printf("Data Admss");
			gotoxy(50,31);
			printf("============================================================================================");
			
			fseek(PtrMot,0,0);
			fread(&Reg,sizeof(TpMotoqueiros),1,PtrMot);
			
			while(!feof(PtrMot))
			{
				if(x==49)
				{
					gotoxy(76,49);
					textcolor(12);
					printf("----> Enter (Continuar) <----");
					getch();
					LimpaQuadroPizzasP();	
					Sleep(600);
					textcolor(7);
					x=33;
				}
				
				if(Reg.StatusM=='A')
				{
					gotoxy(50,x);
					printf("%s",Reg.CPF);
					gotoxy(70,x);
					printf("%s",Reg.nomeM);
					gotoxy(90,x);
					printf("%s",Reg.telefoneM);
					gotoxy(110,x);
					printf("%s",Reg.enderecoM);
					gotoxy(130,x);
					printf("[%d/%d/%d]",Reg.DtaM.dia,Reg.DtaM.mes,Reg.DtaM.ano);
					x=x+2;
				
				}
				fread(&Reg,sizeof(TpMotoqueiros),1,PtrMot);
			}

			fclose(PtrMot);		
		}
		
	textcolor(10);
	gotoxy(80,49);
	printf("----> Enter (Sair) <----");

	getch();
	
	textcolor(11);
	gotoxy(105,49);
	printf("Saindo...");
	Sleep(1500);
	textcolor(7);
}


void CadastroPedidos(void)
{
	FILE *PtrPed = fopen("Pedidos.dat","ab");
	
	FILE *PtrCli = fopen("Clientes.dat","ab");
	
	FILE *PtrPiz = fopen("Pizzas.dat","ab");
	
	FILE *PtrMot = fopen("Motoqueiros.dat","ab");
	
	TpPedidos Reg;
	TpClientes Reg2;
	TpPizzas Reg3;
	TpMotoqueiros Reg4;
	
	int pos,pos2,pos3,pos4,i;
	char confirm;
	
	if(PtrPed== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else
		{
			fclose(PtrPed);
			fclose(PtrCli);
			fclose(PtrPiz);
			fclose(PtrMot);
			
			FILE *PtrPed = fopen("Pedidos.dat","rb+");
			FILE *PtrCli = fopen("Clientes.dat","rb");
			FILE *PtrPiz = fopen("Pizzas.dat","rb+");
			FILE *PtrMot = fopen("Motoqueiros.dat","rb");
			
			gotoxy(83,25);
			printf("CADASTRO DE PEDIDOS");
			
			gotoxy(72,30);
			printf("Digite o Codigo do Pedido:  ");
			scanf("%d",&Reg.numeroP);
			
			while(Reg.numeroP>0)
			{
				pos = BuscaSequencialIndexPD(PtrPed,Reg.numeroP);
				
				if(pos==-1)
				{
					confirm='N';
					gotoxy(72,32);
					printf("Digite o Telefone: ");
					fflush(stdin);
					gets(Reg2.telefoneC);
					
					while(strcmp(Reg2.telefoneC,"\0")!=0 && confirm!='S')
					{
						pos2 = BuscaSequencialIndex(PtrCli,Reg2.telefoneC);
						
						if(pos2==-1)
						{	
							textcolor(12);
							gotoxy(72,34);
							printf("Telefone Invalido!");
							Sleep(1200);
							textcolor(7);
							LimpaQuadroTelefoneP();
						}
						else
							{
								fseek(PtrCli,pos2,0);
								fread(&Reg2,sizeof(TpClientes),1,PtrCli);
								
								if(Reg2.Status=='A')
								{
									gotoxy(72,34);
									printf("Digite o Codigo da Pizza: ");
									scanf("%d",&Reg3.codigoP);
									
									while(Reg3.codigoP>0 && confirm!='S')
									{
										pos3=BuscaExaustivaP(PtrPiz,Reg3.codigoP);
										
										if(pos3==-1)
										{
											textcolor(12);
											gotoxy(72,36);
											printf("Codigo Invalido!");
											Sleep(1200);
											textcolor(7);
											LimpaQuadroPizzasP();
										}
										else
											{
												fseek(PtrPiz,pos3,0);
												fread(&Reg3,sizeof(TpPizzas),1,PtrPiz);
												
												if(Reg3.StatusP=='A')
												{
													gotoxy(72,36);
													printf("Digite o CPF do Motoqueiro: ");
													fflush(stdin);
													gets(Reg4.CPF);
													
													while(strcmp(Reg4.CPF,"\0")!=0 && confirm!='S')
													{
														
														pos4=BuscaExaustivaM(PtrMot,Reg4.CPF);
														
														if(pos4==-1)
														{
															textcolor(12);
															gotoxy(72,38);
															printf("CPF Invalido!");
															Sleep(1200);
															textcolor(7);
															LimpaQuadroCpfP();
														}
														else
															{
																fseek(PtrMot,pos4,0);
																fread(&Reg4,sizeof(TpMotoqueiros),1,PtrMot);
																
																if(Reg4.StatusM=='A')
																{
																	gotoxy(72,38);
																	printf("Digite a data do Pedido [dd mm aaaa]:");
																	
																	gotoxy(110,38);
																	scanf("%d",&Reg.DtaP.dia);
																	
																	gotoxy(113,38);
																	scanf("%d",&Reg.DtaP.mes);
																	
																	gotoxy(116,38);
																	scanf("%d",&Reg.DtaP.ano);
																	
																	gotoxy(72,40);
																	printf("Sit.Pedido ( 1- Em Preparo | 2- A caminho | 3- Entregue): ");
																	scanf("%d",&Reg.sitP);
																	
																	if(Reg.sitP==1)
																		strcpy(Reg.sitPP,"Em Preparo.");
																	else
																		if(Reg.sitP==2)
																			strcpy(Reg.sitPP,"A Caminho.");
																		else
																			if(Reg.sitP==3)
																				strcpy(Reg.sitPP,"Entregue.");
																			
																	Reg.StatusPD='A';
													
																	strcpy(Reg.telefoneP,Reg2.telefoneC);
																	Reg.codigoPD=Reg3.codigoP;
																	strcpy(Reg.CPFP,Reg4.CPF);
																	
																	fseek(PtrPed,pos,0);
																	fwrite(&Reg,sizeof(TpPedidos),1,PtrPed);
																	
																	Reg3.pedP=Reg3.pedP+1;
																	
																	fseek(PtrPiz,pos3,0);
																	fwrite(&Reg3,sizeof(TpPizzas),1,PtrPiz);
																	
																	InsercaoDiretaPD(PtrPed,Reg.numeroP);
																	
																	textcolor(11);
																	gotoxy(72,42);
																	printf("Cadastro Concluido!");
																	Sleep(1200);
																	textcolor(7);
																	LimpaQuadro();
																	
																	confirm = 'S';
																}
																else
																{
																	textcolor(12);
																	gotoxy(72,34);
																	printf("CPF Inativo!");
																	Sleep(1200);
																	textcolor(7);
																	LimpaQuadroCpfP();
																	
																}
															}
														if(confirm!='S')
														{
															gotoxy(72,36);
															printf("Digite o CPF do Motoqueiro: ");
															fflush(stdin);
															gets(Reg4.CPF);
														}
													}
												}
												else
												{
													textcolor(12);
													gotoxy(72,34);
													printf("Codigo Inativo!");
													Sleep(1200);
													textcolor(7);
													LimpaQuadroPizzasP();
												}
											}
										if(confirm!='S')
										{
											gotoxy(72,34);
											printf("Digite o Codigo da Pizza: ");
											scanf("%d",&Reg3.codigoP);
										}
									}
								}
								else
								{
									textcolor(12);
									gotoxy(72,34);
									printf("Usuario Inativo!");
									Sleep(1200);
									textcolor(7);
									LimpaQuadroTelefoneP();
									
								}
						}
						if(confirm!='S')
						{
							gotoxy(72,32);
							printf("Digite o Telefone: ");
							fflush(stdin);
							gets(Reg2.telefoneC);
						}
					}		
				}
				else
					{
						fseek(PtrPed,pos,0);
						fread(&Reg,sizeof(TpPedidos),1,PtrPed);
						
						if(Reg.StatusPD=='I')
						{
							textcolor(12);
							gotoxy(72,32);
							printf("Pedido Inativo!");
							textcolor(7);
							gotoxy(72,34);
							printf("Deseja Reativar? (S|N): ");
							
							if(toupper(getch())=='S')
							{
								strcpy(Reg2.telefoneC,Reg.telefoneP);
								Reg3.codigoP=Reg.codigoPD;
								strcpy(Reg4.CPF,Reg.CPFP);
								
								pos2=BuscaSequencialIndex(PtrCli,Reg2.telefoneC);
								pos3=BuscaBinariaP(PtrPiz,Reg3.codigoP);
								pos4=BuscaExaustivaM(PtrMot,Reg4.CPF);
								
								if(pos2!=-1 && pos3!=-1 && pos4!=-1)
								{
									Reg.StatusPD='A';
									
									fseek(PtrPed,pos,0);
									fwrite(&Reg,sizeof(TpPedidos),1,PtrPed);
									
									textcolor(11);
									gotoxy(72,36);
									printf("Pedido Reativado!");
									Sleep(1200);
									textcolor(7);
									LimpaQuadro();
								}
								else
								{
									gotoxy(72,36);
									textcolor(12);
									printf("Nao e Possivel Reativar Esse Pedido (faca uma exclusao fisica)!");									
									Sleep(1500);
									textcolor(7);
									LimpaQuadro();						
								}
							}
							else
							{
								gotoxy(72,36);
								textcolor(12);
								printf("Reativacao Cancelada!");
								Sleep(1200);
								textcolor(7);
								LimpaQuadro();
							}
						}
						else
						{
							gotoxy(72,32);
							textcolor(12);
							printf("Pedido Cadastrado!");
							Sleep(1200);
							textcolor(7);
							LimpaQuadro();
						}
					}
				LimpaQuadro();
				gotoxy(72,30);
				printf("Digite o Codigo do Pedido: ");
				scanf("%d",&Reg.numeroP);
			}
			fclose(PtrPed);
			fclose(PtrCli);
			fclose(PtrPiz);
			fclose(PtrMot);
		}
}

void ConsultarPedidos(void)
{
	FILE *PtrPed = fopen("Pedidos.dat","rb");
	FILE *PtrCli = fopen("Clientes.dat","rb");
	FILE *PtrPiz = fopen("Pizzas.dat","rb");
	FILE *PtrMot = fopen("Motoqueiros.dat","rb");
	
	TpPedidos Reg;
	TpClientes Reg2;
	TpPizzas Reg3;
	TpMotoqueiros Reg4;
	
	int pos,pos2,pos3,pos4,i;
	
	if(PtrPed== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else	
		{
			if(PtrCli== NULL)
			{
				i=0;
				
				while(i<12)
				{
					textcolor(12);
							
					gotoxy(77,25);
					printf("----->   Erro de abertura   <-----");
					Sleep(250);
					i++;
					gotoxy(77,25);
					printf("                                  ");
					Sleep(250);
					
				}
				textcolor(7);
			}
			else
				{
					if(PtrPiz== NULL)
					{
						i=0;
						
						while(i<12)
						{
							textcolor(12);
									
							gotoxy(77,25);
							printf("----->   Erro de abertura   <-----");
							Sleep(250);
							i++;
							gotoxy(77,25);
							printf("                                  ");
							Sleep(250);
							
						}
						textcolor(7);
					}
					else
						{
							if(PtrMot== NULL)
							{
								i=0;
								
								while(i<12)
								{
									textcolor(12);
											
									gotoxy(77,25);
									printf("----->   Erro de abertura   <-----");
									Sleep(250);
									i++;
									gotoxy(77,25);
									printf("                                  ");
									Sleep(250);
									
								}
								textcolor(7);
							}
							else
								{
									gotoxy(83,25);
									printf("CONSULTAR PEDIDOS");
									
									gotoxy(72,30); 
									printf("Digite o numero do Pedido: ");
									scanf("%d",&Reg.codigoPD);							
									
									while(Reg.codigoPD>0)
									{
										pos = BuscaSequencialIndexPD(PtrPed,Reg.codigoPD);
										
										if(pos==-1)
										{
											textcolor(12);
											gotoxy(72,32);
											printf("Pedido nao Encontrado!");
											Sleep(1200);
											textcolor(7);
											LimpaQuadro();
										}
										else
											{
												fseek(PtrPed,pos,0);
												fread(&Reg,sizeof(TpPedidos),1,PtrPed);
												
												if(Reg.StatusPD=='A')
												{
													LimpaQuadro();
													
													strcpy(Reg2.telefoneC,Reg.telefoneP);
													Reg3.codigoP=Reg.codigoPD;
													strcpy(Reg4.CPF,Reg.CPFP);
													
													pos2=BuscaSequencialIndex(PtrCli,Reg2.telefoneC);
													pos3=BuscaBinariaP(PtrPiz,Reg3.codigoP);
													pos4=BuscaExaustivaM(PtrMot,Reg4.CPF);
													
													gotoxy(58,30);
													printf("Numero do Pedido: %d",Reg.numeroP);
													
													fseek(PtrCli,pos2,0);
													fread(&Reg2,sizeof(TpClientes),1,PtrCli);
													
													gotoxy(58,32);
													printf("Nome: %s",Reg2.nomeC);
													
													gotoxy(98,32);
													printf("---->");
													
													gotoxy(105,32);
													printf("Numero do Cliente: %s",Reg.telefoneP);
													
													fseek(PtrPiz,pos3,0);
													fread(&Reg3,sizeof(TpPizzas),1,PtrPiz);
													
													gotoxy(58,34);
													printf("Tipo de Pizza: %s",Reg3.descricaoP);
													
													gotoxy(98,34);	
													printf("---->");
													
													gotoxy(105,34);
													printf("Codigo da Pizza: %d ",Reg.codigoPD);
													
													fseek(PtrMot,pos4,0);
													fread(&Reg4,sizeof(TpMotoqueiros),1,PtrMot);
													
													gotoxy(58,36);
													printf("Nome: %s",Reg4.nomeM);
													
													gotoxy(98,36);
													printf("---->");
													
													gotoxy(105,36);
													printf("CPF Motoqueiro: %s",Reg.CPFP);

													gotoxy(58,38);
													printf("Data do Pedido: [%d/%d/%d]",Reg.DtaP.dia,Reg.DtaP.mes,Reg.DtaP.ano);
													
													gotoxy(58,40);
													printf("Situacao: %s",Reg.sitPP);
													
													textcolor(12);
													gotoxy(80,43);				
													printf("----> Enter (SAIR) <----");
													textcolor(7);
													getch();
													LimpaQuadro();						
												}
												else
												{
													textcolor(12);
													gotoxy(72,32);
													printf("Pedido Inativo!");
													Sleep(1200);
													textcolor(7);
													LimpaQuadro();		
												}
											}
										
										gotoxy(72,30);
										printf("Digite o numero do Pedido: ");
										scanf("%d",&Reg.codigoPD);	
									}
									fclose(PtrMot);
								}
							fclose(PtrPiz);
						}
					fclose(PtrCli);
				}
			fclose(PtrPed);	
		}
	textcolor(11);
	gotoxy(72,32);
	printf("Saindo...");
	Sleep(1500);
	textcolor(7);
}

void AlterarPedidos(void)
{
	FILE *PtrPed = fopen("Pedidos.dat","rb+");
	FILE *PtrCli = fopen("Clientes.dat","rb");
	FILE *PtrPiz = fopen("Pizzas.dat","rb");
	FILE *PtrMot = fopen("Motoqueiros.dat","rb");
	
	TpPedidos Reg;
	TpClientes Reg2;
	TpPizzas Reg3;
	TpMotoqueiros Reg4;
	
	int pos,pos2,pos3,pos4,i;
	
	if(PtrPed== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else	
		{
			if(PtrCli== NULL)
			{
				i=0;
				
				while(i<12)
				{
					textcolor(12);
							
					gotoxy(77,25);
					printf("----->   Erro de abertura   <-----");
					Sleep(250);
					i++;
					gotoxy(77,25);
					printf("                                  ");
					Sleep(250);
					
				}
				textcolor(7);
			}
			else
				{
					if(PtrPiz== NULL)
					{
						i=0;
						
						while(i<12)
						{
							textcolor(12);
									
							gotoxy(77,25);
							printf("----->   Erro de abertura   <-----");
							Sleep(250);
							i++;
							gotoxy(77,25);
							printf("                                  ");
							Sleep(250);
							
						}
						textcolor(7);
					}
					else
						{
							if(PtrMot== NULL)
							{
								i=0;
								
								while(i<12)
								{
									textcolor(12);
											
									gotoxy(77,25);
									printf("----->   Erro de abertura   <-----");
									Sleep(250);
									i++;
									gotoxy(77,25);
									printf("                                  ");
									Sleep(250);
									
								}
								textcolor(7);
							}
							else
								{
									gotoxy(83,25);
									printf("ALTERACAO DE PEDIDOS");
									
									gotoxy(72,30);
									printf("Digite o numero do Pedido: ");
									scanf("%d",&Reg.codigoPD);							
									
									while(Reg.codigoPD>0)
									{
										pos = BuscaSequencialIndexPD(PtrPed,Reg.codigoPD);
										
										if(pos==-1)
										{
											textcolor(12);
											gotoxy(72,34);
											printf("Pedido nao encontrado!");
											Sleep(1200);
											textcolor(7);
											LimpaQuadro();		
										}
										else
											{
												fseek(PtrPed,pos,0);
												fread(&Reg,sizeof(TpPedidos),1,PtrPed);
												
												if(Reg.StatusPD=='A')
												{
													LimpaQuadro();
													
													strcpy(Reg2.telefoneC,Reg.telefoneP);
													Reg3.codigoP=Reg.codigoPD;
													strcpy(Reg4.CPF,Reg.CPFP);
													
													pos2=BuscaSequencialIndex(PtrCli,Reg2.telefoneC);
													pos3=BuscaBinariaP(PtrPiz,Reg3.codigoP);
													pos4=BuscaExaustivaM(PtrMot,Reg4.CPF);
													
													
													gotoxy(58,30);
													printf("Numero do Pedido: %d",Reg.numeroP);
													
													fseek(PtrCli,pos2,0);
													fread(&Reg2,sizeof(TpClientes),1,PtrCli);
													
													gotoxy(58,32);
													printf("Nome: %s",Reg2.nomeC);
													
													gotoxy(98,32);
													printf("---->");
													
													gotoxy(105,32);
													printf("Numero do Cliente: %s",Reg.telefoneP);
													
													fseek(PtrPiz,pos3,0);
													fread(&Reg3,sizeof(TpPizzas),1,PtrPiz);
													
													gotoxy(58,34);
													printf("Tipo de Pizza: %s",Reg3.descricaoP);
													
													gotoxy(98,34);	
													printf("---->");
													
													gotoxy(105,34);
													printf("Codigo da Pizza: %d ",Reg.codigoPD);
													
													fseek(PtrMot,pos4,0);
													fread(&Reg4,sizeof(TpMotoqueiros),1,PtrMot);
													
													gotoxy(58,36);
													printf("Nome: %s",Reg4.nomeM);
													
													gotoxy(98,36);
													printf("---->");
													
													gotoxy(105,36);
													printf("CPF Motoqueiro: %s",Reg.CPFP);

													gotoxy(58,38);
													printf("Data do Pedido: [%d/%d/%d]",Reg.DtaP.dia,Reg.DtaP.mes,Reg.DtaP.ano);
													
													gotoxy(58,40);
													printf("Situacao: %s",Reg.sitPP);
													
													gotoxy(80,42);
													printf("Deseja Alterar o Pedido? (S|N): ");
													
													if(toupper(getch())=='S')
													{
														LimpaQuadro();
														
														gotoxy(65,30);
														printf("Sit.Pedido ( 1- Em Preparo | 2- A caminho | 3 - Entregue): ");
														scanf("%d",&Reg.sitP);
																	
														if(Reg.sitP==1)
															strcpy(Reg.sitPP,"Em Preparo.");
														else
															if(Reg.sitP==2)
																strcpy(Reg.sitPP,"A Caminho.");
															else
																if(Reg.sitP==3)
																	strcpy(Reg.sitPP,"Entregue.");
														
														gotoxy(65,32);
														printf("Digite a Data do Pedido [dd mm aaaa]: ");
														
														gotoxy(103,32);
														scanf("%d",&Reg.DtaP.dia);
														
														gotoxy(106,32);
														scanf("%d",&Reg.DtaP.mes);
														
														gotoxy(109,32);
														scanf("%d",&Reg.DtaP.ano);
														
														fseek(PtrPed,pos,0);
														fwrite(&Reg,sizeof(TpPedidos),1,PtrPed);
														
														textcolor(11);
														gotoxy(80,34);
														printf("Alteracao Concluida!");
														Sleep(1200);
														textcolor(7);
														LimpaQuadro();		
														
													}
													else
													{
														textcolor(12);
														gotoxy(85,44);
														printf("Alteracao Cancelada!");
														Sleep(1200);
														textcolor(7);
														LimpaQuadro();			
													}	
												}
												else
												{	
													textcolor(12);
													gotoxy(72,34);
													printf("Pedido Inativo!");
													Sleep(1200);
													textcolor(7);
													LimpaQuadro();			
												}			
											}
										
										gotoxy(72,30);
										printf("Digite o numero do Pedido: ");
										scanf("%d",&Reg.codigoPD);	
									}
									fclose(PtrMot);
								}
							fclose(PtrPiz);
						}
					fclose(PtrCli);
				}
			fclose(PtrPed);	
		}
		
	textcolor(11);
	gotoxy(72,32);
	printf("Saindo...");
	Sleep(1500);
	textcolor(7);
}


void ExclusaoLogicaPP(void)
{
	FILE *PtrPed = fopen("Pedidos.dat","rb+");
	FILE *PtrCli = fopen("Clientes.dat","rb");
	FILE *PtrPiz = fopen("Pizzas.dat","rb");
	FILE *PtrMot = fopen("Motoqueiros.dat","rb");
	
	TpPedidos Reg;
	TpClientes Reg2;
	TpPizzas Reg3;
	TpMotoqueiros Reg4;
	
	int pos,pos2,pos3,pos4,i;
	
	if(PtrPed== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else	
		{
			if(PtrCli== NULL)
			{
				i=0;
				
				while(i<12)
				{
					textcolor(12);
							
					gotoxy(77,25);
					printf("----->   Erro de abertura   <-----");
					Sleep(250);
					i++;
					gotoxy(77,25);
					printf("                                  ");
					Sleep(250);
					
				}
				textcolor(7);
			}
			else
				{
					if(PtrPiz== NULL)
					{
						i=0;
						
						while(i<12)
						{
							textcolor(12);
									
							gotoxy(77,25);
							printf("----->   Erro de abertura   <-----");
							Sleep(250);
							i++;
							gotoxy(77,25);
							printf("                                  ");
							Sleep(250);
							
						}
						textcolor(7);
					}
					else
						{
							if(PtrMot== NULL)
							{
								i=0;
								
								while(i<12)
								{
									textcolor(12);
											
									gotoxy(77,25);
									printf("----->   Erro de abertura   <-----");
									Sleep(250);
									i++;
									gotoxy(77,25);
									printf("                                  ");
									Sleep(250);
									
								}
								textcolor(7);
							}
							else
								{
									gotoxy(83,25);
									printf("EXCLUSAO LOGICA PEDIDOS");
									
									gotoxy(72,30);
									printf("Digite o numero do Pedido: ");
									scanf("%d",&Reg.codigoPD);							
									
									while(Reg.codigoPD>0)
									{
										pos = BuscaSequencialIndexPD(PtrPed,Reg.codigoPD);
										
										if(pos==-1)
										{
											textcolor(12);
											gotoxy(72,32);				
											printf("Pedido nao encontrado!");
											textcolor(7);
											Sleep(1200);
											LimpaQuadro();					
											
										}
										else
											{
												fseek(PtrPed,pos,0);
												fread(&Reg,sizeof(TpPedidos),1,PtrPed);
												
												if(Reg.StatusPD=='A')
												{
													LimpaQuadro();
													
													strcpy(Reg2.telefoneC,Reg.telefoneP);
													Reg3.codigoP=Reg.codigoPD;
													strcpy(Reg4.CPF,Reg.CPFP);
													
													pos2=BuscaSequencialIndex(PtrCli,Reg2.telefoneC);
													pos3=BuscaBinariaP(PtrPiz,Reg3.codigoP);
													pos4=BuscaExaustivaM(PtrMot,Reg4.CPF);
													
													gotoxy(58,30);
													printf("Numero do Pedido: %d",Reg.numeroP);
													
													fseek(PtrCli,pos2,0);
													fread(&Reg2,sizeof(TpClientes),1,PtrCli);
													
													gotoxy(58,32);
													printf("Nome: %s",Reg2.nomeC);
													
													gotoxy(98,32);
													printf("---->");
													
													gotoxy(105,32);
													printf("Numero do Cliente: %s",Reg.telefoneP);
													
													fseek(PtrPiz,pos3,0);
													fread(&Reg3,sizeof(TpPizzas),1,PtrPiz);
													
													gotoxy(58,34);
													printf("Tipo de Pizza: %s",Reg3.descricaoP);
													
													gotoxy(98,34);	
													printf("---->");
													
													gotoxy(105,34);
													printf("Codigo da Pizza: %d ",Reg.codigoPD);
													
													fseek(PtrMot,pos4,0);
													fread(&Reg4,sizeof(TpMotoqueiros),1,PtrMot);
													
													gotoxy(58,36);
													printf("Nome: %s",Reg4.nomeM);
													
													gotoxy(98,36);
													printf("---->");
													
													gotoxy(105,36);
													printf("CPF Motoqueiro: %s",Reg.CPFP);

													gotoxy(58,38);
													printf("Data do Pedido: [%d/%d/%d]",Reg.DtaP.dia,Reg.DtaP.mes,Reg.DtaP.ano);
													
													gotoxy(58,40);
													printf("Situacao: %s",Reg.sitPP);	
													
													gotoxy(80,42);
													printf("Deseja Excluir o Pedido? (S|N): ");
													
													if(toupper(getch())=='S')
													{
														Reg.StatusPD='I';
														
														fseek(PtrPed,pos,0);
														fwrite(&Reg,sizeof(TpPedidos),1,PtrPed);
														
														textcolor(11);
														gotoxy(85,44);				
														printf("Exclusao Concluida!");
														textcolor(7);
														Sleep(1200);
														LimpaQuadro();					
														
													}
													else
													{
														textcolor(12);
														gotoxy(85,44);				
														printf("Exclusao Cancelada!");
														textcolor(7);
														Sleep(1200);
														LimpaQuadro();					
													}
												}
												else
												{
													textcolor(12);
													gotoxy(72,32);				
													printf("Pedido Inativo!");		
													textcolor(7);
													Sleep(1200);
													LimpaQuadro();						
												}
											}
											
										gotoxy(72,30);
										printf("Digite o numero do Pedido: ");
										scanf("%d",&Reg.codigoPD);	
									}
									fclose(PtrMot);
								}
							fclose(PtrPiz);
						}
					fclose(PtrCli);
				}
			fclose(PtrPed);	
		}

	textcolor(11);
	gotoxy(72,32);
	printf("Saindo...");
	Sleep(1500);
	textcolor(7);
}


void ExclusaoFisicaPP(void)
{
	FILE *PtrPed = fopen("Pedidos.dat","rb");

	TpPedidos Reg;
	
	int i;
	
	if(PtrPed== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else	
		{
			gotoxy(81,25);
			printf("EXCLUSAO FISICA PEDIDOS");
			
			gotoxy(72,30);
			printf("Excluir Arquivos Inativos? (S|N): ");					
			
			if(toupper(getch())=='S')
			{
				FILE *PtrAux = fopen("ExclusaoPedidos.dat","wb");
				
				fread(&Reg,sizeof(TpPedidos),1,PtrPed);
				
				while(!feof(PtrPed))
				{
					if(Reg.StatusPD=='A')
						fwrite(&Reg,sizeof(TpPedidos),1,PtrAux);												
					fread(&Reg,sizeof(TpPedidos),1,PtrPed);
				}	
				fclose(PtrPed);
				fclose(PtrAux);
				remove("Pedidos.dat");
				
				rename("ExclusaoPedidos.dat","Pedidos.dat");
				
				textcolor(10);
				gotoxy(72,32);				
				printf("Exclusao Concluida!");
				Sleep(1000);
				
				textcolor(11);
				gotoxy(72,34);
				printf("Saindo...");
				Sleep(1200);
				
				textcolor(7);
						
				LimpaQuadro();	
			}
			else
				{
					textcolor(12);
					gotoxy(72,32);				
					printf("Exclusao Cancelada!");
					Sleep(1000);
					textcolor(11);
					gotoxy(72,34);
					printf("Saindo...");
					Sleep(1200);
					textcolor(7);		
					LimpaQuadro();
						
					fclose(PtrPed);
				}
			fclose(PtrPed);	
		}
}


void RelatorioPedidos(void)
{
	FILE *PtrPed = fopen("Pedidos.dat","rb");
	FILE *PtrCli = fopen("Clientes.dat","rb");
	FILE *PtrPiz = fopen("Pizzas.dat","rb");
	FILE *PtrMot = fopen("Motoqueiros.dat","rb");
	
	TpPedidos Reg;
	TpClientes Reg2;
	TpPizzas Reg3;
	TpMotoqueiros Reg4;
	
	int pos,pos2,pos3,pos4,i,x=30,j=50;

	if(PtrPed== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else	
		{
			if(PtrCli== NULL)
			{
				i=0;
				
				while(i<12)
				{
					textcolor(12);
							
					gotoxy(77,25);
					printf("----->   Erro de abertura   <-----");
					Sleep(250);
					i++;
					gotoxy(77,25);
					printf("                                  ");
					Sleep(250);
					
				}
				textcolor(7);
			}
			else
				{
					if(PtrPiz== NULL)
					{
						i=0;
						
						while(i<12)
						{
							textcolor(12);
									
							gotoxy(77,25);
							printf("----->   Erro de abertura   <-----");
							Sleep(250);
							i++;
							gotoxy(77,25);
							printf("                                  ");
							Sleep(250);
							
						}
						textcolor(7);
					}
					else
						{
							if(PtrMot== NULL)
							{
								i=0;
								
								while(i<12)
								{
									textcolor(12);
											
									gotoxy(77,25);
									printf("----->   Erro de abertura   <-----");
									Sleep(250);
									i++;
									gotoxy(77,25);
									printf("                                  ");
									Sleep(250);
									
								}
								textcolor(7);
							}
							else
								{
									gotoxy(83,25);
									printf("RELATORIO PEDIDOS");
									
									fread(&Reg,sizeof(TpPedidos),1,PtrPed);
									
									while(!feof(PtrPed))
									{
										if(Reg.StatusPD=='A')
										{
											strcpy(Reg2.telefoneC,Reg.telefoneP);
											Reg3.codigoP=Reg.codigoPD;
											strcpy(Reg4.CPF,Reg.CPFP);
											
											pos2=BuscaSequencialIndex(PtrCli,Reg2.telefoneC);
											pos3=BuscaBinariaP(PtrPiz,Reg3.codigoP);
											pos4=BuscaExaustivaM(PtrMot,Reg4.CPF);
											
											
											gotoxy(j,x);
											printf("Numero Pedido: %d",Reg.numeroP);
											x=x+2;
											
											fseek(PtrCli,pos2,0);
											fread(&Reg2,sizeof(TpClientes),1,PtrCli);
											
											gotoxy(j,x);
											printf("Nome (C): %s > %s",Reg2.nomeC,Reg.telefoneP);
												
											x=x+2;

											fseek(PtrPiz,pos3,0);
											fread(&Reg3,sizeof(TpPizzas),1,PtrPiz);
								
											
											gotoxy(j,x);
											printf("Codigo (P): %d > %s",Reg.codigoPD,Reg3.descricaoP);
											
											x=x+2;
										
											fseek(PtrMot,pos4,0);
											fread(&Reg4,sizeof(TpMotoqueiros),1,PtrMot);
											
											gotoxy(j,x);
											printf("CPF (M): %s > %s",Reg.CPFP,Reg4.nomeM);
											
											x=x+2;
											
											gotoxy(j,x);
											printf("Data (P): [%d/%d/%d]",Reg.DtaP.dia,Reg.DtaP.mes,Reg.DtaP.ano);
											
											x=x+2;						
											
											gotoxy(j,x);
											printf("Situacao (P): %s",Reg.sitPP);

											x=30;
											
											if(j==100)
											{
												
												gotoxy(76,49);
												textcolor(12);
												printf("----> Enter (Continuar) <----");
												getch();
												LimpaQuadro();	
												Sleep(600);
												textcolor(7);
												j=0;
											}
											
											j=j+50;							
										}
										fread(&Reg,sizeof(TpPedidos),1,PtrPed);
									}
									fclose(PtrMot);
								}
							fclose(PtrPiz);
						}
					fclose(PtrCli);
				}
			fclose(PtrPed);	
		}
		
	textcolor(10);
	gotoxy(80,49);
	printf("----> Enter (Sair) <----");

	getch();
	
	textcolor(11);
	gotoxy(105,49);
	printf("Saindo...");
	Sleep(1500);
	textcolor(7);
}

void DataIDataF(void)
{
	
	FILE *PtrPed = fopen("Pedidos.dat","rb");
	FILE *PtrPiz = fopen("Pizzas.dat","ab");
	FILE *PtrMot = fopen("Motoqueiros.dat","ab");
	
	TpPedidos Reg;
	TpPizzas Reg3;
	TpMotoqueiros Reg4;
	
	int diaI,mesI,anoI,diaF,mesF,anoF,pos3,pos4,cont,i,x=30;
	
	char resp;
	
	if(PtrPed== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else
		{
			fclose(PtrPiz);
			fclose(PtrMot);
			
			FILE *PtrPiz = fopen("Pizzas.dat","rb");
			FILE *PtrMot = fopen("Motoqueiros.dat","rb");
			
			gotoxy(83,25);
			printf("Quantidade de Pizzas Entregues");
			
			gotoxy(72,30);
			printf("Digite a Data Inicial [dd mm aaaa]: ");
			scanf("%d %d %d",&diaI,&mesI,&anoI);
			
			if(diaI>0 && mesI>0 && anoI>0)
			{
				gotoxy(72,32);
				printf("Digite a Data Final [dd mm aaaa]: ");
				scanf("%d %d %d",&diaF,&mesF,&anoF);
			
				resp='S';
			}	
			
			while(resp!='N' && diaI>0 && mesI>0 && anoI>0 && diaF>0 && mesF>0 && anoF>0)
			{
				cont=0;
			
				if(anoF<anoI)
				{
					LimpaQuadro();
					gotoxy(72,30);
					printf("Digite o Ano Final novamente [aaaa]: ");
					scanf("%d",&anoF);
				}
				
				if(mesI==mesF)
					if(diaF<diaI)
					{
						LimpaQuadro();
						gotoxy(72,30);
						printf("Digite o Dia Final novamente: ");
						scanf("%d",&diaF);
					}
				
				fseek(PtrPed,0,0);
				fread(&Reg,sizeof(TpPedidos),1,PtrPed);
				
				LimpaQuadro();
				
				while(!feof(PtrPed))
				{
					if(x>=41)
					{
						
						textcolor(12);
						gotoxy(85,49);				
						printf("----> Enter (Continuar) <----");
						textcolor(7);
						Sleep(1200);
						LimpaQuadro();
						x=30;
					}
					if(Reg.DtaP.ano>=anoI && Reg.DtaP.ano<=anoF)
					{	
						if(Reg.DtaP.mes>=mesI && Reg.DtaP.mes<=mesF)
						{
							if(Reg.DtaP.dia>= diaI && Reg.DtaP.dia<=diaF)
							{
								if(Reg.StatusPD=='A')
								{
									if(Reg.sitP==3)
									{
										
										Reg3.codigoP=Reg.codigoPD;
										strcpy(Reg4.CPF,Reg.CPFP);
										
										pos3=BuscaBinariaP(PtrPiz,Reg3.codigoP);
										pos4=BuscaExaustivaM(PtrMot,Reg4.CPF);
										
										fseek(PtrMot,pos4,0);
										fread(&Reg4,sizeof(TpMotoqueiros),1,PtrMot);
										
										gotoxy(68,x);
										printf("CPF: %s   |  Nome: %s",Reg4.CPF,Reg4.nomeM);
											
										x=x+2;
										fseek(PtrPiz,pos3,0);
										fread(&Reg3,sizeof(TpPizzas),1,PtrPiz);
										
										gotoxy(68,x);
										printf("Codigo: %d  | Tipo: %s",Reg3.codigoP,Reg3.descricaoP);
										
										cont=cont+1;
										x=x+2;
										
										textcolor(12);
										gotoxy(80,49);				
										printf("----> Enter (Continuar) <----");
										textcolor(7);
										getch();			
									}
								}
							}
						}
					}	
						
					fread(&Reg,sizeof(TpPedidos),1,PtrPed);
				}
				
				gotoxy(72,43);
				printf("Quantidade de Pedidos: %d",cont);
				
				gotoxy(72,45);
				printf("Continuar (S|N): ");
				
				if(toupper(getch())=='S')
				{
					LimpaQuadro();
					gotoxy(72,30);
					printf("Digite a Data Inicial [dd mm aaaa]: ");
					scanf("%d %d %d",&diaI,&mesI,&anoI);
					gotoxy(72,32);
					printf("Digite a Data Final [dd mm aaaa]: ");
					scanf("%d %d %d",&diaF,&mesF,&anoF);	
					
					resp='S';
				}
				else
					resp='N';
			}
			fclose(PtrPed);
			fclose(PtrPiz);
			fclose(PtrMot);
		}	
		
		textcolor(11);
		gotoxy(72,49);	
		printf("Saindo...");			
		textcolor(7);
		Sleep(1200);
}

void LetraInicial(void)
{
	FILE *PtrCli = fopen("Clientes.dat","rb");
	
	TpLetras Reg;
	
	int num=0,i;
	
	char letra,resp='S';
	
	if(PtrCli== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else
		{
			FILE *PtrLet = fopen("Letras.dat","wb+");
			
			gotoxy(83,25);
			printf("LETRA INICIAL");
			
			gotoxy(72,30);
			printf("Digite a Letra Inicial: ");
			fflush(stdin);
			scanf("%c",&letra);
			
			while(resp!='N')
			{	
				BuscaLetras(PtrCli,PtrLet,letra);
				
				fseek(PtrLet,0,0);
				fread(&Reg,sizeof(TpLetras),1,PtrLet);
				
				while(!feof(PtrLet))
				{
					if(tolower(letra)==tolower(Reg.nomeL[0]))
					{
						gotoxy(72,32);
						printf("Letra Inicial: %c | Nome: %s[%d]",letra,Reg.nomeL,num);
						num=num+1;
					}
					fread(&Reg,sizeof(TpLetras),1,PtrLet);
				}
				
				if(num==0)
				{
					gotoxy(72,32);				
					printf("Nenhum Usuario com essa Letra!");				
				}
				gotoxy(72,36);
				printf("Continuar? (S|N): ");
				
				if(toupper(getch())=='S')
				{
					LimpaQuadro();
					gotoxy(72,30);
					printf("Digite a Letra Inicial: ");
					fflush(stdin);
					scanf("%c",&letra);
					resp='S';
					num=0;
					fclose(PtrLet);
					FILE *PtrLet = fopen("Letras.dat","wb+");
				}
				else
					resp='N';
				
			}
			fclose(PtrCli);
			fclose(PtrLet);
		}
		
	textcolor(11);
	gotoxy(72,38);
	printf("Saindo...");
	Sleep(1500);
	textcolor(7);
}


void PizzasMpM(void)
{
	FILE *PtrPiz = fopen("Pizzas.dat","rb");
	
	TpPizzas Reg;
	
	int i,x=29;
	
	if(PtrPiz== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else
		{
			OrdenaBolhasMpM(); //Mais para Menos
			
			gotoxy(83,25);
			printf("PIZZA MAIS PARA MENOS PEDIDA");
			
			fread(&Reg,sizeof(TpPizzas),1,PtrPiz);
			
			while(!feof(PtrPiz))
			{
				if(Reg.StatusP=='A')
				{
					if(x==49)
					{
						gotoxy(76,49);
						textcolor(12);
						printf("----> Enter (Continuar) <----");
						getch();
						LimpaQuadro();	
						Sleep(600);
						textcolor(7);
						x=29;
					}
						
					gotoxy(70,x);
					printf("Pedidos: %d    |   Tipo de Pizza: %s",Reg.pedP,Reg.descricaoP);
					
					x++;	
				}
				
				fread(&Reg,sizeof(TpPizzas),1,PtrPiz);
			}
			
			fclose(PtrPiz);
		}
	
	OrdenaBolhasP();
	
	textcolor(10);
	gotoxy(80,49);
	printf("----> Enter (Sair) <----");

	getch();
	
	textcolor(11);
	gotoxy(105,49);
	printf("Saindo...");
	Sleep(1500);
	textcolor(7);
}


void TotalGastoC(void)
{

	FILE *PtrCli = fopen("Clientes.dat","rb");
	FILE *PtrPiz = fopen("Pizzas.dat","ab");
	FILE *PtrPed = fopen("Pedidos.dat","ab");

		
	TpClientes Reg;
	TpPizzas Reg2;
	TpPedidos Reg3;
	
	int pos4,i;
	
	float totalG=0;
	
	if(PtrCli== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else
		{
			fclose(PtrPiz);
			fclose(PtrPed);
			FILE *PtrPiz = fopen("Pizzas.dat","rb");
			FILE *PtrPed = fopen("Pedidos.dat","rb");
			
			gotoxy(83,25);
			printf("TOTAL GASTO CLIENTES");
			
			fread(&Reg,sizeof(TpClientes),1,PtrCli);
			
			while(!feof(PtrCli))
			{
				fseek(PtrPed,0,0);
				fread(&Reg3,sizeof(TpPedidos),1,PtrPed);
				
				
				gotoxy(72,30);
				printf("Cliente: %s",Reg.nomeC);

				while(!feof(PtrPed))
				{
					if(strcmp(Reg.telefoneC,Reg3.telefoneP)==0)
						if(Reg3.StatusPD=='A')
						{
							Reg2.codigoP=Reg3.codigoPD;
							
							pos4=BuscaBinariaP(PtrPiz,Reg2.codigoP);
							
							if(pos4!=-1)
							{
								
								fseek(PtrPiz,pos4,0);
								fread(&Reg2,sizeof(TpPizzas),1,PtrPiz);
								
								gotoxy(72,31);
								printf("Tipo da Pizza: %s   |   Valor: %.2f",Reg2.descricaoP,Reg2.valorP);
								
								totalG=totalG+Reg2.valorP;
							}
						}
					fread(&Reg3,sizeof(TpPedidos),1,PtrPed);
				}
				gotoxy(72,34);
				printf("Total Gasto: %.2f",totalG);
				
				textcolor(12);
				gotoxy(80,49);
				printf("----> Enter (Continuar) <----");
				getch();
				textcolor(7);
				LimpaQuadro();
				totalG=0;
				fread(&Reg,sizeof(TpClientes),1,PtrCli);
			}
			
			fclose(PtrCli);
			fclose(PtrPiz);
			fclose(PtrPed);
		}
		
	textcolor(10);
	gotoxy(80,49);
	printf("----> Enter (Sair) <----");

	getch();
	
	textcolor(11);
	gotoxy(105,49);
	printf("Saindo...");
	Sleep(1500);
	textcolor(7);
}

void PizzasPCE(void) // Pizzas Em Preparo, A Caminho, Entregue.
{
	
	FILE *PtrPed = fopen("Pedidos.dat","rb");
	FILE *PtrPiz = fopen("Pizzas.dat","ab");
	
	TpPedidos Reg;
	TpPizzas Reg2;
	
	int resp=0,tit1=0,tit2=0,tit3=0,pos4,i,x=30;
		
	if(PtrPed== NULL)
	{
		i=0;
		
		while(i<12)
		{
			textcolor(12);
					
			gotoxy(77,25);
			printf("----->   Erro de abertura   <-----");
			Sleep(250);
			i++;
			gotoxy(77,25);
			printf("                                  ");
			Sleep(250);
			
		}
		textcolor(7);
	}
	else
		{
			fclose(PtrPiz);
			FILE *PtrPiz = fopen("Pizzas.dat","rb");
			
			gotoxy(83,25);
			printf("PIZZAS SITUACOES");			
					
			while(resp<3)
			{
				fseek(PtrPed,0,0);
				fread(&Reg,sizeof(TpPedidos),1,PtrPed);
				
				while(!feof(PtrPed))	
				{
					if(x>=49)
					{
						textcolor(12);
						gotoxy(80,49);				
						printf("----> Enter (Continuar) <----");
						textcolor(7);
						Sleep(1200);
						LimpaQuadro();
						
						x=30;
					}
					

					if(Reg.StatusPD=='A')
					{	
						if(Reg.sitP==1 && resp==0)
						{
							
							Reg2.codigoP=Reg.codigoPD;
							
							pos4=BuscaBinariaP(PtrPiz,Reg2.codigoP);
							
							fseek(PtrPiz,pos4,0);
							fread(&Reg2,sizeof(TpPizzas),1,PtrPiz);
							
							if(pos4!=-1)
							{
								gotoxy(70,x);
								printf("Codigo: %d   |   Tipo: %s  | %s",Reg.codigoPD,Reg2.descricaoP,Reg.sitPP);	
								x=x+2;
							}
							tit1=tit1+1;
						}
						else
							if(Reg.sitP==2 && resp==1)
							{
							
								Reg2.codigoP=Reg.codigoPD;
								
								pos4=BuscaBinariaP(PtrPiz,Reg2.codigoP);
								
								fseek(PtrPiz,pos4,0);
								fread(&Reg2,sizeof(TpPizzas),1,PtrPiz);
								
								if(pos4!=-1)
								{
									gotoxy(70,x);
									printf("Codigo: %d   |   Tipo: %s | %s",Reg.codigoPD,Reg2.descricaoP,Reg.sitPP);
									x=x+2;
								}
								tit2=tit2+1;
							}
							else
								if(Reg.sitP==3 && resp==2)
								{
									Reg2.codigoP=Reg.codigoPD;
									
									pos4=BuscaBinariaP(PtrPiz,Reg2.codigoP);
									
									fseek(PtrPiz,pos4,0);
									fread(&Reg2,sizeof(TpPizzas),1,PtrPiz);
									
									if(pos4!=-1)
									{
										gotoxy(70,x);
										printf("Codigo: %d   |   Tipo: %s | %s",Reg.codigoPD,Reg2.descricaoP,Reg.sitPP);
										x=x+2;	
									}	
									tit3=tit3+1;
								}
					}		
					fread(&Reg,sizeof(TpPedidos),1,PtrPed);
				}
				resp=resp+1;
			}
			fclose(PtrPiz);
			fclose(PtrPed);
		}
		
	textcolor(10);
	gotoxy(80,49);
	printf("----> Enter (Sair) <----");

	getch();
	
	textcolor(11);
	gotoxy(105,49);
	printf("Saindo...");
	Sleep(1500);
	textcolor(7);
}


char Menu(void)
{
	//Moldura(4,25,35,45,12);
	//Moldura(4,44,15,46,12);
	
	gotoxy(11,45);
	printf("   ");
	
	gotoxy(6,22);
	printf("M E N U   D E   O P C O E S");
	gotoxy(11,27);
	printf("[1] Cadastro(s)");
	gotoxy(11,29);
	printf("[2] Consulta(s)");
	gotoxy(11,31);
	printf("[3] Alteracoe(s)");
	gotoxy(11,33);
	printf("[4] Exclusoe(s) [L]");
	gotoxy(11,35);
	printf("[5] Exclusoe(s) [F]");
	gotoxy(11,37);
	printf("[6] Relatorio(s)");
	gotoxy(11,39);
	printf("[7] Adicionai(s)");
	gotoxy(11,41);
	printf("[ESC] Sair");
	gotoxy(6,45);
	printf("Opcao: ");
	
	return toupper(getche());
}

 
char MenuCad(void)
{
	gotoxy(77,8);
	printf("M E N U   D E   C A D A S T R O S");
	gotoxy(72,11);
	printf("[Q] Cad. Clientes");
	gotoxy(72,13);
	printf("[W] Cad. Motoqueiros");
	gotoxy(72,15);
	printf("[E] Cad. Pizzas");
	gotoxy(72,17);
	printf("[R] Cad. Pedidos");
	gotoxy(70,20);
	printf("[ESC] Sair");
	gotoxy(85,20);
	printf("Opcao: ");
	
	return toupper(getche());
}


char MenuCons(void)
{
	gotoxy(77,8);
	printf("M E N U   D E   C O N S U L T A S");
	gotoxy(72,11);
	printf("[Q] Cons. Clientes");
	gotoxy(72,13);
	printf("[W] Cons. Motoqueiros");
	gotoxy(72,15);
	printf("[E] Cons. Pizzas");
	gotoxy(72,17);
	printf("[R] Cons. Pedidos");
	gotoxy(70,20);
	printf("[ESC] Sair");
	gotoxy(85,20);
	printf("Opcao: ");
	
	return toupper(getche());
}


char MenuAlt(void)
{
	gotoxy(77,8);
	printf("M E N U   D E   A L T E R A C A O");
	gotoxy(72,11);
	printf("[Q] Alt. Clientes");
	gotoxy(72,13);
	printf("[W] Alt. Motoqueiros");
	gotoxy(72,15);
	printf("[E] Alt. Pizzas");
	gotoxy(72,17);
	printf("[R] Alt. Pedidos");
	gotoxy(70,20);
	printf("[ESC] Sair");
	gotoxy(85,20);
	printf("Opcao: ");
	
	return toupper(getche());
}


char MenuExcL(void)
{
	gotoxy(77,8);
	printf("M E N U   D E   E X C L U S A O [L]");
	gotoxy(72,11);
	printf("[Q] Exc. Clientes");
	gotoxy(72,13);
	printf("[W] Exc. Motoqueiros");
	gotoxy(72,15);
	printf("[E] Exc. Pizzas");
	gotoxy(72,17);
	printf("[R] Exc. Pedidos");
	gotoxy(70,20);
	printf("[ESC] Sair");
	gotoxy(85,20);
	printf("Opcao: ");
	
	return toupper(getche());
}


char MenuExcF(void)
{
	gotoxy(77,8);	
	printf("M E N U   D E  E X C L U S A O [F]");
	gotoxy(72,11);
	printf("[Q] Exc. Clientes");
	gotoxy(72,13);
	printf("[W] Exc. Motoqueiros");
	gotoxy(72,15);
	printf("[E] Exc. Pizzas");
	gotoxy(72,17);
	printf("[R] Exc. Pedidos");
	gotoxy(70,20);
	printf("[ESC] Sair");
	gotoxy(85,20);
	printf("Opcao: ");
	
	return toupper(getch());
}

char MenuRel(void)
{
	gotoxy(77,8);
	printf("M E N U   D E   R E L A T O R I O S");
	gotoxy(72,11);
	printf("[Q] Rel. Clientes");
	gotoxy(72,13);
	printf("[W] Rel. Motoqueiros");
	gotoxy(72,15);
	printf("[E] Rel. Pizzas");
	gotoxy(72,17);
	printf("[R] Rel. Pedidos\n\n");
	gotoxy(70,20);
	printf("[ESC] Sair");
	gotoxy(85,20);
	printf("Opcao: ");
	
	return toupper(getche());
}

char MenuOut(void)
{
	gotoxy(77,8);
	printf("M E N U   D E   A D I C I O N A I S");
	gotoxy(72,11);
	printf("[Q] Data I/F");
	gotoxy(72,13);
	printf("[W] Letra Inicial");
	gotoxy(72,15);
	printf("[E] Pizzas M/M");//mais para menos
	gotoxy(72,17);
	printf("[R] Total Gasto C");
	gotoxy(94,11);
	printf("[T] Situacao Pizzas");
	gotoxy(94,13);
	printf("[0] Inserir Dados");
	gotoxy(70,20);
	printf("[ESC] Sair");
	gotoxy(85,20);
	printf("Opcao: ");
	
	return toupper(getche());
}


void InserirDados(void)
{
	gotoxy(83,25);
	printf("INSERIR DADOS AUTOMATICAMENTE");
	
	gotoxy(72,30);
	printf("Ao Inserir dados todos os outros serao apagados!");
	
	gotoxy(72,32);
	printf("Inserir Dados? (S|N): ");
	
	if(toupper(getch())=='S')
	{
		FILE *PtrCli = fopen("Clientes.dat","wb");
		FILE *PtrPiz = fopen("Pizzas.dat","wb");
		FILE *PtrMot = fopen("Motoqueiros.dat","wb");
		FILE *PtrPed = fopen("Pedidos.dat","wb");
		
		TpClientes Reg;
		TpPizzas Reg2;
		TpMotoqueiros Reg3;
		TpPedidos Reg4;
		
		//Clientes
		
		strcpy(Reg.CEPC,"11250-000");
		strcpy(Reg.cidadeC,"Florianopolis");
		strcpy(Reg.enderecoC,"Rua da Aroeira");
		strcpy(Reg.nomeC,"Annie");
		Reg.Status='A';
		strcpy(Reg.telefoneC,"10-15668-1571");
		
		fwrite(&Reg,sizeof(TpClientes),1,PtrCli);
		
				
		strcpy(Reg.CEPC,"19260-000");
		strcpy(Reg.cidadeC,"Londrina");
		strcpy(Reg.enderecoC,"Rua Tanabe");
		strcpy(Reg.nomeC,"Larissa Fonseca");
		Reg.Status='A';
		strcpy(Reg.telefoneC,"18-99608-1140");
		
		fwrite(&Reg,sizeof(TpClientes),1,PtrCli);
		
		strcpy(Reg.CEPC,"19260-000");
		strcpy(Reg.cidadeC,"Lagoas");
		strcpy(Reg.enderecoC,"Rua Shiguero");
		strcpy(Reg.nomeC,"Emily Oliveira");
		Reg.Status='A';
		strcpy(Reg.telefoneC,"18-99608-6158");
		
		fwrite(&Reg,sizeof(TpClientes),1,PtrCli);
		
		
		strcpy(Reg.CEPC,"19260-000");
		strcpy(Reg.cidadeC,"Mirante");
		strcpy(Reg.enderecoC,"Rua Alberto");
		strcpy(Reg.nomeC,"David Fonseca");
		Reg.Status='A';
		strcpy(Reg.telefoneC,"18-99669-1877");
		
		fwrite(&Reg,sizeof(TpClientes),1,PtrCli);
		
		
		strcpy(Reg.CEPC,"18820-000");
		strcpy(Reg.cidadeC,"Sao Paulo");
		strcpy(Reg.enderecoC,"Rua Alberto");
		strcpy(Reg.nomeC,"Wesley");
		Reg.Status='A';
		strcpy(Reg.telefoneC,"19-88669-7717");
		
		fwrite(&Reg,sizeof(TpClientes),1,PtrCli);
		
		//Pizzas
		
		Reg2.codigoP=1;
		strcpy(Reg2.descricaoP,"Pizza de Calabresa");
		Reg2.StatusP='A';
		Reg2.valorP=15.75;
		Reg2.pedP=2;
		fwrite(&Reg2,sizeof(TpPizzas),1,PtrPiz);
		
		Reg2.codigoP=2;
		strcpy(Reg2.descricaoP,"Pizza de Queijo");
		Reg2.StatusP='A';
		Reg2.valorP=16.25;
		Reg2.pedP=1;
		fwrite(&Reg2,sizeof(TpPizzas),1,PtrPiz);
		
		Reg2.codigoP=3;
		strcpy(Reg2.descricaoP,"Pizza de Panetone");
		Reg2.StatusP='A';
		Reg2.valorP=11.21;
		Reg2.pedP=2;
		fwrite(&Reg2,sizeof(TpPizzas),1,PtrPiz);
		
		Reg2.codigoP=4;
		strcpy(Reg2.descricaoP,"Pizza de Estanho");
		Reg2.StatusP='A';
		Reg2.valorP=52.25;
		Reg2.pedP=0;
		fwrite(&Reg2,sizeof(TpPizzas),1,PtrPiz);
		
		Reg2.codigoP=5;
		strcpy(Reg2.descricaoP,"Pizza de CatuFrango");
		Reg2.StatusP='A';
		Reg2.valorP=35.15;
		Reg2.pedP=1;
		fwrite(&Reg2,sizeof(TpPizzas),1,PtrPiz);
		
		//Motoqueiros
		
		strcpy(Reg3.CPF,"490.755.378-70");
		Reg3.DtaM.dia=15; Reg3.DtaM.mes=11; Reg3.DtaM.ano=2002;
		strcpy(Reg3.enderecoM,"Rua Hoshida");
		strcpy(Reg3.nomeM,"Fantasma");
		Reg3.StatusM='A';
		strcpy(Reg3.telefoneM,"16-55956-1577");
		
		fwrite(&Reg3,sizeof(TpMotoqueiros),1,PtrMot);
		
		
		strcpy(Reg3.CPF,"952.783.752-99");
		Reg3.DtaM.dia=11; Reg3.DtaM.mes=12; Reg3.DtaM.ano=2019;
		strcpy(Reg3.enderecoM,"Rua Sekiro");
		strcpy(Reg3.nomeM,"Denis");
		Reg3.StatusM='A';
		strcpy(Reg3.telefoneM,"15-56448-1594");
		
		fwrite(&Reg3,sizeof(TpMotoqueiros),1,PtrMot);
		
		strcpy(Reg3.CPF,"502.840.912-94");
		Reg3.DtaM.dia=8; Reg3.DtaM.mes=05; Reg3.DtaM.ano=2022;
		strcpy(Reg3.enderecoM,"Rua Maromba");
		strcpy(Reg3.nomeM,"Leo Stronda");
		Reg3.StatusM='A';
		strcpy(Reg3.telefoneM,"12-15589-6568");
		
		fwrite(&Reg3,sizeof(TpMotoqueiros),1,PtrMot);
		
		
		strcpy(Reg3.CPF,"525.437.322-92");
		Reg3.DtaM.dia=13; Reg3.DtaM.mes=01; Reg3.DtaM.ano=2021;
		strcpy(Reg3.enderecoM,"Rua AlgoRythmics");
		strcpy(Reg3.nomeM,"Leandro");
		Reg3.StatusM='A';
		strcpy(Reg3.telefoneM,"18-25618-8428");
		
		fwrite(&Reg3,sizeof(TpMotoqueiros),1,PtrMot);
		
		
		strcpy(Reg3.CPF,"232.656.432-47");
		Reg3.DtaM.dia=12; Reg3.DtaM.mes=9; Reg3.DtaM.ano=2020;
		strcpy(Reg3.enderecoM,"Rua Takemu");
		strcpy(Reg3.nomeM,"Takashi");
		Reg3.StatusM='A';
		strcpy(Reg3.telefoneM,"15-66158-1489");
		
		fwrite(&Reg3,sizeof(TpMotoqueiros),1,PtrMot);
		
		
		//Pedidos
		
		Reg4.codigoPD=1;
		strcpy(Reg4.CPFP,"499.755.381-70");
		Reg4.DtaP.dia=15; Reg4.DtaP.mes=05; Reg4.DtaP.ano=2019;
		Reg4.numeroP=2;
		Reg4.sitP=3;
		strcpy(Reg4.sitPP,"Entregue.");
		Reg4.StatusPD='A';
		strcpy(Reg4.telefoneP,"18-99669-1877");
		
		fwrite(&Reg4,sizeof(TpPedidos),1,PtrPed);
		
		Reg4.codigoPD=3;
		strcpy(Reg4.CPFP,"952.783.752-99");
		Reg4.DtaP.dia=10; Reg4.DtaP.mes=9; Reg4.DtaP.ano=2022;
		Reg4.numeroP=3;
		Reg4.sitP=1;
		strcpy(Reg4.sitPP,"Em Preparo.");
		Reg4.StatusPD='A';
		strcpy(Reg4.telefoneP,"19-88669-7717");
		
		fwrite(&Reg4,sizeof(TpPedidos),1,PtrPed);
		
		Reg4.codigoPD=4;
		strcpy(Reg4.CPFP,"502.840.912-94");
		Reg4.DtaP.dia=11; Reg4.DtaP.mes=06; Reg4.DtaP.ano=2023;
		Reg4.numeroP=5;
		Reg4.sitP=2;
		strcpy(Reg4.sitPP,"A Caminho.");
		Reg4.StatusPD='A';
		strcpy(Reg4.telefoneP,"10-15668-1571");
		
		fwrite(&Reg4,sizeof(TpPedidos),1,PtrPed);
		
		Reg4.codigoPD=5;
		strcpy(Reg4.CPFP,"525.437.322-92");
		Reg4.DtaP.dia=15; Reg4.DtaP.mes=8; Reg4.DtaP.ano=2024;
		Reg4.numeroP=10;
		Reg4.sitP=3;
		strcpy(Reg4.sitPP,"Entregue.");
		Reg4.StatusPD='A';
		strcpy(Reg4.telefoneP,"18-99608-6158");
		
		fwrite(&Reg4,sizeof(TpPedidos),1,PtrPed);		
		
		Reg4.codigoPD=3;
		strcpy(Reg4.CPFP,"232.656.432-47");
		Reg4.DtaP.dia=13; Reg4.DtaP.mes=02; Reg4.DtaP.ano=2020;
		Reg4.numeroP=15;
		Reg4.sitP=2;
		strcpy(Reg4.sitPP,"A Caminho.");
		Reg4.StatusPD='A';
		strcpy(Reg4.telefoneP,"18-99608-1140");
		
		fwrite(&Reg4,sizeof(TpPedidos),1,PtrPed);
		
		
		
		//FIM
		fclose(PtrCli);
		fclose(PtrPiz);
		fclose(PtrMot);
		fclose(PtrPed);
		
		textcolor(12);
		gotoxy(72,34);				
		printf("Dados Inseridos!");
		textcolor(7);
		Sleep(1200);
		LimpaQuadro();
	}
	else
	{
		textcolor(12);
		gotoxy(72,34);				
		printf("Dados nao inseridos!");
		textcolor(7);
		Sleep(1200);
		LimpaQuadro();
	}
}

void LimpaMenuParcial(void)
{
	
	
	int i=69,j=8;
	
	
	// limpa titulo do menu parcial
	
	while(i<115)
	{
		gotoxy(i,j);
		printf(" ");
		i++;
	}
	
	
	// limpa quadro de opcoes do menu parcial
	
	i=69,j=11;
	
	while(i<115)
	{
		gotoxy(i,j);
		printf(" ");
		i++;
		
		if(i==115 && j<17)
			i=69,j++;
	}
	
	
	// limpa esc e opcao do menu parcial
	
	i=69,j=20;
	
	while(i<96)
	{
		gotoxy(i,j);
		printf(" ");
		i++;
		
		if(i==81)
			i=i+3;
	}
	
	// limpa titulo dentro do quadro
	
	i=70,j=25;
	
	while(i<119)
	{
		gotoxy(i,j);
		printf(" ");
		i++;
	}
	
	// limpa quadro
	
	i=39,j=27;
	
	while(i<145)
	{
		gotoxy(i,j);
		printf(" ");
		i++;
		
		if(i==145 && j<49)
			i=39,j++;
		
	}
	
//	Moldura(68,26,119,26,2);

//Moldura(38,22,145,50,8);
//	Moldura(68,7,115,9,12);
//	Moldura(68,10,115,18,7);
	
}


void LimpaQuadro(void)
{
	int i=39,j=27;
	
	while(i<145)
	{
		gotoxy(i,j);
		printf(" ");
		i++;
		
		if(i==145 && j<49)
			i=39,j++;
		
	}
}


void LimpaQuadroTelefoneP(void)
{
	int i=39,j=32;
	
	while(i<145)
	{
		gotoxy(i,j);
		printf(" ");
		i++;
		
		if(i==145 && j<49)
			i=39,j++;
		
	}
}

void LimpaQuadroPizzasP(void)
{
	int i=39,j=34;
	
	while(i<145)
	{
		gotoxy(i,j);
		printf(" ");
		i++;
		
		if(i==145 && j<49)
			i=39,j++;
		
	}
}

void LimpaQuadroCpfP(void)
{
	int i=39,j=36;
	
	while(i<145)
	{
		gotoxy(i,j);
		printf(" ");
		i++;
		
		if(i==145 && j<49)
			i=39,j++;
		
	}
}



void Moldura(int CI, int LI, int CF, int LF, int COR)
{
	int i; 
	
	textcolor(COR);
	
	gotoxy(CI,LI);
	printf("%c",201);
	gotoxy(CF,LI);
	printf("%c",187);
	gotoxy(CI,LF);
	printf("%c",200);
	gotoxy(CF,LF);
	printf("%c",188);
	
	for(i=CI+1;i<CF;i++)
	{
		gotoxy(i,LI);
		printf("%c",205);
		//Sleep(50);
		gotoxy(i,LF);
		printf("%c",205);
	}
	
	for(i=LI+1;i<LF;i++)
	{
		gotoxy(CI,i);
		printf("%c",186);
		//Sleep(50);
		gotoxy(CF,i);
		printf("%c",186);
	}
	textcolor(7);
}


void MoldPrincipal(void)
{
	clrscr();
	
	//CI LI CF LF COR
	
	Moldura(2,1,156,60,11);
	
	gotoxy(7,5);
	printf("P I Z Z A R I A");
	gotoxy(12,8);
	printf("N E W");
	gotoxy(8,11);
	printf("P R O J E C T");
	Moldura(4,2,25,14,12);
	
	
	gotoxy(77,4);
	printf("M E N U   D E   O P C O E S");
	Moldura(28,2,154,6,7);

	// MENU OPCOES gerais
	
	Moldura(10,23,11,25,7);//moldura de ligacao
	Moldura(26,23,27,25,7);//moldura de ligacao
	
	Moldura(4,21,35,23,10);//titulo menu
	
	Moldura(4,25,35,43,12);//caixa total menu

	Moldura(4,44,15,46,12);//opcao
	
	
	//Moldura menu opcoes diversas
	
	Moldura(68,7,115,9,12);
	Moldura(68,10,115,18,7);
	
	//OPCAO
	
	Moldura(68,19,81,21,7);	
		
	//ESC
	
	Moldura(83,19,96,21,7);
	
	//Apresentar Quadro
	
	Moldura(38,22,145,50,8);
	
	//Titulos
	
	Moldura(68,26,119,26,2);
}




void Executar(void)
{
	char op;
	
	int i=0,j=1;
	
	MoldPrincipal();
	
//	while(i<15)
//	{
//		textcolor(j);
//		
//		gotoxy(70,25);
//		printf("      SEJA BEM VINDO A PIZZARIA NEW PROJECT  ");
//		
//		Sleep(400);
//		
//		gotoxy(69,25);
//		printf("                                              "); 
//		
//		Sleep(250);
//		
//		i++;
//		j++;
//		
//		if(j==12)
//			j=1;
//	}
//	
//	textcolor(7);
	
	do{
		
		switch(op)
		{
				
			case'1':
					op=MenuCad();
					switch(op)
					{
						case'Q':
								CadastroClientes();
								break;
						case'W':
								CadastroMotoqueiros();
								break;
						case'E':
								CadastroPizzas();
								break;
						case'R':
								CadastroPedidos();
								break;
						
						//OrdenaBolhas();
					}
					break;
			
			case'2':
					op=MenuCons();
					switch(op)
					{
						case'Q':
								ConsultarClientes();
								break;
						case'W':
								ConsultarMotoqueiros();
								break;
						case'E':
								ConsultarPizzas();
								break;
						case'R':
								ConsultarPedidos();
								break;		
					}
					break;
			
			case'3':
					op=MenuAlt();
					switch(op)
					{
						case'Q':
								AlterarClientes();
								break;
						case'W':
								AlterarMotoqueiros();
								break;
						case'E':
								AlterarPizzas();
								break;
						case'R':
								AlterarPedidos();
								break;
					}
					break;
					
			case'4':
					op=MenuExcL();
					switch(op)
					{
						case'Q':
								ExclusaoLogicaC();
								break;
						case'W':
								ExclusaoLogicaM();
								break;
						case'E':
								ExclusaoLogicaP();
								break;
						case'R':
								ExclusaoLogicaPP();
								break;
					}
					break;
			
			case'5':
					op=MenuExcF();
					switch(op)
					{
						case'Q':
								ExclusaoFisicaC();
								break;
						case'W':
								ExclusaoFisicaM();
								break;
						case'E':
								ExclusaoFisicaP();
								break;
						case'R':
								ExclusaoFisicaPP();
								break;
					}
					break;
					
			case'6':
					op=MenuRel();
					switch(op)
					{
						case'Q':
								RelatorioClientes();
								break;
						case'W':
								RelatorioMotoqueiros();
								break;
						case'E':
								RelatorioPizzas();
								break;
						case'R':
								RelatorioPedidos();
								break;
					}
					break;		
			
			case'7':
					op=MenuOut();
					switch(op)
					{
						case'Q':
								DataIDataF();
								break;
						case'W':
								LetraInicial();
								break;		
						case'E':
								PizzasMpM();
								break;
						case'R':
								TotalGastoC();
								break;
						case'T':
								PizzasPCE();
								break;			
						case'0':
								InserirDados();
								break;		
					}	
					break;
			
		}
		LimpaMenuParcial();
		op=Menu();
	}while(op!=27);
}

int main(void)
{
	Executar();
	
	return 0;
}
		
