#include<stdio.h>
#include<process.h>
#include<string.h>
struct additems
{
	int itemid;
	char itemname[30];
	float itemprice;
}ad;
struct bill
{
	int billid,n;
	char custname[30];
	char itemname[30][30];
	float itemprice[30];
	int quant[30];
	float total;
}bi;
int additem();
int generatebill();
int displaybill();
int deletebill();
FILE *fp1,*fp2,*fp3;
main()
{
	int i,choice,q;
	printf("                \n\n                        WELCOME \n          ");
	printf("\n            SUSHIKA BAKERY BILLING SYSTEM   ");
	
		X:
		printf("\n------------------start-----------------------------");
		printf("\n1.ADD PRODUCT                |");
		printf("\n2.GENERATE BILL              |");
		printf("\n3.DISPLAY BILL               |");
		printf("\n4.DELETE BILL                |");
		printf("\n5.EXIT                       |");
		printf("\n-----------------------------|");
		printf("\n\n\nPress Corresponding Key To Perform====:");
		A:
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				
				q=additem();
				if(q==0)
				{
					printf("\n====THANK===YOU===");
					exit(0);
				}
				else
				{
					goto X;
				}
				break;
			case 2:
				q=generatebill();
				if(q==0)
				{
					printf("\n=====THANK====YOU====");
					exit(0);
				}
				else
				{
					goto X;
				}
				break;
			case 3:
				q=displaybill();
				if(q==0)
				{
					printf("\n=====THANK=====YOU=====");
					exit(0);
				}
				else
				{
					goto X;
				}
				break;
			case 4:
				q=deletebill();
				if(q==0)
				{
					printf("\n=======THANK====YOU=====");
					exit(0);
				}
				else
				{
					goto X;
				}
				break;
			case 5:
				printf("\n========THANK=====YOU=====");
				exit(0);
			default:
				printf("\n==You Enter Wrong Choice====");
				goto A;
		}
	
}
int additem()
{
	int s=1,i=0,id=0,p[30];
	while(s==1)
	{
		fp1=fopen("product.txt","r");
		while((fread(&ad,sizeof(ad),1,fp1))!='\0')
		{
			id=ad.itemid;
		}
		fclose(fp1);
		printf("\nEnter Product Name=");
		scanf("%s",ad.itemname);
		printf("\nEnter Product Price=");
		scanf("%f",&ad.itemprice);
		//fprintf(fp1,"%f",ad.itemprice);
		id++;
		p[i]=id;
		i++;
		ad.itemid=id;
		fp1=fopen("product.txt","a");
		fwrite(&ad,sizeof(ad),1,fp1);
		fclose(fp1);
		printf("\n==Your Product With id=%d is Successfully Added===",ad.itemid);
		printf("\n===Press '1' to add new Product or '0' to exit==");
		scanf("%d",&s);
		if(s!=1)
		{
			break;
		}
	}
	fp1=fopen("product.txt","r");
	i=0;
	while((fread(&ad,sizeof(ad),1,fp1))!='\0')
	{
		if(p[i]==ad.itemid)
		{
			printf("\nProduct id=%d",ad.itemid);
			printf("\nProduct Name=%s",ad.itemname);
			printf("\nProduct Price=%f",ad.itemprice);
			printf("\n-------------------------------------------");
			i++;
		}
	}
	fclose(fp1);
	printf("\nPress '1' to go to MAIN MANU or '0' to exit");
	int q;
	scanf("%d",&q);
	return q;
}
int generatebill()
{
	int s=1,p,q,itemid=0,quant=0,i=0,j=0,n,billid;
	float total=0;
	while(s==1)
	{
		int f=0;
		if(j==0)
		{
			fp2=fopen("generate.txt","r");
			while((fread(&bi,sizeof(bi),1,fp2))!='\0')
			{
				billid=bi.billid;
			}
			billid++;
			bi.billid=billid;
			fclose(fp2);
			j++;
		}
		printf("\n==Enter Product id of Buying====");
		printf("\nProduct ID=");
		scanf("%d",&itemid);
		fp1=fopen("product.txt","r");
		while((fread(&ad,sizeof(ad),1,fp1))!='\0')
		{
			if(itemid==ad.itemid)
			{
				printf("\nProduct Name=%s",ad.itemname);
				strcpy(bi.itemname[i],ad.itemname);
				printf("\nProduct Price=%f",ad.itemprice);
				bi.itemprice[i]=ad.itemprice;
				printf("\n-------------------------------");
				f=1;
			}
		}
		if(f==0)
		{
			printf("\n======Your Product ID not found======");
		}
		else
		{
			printf("\nQuantity of Product=");
			scanf("%d",&quant);
			bi.quant[i]=quant;
			total+=quant*(ad.itemprice);
			f=0;
			bi.n=i;
			n=i;
			i++;
		}
		printf("\n==Press '1' to add more product or '0' to enter customer details===");
		scanf("%d",&s);
	}
	
	printf("n=%d",n);
	printf("\nPut down customer information====");
	printf("\nCustomer Name=");
	scanf("%s",bi.custname);
	printf("\n==Press '1' to generate bill or '0' to go to MAIN MANU==");
	scanf("%d",&p);
	if(p!=1)
	{
		return p;
	}
	else
	{
		int i=0,n;
		fp2=fopen("generate.txt","a");
		fwrite(&bi,sizeof(bi),1,fp2);
		fclose(fp2);
		printf("\n-----------------YOUR BILL---------------------------");
		printf("\nCustomer Name=%s",bi.custname);
		printf("\nBill ID=%d",bi.billid);
		printf("\n----------------------------------");
		total=0;
		for(i=0;i<=n-1;i++)
		{
			printf("\nS.N.=%d",i+1);
			printf("\nitem name=%s",bi.itemname[i]);
			printf("\nitem price=%f",bi.itemprice[i]);
			printf("\nquqntity=%d",bi.quant[i]);
			printf("\nprice=%f",(bi.itemprice[i])*(bi.quant[i]));
			total=total+((bi.itemprice[i])*(bi.quant[i]));
		}
		printf("\n---------------------------------------------------------");
		printf("\nTotal Price of all Product Combined is=%f",total);
		printf("\n---------------------------------------------------------");
		printf("\nPress '1' to go to MAIN MANU or '0' to exit");
	    scanf("%d",&q);
	    return q;
	}
}

int displaybill()
{
	int q,billid,i=0,f=0;
	float total;
	printf("\nEnter Your Bill ID to Display the BILL");
	scanf("%d",&billid);
	fp2=fopen("generate.txt","r");
	while((fread(&bi,sizeof(bi),1,fp2))!='\0')
	{
		if(billid==bi.billid)
		{
			f=1;
			printf("\n\n               SUSHIKA BAKERY                                      ");
			printf("\n        New Baneshwor, Kathmandu Nepal                         ");
			printf("\n          sushikabakery@gmail.com\n\t\t9808080608                ");
			printf("\n\n-----------------YOUR BILL---------------------------");
		    printf("\nCustomer Name=%s",bi.custname);
		    printf("\nBill ID=%d",bi.billid);
		    printf("\n----------------------------------");
		    total=0;
		    for(i=0;i<=bi.n;i++)
		    {
			    printf("\nS.N=%d",i+1);
			    printf("\nitem name=%s",bi.itemname[i]);
			    printf("\nitem price=%f",bi.itemprice[i]);
		    	printf("\nquqntity=%d",bi.quant[i]);
		    	printf("\nprice=%f",(bi.itemprice[i])*(bi.quant[i]));
		    	total=total+((bi.itemprice[i])*(bi.quant[i]));
		    }
			printf("\n-------------------------------------");
			printf("\nTotal Price of all Product Combined is=%f",total);
	    	printf("\n---------------------------------------------------------");
	    	break;
		}
	}
	if(f==0)
	{
		printf("\n===bill---id---does--not---exit==============");
	}
	fclose(fp2);
	printf("\nPress '1' to go to MAIN MANU or '0' to exit");
	scanf("%d",&q);
	return q;
}
int deletebill()
{
	int q,billid,f;
	fp2=fopen("generate.txt","w");
	fclose(fp2);
	printf("\nEnter your bill ID to Delete BILL==");
	scanf("%d",&billid);
	fp2=fopen("generate.txt","r");
	while(fread(&bi,sizeof(bi),1,fp2)!='\0')
	{
		if(billid==bi.billid)
		{
			f=1;
			break;
		}
	}
	fclose(fp2);
	if(f==1)
	{
		fp2=fopen("generate.txt","r");
		fp3=fopen("delete.txt","w");
		while(fread(&bi,sizeof(bi),1,fp3)!='\0')
		{
			if(billid==billid)
			{
				fwrite(&bi,sizeof(bi),1,fp2);
			}
		}
		fclose(fp2);
		fclose(fp3);
		printf("\n----Your---BILL---is----deleated-----");
	}
	else
	{
		printf("\n---bill--id---does---not---exit----");
	}
	printf("\nPress '1' to go to MAIN MANU or '0' to exit");
	scanf("%d",&q);
	return q;
}
